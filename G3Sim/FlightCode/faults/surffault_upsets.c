/*! \file fault_upsets.c
 *	\brief Simulated upset maneuvers.
 *
 *	\details Inject inputs to simulate an upset.
 *	\ingroup fault_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: upsets.c 757 2012-01-04 21:57:48Z murch $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "fault_interface.h"

extern void get_surface_fault(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr){
	int state = 0;

	if(controlData_ptr->run_num > 12){
		state = controlData_ptr->run_num - 12;
	}else{
		state = controlData_ptr->run_num;
	}

	switch(state){
		case 1:
		case 2:
		case 3:
		case 4:
			// Step input on aileron for 0.5 seconds, should roll off to ~60deg bank angle
			if(time > 2.0 && time < 2.5){
				controlData_ptr->da_r -= 14*D2R;
				controlData_ptr->da_l += 14*D2R;
			}
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			// Step input on rudder for 1.0 seconds, should roll off to ~60deg bank angle
			if(time > 2.0 && time < 3.0){
				controlData_ptr->dr += 6*D2R;
			}
			break;	
		case 9:
		case 10:
		case 11:
		case 12:
			// Additive ramp input on elevator to -25deg, starting at 2 sec after AP engaged, should be ~4kts/sec decel to stall
			ramp_fault(2.0,time,8.0,-25.0 * D2R,&controlData_ptr->de,1);
			break;	

	};
}
