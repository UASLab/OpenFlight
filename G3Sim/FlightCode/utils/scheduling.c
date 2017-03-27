/*! \file scheduling.c
 *	\brief Scheduling functions.
 *
 *	\details This file creates and starts threads, alarms, and conditional variables used to control
 *	thread and function execution.
 *	\ingroup sched_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: scheduling.c 969 2013-04-12 22:06:43Z joh07594 $
 */
#include <pthread.h>
#include <cyg/kernel/kapi.h>

#include "../globaldefs.h"
#include "../extern_vars.h"
#include "scheduling.h"

static cyg_handle_t rtclock, rtc_counter;
static cyg_handle_t alarm_hdl[NUM_ALARMS];
static cyg_alarm alarm_obj[NUM_ALARMS];
static cyg_resolution_t rtc_resolution;

void init_scheduler(void)
{
	int rtc_ticks_per_sec;

	/* get handle to the system realtime clock */
	rtclock = cyg_real_time_clock ();
	rtc_resolution = cyg_clock_get_resolution ( rtclock );
	rtc_ticks_per_sec = rtc_resolution.divisor;
	cyg_clock_to_counter ( rtclock, &rtc_counter );
	
	// Real time clock frequency must be changed in eCos configuration, as there is another
	// macro that depends on its value.
	//fprintf ( stderr, "cyg_realtime_clock() resolution: dividend=%d, \t divisor=%d\n", rtc_resolution.dividend, rtc_resolution.divisor );

	// Create alarms
	cyg_alarm_create ( rtc_counter, alarm_handlerfn_daq,0,&alarm_hdl[0],&alarm_obj[0] );
	cyg_alarm_create ( rtc_counter, alarm_handlerfn_actuators,0,&alarm_hdl[1],&alarm_obj[1] );
	cyg_alarm_create ( rtc_counter, alarm_handlerfn_thread1,0,&alarm_hdl[2],&alarm_obj[2] );

	// Initialize conditional variables
	pthread_cond_init (&trigger_daq, NULL);
	pthread_cond_init (&trigger_actuators, NULL);
	pthread_cond_init (&trigger_thread1, NULL);

	// Start alarms
	// DAQ, executes at t0 + 0.0000
	cyg_alarm_initialize ( alarm_hdl[0], DAQ_OFFSET*rtc_ticks_per_sec, rtc_ticks_per_sec/BASE_HZ );
	
	// ACTUATORS, executes at t0 + 0.014
	cyg_alarm_initialize ( alarm_hdl[1], ACTUATORS_OFFSET*rtc_ticks_per_sec, rtc_ticks_per_sec/BASE_HZ);

	// Thread1, executes at t0 + 0.0130
	cyg_alarm_initialize ( alarm_hdl[2], THREAD1_OFFSET*rtc_ticks_per_sec, rtc_ticks_per_sec/THREAD1_HZ );

}

/* destroy alarm objects and pthread_cond objects */
void close_scheduler(void)
{
	int i;

	for (i=0; i<NUM_ALARMS; i++)
		cyg_alarm_delete (alarm_hdl[i]);

	pthread_cond_destroy (&trigger_daq);
	pthread_cond_destroy (&trigger_actuators);
	pthread_cond_destroy (&trigger_thread1);
}


/* alarm handler functions */
void alarm_handlerfn_daq ( cyg_handle_t alarm, cyg_addrword_t data ){pthread_cond_signal (&trigger_daq);}
void alarm_handlerfn_actuators ( cyg_handle_t alarm, cyg_addrword_t data ){pthread_cond_signal (&trigger_actuators);}
void alarm_handlerfn_thread1 ( cyg_handle_t alarm, cyg_addrword_t data ){pthread_cond_signal (&trigger_thread1);}

