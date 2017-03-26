/*! \file scheduling.h
 *	\brief Scheduling functions header
 *
 *	\details This file defines the number of alarms and threads, the time offset of each alarm, and the
 *	execution rate.
 *	\ingroup sched_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: scheduling.h 969 2013-04-12 22:06:43Z joh07594 $
 */

#ifndef SCHEDULING_H_
#define SCHEDULING_H_

#define NUM_ALARMS 3	///< Number of alarms

// Update rates
#define BASE_HZ 50		///< Base frequency of the main thread
#define TELEMETRY_HZ 25	///< Frequency of the telemetry function
#define THREAD1_HZ 10	///< Frequency of thread1

// Time offset of each alarm relative to the start of the BASE_HZ frame, units of sec
#define DAQ_OFFSET 			0.0000	///< [sec], time offset of daq() relative to the start of the BASE_HZ frame
#define ACTUATORS_OFFSET 	0.0140	///< [sec], time offset of actuators() relative to the start of the BASE_HZ frame
#define THREAD1_OFFSET	 	0.0130	///< [sec], time offset of thread1() relative to the start of the BASE_HZ frame

// Conditional variables, defined in main.c
extern pthread_cond_t  trigger_daq, \
				trigger_actuators, \
				trigger_thread1;

/*! \addtogroup sched_fcns
 * @{*/
/* function prototypes */
// Alarm handler functions
void alarm_handlerfn_daq ( cyg_handle_t alarm, cyg_addrword_t data );		///< daq() alarm handler function
void alarm_handlerfn_actuators ( cyg_handle_t alarm, cyg_addrword_t data );	///< actuators() alarm handler function
void alarm_handlerfn_thread1 ( cyg_handle_t alarm, cyg_addrword_t data );	///< thread1() alarm handler function

// scheduling functions
void close_scheduler(void);	///< Delete alarms and trigger variables
void init_scheduler(void);	///< Create and initialize alarms and initialize trigger variables

/*! @}*/
#endif
