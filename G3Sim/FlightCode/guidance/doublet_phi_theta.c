/*! \file doublet_phi_theta.c
 *	\brief Doublet commands on pitch and roll angle
 *
 *	\details
 *	\ingroup guidance_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: doublet_phi_theta.c 869 2012-08-06 22:40:38Z joh07594 $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "../system_id/systemid_interface.h"
#include "guidance_interface.h"


extern void get_guidance(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr){
	
	controlData_ptr->phi_cmd = doublet(3, time, 6, 25*D2R); // Roll angle command
	controlData_ptr->theta_cmd = doublet(14, time, 6, 8*D2R); // Pitch angle command

}

