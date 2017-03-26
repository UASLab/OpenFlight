/*! \file telemetry.c
 *	\brief Send telemetry data through serial port
 *
 *	\details
 *	\ingroup telemetry_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: telemetry.c 761 2012-01-19 17:23:49Z murch $
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <pthread.h>
#include <sched.h>
#include <cyg/posix/pthread.h>
#include <cyg/kernel/kapi.h>
#include <cyg/cpuload/cpuload.h>
#include <cyg/io/io.h>
#include <cyg/io/serialio.h>

#include "../globaldefs.h"
#include "../utils/serial_mpc5200.h"
#include "../utils/misc.h"
#include "../extern_vars.h"
#include "telemetry_interface.h"
#include AIRCRAFT_UP1DIR

#define TELE_PACKET_SIZE  51
extern char statusMsg[103];	

/* send_telemetry packet structure = [ <UUT> time, <empty>, <empty>, p, q, r, alt, IAS, psi, theta, phi, rud, ele, thr, ail, cpuload, lon, lat, statusFlags, <empty> <16bit_CKSUM> ] */

static int port;

void init_telemetry(){
	// Open serial port for send_telemetry. Set in /aircraft/xxx_config.h
	port = open_serial(TELEMETRY_PORT, TELEMETRY_BAUDRATE);	
}

void send_telemetry(struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr, uint16_t cpuLoad)
{
	int bytes=0;
	unsigned short flags=0;
	unsigned long tmp;
	uint16_t tele_data[23], output_CKSUM=0;
	static byte sendpacket[TELE_PACKET_SIZE]={'U','U','T',};

	// Build send_telemetry data packet
	tmp = (unsigned long)( sensorData_ptr->imuData_ptr->time*1e04 );		// time buffer will now overflow after 59.6 hrs (thats what 4 bytes' worth!)
	memcpy(&tele_data[0],&tmp,4);

	tele_data[2] = (uint16_t)(0);
	tele_data[3] = (uint16_t)(0);

	tele_data[4] = (uint16_t)( sensorData_ptr->imuData_ptr->p*R2D / 200.0 * 0x7FFF );	//rate = 200 deg/s max saturation
	tele_data[5] = (uint16_t)( sensorData_ptr->imuData_ptr->q*R2D / 200.0 * 0x7FFF );
	tele_data[6] = (uint16_t)( sensorData_ptr->imuData_ptr->r*R2D / 200.0 * 0x7FFF );
	
	tele_data[7] = (uint16_t)( (sensorData_ptr->adData_ptr->h) / 10000.0 * 0x7FFF );			// max AGL Alt.(m) = 10000 m
	tele_data[8] = (uint16_t)( (sensorData_ptr->adData_ptr->ias) / 80.0 * 0x7FFF );				// max Indicated Airspeed(IAS) = 80 m/s	

	tele_data[9] = (uint16_t)( navData_ptr->psi*R2D / 180.0 * 0x7FFF );		// Euler angles [psi,theta,phi] (deg)
	tele_data[10]= (uint16_t)( navData_ptr->the*R2D / 90.0 * 0x7FFF );
	tele_data[11]= (uint16_t)( navData_ptr->phi*R2D / 180.0 * 0x7FFF );

	tele_data[12]= (uint16_t)( (controlData_ptr->da_r-controlData_ptr->da_l)/2 / R_AILERON_MAX * 0x7FFF );		// control surface commands (normalized 0-1)
	tele_data[13]= (uint16_t)( controlData_ptr->de / ELEVATOR_MAX * 0x7FFF );
	tele_data[14]= (uint16_t)( controlData_ptr->dthr * 0x7FFF );
	tele_data[15]= (uint16_t)( controlData_ptr->dr / RUDDER_MAX * 0x7FFF );


	tele_data[16] = cpuLoad;		/* cpuload */

	tmp = (unsigned long)( sensorData_ptr->gpsData_ptr->lon *1e07 );
	memcpy(&tele_data[17],&tmp,4);
	tmp = (unsigned long)( sensorData_ptr->gpsData_ptr->lat *1e07 );
	memcpy(&tele_data[19],&tmp,4);

	//if (ofpMode == standby) flags = flags | 0x01;
	if (missionData_ptr->mode == 2) flags = flags | 0x01<<1;	// Autopilot mode
	if (missionData_ptr->mode == 1) flags = flags | 0x01<<4;  // Manual mode
	if ( (sensorData_ptr->imuData_ptr->err_type != checksum_err) && (sensorData_ptr->imuData_ptr->err_type != got_invalid) ) flags = flags | 0x01<<6;
	if (sensorData_ptr->gpsData_ptr->err_type == data_valid || sensorData_ptr->gpsData_ptr->err_type == incompletePacket) flags = flags | 0x01<<7;
	if (sensorData_ptr->gpsData_ptr->navValid == 0) flags = flags | 0x01<<8;
	
	tele_data[21] = flags;
	tele_data[22] = (uint16_t)sensorData_ptr->gpsData_ptr->satVisible;
	
	
	memcpy(&sendpacket[3],&tele_data,46);
	// compute 16-bit checksum of output data (excluding the header)
	output_CKSUM = do_chksum (sendpacket, 2,TELE_PACKET_SIZE-2);
	*(uint16_t *)&sendpacket[49] = output_CKSUM;

	// send send_telemetry data packet to serial port
	while(bytes != TELE_PACKET_SIZE) bytes += write(port, &sendpacket[bytes], TELE_PACKET_SIZE-bytes); bytes=0;
	
	// Send status message if present
	if (statusMsg[0] != 0){
		while(bytes != 103) bytes += write(port, &statusMsg[bytes], 103-bytes); bytes=0;
		statusMsg[0] =0;
	}
}
