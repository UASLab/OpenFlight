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
 * $Id: fault_onesurf.c 757 2012-01-04 21:57:48Z murch $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "fault_interface.h"

extern void get_sensor_fault(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr){
	double *cmd;
	
	cmd = &sensorData_ptr->imuData_ptr->p;// pointer to roll rate


			// Additive step fault on roll rate, starting at 12 sec after AP engaged
			ramp_fault(12,time,0,-80 * D2R,cmd,1);

}
