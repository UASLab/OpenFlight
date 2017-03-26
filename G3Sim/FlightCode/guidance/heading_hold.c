/*! \file heading_hold.c
 *	\brief Source code to fly straight and level, tracking altitude, airspeed, and heading
 *
 *	\details
 *	\ingroup guidance_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: straight_level.c 777 2012-02-23 16:58:44Z murch $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "../system_id/systemid_interface.h"
#include "guidance_interface.h"

extern void get_guidance(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr){

		controlData_ptr->psi_cmd = 0;
		controlData_ptr->h_cmd = 0;
		controlData_ptr->ias_cmd = 0;

	}

