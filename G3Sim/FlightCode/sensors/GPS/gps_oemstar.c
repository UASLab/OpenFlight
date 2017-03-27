#include <termios.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <cyg/io/io.h>
#include <cyg/io/serialio.h>
#include <pthread.h>
#include <sched.h>
#include <cyg/posix/pthread.h>
#include <cyg/kernel/kapi.h>

#include "../../globaldefs.h"
#include "gps_oemstar.h"
#include "gps_interface.h"
#include "../../utils/serial_mpc5200.h"
#include "../../utils/misc.h"
#include "../../utils/matrix.h"
#include "../../navigation/nav_functions.h"


static unsigned char* localBuffer;
static int bytesInLocalBuffer, readState ;

static void parse_gps( struct gps *gpsData_ptr ){
	double old_GPS_TOW;
    double sig_X, sig_Y, sig_Z, sig_VX, sig_VY, sig_VZ;
    uint8_t finesteering_ok, solution_ok;
       
    MATRIX ecef_mat = mat_creat(3,1,ZERO_MATRIX);
    MATRIX lla_mat = mat_creat(3,1,ZERO_MATRIX);
    MATRIX ned_mat = mat_creat(3,1,ZERO_MATRIX);
    
    switch(localBuffer[5]*256 + localBuffer[4] ){

    case 241: // parse BESTXYZ
    
        endian_swap(localBuffer,14,2);     // GPS Week No
        endian_swap(localBuffer,16,4);     // GPS_TOW
        endian_swap(localBuffer,28,4);     // Solution Status
        endian_swap(localBuffer,28+8,8);   // X
        endian_swap(localBuffer,28+16,8);  // Y
        endian_swap(localBuffer,28+24,8);  // Z
        endian_swap(localBuffer,28+32,4);  // stdevXe
        endian_swap(localBuffer,28+36,4);  // stdevYe
        endian_swap(localBuffer,28+40,4);  // stdevZe
        endian_swap(localBuffer,28+52,8);  // Vx
        endian_swap(localBuffer,28+60,8);  // Vy
        endian_swap(localBuffer,28+68,8);  // Vz
        endian_swap(localBuffer,28+76,4);  // stdevVx
        endian_swap(localBuffer,28+80,4);  // stdevVy
        endian_swap(localBuffer,28+84,4);  // stdevVz
        
        gpsData_ptr->GPS_week = *((uint16_t *)(&localBuffer[14]));
        gpsData_ptr->satVisible = (uint16_t)(localBuffer[28+105]);
        
        old_GPS_TOW = gpsData_ptr->GPS_TOW;
		gpsData_ptr->GPS_TOW =  (double) *((uint32_t *)(&localBuffer[16])) / 1000.0;
        
        // convert positions from ECEF to LLA
        gpsData_ptr->Xe = *((double *)(&localBuffer[28+8]));
        gpsData_ptr->Ye = *((double *)(&localBuffer[28+16]));
        gpsData_ptr->Ze = *((double *)(&localBuffer[28+24]));
        
        ecef_mat[0][0] = gpsData_ptr->Xe;
        ecef_mat[1][0] = gpsData_ptr->Ye;
        ecef_mat[2][0] = gpsData_ptr->Ze;
		
		if(sqrt(gpsData_ptr->Xe*gpsData_ptr->Xe + gpsData_ptr->Ye*gpsData_ptr->Ye + gpsData_ptr->Ze*gpsData_ptr->Ze) < 1e-3) {
			lla_mat[0][0] = 0.0;
			lla_mat[1][0] = 0.0;
			lla_mat[2][0] = 0.0;
		} else {
			lla_mat = ecef2lla(ecef_mat,lla_mat);
		}
        
        gpsData_ptr->lat = lla_mat[0][0]*R2D;
        gpsData_ptr->lon = lla_mat[1][0]*R2D;
        gpsData_ptr->alt = lla_mat[2][0];
        
        // convert velocities from ECEF to NED
        gpsData_ptr->Ue = *((double *)(&localBuffer[28+52]));
        gpsData_ptr->Ve = *((double *)(&localBuffer[28+60]));
        gpsData_ptr->We = *((double *)(&localBuffer[28+68]));
        
        ecef_mat[0][0] = gpsData_ptr->Ue;
        ecef_mat[1][0] = gpsData_ptr->Ve;
        ecef_mat[2][0] = gpsData_ptr->We;
        
        ned_mat = ecef2ned(ecef_mat,ned_mat,lla_mat);
        
        gpsData_ptr->vn = ned_mat[0][0];
        gpsData_ptr->ve = ned_mat[1][0];
        gpsData_ptr->vd = ned_mat[2][0];
        
        // convert stdev position from ECEF to NED
        sig_X = (double) *((float *)(&localBuffer[28+32]));
        sig_Y = (double) *((float *)(&localBuffer[28+36]));
        sig_Z = (double) *((float *)(&localBuffer[28+40]));
        
        ecef_mat[0][0] = sig_X;
        ecef_mat[1][0] = sig_Y;
        ecef_mat[2][0] = sig_Z;
        
        ned_mat = ecef2ned(ecef_mat,ned_mat,lla_mat);
        
        gpsData_ptr->sig_N = ned_mat[0][0];
        gpsData_ptr->sig_E = ned_mat[1][0];
        gpsData_ptr->sig_D = ned_mat[2][0];
        
        // convert stdev velocities from ECEF to NED
        sig_VX = (double) *((float *)(&localBuffer[28+76]));
        sig_VY = (double) *((float *)(&localBuffer[28+80]));
        sig_VZ = (double) *((float *)(&localBuffer[28+84]));
        
        ecef_mat[0][0] = sig_VX;
        ecef_mat[1][0] = sig_VY;
        ecef_mat[2][0] = sig_VZ;
        
        ned_mat = ecef2ned(ecef_mat,ned_mat,lla_mat);
        
        gpsData_ptr->sig_vn = ned_mat[0][0];
        gpsData_ptr->sig_ve = ned_mat[1][0];
        gpsData_ptr->sig_vd = ned_mat[2][0];
		
		//fprintf(stderr,"Stat:%d \n",(*((uint32_t *)(&localBuffer[28]))));
        //fprintf(stderr,"Time:%d \n",(*((uint8_t *)(&localBuffer[13]))));
		
		//endian_swap(localBuffer,20,4);
		//fprintf(stderr,"Rx:%08X \n",(*((uint32_t *)(&localBuffer[20]))));
		
        solution_ok = ((*((uint32_t *)(&localBuffer[28]))) == 0);
        //finesteering_ok = ( (*((uint8_t *)(&localBuffer[13]))) == 160 ) || ( (*((uint8_t *)(&localBuffer[13]))) == 170 ) || ( (*((uint8_t *)(&localBuffer[13]))) == 180 );
		finesteering_ok=1;
        if(solution_ok & finesteering_ok) {
            if(fabs(gpsData_ptr->GPS_TOW - old_GPS_TOW) > 1e-3) {
                // Check that this is a new data (no GPS outage)
                gpsData_ptr->navValid = 0; // Light the GPS LOCK in Ground Station
                gpsData_ptr->newData = 1;  // Execute measurement update
            }
			else gpsData_ptr->navValid = 1; // Turn off the GPS LOCK light in Ground station
        }								   // Also, no measurement update will occur since newData is not set to 1
        else gpsData_ptr->navValid = 1; // Turn off the GPS LOCK light in Ground station
                                        // Also, no measurement update will occur since newData is not set to 1
        
        break;
    }
	mat_free(ecef_mat);
	mat_free(lla_mat);
	mat_free(ned_mat);
}


