/*! \file actuator_serial.c
 *	\brief Functions for serial set_actuators (HIL sim)
 *
 *	\details This file contains functions for driving actuators via the serial port. This is for the HIL simulation.
 *	\ingroup actuator_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: actuator_serial.c 1030 2014-05-21 20:23:20Z brtaylor $
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
#include "../extern_vars.h"
#include "../utils/misc.h"
#include "../utils/serial_mpc5200.h"

#include "actuator_interface.h"
#include AIRCRAFT_UP1DIR


//static unsigned char control_data[60];

extern void init_actuators(){
	
	hilPort = open_serial(HIL_PORT,HIL_BAUDRATE);
	
}

// Return control outputs based on references and feedback signals.
extern void set_actuators(struct control * controlData_ptr) {
	double controls[10];
	uint8_t header[3];
	header[0] = 171;
	header[1] = 171;
	header[2] = 170;
			
	// Enforce surface limits
	controls[0] = saturation(controlData_ptr->dthr,THROTTLE_MIN,THROTTLE_MAX);
	controls[1] = saturation(controlData_ptr->de,ELEVATOR_MIN,ELEVATOR_MAX);
	controls[2] = saturation(controlData_ptr->dr,RUDDER_MIN,RUDDER_MAX);
	controls[3] = saturation(controlData_ptr->da_l,L_AILERON_MIN,L_AILERON_MAX);
	controls[4] = saturation(controlData_ptr->da_r,R_AILERON_MIN,R_AILERON_MAX);
	controls[5] = saturation(controlData_ptr->df_l,L_FLAP_MIN,L_FLAP_MAX);
	controls[6] = saturation(controlData_ptr->df_r,R_FLAP_MIN,R_FLAP_MAX);	

	write(hilPort,&header,3);
	write(hilPort,&controls,sizeof(controls));

}


extern void close_actuators(){
	
}
