/*! \file gpsfaser_datalog.h
 *	\brief GPS FASER data logging setup
 *
 *	\details Defines what variables are logged for the GPS FASER aircraft.
 *	\ingroup datalog_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: ibis_datalog.h 974 2013-04-12 22:21:48Z lie $
 */
#ifndef GPSFASER_DATALOG_H_
#define GPSFASER_DATALOG_H_

// Datalogging setup
#define LOG_ARRAY_SIZE 90000 ///< Number of data points in the logging array. 50 Hz * 60 sec/min * 30 minutes = 90000

#define NUM_DOUBLE_VARS 12	///< Number of variables that will be logged as doubles
#define NUM_FLOAT_VARS 57	///< Number of variables that will be logged as floats
#define NUM_INT_VARS 2		///< Number of variables that will be logged as ints
#define NUM_SHORT_VARS 5	///< Number of variables that will be logged as shorts

//Names of matlab variables MUST match pointers!!

/// char array of variable names for doubles
char* saveAsDoubleNames[NUM_DOUBLE_VARS] = {
		"lat", "lon","alt",
		"lat_l", "lon_l","alt_l",
		"lat_r", "lon_r","alt_r",
		"navlat", "navlon", "navalt"};

/// double pointer array to variables that will be saved as doubles
double* saveAsDoublePointers[NUM_DOUBLE_VARS] = {
		&gpsData.lat, &gpsData.lon, &gpsData.alt,
		&gpsData_l.lat, &gpsData_l.lon, &gpsData_l.alt,
		&gpsData_r.lat, &gpsData_r.lon, &gpsData_r.alt,
		&navData.lat, &navData.lon, &navData.alt};

/// char array of variable names for floats
char* saveAsFloatNames[NUM_FLOAT_VARS] = {
			"time",
			"p", "q", "r", 
			"ax", "ay", "az", 
			"hx", "hy", "hz",
			"h", "ias", 
			"Ps","Pd", 
			"vn", "ve", "vd",
			"GPS_TOW", 
			"navvn", "navve","navvd",
			"phi", "the", "psi",
			"p_bias", "q_bias", "r_bias",
			"ax_bias", "ay_bias", "az_bias",
			"pitch_ref", "roll_ref", 
			"de", "da_l", "da_r",
			"df_l", "df_r", "dr", "dthr",
			"de_pos","da_l_pos","da_r_pos","dr_pos",
			"l_alpha","r_alpha","l_beta","r_beta",
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
			&gpsData.vn, &gpsData.ve, &gpsData.vd, 
			&gpsData.GPS_TOW, 
			&navData.vn, &navData.ve, &navData.vd, 
			&navData.phi, &navData.the, &navData.psi,
			&navData.gb[0], &navData.gb[1], &navData.gb[2],
			&navData.ab[0], &navData.ab[1], &navData.ab[2],
			&controlData.theta_cmd, &controlData.phi_cmd, 
			&controlData.de, &controlData.da_l, &controlData.da_r, 
			&controlData.df_l, &controlData.df_r, &controlData.dr, &controlData.dthr,
			&surfData.de_pos, &surfData.da_l_pos, &surfData.da_r_pos, &surfData.dr_pos,
			&adData.l_alpha,&adData.r_alpha, &adData.l_beta, &adData.r_beta,
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

