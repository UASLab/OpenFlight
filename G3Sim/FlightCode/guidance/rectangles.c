/*! \file rectangles.c
 *	\brief Guidance law which commands a series of 90 degree heading commands, making a rectangular flight pattern.
 *
 *	\details
 *	\ingroup guidance_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: doublet_phi_theta.c 757 2012-01-04 21:57:48Z murch $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "../system_id/systemid_interface.h"
#include "guidance_interface.h"


extern void get_guidance(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr){

				if( time >= 0 && time < 5){
					controlData_ptr->psi_cmd = 0;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 5 && time < 13){
					controlData_ptr->psi_cmd = 90*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 13 && time < 21){
					controlData_ptr->psi_cmd = 180*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 21 && time < 29){
					controlData_ptr->psi_cmd = 270*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 29 && time < 37){
					controlData_ptr->psi_cmd = 360*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 37 && time < 45){
					controlData_ptr->psi_cmd = (360+90)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 45 && time < 53){
					controlData_ptr->psi_cmd = (360+180)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 53 && time < 61){
					controlData_ptr->psi_cmd = (360+270)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 61 && time < 69){
					controlData_ptr->psi_cmd = (2*360)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 69 && time < 77){
					controlData_ptr->psi_cmd = (2*360+90)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 77 && time < 85){
					controlData_ptr->psi_cmd = (2*360+180)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 85 && time < 93){
					controlData_ptr->psi_cmd = (2*360+270)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}
				if( time >= 93 && time < 120){
					controlData_ptr->psi_cmd = (2*360+360)*D2R;
					controlData_ptr->h_cmd = 0;
					controlData_ptr->ias_cmd = 0;
				}

}