// Initialize GPS and configure it to send the desired messages
void init_gps(struct gps *gpsData_ptr){
    
    // Open serial port
	gpsData_ptr->port = open_serial( gpsData_ptr->portName, gpsData_ptr->baudRate );
	/*
	char buf[100];
	int len;

	// configure the gps to send the message we want
	strcpy(buf, "LOG COM2 BESTPOSB ONTIME 1 0 NOHOLD");
	buf[35] = 0x0D;
	buf[36] = 0x0A;
	len = write( gpsData_ptr->port, buf, 37 );
	fprintf(stderr, "wrote %d bytes (should be 37)\n", len);
	cyg_thread_delay(10);

	strcpy(buf, "LOG COM2 BESTVELB ONTIME 1 0 NOHOLD");
	buf[35] = 0x0D;
	buf[36] = 0x0A;
	len = write( gpsData_ptr->port, buf, 37 );
	fprintf(stderr, "wrote %d bytes (should be 37)\n", len);
	cyg_thread_delay(10);
	
	strcpy(buf, "LOG COM2 RANGEB ONTIME 1 0 NOHOLD");
	buf[33] = 0x0D;
	buf[34] = 0x0A;
	len = write( gpsData_ptr->port, buf, 37 );
	fprintf(stderr, "wrote %d bytes (should be 35)\n", len);
	cyg_thread_delay(10);
	
	strcpy(buf, "SAVECONFIG");
	buf[10] = 0x0D;
	buf[11] = 0x0A;
	len = write( gpsData_ptr->port, buf, 12 );
	fprintf(stderr, "wrote %d bytes (should be 12)\n", len);
	cyg_thread_delay(10);
	*/
	
}

