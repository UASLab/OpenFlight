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

extern void get_surface_fault(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr){
	double *cmd;
	
	cmd = &controlData_ptr->da_r;// pointer to right aileron


			// Additive step fault on right aileron, starting at 7 sec after AP engaged,
			ramp_fault(7.0,time,0,10.0 * D2R,cmd,1);

}
