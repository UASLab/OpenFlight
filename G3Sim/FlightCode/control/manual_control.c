/*! \file manual_control.c
 *	\brief Manual control source code
 *
 *	\details Manual control commands are passed directly through.
 *
 *	\ingroup control_fcns
 *
 *	\author University of Minnesota
 *	\author Aerospace Engineering and Mechanics
 *	\copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: manual_control.c 797 2012-04-16 15:41:52Z murch $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "control_interface.h" 

/// Return control outputs based on references and feedback signals.
extern void get_control(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr) {

	controlData_ptr->dthr = sensorData_ptr->inceptorData_ptr->throttle; // throttle
    controlData_ptr->de = sensorData_ptr->inceptorData_ptr->pitch; 		// Elevator deflection [rad]
    controlData_ptr->dr = sensorData_ptr->inceptorData_ptr->yaw; 		// Rudder deflection [rad]
	controlData_ptr->da_l = sensorData_ptr->inceptorData_ptr->roll; 	// left aileron
    controlData_ptr->da_r = -1*sensorData_ptr->inceptorData_ptr->roll; // Aileron deflection [rad], right

	subtract_trim_bias(controlData_ptr);
}

// Reset of controller
extern void reset_control(struct control *controlData_ptr){
	// Here: code to reset the controller
	controlData_ptr->dthr = 0; // throttle
	controlData_ptr->de   = 0; // elevator
	controlData_ptr->dr   = 0; // rudder
	controlData_ptr->da_l = 0; // left aileron
	controlData_ptr->da_r = 0; // right aileron
	controlData_ptr->df_l = 0; // left flap
	controlData_ptr->df_r = 0; // right flap	

}
