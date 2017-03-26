/*! \file fault_onesurf.c
 *	\brief Fault on one control surface.
 *
 *	\details Inject a ramp fault on one control surface. Eight different variations.
 *	\ingroup fault_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: fault_onesurf.c 903 2012-09-26 21:08:13Z dorob002 $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "fault_interface.h"

extern void get_sensor_fault(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr){
	double *cmd;
	int state = 0;
	
	cmd = &sensorData_ptr->imuData_ptr->p;// pointer to roll rate


	state = controlData_ptr->run_num;


	switch(state){
		case 1:
		case 2:
			// Do nothing, unfaulted scenario
			break;
		case 3:	
		case 4:
		case 5:
		case 6:
			// Additive step fault on roll rate, starting at 12 sec after AP engaged
			ramp_fault(12,time,0,-80 * D2R,cmd,1);
			break;

		case 7:
		case 8:
			// Do nothing, unfaulted scenario
			break;
		case 9:
		case 10:
		case 11:
		case 12:
			// Additive step fault on roll rate, starting at 12 sec after AP engaged
			ramp_fault(12,time,0,-80 * D2R,cmd,1);
			break;

		case 13:
		case 14:
			// Do nothing, unfaulted scenario
			break;
		case 15:
		case 16:
		case 17:
		case 18:
			// Additive step fault on roll rate, starting at 12 sec after AP engaged
			ramp_fault(12,time,0,-80 * D2R,cmd,1);
			break;
	}
}
