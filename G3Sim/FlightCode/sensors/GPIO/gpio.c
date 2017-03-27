/*! \file gpio.c
 *	\brief GPIO file for MPC5200B
 *
 *	\details This file implements the init_gpio() and read_gpio() functions for the MPC5200B.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gpio.c 888 2012-08-20 22:59:41Z joh07594 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cyg/io/mpc5xxx_gpio.h>

#include "../../globaldefs.h"
#include "../../extern_vars.h"
#include "../../utils/misc.h"
#include "gpio_interface.h"

void init_gpio(void)
{
	/* Init GPIO channels */
// WKUP	
	GPIO_GPW_EnableGPIO (MPC5XXX_GPW_GPIO_WKUP_7, GPIO_ENABLE_CHANNEL);
	GPIO_GPW_SetDirection (MPC5XXX_GPW_GPIO_WKUP_7, GPIO_DR_INPUT);
	
	GPIO_GPW_EnableGPIO (MPC5XXX_GPW_GPIO_WKUP_6, GPIO_ENABLE_CHANNEL);
	GPIO_GPW_SetDirection (MPC5XXX_GPW_GPIO_WKUP_6, GPIO_DR_INPUT);
	
// GPS
	//GPIO_GPS_EnableChannel(MPC5XXX_GPS_PSC1_2,GPIO_ENABLE_CHANNEL); // adcube reset
	//GPIO_GPS_SetDirection(MPC5XXX_GPS_PSC1_2,GPIO_DR_OUTPUT);
	
	GPIO_GPS_EnableChannel(MPC5XXX_GPS_PSC3_6,GPIO_ENABLE_CHANNEL);
	GPIO_GPS_SetDirection(MPC5XXX_GPS_PSC3_6,GPIO_DR_OUTPUT);
	
	GPIO_GPS_EnableChannel(MPC5XXX_GPS_PSC3_7,GPIO_ENABLE_CHANNEL);
	GPIO_GPS_SetDirection(MPC5XXX_GPS_PSC3_7,GPIO_DR_OUTPUT);	
	
	GPIO_GPS_EnableChannel(MPC5XXX_GPS_USB1_0,GPIO_ENABLE_CHANNEL);
	GPIO_GPS_SetDirection(MPC5XXX_GPS_USB1_0,GPIO_DR_OUTPUT);		
	
// Int	
	GPIO_Int_EnableGPIO(MPC5XXX_GPIO_INT_PSC3_8,GPIO_ENABLE_CHANNEL);
	GPIO_Int_SetDirection(MPC5XXX_GPIO_INT_PSC3_8,GPIO_DR_OUTPUT);	
	
	GPIO_Int_EnableGPIO(MPC5XXX_GPIO_INT_USB1_9,GPIO_ENABLE_CHANNEL);
	GPIO_Int_SetDirection(MPC5XXX_GPIO_INT_USB1_9,GPIO_DR_OUTPUT);	

// GPW	
	GPIO_GPW_EnableGPIO(MPC5XXX_GPW_PSC3_9,GPIO_ENABLE_CHANNEL);
	GPIO_GPW_SetDirection(MPC5XXX_GPW_PSC3_9,GPIO_DR_OUTPUT);	
	
}

void read_gpio(struct mission *missionData_ptr){
	static int delay =0;
	// control mode
	if(GPIO_GPW_GetInputStatus(MPC5XXX_GPW_GPIO_WKUP_6) == 1){
		if(missionData_ptr->mode==1){
			missionData_ptr->run_num++;

		}

		missionData_ptr->mode = 2; // autopilot

	}
	else{
		missionData_ptr->mode = 1; // manual
	}
	
	// data dump
	// check if trigger has arrived for data transfer / OFP termination
	if (GPIO_GPW_GetInputStatus(MPC5XXX_GPW_GPIO_WKUP_7) == 1) {
		if (++delay > 50){
			missionData_ptr->mode = 0; // datadump
			delay = 0;
		}
	}

}