// How to handle static variables with multiple sensors?  objects? add to gpspacket?
int read_gps(struct gps *gpsData_ptr)
{
	cyg_io_handle_t port_handle;
	cyg_serial_buf_info_t buff_info;
	unsigned int len = sizeof (buff_info);

	// get serial port handle
	cyg_io_lookup( gpsData_ptr->portName, &port_handle );
	
	cyg_io_get_config (port_handle, CYG_IO_GET_CONFIG_SERIAL_BUFFER_INFO,\
			&buff_info, &len);
	unsigned int bytesInBuffer = buff_info.rx_count;
	unsigned int bytesReadThisCall = 0;
	unsigned short msgPayloadSize = 0, bytesToRead = 0, bytesRead = 0;
    unsigned long CRC_computed, CRC_read;
	int j, status =0;
	
	// Initialization of persistent local buffer
	if (gpsData_ptr->localBuffer == NULL)
	{
		gpsData_ptr->localBuffer = (unsigned char*) malloc (1024 * sizeof (unsigned char));
	}

	// First check if there are any bytes in the serial buffer, return if none
	if( bytesInBuffer == 0 )
		return -1;

	// Get localBuffer stored in gps packet. This is to keep the following code readable
	localBuffer = gpsData_ptr->localBuffer;
	bytesInLocalBuffer= gpsData_ptr->bytesInLocalBuffer;
	readState = gpsData_ptr->readState;

	while (bytesReadThisCall < bytesInBuffer){

        switch (readState){
            case 0: //Look for packet header bytes
                // Read in up to 3 bytes to the first open location in the local buffer
                //fprintf(stderr,"bytesInLocalBuffer is %d\n",bytesInLocalBuffer);
                
                bytesRead = read(gpsData_ptr->port,&localBuffer[bytesInLocalBuffer],3-bytesInLocalBuffer);
                
                //fprintf(stderr,"The first three bytes are %0X %0X %0X\n",localBuffer[0],localBuffer[1],localBuffer[2]);    
                //fprintf(stderr,"bytesRead is %d\n",bytesRead);
                //fprintf(stderr,"Read %d bytes, The first three bytes are %0X %0X %0X\n", bytesRead,localBuffer[0],localBuffer[1],localBuffer[2]);    
                
                bytesReadThisCall += bytesRead; // keep track of bytes read during this call
                
                if (localBuffer[0] == 0xAA){ // Check for first header byte
                    bytesInLocalBuffer = 1;
                    //fprintf(stderr, "case 0, 0xAA header type \n");
                    if (localBuffer[1] == 0x44){ // Check for second header byte
                        bytesInLocalBuffer = 2;
                        if (localBuffer[2] == 0x12){ // Check for third header byte
                            bytesInLocalBuffer = 3;
                            readState++;
                        }
                    }
                }
                else {
                    gpsData_ptr->err_type = noPacketHeader;
                }
                break;	// end case 0
                
            case 1: // Look for block ID and data length
                // Read 28 Header Bytes
                bytesToRead = 28 - bytesInLocalBuffer;
                
                // Read in bytes to the last location in the local buffer
                bytesRead = read(gpsData_ptr->port,&localBuffer[bytesInLocalBuffer],bytesToRead);
                bytesInLocalBuffer += bytesRead; // keep track of bytes in local buffer
                bytesReadThisCall += bytesRead;  // keep track of bytes read during this call
                
                if (bytesRead == bytesToRead){
                    readState++;
                    //fprintf (stderr,"<GPS>: Got msgID: %d and Data Length: %d\n", localBuffer[5]*256 + localBuffer[4], localBuffer[9]*256 + localBuffer[8]);
                    //printf ("<GPS>: localBuffer[0] = %02X localBuffer[1] = %02X localBuffer[2] = %02X localBuffer[3] = %02X localBuffer[4] = %02X localBuffer[5] = %02X \n", localBuffer[0], localBuffer[1], localBuffer[2], localBuffer[3], localBuffer[4], localBuffer[5]);
                }
                else{
                    gpsData_ptr->err_type = incompletePacket;
                }
                break;  // end case 1
        
            case 2: //Read payload
                // Find message payload size
                msgPayloadSize = localBuffer[9]*256 + localBuffer[8]; // data is in little endian format
                
                // Error checking on payload size. If size is bigger than expected, dump packet
                if(msgPayloadSize > GPS_MAX_MSG_SIZE){			
                    gpsData_ptr->err_type = incompletePacket;
                    reset_localBuffer();
                }
                
                // Find how many bytes need to be read for the total message (Sync (3)  + Remaining Header (25) + Payload - bytes already read )
                bytesToRead = msgPayloadSize + 28 - bytesInLocalBuffer;
                
                //printf("bytesInLocalBuffer is %d bytesToRead is %d \n",bytesInLocalBuffer,bytesToRead);
                
                // Read in the remainder of the message to the local buffer, starting at the first empty location
                bytesRead = read (gpsData_ptr->port, &localBuffer[bytesInLocalBuffer], bytesToRead);
                bytesInLocalBuffer += bytesRead; // keep track of bytes in local buffer
                bytesReadThisCall += bytesRead; // keep track of bytes read during this call
                
                if (bytesRead == bytesToRead){
                    //printf ("<GPS>: Got complete message! Tried for %d, got %d\n",bytesToRead,bytesRead);
					readState++;
				}
				else {
					gpsData_ptr->err_type = incompletePacket;
				}
				
				break; // end case 2
				
			case 3: // read CRC bytes (4 bytes)
				bytesToRead = 4;
				bytesRead = read (gpsData_ptr->port, &localBuffer[bytesInLocalBuffer], bytesToRead);
				bytesInLocalBuffer += bytesRead;
				bytesReadThisCall += bytesRead;
					
				if(bytesRead == bytesToRead) {
					// CRC verification
					CRC_computed = CalculateBlockCRC32(bytesInLocalBuffer-4,localBuffer);
					endian_swap(localBuffer,140,4);
					CRC_read = *(uint32_t *) (localBuffer+140);
                    if (CRC_computed == CRC_read) {
                        gpsData_ptr->err_type = data_valid;
						parse_gps(gpsData_ptr);
                        //fprintf (stderr,"<GPS t = %9.3lf>: Success!\n",gpsData_ptr->GPS_TOW);
                    }
                    else{ 
						send_status("GPS CRC ERR");
                        //fprintf (stderr,"<GPS>: Checksum mismatch!\n");
						/* ============= DEBUG CHECKSUM ERROR ================
						fprintf (stderr,"<GPS %d>: Checksum mismatch! Buffer: %02X%02X%02X%02X Read: %08lX Computed: %08lX\n",localBuffer[5]*256 + localBuffer[4],localBuffer[140],localBuffer[141],localBuffer[142],localBuffer[143],CRC_read,CRC_computed);
                        fprintf (stderr,"Hex: \n");
                            for (j = 0; j < bytesInLocalBuffer; j++) {
                                fprintf(stderr,"%02X ",localBuffer[j]);
                                if(j%8==7) 
                                    fprintf(stderr,"\n");
                            }
						*/
						gpsData_ptr->err_type = checksum_err;
                    }
                    
                    reset_localBuffer();
                }
                else{
                    //printf ("\n<GPS>: Didn't get complete message. Tried for %d, got %d",bytesToRead,bytesRead);
                    gpsData_ptr->err_type= incompletePacket;
                    
                    status = 0;									
                }
                break;	// end case 3
                
                default:
                    reset_localBuffer();
                    printf ("\n<GPS>: Why are you here?");
                    status = 0;
                break; // end default
        
        } // end switch (readState)

    } // end while (bytesReadThisCall < bytesInBuffer)	

    // Store local buffer in gps packet
    gpsData_ptr->localBuffer = localBuffer;
    gpsData_ptr->bytesInLocalBuffer = bytesInLocalBuffer;
    gpsData_ptr->readState = readState;
    
    return status;
}

