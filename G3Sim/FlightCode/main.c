/*! \file main.c
 *	\brief Main function, thread 0
 *
 *	\details The main function is here, which creates and runs all threads. It also
 *	is thread 0, the highest priority thread, which runs the primary avionics software
 *	modules.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: main.c 1006 2013-10-30 15:33:32Z brtaylor $
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <cyg/kernel/kapi.h>
#include <cyg/cpuload/cpuload.h>

#include "globaldefs.h"
#include "utils/misc.h"
#include "utils/scheduling.h"
#include "threads/threads.h"

// Interfaces
#include "sensors/AirData/airdata_interface.h"
#include "sensors/daq_interface.h"
#include "actuators/actuator_interface.h"
#include "navigation/nav_interface.h"
#include "researchNavigation/researchnav_interface.h"
#include "guidance/guidance_interface.h"
#include "control/control_interface.h"
#include "system_id/systemid_interface.h"
#include "faults/fault_interface.h"
#include "datalog/datalog_interface.h"
#include "telemetry/telemetry_interface.h"

#include AIRCRAFT

// External variable definition. Declared in extern_vars.h

// End extern_vars.h

// dataLog structure. External but used only in datalogger.c
struct datalog dataLog;

// Conditional variables. These are external but only used in scheduling.c
pthread_cond_t  trigger_daq, trigger_nav, trigger_guidance, trigger_sensfault, \
trigger_control, trigger_sysid, trigger_surffault, \
trigger_actuators,  trigger_datalogger, trigger_telemetry;


/// Main function, primary avionics functions, thread 0, highest priority.
int main(int argc, char **argv) {

	// Data Structures
	struct 	mission 		missionData;
	struct  nav   			navData;
	struct  nav   			tempNavData;
	struct  researchNav   	researchNavData;
	struct  control 		controlData;
	struct  imu   			imuData;
	struct  gps   			gpsData;
	struct  airdata 		adData;
	struct  surface 		surfData;
	struct  inceptor 		inceptorData;

	// Additional data structures for GPS FASER
	struct  gps   gpsData_l;
	struct  gps   gpsData_r;

	// sensor data
	struct sensordata sensorData;

	uint16_t cpuLoad;

	// Timing variables
	double etime_daq, etime_nav, etime_guidance, etime_sensfault, \
	etime_control, etime_sysid, etime_surffault, \
	etime_actuators, etime_datalog, etime_telemetry;

	// Include datalog definition
	#include DATALOG_CONFIG

	// Populate dataLog members with initial values
	dataLog.saveAsDoubleNames = &saveAsDoubleNames[0];
	dataLog.saveAsDoublePointers = &saveAsDoublePointers[0];
	dataLog.saveAsFloatNames = &saveAsFloatNames[0];
	dataLog.saveAsFloatPointers = &saveAsFloatPointers[0];
	dataLog.saveAsIntNames = &saveAsIntNames[0];
	dataLog.saveAsIntPointers = &saveAsIntPointers[0];
	dataLog.saveAsShortNames = &saveAsShortNames[0];
	dataLog.saveAsShortPointers = &saveAsShortPointers[0];
	dataLog.logArraySize = LOG_ARRAY_SIZE;
	dataLog.numDoubleVars = NUM_DOUBLE_VARS;
	dataLog.numFloatVars = NUM_FLOAT_VARS;
	dataLog.numIntVars = NUM_INT_VARS;
	dataLog.numShortVars = NUM_SHORT_VARS;

	double tic,time,t0=0;
	static int t0_latched = FALSE;
	int loop_counter = 0;
	pthread_mutex_t	mutex;

	uint32_t cpuCalibrationData, last100ms, last1s, last10s;
	cyg_cpuload_t cpuload;
	cyg_handle_t loadhandle;

	// Populate sensorData structure with pointers to data structures
	sensorData.imuData_ptr = &imuData;
	sensorData.gpsData_ptr = &gpsData;
	sensorData.gpsData_l_ptr = &gpsData_l;
	sensorData.gpsData_r_ptr = &gpsData_r;
	sensorData.adData_ptr = &adData;
	sensorData.surfData_ptr = &surfData;
	sensorData.inceptorData_ptr = &inceptorData;

	// Set main thread to highest priority
	struct sched_param param;
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);

	// Setup CPU load measurements
	cyg_cpuload_calibrate(&cpuCalibrationData);
	cyg_cpuload_create(&cpuload, cpuCalibrationData, &loadhandle);

	// Initialize set_actuators (PWM or serial) at zero
	init_actuators();
	set_actuators(&controlData);

	// Initialize mutex variable. Needed for pthread_cond_wait function
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);

	// initialize functions	
	init_daq(&sensorData, &navData, &controlData);
	init_telemetry();

	while(1){
		missionData.mode = 1; 						// initialize to manual mode
		missionData.run_num = 0; 					// reset run counter
		missionData.researchNav = 0;				// initialize to use standard nav filter in feedback
		navData.err_type = got_invalid;				// initialize nav filter as invalid
		researchNavData.err_type = got_invalid;		// initialize research nav filter as invalid

		//initialize real time clock at zero
		reset_Time();

		// Initialize scheduling
		init_scheduler();

		// start additional threads
		threads_create();

		// Initialize data logging
		init_datalogger();
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//main-loop
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		while (missionData.mode != 0) {

			loop_counter++; //.increment loop counter

			//**** DATA ACQUISITION **************************************************
			pthread_cond_wait (&trigger_daq, &mutex); // WAIT FOR DAQ ALARMS
			tic = get_Time();			
			get_daq(&sensorData, &navData, &controlData, &missionData);		
			etime_daq = get_Time() - tic - DAQ_OFFSET; // compute execution time
			//************************************************************************

			//**** NAVIGATION ********************************************************
			if(navData.err_type == got_invalid){ // check if NAV filter has been initialized

					//if(gpsData.navValid == 0) // check if GPS is locked, comment out if using micronav_ahrs

					init_nav(&sensorData, &navData, &controlData);// Initialize NAV filter
			}
			else
				get_nav(&sensorData, &navData, &controlData);// Call NAV filter
			
			//**** RESEARCH NAVIGATION ***********************************************
			if(researchNavData.err_type == got_invalid){ // check if research NAV filter has been initialized

					//if(gpsData.navValid == 0) // check if GPS is locked, comment out if using micronav_ahrs

					init_researchNav(&sensorData, &researchNavData);// Initialize research NAV filter
			}
			else
				get_researchNav(&sensorData, &researchNavData);// Call research NAV filter

			etime_nav = get_Time() - tic - etime_daq; // compute execution time			
			//************************************************************************

			if(missionData.researchNav == 1){	// use research nav filter for feedback
				memcpy(&tempNavData,&navData,sizeof(navData));					// copy nav data into temp struct
				memcpy(&navData,&researchNavData,sizeof(researchNavData));		// copy research nav data into nav data
			}

			if (missionData.mode == 2) { // autopilot mode
				if (t0_latched == FALSE) {
					t0 = get_Time();
					t0_latched = TRUE;
				}

				time = get_Time()-t0; // Time since in auto mode

				//**** GUIDANCE **********************************************************
				get_guidance(time, &sensorData, &navData, &controlData, &missionData);
				etime_guidance= get_Time() - tic - etime_nav - etime_daq; // compute execution time
				//************************************************************************		

				//**** SENSOR FAULT ******************************************************
				get_sensor_fault(time, &sensorData, &navData, &controlData);
				etime_sensfault = get_Time() - tic - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************

				//**** CONTROL ***********************************************************
				get_control(time, &sensorData, &navData, &controlData, &missionData);
				etime_control = get_Time() - tic - etime_sensfault - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************		

				//**** SYSTEM ID *********************************************************
				get_system_id(time, &sensorData, &navData, &controlData);
				etime_sysid = get_Time() - tic - etime_control - etime_sensfault - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************

				//**** SURACE FAULT ******************************************************
				get_surface_fault(time, &sensorData, &navData, &controlData);
				etime_surffault = get_Time() - tic - etime_sysid - etime_control - etime_sensfault - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************

			}
			else{
				if (t0_latched == TRUE) {				
					t0_latched = FALSE;
				}
				reset_control(&controlData); // reset controller states and set get_control surfaces to zero
			} // end if (controlData.mode == 2) 

			// Add trim biases to get_control surface commands
			add_trim_bias(&controlData);

			//**** ACTUATORS *********************************************************
			pthread_cond_wait (&trigger_actuators, &mutex);		   // WAIT FOR ACTUATOR ALARMS
			set_actuators(&controlData);
			etime_actuators = get_Time() - tic - ACTUATORS_OFFSET; // compute execution time
			//************************************************************************

			if(missionData.researchNav == 1){	// use research nav filter for feedback
				memcpy(&navData,&tempNavData,sizeof(tempNavData));					// copy nav data back for data logging
			}
			
			//**** DATA LOGGING ******************************************************
			datalogger();
			etime_datalog = get_Time() - tic - etime_actuators - ACTUATORS_OFFSET; // compute execution time
			//************************************************************************

			//**** TELEMETRY *********************************************************
			if(loop_counter >= BASE_HZ/TELEMETRY_HZ){
				loop_counter = 0;

				// get current cpu load
				cyg_cpuload_get (loadhandle, &last100ms, &last1s, &last10s);
				cpuLoad = (uint16_t)last100ms;

				send_telemetry(&sensorData, &navData, &controlData, &missionData, cpuLoad);
				
				etime_telemetry = get_Time() - tic - etime_datalog - etime_actuators - ACTUATORS_OFFSET; // compute execution time
			}
			//************************************************************************	

#ifndef HIL_SIM
			// Take zero on pressure sensors during first 10 seconds
			if (tic > 4.0 && tic < 10.0){
				airdata_bias_estimate(&adData);
			}
#endif
		} //end while (controlData.mode != 0)

		close_scheduler();
		close_datalogger(); // dump data

	} // end while(1)
	/**********************************************************************
	 * close
	 **********************************************************************/
	pthread_mutex_destroy(&mutex);
	close_actuators();	
	close_nav();

	return 0;

} // end main

