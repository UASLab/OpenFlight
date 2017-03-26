/*! \file straight_level.c
 *	\brief Straight and level pitch/roll commands
 *
 *	\details
 *	\ingroup guidance_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: straight_level.c 860 2012-07-18 18:27:25Z joh07594 $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "../system_id/systemid_interface.h"
#include "guidance_interface.h"

extern void get_guidance(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr){
	if (time < 25.0){
		controlData_ptr->phi_cmd = 0;
		controlData_ptr->theta_cmd = 0;
	}else{
		controlData_ptr->phi_cmd = 0;  //15*D2R set to zero for bench testing, 15 deg for flight as a safehold
		controlData_ptr->theta_cmd = 0;
	}
	}

