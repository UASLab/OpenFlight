/*! \file gps_crescent.c
 *	\brief Hemisphere Crescent OEM GPS receiver source code
 *
 *	\details This file implements the init_gps() and read_gps() functions for the Hemisphere Crescent OEM GPS receiver.
 *	\ingroup gps_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gps_crescent.c 887 2012-08-16 20:52:34Z joh07594 $
 */

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
#include "gps_crescent.h"
#include "gps_interface.h"
#include "../../utils/serial_mpc5200.h"
#include "../../utils/misc.h"


static unsigned char* localBuffer;
static int bytesInLocalBuffer, readState ;


static void parse_gps( struct gps *gpsData_ptr ){
	double old_GPS_TOW;
	// parse msg ID 
	switch(localBuffer[5]*256 + localBuffer[4] ){

	case 1: // parse msg 1 

		// Swap byte order first
		endian_swap(localBuffer, 10, 2);
		endian_swap(localBuffer, 12, 8);
		endian_swap(localBuffer, 20, 8);
		endian_swap(localBuffer, 28, 8);
		endian_swap(localBuffer, 36, 4);
		endian_swap(localBuffer, 40, 4);
		endian_swap(localBuffer, 44, 4);
		endian_swap(localBuffer, 48, 4);
		endian_swap(localBuffer, 52, 4);
		endian_swap(localBuffer, 56, 2);
		endian_swap(localBuffer, 58, 2);
		
		// Cast bytes into appropriate datatypes
		gpsData_ptr->satVisible = (uint16_t)(localBuffer[9]);
		gpsData_ptr->GPS_week = *((uint16_t *)(&localBuffer[10]));
		
		old_GPS_TOW = gpsData_ptr->GPS_TOW;
		gpsData_ptr->GPS_TOW = *((double *)(&localBuffer[12]));
		
		gpsData_ptr->lat = *((double *)(&localBuffer[20]));
		gpsData_ptr->lon = *((double *)(&localBuffer[28]));
		gpsData_ptr->alt = (double)(*((float *)(&localBuffer[36])));
		gpsData_ptr->vn = (double)(*((float *)(&localBuffer[40])));
		gpsData_ptr->ve = (double)(*((float *)(&localBuffer[44])));
		gpsData_ptr->vd = (double)(*((float *)(&localBuffer[48]))) * -1;
		gpsData_ptr ->courseOverGround = atan2(gpsData_ptr->ve,gpsData_ptr->vn);
		gpsData_ptr ->speedOverGround = sqrt(gpsData_ptr->vn*gpsData_ptr->vn + gpsData_ptr->ve*gpsData_ptr->ve);
		

		// Checking for GPS lock and outages

		// First, we check that the GPS receiver is outputting some form of GPS data
		// Second, we check that the GPS data is fine-steered
		// Third, we check that the GPS data is distinct from the previous data point

		// All three conditions must be satisfied for GPS lock and GPS new data.
		
		// When there is no new GPS information, GPS_TOW sent by the receiver is the old TOW
		// The new data flag is not set if the GPS is not new, when prevents measurement updates

		
		if((*((uint16_t *)(&localBuffer[56]))) != 0) {
			// Check internal navigation mode sent by the receiver.
			// Crescent: 0 means no fix. (SirfIII: 0 means fix, not relevant here)
			// Added 1e-5 to GPW_TOW in order to deal with numerical issue in floor() function in C
			if(fabs(gpsData_ptr->GPS_TOW - floor(gpsData_ptr->GPS_TOW+1e-5)) < 1e-3) {
				// GPS TOW needs to be fine-steered to a whole number of TOW.
				if(fabs(gpsData_ptr->GPS_TOW - old_GPS_TOW) > 1e-3) {
					// Check that this is a new data (no GPS outage)
					gpsData_ptr->navValid = 0; // Light the GPS LOCK in Ground Station
					gpsData_ptr->newData = 1;  // Execute measurement update
				}
				else {
			        gpsData_ptr->navValid = 1; // Turn off the GPS LOCK light in Ground station
				}
			}								   // Also, no measurement update will occur since newData is not set to 1
			else {
			    gpsData_ptr->navValid = 1; // Turn off the GPS LOCK light in Ground station
			}
		}								   // Also, no measurement update will occur since newData is not set to 1 
		else {
			gpsData_ptr->navValid = 1; // Turn off the GPS LOCK light in Ground station
		}							   // Also, no measurement update will occur since newData is not set to 1
		break;
	
	}

}


