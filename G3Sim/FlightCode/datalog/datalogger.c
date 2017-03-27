/*! \file datalogger.c
 *	\brief Data logging source code
 *
 *	\details Logs data in MATLAB format onboard the MPC5200B in RAM memory.
 *	\ingroup datalog_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: datalogger.c 869 2012-08-06 22:40:38Z joh07594 $
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <cyg/posix/pthread.h>
#include <cyg/kernel/kapi.h>
#include <cyg/cpuload/cpuload.h>
#include <cyg/io/io.h>
#include <cyg/io/serialio.h>

#include <dirent.h>
#include <sys/stat.h>
#include <cyg/fileio/fileio.h>
#include <pkgconf/io_fileio.h>
#include <sys/socket.h>
#include <network.h>
#include <tftp_support.h>		// TFTP support
#include <netdb.h>
#include <arpa/inet.h>
#include <pkgconf/fs_ram.h>

#include "../globaldefs.h"
#include "../extern_vars.h"
#include "../utils/misc.h"
#include "datalog_interface.h"

#define RAMFILE_NAME	  	"/flightdata.ram"

// Global datalog structure. Defined in main.c
extern struct datalog dataLog;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Internal Function Prototypes
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int createfile( char *name );
int tftpTransfer(char *outfile, char *txbuf, int len);
char *tftp_error(int err);
int filetransferToGCS();
int umountFilesystem();
int writeMATLAB ();


#define SHOW_RESULT( _fn, _res ) \
		printf("\n<FAIL>: " #_fn "() returned %ld %s\n",  \
				(unsigned long)_res, _res<0?strerror(errno):"");

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Internal Variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// memory usage status data structure
static struct 		mallinfo info;		

#define MATLAB_HEADER_SIZE 20

//Index of the current datapoint in the arrays
static int32_t currentDataPoint;

// Data arrays
static double* doubleData[100];
static float* floatData[100];
static int32_t* intData[100];
static uint16_t* shortData[100];



//------------------------------- functions -----------------------------------

int createfile( char *name )
{
	int fd;
	int err;

	err = mount( "", "/", "ramfs" );
	if( err < 0 ) {
		SHOW_RESULT( mount, err );
	}
	else
	{
		printf("\nRAMFS mounted successfully");
	}



	err = chdir( "/" );
	if( err < 0 ) SHOW_RESULT( chdir, err );

	// if a datafile already exists, delete it
	if ( access( name, F_OK ) == 0 )
		unlink(name);

	fd = open( name, O_RDWR | O_CREAT );
	if( fd < 0 ) {
		SHOW_RESULT( open, fd );
	}

	return fd;
}

int umountFilesystem()
{
	int err;

	// delete datalog file from filesystem
	err = unlink(RAMFILE_NAME);
	if( err < 0 ){
		fprintf(stderr,"Deleting this file in RAMFS failed: %s",RAMFILE_NAME);
	}

	sleep(1);
	// unmount FS
	err = umount("/");

	if( err < 0 ){
		SHOW_RESULT( umount, err );
		return err;
	}
	else
		return 0;
}

int filetransferToGCS()
{

	int err, fd, filesize=0;
	struct stat filestatus;
	char * buf = NULL;			// for TFTP file transfer 
	char matfile_name[50];

	err = access( RAMFILE_NAME, F_OK );
	if( err < 0 && errno != EACCES )
		SHOW_RESULT( access, err );

	// open file to transfer
	fd = open( RAMFILE_NAME, O_RDONLY );
	if( fd < 0 )
		SHOW_RESULT( open, fd );

	info =  mallinfo();		// Free memory in the heap at the end of datalogging operation
	fprintf(stderr,"\nTotal allocated memory:%d, Max. free memory: %d\n", info.uordblks, info.fordblks);
	fprintf(stderr,"Largest free block of memory:%d \n", info.maxfree);
	
	// Get file stats
	fstat(fd, &filestatus);
	filesize = (size_t)(filestatus.st_size);
	
	if( info.maxfree < filesize )
		fprintf(stderr,"\n Insufficient memory for filetransfer !!\n");

	// allocated memory to store file contents in buffer
	buf = (char *)malloc(filesize);

	if (buf == NULL)
		fprintf(stderr,"\n malloc() failed");
	else
		fprintf(stderr,"\n malloc() allocated %d bytes to buf for filetransfer (TFTP).\n", (int)filesize);
	
	// read file contents to a temp buffer
	read(fd,&buf[0],filesize);
	close(fd);

	sprintf(matfile_name,"flightdata_%.4fsec.mat",get_Time());
	tftpTransfer(matfile_name, buf, filesize);

	free(buf);
	return filesize;
}


int tftpTransfer(char *outfile, char *txbuf, int len)
{
	int res, err;
	struct sockaddr_in host;

	build_bootp_record(&eth0_bootp_data,
			eth0_name,
			"192.168.3.11",		// eth0 ip_addr
			"255.255.255.0",	// netmask
			"192.168.3.255",	// broadcast
			"192.168.3.1",		// gateway
			"192.168.3.10");	// server ip_addr

	struct bootp *bp = &eth0_bootp_data;

	// initialize 'eth0' network interface
	if (!init_net(eth0_name, bp)) {
		diag_printf("Network initialization failed for eth0\n");
	}

	sleep(1);	// wait for connection to be established

	memset((char *)&host, 0, sizeof(host));
	host.sin_len = sizeof(host);
	host.sin_family = AF_INET;
	host.sin_addr = bp->bp_siaddr;
	host.sin_port = 0;

	fprintf(stderr,"Initiating TFTP filetransfer to %s to Host:%16s, length %d\n",
			outfile, inet_ntoa(host.sin_addr), len);


	res = tftp_put( outfile, &host, txbuf, len, TFTP_OCTET, &err);

	if (res < 0) {
		SHOW_RESULT (tftp_put, err);
		return res;
	}
	else {
		fprintf(stderr,"\n Transfer successful. %d bytes transferred", res);
		return res;
	}

}

char *tftp_error(int err)
{
	char *errmsg = "Unknown error";

	switch (err) {
	case TFTP_ENOTFOUND:
		return "file not found";
	case TFTP_EACCESS:
		return "access violation";
	case TFTP_ENOSPACE:
		return "disk full or allocation exceeded";
	case TFTP_EBADOP:
		return "illegal TFTP operation";
	case TFTP_EBADID:
		return "unknown transfer ID";
	case TFTP_EEXISTS:
		return "file already exists";
	case TFTP_ENOUSER:
		return "no such user";
	case TFTP_TIMEOUT:
		return "operation timed out";
	case TFTP_NETERR:
		return "some sort of network error";
	case TFTP_INVALID:
		return "invalid parameter";
	case TFTP_PROTOCOL:
		return "protocol violation";
	case TFTP_TOOLARGE:
		return "file is larger than buffer";
	}
	return errmsg;
}

void add_double_datalog(double * vars[], char * names[], int num_vars){
	int i;

	for (i = 0; i < num_vars; i++){
		*(dataLog.saveAsDoubleNames)[dataLog.numDoubleVars + i] = *names[i];
		*(dataLog.saveAsDoublePointers)[dataLog.numDoubleVars + i] = *vars[i];
	}
	dataLog.numDoubleVars += num_vars;
}

void add_float_datalog(double * vars[], char * names[], int num_vars){
	int i;

	for (i = 0; i < num_vars; i++){
		dataLog.saveAsFloatNames[dataLog.numFloatVars + i] = names[i];
		dataLog.saveAsFloatPointers[dataLog.numFloatVars + i] = vars[i];
	}
	dataLog.numFloatVars += num_vars;
}

void add_int_datalog(int * vars[], char * names[], int num_vars){
	int i;

	for (i = 0; i < num_vars; i++){
		dataLog.saveAsIntNames[dataLog.numIntVars + i] = names[i];
		dataLog.saveAsIntPointers[dataLog.numIntVars + i] = vars[i];
	}
	dataLog.numIntVars += num_vars;
}

void add_short_datalog(unsigned short * vars[], char * names[], int num_vars){
	int i;

	for (i = 0; i < num_vars; i++){
		dataLog.saveAsShortNames[dataLog.numShortVars + i] = names[i];
		dataLog.saveAsShortPointers[dataLog.numShortVars + i] = vars[i];
	}
	dataLog.numShortVars += num_vars;
}
//Initializes the arrays needed for logging, Returns 0 on success, non-zero otherwise
 int init_datalogger()
{
	currentDataPoint = 0;
	
	if (sizeof(double) != 8){
		fprintf (stderr, "\nFATAL: double is wrong size: %d", sizeof(double));
		return -1;
	}
	
	if (sizeof(float) != 4){
		fprintf (stderr, "\nFATAL: float is wrong size: %d", sizeof(float));
		return -1;
	}	
	
	//fprintf (stderr, "\nCreating logging arrays... ");
	int i;
	
	for (i = 0; i < dataLog.numDoubleVars; i++){
		doubleData[i] = malloc (sizeof(double) * dataLog.logArraySize);
		if (doubleData[i] == NULL){
			fprintf(stderr, "\nFATAL: Couldn't allocate space for double logging arrays! Memory NOT freed");
			return -1;
		}
	}
	
	for (i = 0; i < dataLog.numFloatVars; i++){
		floatData[i] = malloc (sizeof(float) * dataLog.logArraySize);
		if (floatData[i] == NULL){
			fprintf(stderr, "\nFATAL: Couldn't allocate space for float logging arrays! Memory NOT freed");
			return -1;
		}
	}
	
	for (i = 0; i < dataLog.numIntVars; i++){
		intData[i] = malloc (sizeof(int32_t) * dataLog.logArraySize);
		if (intData[i] == NULL){
			fprintf(stderr, "\nFATAL: Couldn't allocate space for int logging arrays! Memory NOT freed");
			return -1;
		}
	}
	
	for (i = 0; i < dataLog.numShortVars; i++){
		shortData[i] = malloc (sizeof(uint16_t) * dataLog.logArraySize);
		if (shortData[i] == NULL){
			fprintf(stderr, "\nFATAL: Couldn't allocate space for short logging arrays! Memory NOT freed");
			return -1;
		}
	}
	
	//fprintf (stderr, "Done");
	
	return 0;
}


//Frees the memory used by logging arrays
void close_datalogger ()
{
	//Write logging data to in MATLAB format to RAMFILE_NAME
	writeMATLAB();
	
	int i;
	
	for (i = 0; i < dataLog.numDoubleVars; i++)
		free (doubleData[i]);

	for (i = 0; i < dataLog.numFloatVars; i++)
		free (floatData[i]);
	
	for (i = 0; i < dataLog.numIntVars; i++)
		free(intData[i]);
	
	for (i = 0; i < dataLog.numShortVars; i++)
		free(shortData[i]);
	
	
		// Transfer data file
	fprintf(stderr,"\n Initiating filetransfer over TFTP...\n");
	filetransferToGCS();
	//sleep(1);
	//umountFilesystem();
	
	
	return;
}


//Writes values to arrays
//Assumes the arrays have been initialized with initLogging, returns immediately if no space is left in the arrays.
void datalogger ()
{
	if (currentDataPoint >= dataLog.logArraySize)
		return;
	
	int i;
	
	for (i = 0; i < dataLog.numDoubleVars; i++)
		(doubleData[i])[currentDataPoint] = (double)*(dataLog.saveAsDoublePointers[i]);

	for (i = 0; i < dataLog.numFloatVars; i++)
		(floatData[i])[currentDataPoint] = (float)*(dataLog.saveAsFloatPointers[i]);
	
	for (i = 0; i < dataLog.numIntVars; i++)
		(intData[i])[currentDataPoint] = (int32_t)*(dataLog.saveAsIntPointers[i]);
	
	for (i = 0; i < dataLog.numShortVars; i++)
		(shortData[i])[currentDataPoint] = (uint16_t)*(dataLog.saveAsShortPointers[i]);
	
	currentDataPoint++;
	
	return;
}


//Actually writes the MATLAB file; returns the file handle
int writeMATLAB ()
{
	//Make header
	//Write header
	//Write body
	
	int fd = createfile (RAMFILE_NAME);
	
	char headerbuf[MATLAB_HEADER_SIZE];
	
	//Make header variables
	int32_t* type = (int32_t*)headerbuf;
	int32_t* mrows = (int32_t*)(headerbuf + 4);
	int32_t* ncols = (int32_t*)(headerbuf + 8);
	int32_t* imagf = (int32_t*)(headerbuf + 12);
	int32_t* namelen = (int32_t*)(headerbuf + 16);
	
	//We have rows equal to how many datapoints have been collected
	*mrows = currentDataPoint;
	
	//Everything is in one column -> only need one
	*ncols = 1;
	
	//No imaginary values!
	*imagf = 0;
	
	int i;
	
	//Doubles
	//Big-endian, 64-bit float formatting
	*type = 1000;
	
	for (i = 0; i < dataLog.numDoubleVars; i++)
	{
		//Write header
		*namelen = strlen (dataLog.saveAsDoubleNames[i]) + 1; //keep trailing null
		write (fd, headerbuf, MATLAB_HEADER_SIZE);
		
		//Write matrix name
		write (fd, dataLog.saveAsDoubleNames[i], *namelen);
		
		//Write values
		write (fd, doubleData[i], sizeof(double) * currentDataPoint);
	}
	

	//Floats
	//Big-endian, 32-bit float formatting
	*type = 1010;
	
	for (i = 0; i < dataLog.numFloatVars; i++)
	{
		//Write header
		*namelen = strlen (dataLog.saveAsFloatNames[i]) + 1; //keep trailing null
		write (fd, headerbuf, MATLAB_HEADER_SIZE);
		
		//Write matrix name
		write (fd, dataLog.saveAsFloatNames[i], *namelen);
		
		//Write values
		write (fd, floatData[i], sizeof(float) * currentDataPoint);
	}
	
	//Ints
	//Big-endian, 32-bit integer formatting
	*type = 1020;
	
	for (i = 0; i < dataLog.numIntVars; i++)
	{
		//Write header
		*namelen = strlen (dataLog.saveAsIntNames[i]) + 1; //keep trailing null
		write (fd, headerbuf, MATLAB_HEADER_SIZE);
		
		//Write matrix name
		write (fd, dataLog.saveAsIntNames[i], *namelen);
		
		//Write values
		write (fd, intData[i], sizeof(int32_t) * currentDataPoint);
	}
	
	//Shorts
	//Big-endian, 16-bit integer formatting
	*type = 1030;
	
	for (i = 0; i < dataLog.numShortVars; i++)
	{
		//Write header
		*namelen = strlen (dataLog.saveAsShortNames[i]) + 1; //keep trailing null
		write (fd, headerbuf, MATLAB_HEADER_SIZE);
		
		//Write matrix name
		write (fd, dataLog.saveAsShortNames[i], *namelen);
		
		//Write values
		write (fd, shortData[i], sizeof(int16_t) * currentDataPoint);
	}
	
	
	return fd;
}
