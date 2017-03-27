/*! \file standard_datalog.h
 *	\brief Standard data logging setup
 *
 *	\details Defines what variables are logged for the standard UAV or PIL simulation.
 *	\ingroup datalog_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: standard_datalog.h 936 2013-01-04 17:00:37Z joh07594 $
 */
#ifndef STANDARD_DATALOG_H_
#define STANDARD_DATALOG_H_

// Datalogging setup
#define LOG_ARRAY_SIZE 90000 ///< Number of data points in the logging array. 50 Hz * 60 sec/min * 30 minutes = 90000

#define NUM_DOUBLE_VARS 0	///< Number of variables that will be logged as doubles
#define NUM_FLOAT_VARS 55	///< Number of variables that will be logged as floats
#define NUM_INT_VARS 2		///< Number of variables that will be logged as ints
#define NUM_SHORT_VARS 5	///< Number of variables that will be logged as shorts

//Names of matlab variables MUST match pointers!!

/// char array of variable names for doubles
char* saveAsDoubleNames[NUM_DOUBLE_VARS] = {};

/// double pointer array to variables that will be saved as doubles
double* saveAsDoublePointers[NUM_DOUBLE_VARS] = {};

/// char array of variable names for floats
char* saveAsFloatNames[NUM_FLOAT_VARS] = {
			"time",
			"p", "q", "r", 
			"ax", "ay", "az", 
			"hx", "hy", "hz",
			"h", "ias", 
			"Ps","Pd", 
			"lat", "lon","alt", 
			"vn", "ve", "vd",
			"phi", "the", "psi",
			"p_bias", "q_bias", "r_bias",
			"ax_bias", "ay_bias", "az_bias",
			"GPS_TOW", 
			"navlat", "navlon", "navalt", 
			"navvn", "navve","navvd",
			"pitch_ref", "roll_ref", 
			"de", "da_l", "da_r",
			"df_l", "df_r", "dr", "dthr",
			"etime_daq", "etime_nav", "etime_guidance",
			"etime_sensfault","etime_control", "etime_sysid",
			"etime_surffault","etime_actuators","etime_datalog","etime_telemetry"};
								
/// double pointer array to variables that will be saved as floats
double* saveAsFloatPointers[NUM_FLOAT_VARS] = {
			&imuData.time,
			&imuData.p, &imuData.q, &imuData.r,
			&imuData.ax, &imuData.ay, &imuData.az,
			&imuData.hx, &imuData.hy, &imuData.hz,
			&adData.h, &adData.ias, 
			&adData.Ps, &adData.Pd, 				
			&gpsData.lat, &gpsData.lon, &gpsData.alt, 
			&gpsData.vn, &gpsData.ve, &gpsData.vd, 
			&navData.phi, &navData.the, &navData.psi,
			&navData.gb[0], &navData.gb[1], &navData.gb[2],
			&navData.ab[0], &navData.ab[1], &navData.ab[2],
			&gpsData.GPS_TOW, 
			&navData.lat, &navData.lon, &navData.alt, 
			&navData.vn, &navData.ve, &navData.vd, 
			&controlData.theta_cmd, &controlData.phi_cmd, 
			&controlData.de, &controlData.da_l, &controlData.da_r, 
			&controlData.df_l, &controlData.df_r, &controlData.dr, &controlData.dthr,
			&etime_daq, &etime_nav, &etime_guidance,
			&etime_sensfault, &etime_control, &etime_sysid,
			&etime_surffault, &etime_actuators, &etime_datalog, &etime_telemetry};

/// char array of variable names for ints
char* saveAsIntNames[NUM_INT_VARS] = {"imuStatus","gpsStatus"};

/// int32_t pointer array to variables that will be saved as ints
int32_t* saveAsIntPointers[NUM_INT_VARS] = {(int32_t *)&imuData.err_type,(int32_t *)&gpsData.err_type};


/// char array of variable names for shorts
char* saveAsShortNames[NUM_SHORT_VARS] = {"mode", "satVisible", "navValid","cpuLoad","adStatus"};

/// uint16_t pointer array to variables that will be saved as shorts
uint16_t* saveAsShortPointers[NUM_SHORT_VARS] = {&missionData.mode, &gpsData.satVisible,
												  &gpsData.navValid,&cpuLoad,&adData.status};	


#endif	

