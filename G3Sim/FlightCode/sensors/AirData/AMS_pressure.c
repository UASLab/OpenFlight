/*! \file AMS_pressure.c
 *	\brief Header file for AMS pressure sensors.
 *
 *	\details This program is designed to read data off 4 AMS pressure sensor units:
 *  AMS 5812-0003-D (unidirectional 0.3psi differential for airspeed)
 *  AMS 5812-0003-DB (x2) (bidirectional +-0.3psi differential for alpha and beta)
 *  AMS 5812-0150-B (barometric sensor for altitude)
 *  \ingroup airdata_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: AMS_pressure.c 756 2012-01-04 18:51:43Z murch $
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <cyg/io/i2c_mpc5xxx.h>

#include "../../globaldefs.h"
#include "airdata_interface.h"
#include "airdata_constants.h"
#include "AMS_pressure.h"



void init_airdata(){
return;
}

int read_airdata (struct airdata *adData_ptr)
{
	int status = 0;

	
	// Read AMS pressure sensors, passing in pointers to air data structure locations
	// Thread delay is needed to allow I2C transaction sufficient time to complete.
	if(0 == read_AMS_sensor(&AMS5812_0150B,&adData_ptr->Ps,11.0,17.5))
		status |= 1;
		
	cyg_thread_delay(1);
	
	if(0 == read_AMS_sensor(&AMS5812_0003D,&adData_ptr->Pd,0.0, 0.3))
		status |= 1 << 1;
	
	// These are only on Thor and FASER
	cyg_thread_delay(1);
	if(0 == read_AMS_sensor(&AMS5812_0003DB_1,&adData_ptr->Pd_aoa,-0.3,0.3))
		status |= 1 << 2;
	
	cyg_thread_delay(1);
	
	if(0 == read_AMS_sensor(&AMS5812_0003DB_2,&adData_ptr->Pd_aos,-0.3,0.3))
		status |= 1 << 3;
	return status;
}


static int	read_AMS_sensor(cyg_i2c_device* device,double* pressure_data, double p_min, double p_max)
{	
	uint8_t  DataBuf[4];	//databuffer that stores the binary words output from sensor
	uint16_t pressure_counts; // temporary variables
	//uint16_t temp_counts; 
	
	//Equations for conversion are as follows:
	//P = (Digout(p) - Digoutp_min)/Sensp + p_min
	//Where Sensp = (Digoutp_max - Digoutp_min)/(p_max - p_min)
	//Therein p is current pressure in PSI and p_min and p_max are the specific max and min
	//pressure of the respective sensor. The Digoutp_max and Digoutp_min are the 90% and 10% 
	//values of the 15 bit output word i.e. 0111111111111111_binary = 32767_decimal
	//For temperature conversion replace T for p in above equations where T_max 85c and 
	//T_min = -25c. Temperature is the sensor temperature at the measurement cell and includes
	//self heating. This is NOT the actual air temperature.
	
	// Try to read 2 bytes from sensor (just pressure data). Don't update pressure data if 2 bytes are not read.
	if (2 == cyg_i2c_rx(device, DataBuf, 2)){
	
		//Combine the two bytes of returned data
		pressure_counts = (((uint16_t) (DataBuf[0]&0x7F)) <<8) + (((uint16_t) DataBuf[1])); // data is a 15-bit word. Bitwise AND ensures only 7 bits of upper byte are used.
		//temp_counts = (((uint16_t) (DataBuf[2]&0x7F)) <<8) + (((uint16_t) DataBuf[3]));
		
		// Convert counts to engineering units
		*pressure_data = (double)((pressure_counts - P_MIN_COUNTS)/((P_MAX_COUNTS-P_MIN_COUNTS)/(p_max-p_min)) + p_min)*PSI_TO_KPA; 	//pressure in kpa for bi_dir_1
		//*temp_data = (double)(temp_counts - P_MIN_COUNTS)/((P_MAX_COUNTS-P_MIN_COUNTS)/110.0) - 25.0;			//temperature in celcius
		return 1;
	}
	else{
//		printf("\n<read_AMS_sensor>: 4 bytes NOT read!");
		return 0;
	}			
	
}

