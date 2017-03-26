/*! \file actuator_PWM.c
 *	\brief Functions for PWM set_actuators
 *
 *	\details This file contains functions for driving PWM actuators (servos) via the MPC5200B general purpose timers (GPT).
 *	\ingroup actuator_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: actuator_PWM.c 781 2012-03-15 16:09:37Z murch $
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <cyg/posix/pthread.h>
#include <cyg/kernel/kapi.h>
#include <cyg/cpuload/cpuload.h>
#include <cyg/gpt/mpc5xxx_gpt.h>
#include <cyg/io/mpc5xxx_gpio.h>
#include <cyg/io/i2c_mpc5xxx.h>
#include <cyg/io/io.h>
#include <cyg/io/serialio.h>

#include "../globaldefs.h"
#include "../utils/misc.h"
#include "actuator_interface.h"
#include AIRCRAFT_UP1DIR

/// Absolute limits for PWM output.
/// Note that most servos can respond to commands outside this range, but it is unlikely that commands outside this range will be valid.
#define PWMOUT_1MSEC 2720	///< GPT value corresponding to 1 msec PWM
#define PWMOUT_2MSEC 5440	///< GPT value corresponding to 2 msec PWM

/// Arrays of calibration coefficients using macros defined in aircraft/XXX_config.h.
static double dthr_cal[] = PWMOUT_DTHR_CAL;
static double de_cal[]   = PWMOUT_DE_CAL;
static double dr_cal[]   = PWMOUT_DR_CAL;
static double da_l_cal[] = PWMOUT_DA_L_CAL;
static double da_r_cal[] = PWMOUT_DA_R_CAL;
static double df_l_cal[] = PWMOUT_DF_L_CAL;
static double df_r_cal[] = PWMOUT_DF_R_CAL;

/// Compute order of polynomial calibration (length of array - 1)
static int dthr_ord = sizeof(dthr_cal)/sizeof(*dthr_cal) - 1;
static int de_ord   = sizeof(de_cal)/sizeof(*de_cal) - 1;
static int dr_ord   = sizeof(dr_cal)/sizeof(*dr_cal) - 1;
static int da_l_ord = sizeof(da_l_cal)/sizeof(*da_l_cal) - 1;
static int da_r_ord = sizeof(da_r_cal)/sizeof(*da_r_cal) - 1;
static int df_l_ord = sizeof(df_l_cal)/sizeof(*df_l_cal) - 1;
static int df_r_ord = sizeof(df_r_cal)/sizeof(*df_r_cal) - 1;

/// commands in counts
static double dthr_cnts = 0;
static double de_cnts = 0;
static double dr_cnts = 0;
static double da_l_cnts = 0;
static double da_r_cnts = 0;
static double df_l_cnts = 0;
static double df_r_cnts = 0;

extern void init_actuators(){
	int i;
	
	// initialize PWM I/O channels
	GPT_Init();
	
	// PWM Output
	for(i=0;i<8;i++)
		if( GPT_Open_PWM(i) < 0) fprintf(stderr, "\n GPT_Open_PWM() failed Ch. %d",i);	
}

// Return control outputs based on references and feedback signals.
extern void set_actuators(struct control *controlData_ptr) {
	
	// Enforce surface limits and apply calibration
	dthr_cnts = polyval(dthr_cal, saturation(controlData_ptr->dthr,THROTTLE_MIN,THROTTLE_MAX),dthr_ord);
	de_cnts   = polyval(de_cal, saturation(controlData_ptr->de,ELEVATOR_MIN,ELEVATOR_MAX),de_ord);
	dr_cnts   = polyval(dr_cal, saturation(controlData_ptr->dr,RUDDER_MIN,RUDDER_MAX),dr_ord);
	da_l_cnts = polyval(da_l_cal, saturation(controlData_ptr->da_l,L_AILERON_MIN,L_AILERON_MAX),da_l_ord);
	da_r_cnts = polyval(da_r_cal, saturation(controlData_ptr->da_r,R_AILERON_MIN,R_AILERON_MAX),da_r_ord);
	df_l_cnts = polyval(df_l_cal, saturation(controlData_ptr->df_l,L_FLAP_MIN,L_FLAP_MAX), df_l_ord);
	df_r_cnts = polyval(df_r_cal, saturation(controlData_ptr->df_r,R_FLAP_MIN,R_FLAP_MAX), df_r_ord);	
	
	// Enforce absolute PWM limits for servos and write to mpc5200 PWM channels
	GPT_PWM_Write_Width(PWMOUT_DTHR_CH,  (uint16_t) saturation(dthr_cnts,PWMOUT_1MSEC,PWMOUT_2MSEC));// throttle
	GPT_PWM_Write_Width(PWMOUT_DE_CH,  (uint16_t) saturation(de_cnts,PWMOUT_1MSEC,PWMOUT_2MSEC)); // elevator
	GPT_PWM_Write_Width(PWMOUT_DR_CH,    (uint16_t) saturation(dr_cnts,PWMOUT_1MSEC,PWMOUT_2MSEC)); // rudder
	GPT_PWM_Write_Width(PWMOUT_DA_L_CH, (uint16_t) saturation(da_l_cnts,PWMOUT_1MSEC,PWMOUT_2MSEC)); // left aileron
	GPT_PWM_Write_Width(PWMOUT_DA_R_CH, (uint16_t) saturation(da_r_cnts,PWMOUT_1MSEC,PWMOUT_2MSEC)); // right aileron
	GPT_PWM_Write_Width(PWMOUT_DF_L_CH,    (uint16_t) saturation(df_l_cnts,PWMOUT_1MSEC,PWMOUT_2MSEC)); // left flap
	GPT_PWM_Write_Width(PWMOUT_DF_R_CH,    (uint16_t) saturation(df_r_cnts,PWMOUT_1MSEC,PWMOUT_2MSEC)); // right flap
}


extern void close_actuators(){
	int i;
	
	// PWM Output
	for(i=0;i<8;i++)
		GPT_PWM_Exit(i);
}
