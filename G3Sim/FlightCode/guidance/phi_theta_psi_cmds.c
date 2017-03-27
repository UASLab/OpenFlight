/*! \file phi_theta_psi_cmds.c
 *      \brief Guidance law to track various pitch and roll and yaw angle commands
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
#include <stdio.h>
#include <math.h>

#include "../globaldefs.h"
#include "../system_id/systemid_interface.h"
#include "guidance_interface.h"

//#include "../aircraft/thor_config.h"
//#include "../aircraft/ibis_config.h"
#include AIRCRAFT_UP1DIR

//local functions
static void filter_trim(double *filt_inp, struct control *controlData_ptr, double time);

/////////////// filters to compute real trim condition/////////////////////
//filtered surface control signals
static double da_filt_u[3]={AILERON_TRIM,0,0};
static double da_filt_y[3]={0,0,0};

static double de_filt_u[3]={ELEVATOR_TRIM,0,0};
static double de_filt_y[3]={0,0,0};

static double dr_filt_u[3]={RUDDER_TRIM,0,0};
static double dr_filt_y[3]={0,0,0};

static double dthr_filt_u[3]={THROTTLE_TRIM,0,0};
static double dthr_filt_y[3]={0,0,0};

//filter coefficients
static double b_filt[3]={ 0,   0.000197483985377198,   0.000194998290973465};
static double a_filt[3]={ 1.000000000000000,  -1.962320458614849,   0.962712940891200};

//order of filters
static int l=2; 

//filtered signals
static double filt_inp[4]={0,0,0,0};
///////////////////////////////////////////////////////////////////////////

#ifdef AIRCRAFT_THOR
    static double trim_vel=17;
#else
    static double trim_vel=23;
#endif
    
///////////////////doublet amplitudes//////////////////////////////////////
//AILERON
static double ail_amp_1=-8*D2R;
static double ail_amp_2=16*D2R;
static double ail_amp_3=-7.2*D2R;
//ELEVATOR
static double ele_amp_1=-12*D2R;
static double ele_amp_2=19*D2R;
static double ele_amp_3=-11*D2R;
//RUDDER
static double rud_amp_1=-16*D2R;
static double rud_amp_2=36*D2R;
static double rud_amp_3=-10*D2R;
///////////////////////////////////////////////////////////////////////////

//warming up the filters in SIL sim
//only SIL sim
//static int wtime=25;
//in flight mode
static int wtime=0;


//FILE *rudder;


extern void get_guidance(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr){
    int state=4;
    
    state=(missionData_ptr->run_num)%3; 
    
    //rudder = fopen("rudder.txt", "a");
    
   switch (state)
    {
        //phi doublet
        case 1:
            //closed loop control
            if( time >= (0) && time < (9.5+wtime))
            {
                controlData_ptr->psi_cmd=0;
                controlData_ptr->ias_cmd=trim_vel;
                controlData_ptr->h_cmd=0;
            }
            //filtering of surface signals start
            //only after warmup of the heading, speed filters
            if( time >= (wtime) && time < (9.5+wtime))
            {
                filter_trim(filt_inp, controlData_ptr, time);
            }
            //open loop control
            if(time >= (9.5+wtime) && time < (10+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }

            if( time >= (10+wtime) && time < (10.2+wtime))
            {
                controlData_ptr->da_r=ail_amp_1;
                controlData_ptr->da_l=-ail_amp_1;
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if( time >= (10.2+wtime) && time < (12+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if( time >= (12+wtime) && time < (12.2+wtime))
            {
                controlData_ptr->da_r=ail_amp_2;
                controlData_ptr->da_l=-ail_amp_2;
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (12.2+wtime) && time < (14+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (14+wtime) && time < (14.2+wtime))
            {
                controlData_ptr->da_r=ail_amp_3;
                controlData_ptr->da_l=-ail_amp_3;
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (14.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            // fclose(rudder);
            break;
    
            
           
          //theta doublet
        case 2: 
            //closed loop control
            if( time >= (0) && time < (9.5+wtime))
            {
                controlData_ptr->psi_cmd=0;
                controlData_ptr->ias_cmd=trim_vel;
                controlData_ptr->h_cmd=0;
            }
            //filtering of surface signals start
            //only after warmup of the heading, speed filters
            if( time >= (wtime) && time < (9.5+wtime))
            {
                filter_trim(filt_inp, controlData_ptr, time);
            }
            //open loop control
            if(time >= (9.5+wtime) && time < (10+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if( time >= (10+wtime) && time < (10.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=ele_amp_1;
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if( time >= (10.2+wtime) && time < (12+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if( time >= (12+wtime) && time < (12.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=ele_amp_2;
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (12.2+wtime) && time < (14+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (14+wtime) && time < (14.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=ele_amp_3;
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (14.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
			break;
    
            
        case 0: //psi doublet
            //closed loop control*/
            if( time >= (0) && time < (9.5+wtime))
            {
                controlData_ptr->psi_cmd=0;
                controlData_ptr->ias_cmd=trim_vel;
                controlData_ptr->h_cmd=0;
            }
            //filtering of surface signals start
            //only after warmup of the heading, speed filters
            if( time >= (wtime) && time < (9.5+wtime))
            {
                filter_trim(filt_inp, controlData_ptr, time);
            }
            //open loop control
            if(time >= (9.5+wtime) && time < (10+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if( time >= (10+wtime) && time < (10.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=rud_amp_1;
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (10.2+wtime) && time < (12+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if( time >= (12+wtime) && time < (12.4+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=rud_amp_2;
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (12.4+wtime) && time < (14+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (14+wtime) && time < (14.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=rud_amp_3;
                controlData_ptr->dthr=filt_inp[3];
            }
            if(time >= (14.2+wtime))
            {
                controlData_ptr->da_r=filt_inp[0];
                controlData_ptr->da_l=-filt_inp[0];
                controlData_ptr->de=filt_inp[1];
                controlData_ptr->dr=filt_inp[2];
                controlData_ptr->dthr=filt_inp[3];
            }
            break;
    }
    
    
    
    
}

void filter_trim (double *filt_inp, struct control *controlData_ptr, double time)
{

    int i=0;
    //double tt=time;
    
    // aileron filtering
    da_filt_u[l]=controlData_ptr->da_r;
	da_filt_y[l]=b_filt[0]*da_filt_u[l] + b_filt[1]*da_filt_u[l-1] + b_filt[2]*da_filt_u[l-2]- a_filt[1]*da_filt_y[l-1] - a_filt[2]*da_filt_y[l-2];
    
    // elevator filtering
    de_filt_u[l]=controlData_ptr->de;
	de_filt_y[l]=b_filt[0]*de_filt_u[l] + b_filt[1]*de_filt_u[l-1] + b_filt[2]*de_filt_u[l-2] - a_filt[1]*de_filt_y[l-1] - a_filt[2]*de_filt_y[l-2];
    
    // rudder filtering
    dr_filt_u[l]=controlData_ptr->dr;
	dr_filt_y[l]=b_filt[0]*dr_filt_u[l] + b_filt[1]*dr_filt_u[l-1] + b_filt[2]*dr_filt_u[l-2] - a_filt[1]*dr_filt_y[l-1] - a_filt[2]*dr_filt_y[l-2];

    // throttle filtering
    dthr_filt_u[l]=controlData_ptr->dthr;
	dthr_filt_y[l]=b_filt[0]*dthr_filt_u[l] + b_filt[1]*dthr_filt_u[l-1] + b_filt[2]*dthr_filt_u[l-2] - a_filt[1]*dthr_filt_y[l-1]- a_filt[2]*dthr_filt_y[l-2];

    //filtered value: will be used at 9.5
    filt_inp[0]=da_filt_y[l];
    filt_inp[1]=de_filt_y[l];
    filt_inp[2]=dr_filt_y[l];
    filt_inp[3]=dthr_filt_y[l];
    
    
    //fprintf(rudder, "%f\n %f\n",tt,filt_inp[2]);
    
    //update time history
    for (i=0; i<l; i++)
    {
        da_filt_u[i]=da_filt_u[i+1];
        da_filt_y[i]=da_filt_y[i+1];
        de_filt_u[i]=de_filt_u[i+1];
        de_filt_y[i]=de_filt_y[i+1];
        dr_filt_u[i]=dr_filt_u[i+1];
        dr_filt_y[i]=dr_filt_y[i+1];
        dthr_filt_u[i]=dthr_filt_u[i+1];
        dthr_filt_y[i]=dthr_filt_y[i+1];
    }
}
