/*! \file empty_control.c
 *	\brief Empty controller source code
 *
 *	\details Empty template for implementing a controller.
 *
 *	\ingroup control_fcns
 *
 *	\author University of Minnesota
 *	\author Aerospace Engineering and Mechanics
 *	\copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: empty_control.c 757 2012-01-04 21:57:48Z murch $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "control_interface.h" 

/// Return control outputs based on references and feedback signals.
extern void get_control(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr) {

    // Control law: ***********************************************************
    // Here: get_control surface outputs.

      /// Control implementation ...

    // ************************************************************************
    controlData_ptr->de = 0; // Elevator deflection [rad]
    controlData_ptr->dr = 0; // Rudder deflection [rad]
    controlData_ptr->da_r = 0; // Aileron deflection [rad], right
	controlData_ptr->da_l = 0; // left aileron
	controlData_ptr->dthr = 0; // throttle
	controlData_ptr->df_l = 0; // left flap
	controlData_ptr->df_r = 0; // right flap	


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
