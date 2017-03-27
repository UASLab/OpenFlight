/*! \file chirp_sysid.c
 *	\brief System ID chirp inputs
 *
 *	\details  Inject a system id sequence on the elevator, aileron, rudder.
 *	\ingroup systemid_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: chirp_sysid.c 908 2012-10-04 20:40:18Z joh07594 $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "systemid_interface.h"
#include "twoto15chirp.h"


//#include "aircraft/thor_config.h"  // for SIL sim only
#include AIRCRAFT_UP1DIR


extern void get_system_id( double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr){

	// static variable for position in time history signal.
	static int count = 0;
	int state = 0;

	if(controlData_ptr->run_num > 15){
		state = controlData_ptr->run_num - 15;
	}else{
		state = controlData_ptr->run_num;
	}

	switch(state){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				if ( time >= 2.0 && time < (SYSID_LENGTH*TIMESTEP+2.0) && count < SYSID_LENGTH){
     				controlData_ptr->de = controlData_ptr->de_in + twoto15chirp[count]*5*D2R - ELEVATOR_TRIM;
					count++;
				}
				else{
					count = 0;
					controlData_ptr->de = controlData_ptr->de_in - ELEVATOR_TRIM;
				}
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				if ( time >= 2.0 && time < (SYSID_LENGTH*TIMESTEP+2.0) && count < SYSID_LENGTH){
					controlData_ptr->da_r = controlData_ptr->da_r_in + twoto15chirp[count]*5*D2R  - AILERON_TRIM;
					controlData_ptr->da_l = controlData_ptr->da_l_in - twoto15chirp[count]*5*D2R  + AILERON_TRIM;
					controlData_ptr->dr = 0;
					count++;
				}
				else{
					count = 0;
					controlData_ptr->da_r = controlData_ptr->da_r_in - AILERON_TRIM;
					controlData_ptr->da_l = controlData_ptr->da_l_in + AILERON_TRIM;
					controlData_ptr->dr = 0;
				}
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				if ( time >= 2.0 && time < (SYSID_LENGTH*TIMESTEP+2.0) && count < SYSID_LENGTH){
					controlData_ptr->da_r = 0;
					controlData_ptr->da_l = 0;
					controlData_ptr->dr = controlData_ptr->dr_in + twoto15chirp[count]*5*D2R - RUDDER_TRIM;
					count++;
				}
				else{
					count = 0;
					controlData_ptr->dr = controlData_ptr->dr_in - RUDDER_TRIM;
					controlData_ptr->da_r = controlData_ptr->da_r_in - AILERON_TRIM;
					controlData_ptr->da_l = controlData_ptr->da_l_in + AILERON_TRIM;
				}
				break;
	}

}