static void reset_localBuffer(){
	int i;
	// Clear the first four bytes of the local buffer
	for(i=0;i<4;i++)
		localBuffer[i] = '\0';
	
	bytesInLocalBuffer = 0;
	
	readState = 0; // reset readState counter as all bytes for this packet have been read
}

/* ====================== CHECKSUM ===================================*/
// CRC Value
unsigned long CRC32Value(int i)
{
   int j;
   unsigned long ulCRC;
    ulCRC = i;
   for ( j = 8 ; j > 0; j-- )
   {
      if ( ulCRC & 1 )
         ulCRC = ( ulCRC >> 1 ) ^ CRC32_POLYNOMIAL;
      else
         ulCRC >>= 1;
   }
   return ulCRC;
}
// CRC of a block of data
unsigned long CalculateBlockCRC32(
   unsigned long ulCount,     /* Number of bytes in the data block */
   unsigned char *ucBuffer ) /* Data block */
{
   unsigned long ulTemp1;
   unsigned long ulTemp2;
   unsigned long ulCRC = 0;
while ( ulCount-- != 0 )
{
      ulTemp1 = ( ulCRC >> 8 ) & 0x00FFFFFFL;
      ulTemp2 = CRC32Value( ((int) ulCRC ^ *ucBuffer++ ) & 0xff );
      ulCRC = ulTemp1 ^ ulTemp2;
   }
   return( ulCRC );
}
