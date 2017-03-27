/*! \file gps_sirf.c
 *	\brief SiRFIII GPS receiver source code
 *
 *	\details This file implements the init_gps() and read_gps() functions for SiRFIII GPS receiver.
 *	\ingroup gps_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gps_sirf.c 800 2012-04-20 14:18:42Z murch $
 */

/* SiRF packet structure
 * <0xA0,0xA2> <packet length> <packet> <cksum> <0xB0,0xB3>
 * bytes: <2> <2> <variable_size> <2> <2>
 *
 * Default packets: 4, 2, 9, 7, 27, 41
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <math.h>
#include <cyg/io/serialio.h>
#include <cyg/io/io.h>

#include "../../globaldefs.h"
#include "gps_sirf.h"
#include "gps_interface.h"
#include "../../utils/serial_mpc5200.h"
#include "../../utils/misc.h"

static unsigned char* localBuffer;
static int bytesInLocalBuffer, readState ;

void init_gps(struct gps *gpsData_ptr)
{
	// NMEA Checksums are already included
	unsigned char cmdNmea2BinaryMode_B9600[] = "$PSRF100,0,9600,8,1,0*0C\r\n";
	unsigned char cmdNmea2BinaryMode_B38400[] = "$PSRF100,0,38400,8,1,0*3C\r\n";
	unsigned char cmdNmea2BinaryMode_B57600[] = "$PSRF100,0,57600,8,1,0*37\r\n";	
	unsigned char cmdNmea2BinaryMode_B115200[] = "$PSRF100,0,115200,8,1,0*04\r\n";

	unsigned char cmdSirfMsg2[] = {0xA0,0xA2,0x00,0x08,0xA6,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0xA8,0xB0,0xB3}; // command to turn off Message 2
	unsigned char cmdSirfMsg4[] = {0xA0,0xA2,0x00,0x08,0xA6,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0xAA,0xB0,0xB3}; // command to turn off Message 4
	unsigned char cmdSirfMsg7[] = {0xA0,0xA2,0x00,0x08,0xA6,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0xAD,0xB0,0xB3}; // command to turn off Message 7
	unsigned char cmdSirfMsg9[] = {0xA0,0xA2,0x00,0x08,0xA6,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0xAF,0xB0,0xB3}; // command to turn off Message 9
	unsigned char cmdSirfMsg27[] = {0xA0,0xA2,0x00,0x08,0xA6,0x00,0x1B,0x00,0x00,0x00,0x00,0x00,0x00,0xC1,0xB0,0xB3}; // command to turn off Message 27

	// open serial port at default GPS baudrate 4800
	gpsData_ptr->port = open_serial(gpsData_ptr->portName, B4800);
	if (gpsData_ptr->port < 0)
		return;
		
	//change GPS output to binary at given baudrate
	switch( gpsData_ptr->baudRate ){
	case B9600:
		write( gpsData_ptr->port, cmdNmea2BinaryMode_B9600, sizeof(cmdNmea2BinaryMode_B9600) ); break;
	case B38400:
		write( gpsData_ptr->port, cmdNmea2BinaryMode_B38400, sizeof(cmdNmea2BinaryMode_B38400) ); break;
	case B57600:
		write( gpsData_ptr->port, cmdNmea2BinaryMode_B57600, sizeof(cmdNmea2BinaryMode_B57600) ); break;
	case B115200:
		write( gpsData_ptr->port, cmdNmea2BinaryMode_B115200, sizeof(cmdNmea2BinaryMode_B115200) ); break;
	}
	close(gpsData_ptr->port);
	sleep(1);

	// change serial port baudrate
	gpsData_ptr->port = open_serial( gpsData_ptr->portName, gpsData_ptr->baudRate );

	// Turn off messages we don't need
	sleep(3);
	write( gpsData_ptr->port, cmdSirfMsg2, sizeof(cmdSirfMsg2) );
	write( gpsData_ptr->port, cmdSirfMsg4, sizeof(cmdSirfMsg4) );
	write( gpsData_ptr->port, cmdSirfMsg7, sizeof(cmdSirfMsg7) );
	write( gpsData_ptr->port, cmdSirfMsg9, sizeof(cmdSirfMsg9) );
	write( gpsData_ptr->port, cmdSirfMsg27, sizeof(cmdSirfMsg27) );
}

int read_gps(struct gps *gpsData_ptr)
{
	// serial port buffer handle
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
	int status = 0;
	
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
	
	// Keep reading until we've processed all of the bytes in the buffer
	while (bytesReadThisCall < bytesInBuffer){
		
		switch (readState){
			case 0: //Look for packet header bytes
				// Read in up to 2 bytes to the first open location in the local buffer
				bytesRead = read(gpsData_ptr->port,&localBuffer[bytesInLocalBuffer],2-bytesInLocalBuffer);
				bytesReadThisCall += bytesRead; // keep track of bytes read during this call
					
				if (localBuffer[0] == 0xA0){ // Check for first header byte
					bytesInLocalBuffer = 1;
					if (localBuffer[1] == 0xA2){ // Check for second header byte
						bytesInLocalBuffer = 2;
						readState++; // header complete, move to next stage
					}
				}
				else {
					gpsData_ptr->err_type = noPacketHeader;
				}
			break;	// end case 0
			
			case 1: //Look for message size bytes
				// Find how many bytes need to be read for data length (2) - bytes already read (includes 2 byte header)
				bytesToRead = 4 - bytesInLocalBuffer;	
		
				// Read in up to 2 bytes to the first open location in the local buffer
				bytesRead = read(gpsData_ptr->port,&localBuffer[bytesInLocalBuffer],bytesToRead);
				bytesReadThisCall += bytesRead; // keep track of bytes read during this call
				bytesInLocalBuffer += bytesRead; // keep track of bytes in local buffer
				
				if (bytesRead == bytesToRead){
					readState++; // size bytes complete, move to next stage
				}
				else{
					//printf ("\n<GPS>: Failed to get size bytes");
					gpsData_ptr->err_type = incompletePacket;				
				}
			break;	// end case 1
		
			case 2: //Read payload, checksum, and stop bytes
				// Find message payload size
				msgPayloadSize = getbeuw(localBuffer,2)&0x7FFF; // packet size is 15 bits. bitwise AND ensures only 15 bits are used.
				
				//printf("<GPS>: msgPayloadSize: %d\n",msgPayloadSize);
				
				// Error checking on payload size. If size is bigger than expected, dump packet
				if(msgPayloadSize > GPS_MAX_MSG_SIZE){			
					gpsData_ptr->err_type = incompletePacket;
					reset_localBuffer();
				}
				
				// Find how many bytes need to be read for the total message (Header (2) + Size (2) + Payload + checksum (2) + stop (2) - bytes already read )
				bytesToRead = msgPayloadSize + 8 - bytesInLocalBuffer;
				
				// Read in the remainder of the message to the local buffer, starting at the first empty location
				bytesRead = read (gpsData_ptr->port, &localBuffer[bytesInLocalBuffer], bytesToRead);
				bytesInLocalBuffer += bytesRead; // keep track of bytes in local buffer
				bytesReadThisCall += bytesRead; // keep track of bytes read during this call
				
				if (bytesRead == bytesToRead){
					//printf ("\n<GPS>: Got complete message! Tried for %d, got %d",bytesToRead,bytesRead);
					//printf("<GPS>: Packet ID %d \n", localBuffer[4]);
					//printf("<GPS>: msgPayloadSize: %d\n",msgPayloadSize);
					//printf("<GPS>: My checksum: %d  Recv: %d\n",do_chksum(localBuffer, 4, msgPayloadSize+4),getbeuw(localBuffer,4+msgPayloadSize));

					// Checksum verification (15-bit, big endian)
					if ( (do_chksum(localBuffer, 4, msgPayloadSize+4)&0x7FFF) == (getbeuw(localBuffer,4+msgPayloadSize)&0x7FFF) ){
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
					reset_localBuffer(); // Clear the local buffer regardless
				}
				else{
					//printf ("<GPS>: Didn't get complete message. Tried for %d, got %d. %d\n",bytesToRead,bytesRead,msgPayloadSize);
					gpsData_ptr->err_type= incompletePacket;
					
					status = 0;
				}
			break;	// end case 2
				
			default:
				reset_localBuffer();
				printf ("\n<GPS>: Why are you here?");
				status = 0;
			break;	// end default
		
		} // end switch (readState)

	} // end while (bytesReadThisCall < bytesInBuffer)
	
	// Store local buffer in gps packet
	gpsData_ptr->localBuffer = localBuffer;
	gpsData_ptr->bytesInLocalBuffer = bytesInLocalBuffer;
	gpsData_ptr->readState = readState;
	
	return status;
}


void parse_gps( struct gps *gpsData_ptr  )
{
	unsigned char *base = &localBuffer[0]+4; 

#ifdef verbose
		fprintf( stderr, "<GPS>: Packet ID %d \n", base[0]);
#endif

	switch ( base[0] ){
	case 0x06: // msgID6: response to poll software version (msg 132)
			fprintf( stderr, "<GPS>: SiRF firmware version: %s\n", base+1 );
		break;

	case 0x02: // msgID2: Measure Nav data out (ECEF)
		gpsData_ptr ->Xe = (double)getbesl(base,1);
		gpsData_ptr ->Ye = (double)getbesl(base,5);
		gpsData_ptr ->Ze = (double)getbesl(base,9);
		gpsData_ptr ->Ue = (double)getbesw(base,13) / 8;
		gpsData_ptr ->Ve = (double)getbesw(base,15) / 8;
		gpsData_ptr ->We = (double)getbesw(base,17) / 8;
		//mode = *(b+18)
		gpsData_ptr ->GPS_week = getbeuw(base,22);
		gpsData_ptr ->GPS_TOW = (double)(getbeul(base,24)) / 100;
		gpsData_ptr ->satVisible = base[28];
		// append time tag
		gpsData_ptr ->time = get_Time();
		break;

	case 0x0B:	//msgID11: Command Acknowledge
		fprintf( stderr, "\n<GPS>: Command ID %d acknowledged",base[1]);
		break;

	case 0x0C:	//msgID12: Command NOT Acknowledge
		fprintf( stderr, "\n<GPS>: Command ID %d NOT acknowledged",base[1]);
		break;

	case 0x29:	 //msgID41: Geodetic Nav Data
		gpsData_ptr ->navValid = getbeuw(base,1);
		gpsData_ptr ->GPS_week = getbeuw(base,5);
		gpsData_ptr ->GPS_TOW = (double)(getbeul(base,7)) / 1000;
		gpsData_ptr ->lat = (double)getbesl(base,23)*1e-07;
		gpsData_ptr ->lon = (double)getbesl(base,27)*1e-07;
		gpsData_ptr ->alt = (double)getbesl(base,35)*1e-02;			// AMSL	meters
		gpsData_ptr ->speedOverGround = (double)getbeuw(base,40)*1e-02;		// m/s
		gpsData_ptr ->courseOverGround = D2R*(double)getbeuw(base,42)*1e-02;	// rad
		gpsData_ptr ->vd = -(double)getbesw(base,46)*1e-02;
		gpsData_ptr ->vn = cos(gpsData_ptr ->courseOverGround)*gpsData_ptr ->speedOverGround;
		gpsData_ptr ->ve = sin(gpsData_ptr ->courseOverGround)*gpsData_ptr ->speedOverGround;
		gpsData_ptr ->satVisible = base[87];
		// append time tag
		gpsData_ptr ->time = get_Time();
		gpsData_ptr ->newData = 1; // set newData flag to one

		//			printf("\n Lat=%f,\t Lon=%f, vn=%f",gpsData_ptr ->lat,gpsData_ptr ->lon,gpsData_ptr ->vn);
		
		break;

	case 0x1c: // msgID28: Carrier phase info (Nav Lib Measurement Data)
		/* not yet implemented */
		break;
	
	
	case 0x09: // msgID9
		/* not yet implemented */
	break;
	}

}

void reset_localBuffer(){
	int i;
	// Clear the first two bytes of the local buffer
	for(i=0;i<2;i++)
		localBuffer[i] = '\0';
	
	bytesInLocalBuffer = 0;
	
	readState = 0; // reset readState counter as all bytes for this packet have been read
}
