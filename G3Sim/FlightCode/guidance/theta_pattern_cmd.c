/*! \file theta_pattern_cmd.c
 *      \brief Guidance code to track various pitch angle commands while maintaining a constant roll angle
 *
 *      \details
 *      \ingroup guidance_fcns
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


                                if( time >= 0 && time < 2){
                                        controlData_ptr->theta_cmd =    0;
                                        controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 2 && time < 3.5){
                                        controlData_ptr->theta_cmd =      -2*D2R;
                                }
                                if( time >= 3.5 && time < 5){
                                        controlData_ptr->theta_cmd =      4*D2R;
                                }
                                if( time >= 5 && time < 6){
                                        controlData_ptr->theta_cmd =      -1*D2R;
                                }
                                if( time >= 6 && time < 8){
                                        controlData_ptr->theta_cmd =      -3*D2R;
                                }
                                if( time >= 8 && time < 10){
                                        controlData_ptr->theta_cmd =      4*D2R;
                                }
                                if( time >= 10 && time < 11){
                                        controlData_ptr->theta_cmd =      6*D2R;
                                }   
                                if( time >= 11 && time < 13){
                                        controlData_ptr->theta_cmd =      0;
                                }
								if( time >= 13 && time < 14.5){
                                        controlData_ptr->theta_cmd =      -5*D2R;
                                }
						     	if( time >= 14.5 && time < 15){
                                        controlData_ptr->theta_cmd =      2*D2R;
                                }
						     	if( time >= 15 && time < 16.5){
                                        controlData_ptr->theta_cmd =      -3*D2R;
                                }
								if( time >= 16.5 && time < 17.5){
                                        controlData_ptr->theta_cmd =      1*D2R;
                                }
                                if( time >= 17.5 && time < 25){
                                        controlData_ptr->theta_cmd =      0;
                                }

                                

}
