/*! \file sensors_hil.c
 *	\brief Data acquisition source code for HIL simulation
 *
 *	\details This file implements the init_daq() and daq() functions for the HIL simulation. Acquires data from HIL simulation over serial
 * 	port of MPC5200 and emulates IMU, GPS, and Air Data sensors.
 * 	\ingroup daq_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
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
#include <cyg/gpt/mpc5xxx_gpt.h>
#include <cyg/io/mpc5xxx_gpio.h>
#include <cyg/io/i2c_mpc5xxx.h>
#include <cyg/io/io.h>
#include <cyg/io/serialio.h>

#include "../globaldefs.h"
#include "../utils/serial_mpc5200.h"
#include "../utils/misc.h"
#include "../utils/scheduling.h"
#include "../extern_vars.h"
#include "AirData/airdata_interface.h"
#include "GPS/gps_interface.h"
#include "IMU/imu_interface.h"
#include "ADC/adc_interface.h"
#include "GPIO/gpio_interface.h"
#include AIRCRAFT_UP1DIR

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//HIL packet length, in bytes
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define PACKET_LENGTH		157
#define MAX_TIME_DAQ	0.009 // maximum time for DAQ (ms)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//prototype definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void read_hil_serial();
void reset_localBuffer();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Internal Variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static unsigned char* localBuffer = NULL;
static int bytesInLocalBuffer = 0, readState = 0;
static cyg_io_handle_t hilPort_handle;
static cyg_serial_buf_info_t buff_info;
static double hil_data[21];
static unsigned int countBuf = 0;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GPIO Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_gpio() {
}

void read_gpio(struct mission *missionData_ptr) {
	if (hil_data[1] == 1) {
		missionData_ptr->mode = 0; // data dump
	} else {
		missionData_ptr->mode = hil_data[0] + 1; // manual or auto mode
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IMU Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int init_imu() {
	// get serial port handle
	cyg_io_lookup(HIL_PORT, &hilPort_handle);
	hilPort = open_serial(HIL_PORT, HIL_BAUDRATE);

	// Initialization of persistent local buffer
	if (localBuffer == NULL) {
			localBuffer = (unsigned char*) malloc(1024 * sizeof(unsigned char));
			reset_localBuffer();
	}

	return 1;
}

int read_imu(struct imu *imuData_ptr) {


	imuData_ptr->time = get_Time();
	read_hil_serial();
	imuData_ptr->err_type = data_valid;

	/* angular rate in rad/s */
	imuData_ptr->p = hil_data[2];
	imuData_ptr->q = hil_data[3];
	imuData_ptr->r = hil_data[4];

	/* acceleration in m/s^2 */
	imuData_ptr->ax = hil_data[5];
	imuData_ptr->ay = hil_data[6];
	imuData_ptr->az = hil_data[7];

	/* magnetic field in Gauss */
	imuData_ptr->hx = hil_data[8];
	imuData_ptr->hy = hil_data[9];
	imuData_ptr->hz = hil_data[10];
	return 1;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GPS Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_gps(struct gps *gpsData_ptr) {
}

int read_gps(struct gps *gpsData_ptr) {
	static int count = 0;

	if (++count > BASE_HZ) {
		gpsData_ptr->newData = 1; // set newData flag at 1Hz				
		count = 0;
		/* gps position */
		gpsData_ptr->lat = hil_data[11];
		gpsData_ptr->lon = hil_data[12];
		gpsData_ptr->alt = hil_data[13];

		/* gps velocity in m/s */
		gpsData_ptr->vn = hil_data[14];
		gpsData_ptr->ve = hil_data[15];
		gpsData_ptr->vd = hil_data[16];

		// Set err_type fields
		gpsData_ptr->err_type = data_valid;
		gpsData_ptr->navValid = 0;
		return 1;
	} else
		return -1;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Air Data Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_airdata() {
}

int read_airdata(struct airdata *adData_ptr) {
	adData_ptr->bias[0] = 0.0; // biases for air data
	adData_ptr->bias[1] = 0.0; // biases for air data
	adData_ptr->aoa = hil_data[17]; // aoa
	adData_ptr->aos = hil_data[18]; // aos
	adData_ptr->Pd = hil_data[19]; // Pd
	adData_ptr->Ps = hil_data[20]; // Ps
	return 0;
}

void read_hil_serial() {

	double tic = get_Time();
	unsigned int len, bytesInBuffer;//my_chksum,rcv_chksum;
	unsigned short bytesToRead = 0, bytesRead = 0;
	unsigned short exit = 0;

	cyg_io_get_config(hilPort_handle, CYG_IO_GET_CONFIG_SERIAL_BUFFER_INFO,
			&buff_info, &len);

	bytesInBuffer = buff_info.rx_count;

	/*if (bytesInBuffer <= 76) {
		return;
	}*/

	//printf("\n b= %d", bytesInBuffer) ;

	if (bytesInBuffer > PACKET_LENGTH * 2 ) {
		bytesToRead = bytesInBuffer - 2 * PACKET_LENGTH;
		bytesRead = read(hilPort, localBuffer, bytesToRead);
		localBuffer[0] = 0;
		localBuffer[1] = 0;
		localBuffer[2] = 0;
		//printf("full") ;
	}

	len = 0;

	unsigned char byteIn[1] = { 0 };
	while (exit == 0) {

		// Reading a byte from the buffer
		while (len == 0) {
			len = read(hilPort, byteIn, 1);
			if (len == -1) {
				return;
			}
			if (get_Time() - tic > MAX_TIME_DAQ) {
				//printf("\n exit ") ;
				return;
			}
		}

		if (get_Time() - tic > MAX_TIME_DAQ) {
			//printf("\n exit ") ;
			return;
		}

		len = 0;
		// ----------------------------------------------------

		if (localBuffer[0] != 170) {
			countBuf = 0;

		}
		localBuffer[countBuf] = byteIn[0];

		if (countBuf >= PACKET_LENGTH - 1 && localBuffer[0] == 170
				&& localBuffer[1] == 170 && localBuffer[2] == 171) {

			hil_data[0] = (double) localBuffer[3];
			hil_data[1] = (double) localBuffer[4];
			memcpy(&hil_data[2], &localBuffer[5], PACKET_LENGTH - 5); //

			localBuffer[0] = 0;
			localBuffer[1] = 0;
			localBuffer[2] = 0;
			countBuf = 0;
			//printf("\n dt %f", get_Time() - tic) ;
			//exit = 1;
			return ;

		}

		if (countBuf > 1 && localBuffer[countBuf - 2] == 170
				&& localBuffer[countBuf - 1] == 170 && localBuffer[countBuf]
				== 171) {

			localBuffer[0] = localBuffer[countBuf - 2];
			localBuffer[1] = localBuffer[countBuf - 1];
			localBuffer[2] = localBuffer[countBuf];
			countBuf = 2;

		}

		countBuf++;

	} // End of while(exit)


}




void reset_localBuffer() {
	int i;
	// Clear the first two bytes of the local buffer
	for (i = 0; i < 2; i++)
		localBuffer[i] = '\0';

	bytesInLocalBuffer = 0;

	readState = 0; // reset readState counter as all bytes for this packet have been read
}