// Initialize GPS and configure it to send the desired messages
void init_gps(struct gps *gpsData_ptr){

	// Use this section to setup the messages on the receivers. The configuration
	// is saved into the flash memory, so this only needs to be done once.
	/*******************************************************************
	// open the serial port used for gps communication at the default baudrate
	gpsData_ptr->port = open_serial( gpsData_ptr->portName, gpsData_ptr->baudRate );
	if ( gpsData_ptr->port == -1 )	{
		fprintf( stderr, "<gps_crescent.c>Open serial port error!\n" );		
	}

	char buf[100];
	int len;

	// configure the gps to send the message we want
	strcpy(buf, "$JBIN,1,1");
	buf[9] = 0x0D;
	buf[10] = 0x0A;
	len = write( gpsData_ptr->port, buf, 11 );
	fprintf(stderr, "wrote %d bytes (should be 11)\n", len);
	cyg_thread_delay(10);

	strcpy(buf, "$JBIN,96,0");
	buf[10] = 0x0D;
	buf[11] = 0x0A;
	len = write( gpsData_ptr->port, buf, 12 );
	fprintf(stderr, "wrote %d bytes (should be 12)\n", len);
	cyg_thread_delay(10);
	
	// configure the baudrate
	strcpy(buf, "$JBAUD,115200");
	buf[13] = 0x0D;
	buf[14] = 0x0A;
	len = write( gpsData_ptr->port, buf, 15 );
	fprintf(stderr, "wrote %d bytes (should be 14)\n", len);
	cyg_thread_delay(10);

	strcpy(buf, "$JSAVE");
	buf[6] = 0x0D;
	buf[7] = 0x0A;
	len = write( gpsData_ptr->port, buf, 8 );
	fprintf(stderr, "wrote %d bytes (should be 8)\n", len);
	
	sleep(10);	// wait for save to complete
	close(gpsData_ptr->port);
	sleep(1);
	*******************************************************************/

	// Open serial port
	gpsData_ptr->port = open_serial( gpsData_ptr->portName, gpsData_ptr->baudRate );

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
	unsigned int bytesReadThisCall =0;;
	unsigned short msgPayloadSize = 0, bytesToRead = 0, bytesRead = 0;
	int status =0;
	
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

	//fprintf(stderr, "read state is %d (before while)\n", readState);

	// Keep reading until we've processed all of the bytes in the buffer
	while (bytesReadThisCall < bytesInBuffer){
		
		//fprintf(stderr, "read state is %d (after while)\n", readState);

		switch (readState){
			case 0: //Look for packet header bytes
				// Read in up to 4 bytes to the first open location in the local buffer
				bytesRead = read(gpsData_ptr->port,&localBuffer[bytesInLocalBuffer],4-bytesInLocalBuffer);
				bytesReadThisCall += bytesRead; // keep track of bytes read during this call
					
				if (localBuffer[0] == '$'){ // Check for first header byte
					bytesInLocalBuffer = 1;

					//fprintf(stderr, "case 0, $ header type \n");

					if (localBuffer[1] == 'B'){ // Check for second header byte
						bytesInLocalBuffer = 2;
						if (localBuffer[2] == 'I'){ // Check for third header byte
							bytesInLocalBuffer = 3;
							if (localBuffer[3] == 'N'){ // Check for fourth header byte
								bytesInLocalBuffer = 4;
								readState++; // header complete, move to next stage
							}
						}
					}
				}
				else {
					gpsData_ptr->err_type = noPacketHeader;
				}
				break;	// end case 0
				
			case 1: // Look for block ID and data length
				// Find how many bytes need to be read for block ID (2) + data length (2) - bytes already read (includes 4 byte header)
				bytesToRead = 8 - bytesInLocalBuffer;
			
				// Read in bytes to the last location in the local buffer
				bytesRead = read(gpsData_ptr->port,&localBuffer[bytesInLocalBuffer],bytesToRead);
				bytesInLocalBuffer += bytesRead; // keep track of bytes in local buffer
				bytesReadThisCall += bytesRead; // keep track of bytes read during this call
				
				if (bytesRead == bytesToRead){
					readState++;
					//printf ("\n<GPS>: Got msgID: %d and Data Length: %d", localBuffer[5]*256 + localBuffer[4], localBuffer[7]*256 + localBuffer[6]);
				}
				else{
					gpsData_ptr->err_type = incompletePacket;
				}
				break;	// end case 1
		
			case 2: //Read payload, checksum, and stop bytes
				// Find message payload size
				msgPayloadSize = localBuffer[7]*256 + localBuffer[6]; // data is in little endian format
				
				// Error checking on payload size. If size is bigger than expected, dump packet
				if(msgPayloadSize > GPS_MAX_MSG_SIZE){			
					gpsData_ptr->err_type = incompletePacket;
					reset_localBuffer();
				}
				
				// Find how many bytes need to be read for the total message (Header (4)  + ID (2) + Size (2) + Payload + checksum (2) + stop (2) - bytes already read )
				bytesToRead = msgPayloadSize + 12 - bytesInLocalBuffer;
				
				// Read in the remainder of the message to the local buffer, starting at the first empty location
				bytesRead = read (gpsData_ptr->port, &localBuffer[bytesInLocalBuffer], bytesToRead);
				bytesInLocalBuffer += bytesRead; // keep track of bytes in local buffer
				bytesReadThisCall += bytesRead; // keep track of bytes read during this call
				
				if (bytesRead == bytesToRead){
					//printf ("\n<GPS>: Got complete message! Tried for %d, got %d",bytesToRead,bytesRead);
					//printf ("\n<GPS>: My checksum: %d  Recv: %d",do_chksum(localBuffer, 8, msgPayloadSize+8),(localBuffer[8+msgPayloadSize+1]*256 + localBuffer[8+msgPayloadSize]));
					// Checksum verification
					if ( do_chksum(localBuffer, 8, msgPayloadSize+8) == (localBuffer[8+msgPayloadSize+1]*256 + localBuffer[8+msgPayloadSize]) ){
						// If it's OK, extract data
						parse_gps( gpsData_ptr );
						gpsData_ptr->err_type = data_valid;
						//printf ("\n<GPS>: Success!");
						status = 1;
					}										
					else{ 
						//printf ("\n<GPS>: Checksum mismatch!");
						gpsData_ptr->err_type = checksum_err;
					}
					reset_localBuffer();
				}
				else{
					//printf ("\n<GPS>: Didn't get complete message. Tried for %d, got %d",bytesToRead,bytesRead);
					gpsData_ptr->err_type= incompletePacket;
					
					status = 0;									
				}
				break;	// end case 2
				
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
