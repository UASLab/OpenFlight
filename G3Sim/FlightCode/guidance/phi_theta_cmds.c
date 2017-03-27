/*! \file phi_theta_cmds.c
 *      \brief Guidance law to track various pitch and roll angle commands
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



        int state = 0;

        if(missionData_ptr->run_num > 9){
                state = missionData_ptr->run_num - 9;
        }
       else{
                state = missionData_ptr->run_num;
        }

        switch(state){
                        case 1:
                        case 2:
                        case 3: // straight & level
                                if( time > 20){
                                        controlData_ptr->phi_cmd =      15*D2R; // 15 deg
                                        controlData_ptr->theta_cmd =    0;
                                }else{
                                        controlData_ptr->phi_cmd =      0;
                                        controlData_ptr->theta_cmd =    0;
                                }
                                break;
                        case 4:
                        case 5: // roll tracking pattern
                                if( time >= 0 && time < 2){
                                        controlData_ptr->theta_cmd =    0;
                                        controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 2 && time < 3.5){
                                        controlData_ptr->phi_cmd =      -10*D2R;
                                }
                                if( time >= 3.5 && time < 5){
                                        controlData_ptr->phi_cmd =      20*D2R;
                                }
                                if( time >= 5 && time < 6){
                                        controlData_ptr->phi_cmd =      -5*D2R;
                                }
                                if( time >= 6 && time < 8){
                                        controlData_ptr->phi_cmd =      -15*D2R;
                                }
                                if( time >= 8 && time < 10){
                                        controlData_ptr->phi_cmd =      20*D2R;
                                }
                                if( time >= 10 && time < 11.5){
                                        controlData_ptr->phi_cmd =      10*D2R;
                                }
                                if( time >= 11.5 && time < 13.5){
                                        controlData_ptr->phi_cmd =      30*D2R;
                                }
                                if( time >= 13.5 && time < 20){
                                        controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 20 ){
                                        controlData_ptr->phi_cmd =      15*D2R; // fail safe
                                }
                                break;
                        case 6:
                        case 7: // theta tracking pattern
                                if( time >= 0 && time < 2){
                                        controlData_ptr->theta_cmd =    0;
                                        controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 2 && time < 3.5){
                                        controlData_ptr->theta_cmd = -5*D2R;
                                }
                                if( time >= 3.5 && time < 4.5){
                                        controlData_ptr->theta_cmd =    -8*D2R;
                                }
                                if( time >= 4.5 && time < 7){
                                        controlData_ptr->theta_cmd =    5*D2R;
                                }
                                if( time >= 7 && time < 8){
                                        controlData_ptr->theta_cmd =    8*D2R;
                                }
                                if( time >= 8 && time < 10){
                                        controlData_ptr->theta_cmd =    0;
                                }
                                if( time >= 10 && time < 11){
                                        controlData_ptr->theta_cmd =    3*D2R;
                                }
                                if( time >= 11 && time < 12){
                                        controlData_ptr->theta_cmd =    6*D2R;
                                }
                                if( time >= 12 && time < 13){
                                        controlData_ptr->theta_cmd =    9*D2R;
                                }
                                if( time >= 13 && time < 16){
                                        controlData_ptr->theta_cmd =    -3*D2R;
                                }
                                if( time >= 16 && time < 17){
                                        controlData_ptr->theta_cmd =    -6*D2R;
                                }
                                if( time >= 17 && time < 18){
                                        controlData_ptr->theta_cmd =    -9*D2R;
                                }
                                if( time >= 18 && time < 28){
                                        controlData_ptr->theta_cmd =    0;
                                }
                                if( time >= 28){
                                        controlData_ptr->phi_cmd =    15*D2R;	// fail safe
                                }
                                break;
                        case 8:
                        case 9: // intermixed pitch and roll tracking commands

                                if( time >= 0 && time < 2){
                                       	controlData_ptr->theta_cmd = 0;
                                        controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 2 && time < 4.5){
                                        controlData_ptr->theta_cmd = 5*D2R;
                                        controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 4.5 && time < 7){
                                        controlData_ptr->phi_cmd =      20*D2R;
                                        controlData_ptr->theta_cmd = 0;
                                }
                                if( time >= 7 && time < 9.5){
                                        controlData_ptr->theta_cmd = 5*D2R;
                                        controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 9.5 && time < 12){
                                        controlData_ptr->phi_cmd =      20*D2R;
                                        controlData_ptr->theta_cmd = 0;
                                }
	                                if( time >= 12 && time < 14.5){
                                         controlData_ptr->theta_cmd = -5*D2R;
                                         controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 14.5 && time < 17){
                                         controlData_ptr->phi_cmd =      -20*D2R;
                                         controlData_ptr->theta_cmd = 0;
                                }
								if( time >= 17 && time < 19.5){
                                         controlData_ptr->theta_cmd = -5*D2R;
                                         controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 19.5 && time < 22){
                                         controlData_ptr->phi_cmd =      -20*D2R;
                                         controlData_ptr->theta_cmd = 0;
                                }
                                if( time >= 22 && time < 30){
                                         controlData_ptr->theta_cmd = 0;
                                         controlData_ptr->phi_cmd =      0;
                                }
                                if( time >= 30){
                                         controlData_ptr->phi_cmd =      15*D2R;
                                         controlData_ptr->theta_cmd = 0;
                                }
                                break;
        }
}
