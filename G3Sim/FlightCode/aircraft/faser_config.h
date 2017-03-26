/*! \file faser_config.h
 *	\brief Configuration defines for the FASER aircraft.
 *
 *	\details This file contains the geometry, surface calibrations and limits, and serial port configuration for the FASER aircraft.
 *	\ingroup aircraft_cfg
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: faser_config.h 1010 2013-11-27 16:13:09Z brtaylor $
 */

#ifndef FASER_CONFIG_H_
#define FASER_CONFIG_H_

#define AIRCRAFT_FASER	///< Aircraft name. Used in daq() for sensor processing.

// GPS Sensor Configuration
#define GPS_PORT 		SERIAL_PORT2	///< Serial port for GPS receiver, used in init_daq()
#define GPS_BAUDRATE	B115200			///< Baud rate of serial port for GPS receiver, used in init_daq()

// Downlink telemetry configuration
#define TELEMETRY_PORT SERIAL_PORT3		///< Serial port for telemetry()
#define TELEMETRY_BAUDRATE B115200		///< Baud rate of serial port for telemetry()

// Set geometry values to zero to 'disable' the rate corrections for now. AMM 9/12/11
// Geometry Data for Left Air Data Vane
#define L_VANE_ALPHA_BIAS    0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define L_VANE_BETA_BIAS     0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define L_VANE2CG_X     0.00 ///< [m], position of vane relative to cg, in body axis frame  0.475
#define L_VANE2CG_Y	    0.00 ///< [m], position of vane relative to cg, in body axis frame -0.999
#define L_VANE2CG_Z		0.00 ///< [m], position of vane relative to cg, in body axis frame -0.070 est

// Geometry Data for Right Air Data Vane
#define R_VANE_ALPHA_BIAS    0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define R_VANE_BETA_BIAS     0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define R_VANE2CG_X     0.00 ///< [m], position of vane relative to cg, in body axis frame  0.480
#define R_VANE2CG_Y		0.00 ///< [m], position of vane relative to cg, in body axis frame  0.982
#define R_VANE2CG_Z		0.00 ///< [m], position of vane relative to cg, in body axis frame -0.070 est

// Calibration data for Left Air Data Vane
#define L_ALPHA1_SLOPE -0.0014576	///< [rad/count]
#define L_ALPHA2_SLOPE	1.0  		///< [rad/count]
#define L_BETA_SLOPE   -0.0010477	///< [rad/count]
#define L_ALPHA1_BIAS	2.3797		///< [rad]
#define L_ALPHA2_BIAS	0.0			///< [rad]
#define L_BETA_BIAS		1.5206		///< [rad]

// Calibration data for Right Air Data Vane
#define R_ALPHA1_SLOPE	0.0013434	///< [rad/count]
#define R_ALPHA2_SLOPE	1.0			///< [rad/count]
#define R_BETA_SLOPE	0.00086635	///< [rad/count]
#define R_ALPHA1_BIAS  -2.1523		///< [rad]
#define R_ALPHA2_BIAS   0.0			///< [rad]
#define R_BETA_BIAS	   -1.3216		///< [rad]

// Geometry Data for Air Data Probe
#define PITOT_ALPHA_BIAS  0.0611 ///< [rad], pitch angular offset of 5-hole pitot probe. Positive downwards from level
#define PITOT_BETA_BIAS   0.0    ///< [rad], lateral angular offset of 5-hole pitot probe. Positive right from centerline
#define PITOT2CG_X      0.18 ///< [m], position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Y		0.36 ///< [m], position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Z		0.00 ///< [m], position of pitot probe relative to cg, in body axis frame

// Control Surface Trims, from faser_flight01
#define THROTTLE_TRIM   0.65 ///< [ND], approximate throttle trim value
#define ELEVATOR_TRIM  -0.09 ///< [rad], approximate elevator trim value
#define RUDDER_TRIM     0.0  ///< [rad], approximate rudder trim value
#define AILERON_TRIM   -0.06 ///< [rad], approximate aileron trim value

// Control Surface Limits, max and min
#define 	THROTTLE_MAX 	 1.0
#define		THROTTLE_MIN	 0.0
#define		RUDDER_MAX		 0.4363	///< [rad], 25deg
#define		RUDDER_MIN		-0.4363 ///< [rad],-25deg
#define		ELEVATOR_MAX	 0.4363	///< [rad], 25deg
#define		ELEVATOR_MIN	-0.4363 ///< [rad],-25deg
#define 	L_AILERON_MAX	 0.4363	///< [rad], 25deg
#define 	L_AILERON_MIN	-0.4363 ///< [rad],-25deg
#define 	R_AILERON_MAX	 0.4363	///< [rad], 25deg
#define 	R_AILERON_MIN	-0.4363 ///< [rad],-25deg
#define 	L_FLAP_MAX	 	 0.4363	///< [rad], 25deg
#define 	L_FLAP_MIN		-0.4363 ///< [rad],-25deg
#define 	R_FLAP_MAX	 	 0.4363	///< [rad], 25deg
#define 	R_FLAP_MIN		-0.4363	///< [rad],-25deg

// MPC5200 PWM output channel assignments
#define PWMOUT_DTHR_CH  0 ///<  PWM output channel for throttle
#define PWMOUT_DE_CH  	1 ///<  PWM output channel for elevator
#define PWMOUT_DR_CH 	2 ///<  PWM output channel for rudder
#define PWMOUT_DA_L_CH 	3 ///<  PWM output channel for left aileron
#define PWMOUT_DA_R_CH 	4 ///<  PWM output channel for right aileron
#define PWMOUT_DF_L_CH 	5 ///<  PWM output channel for left flap
#define PWMOUT_DF_R_CH	7 ///<  PWM output channel for right flap

// MPC5200 PWM output command calibration parameters
#define PWMOUT_DTHR_CAL {2087,3033} ///< linear calibration for throttle, based on measured PWM throttle output
//#define PWMOUT_DE_CAL  	{ 1317.37945687615,	-442.259730472931,	 2432.51859623459,	4196.57630248332} ///< cubic calibration for elevator
//#define PWMOUT_DR_CAL   { 1548.76770164177,	-207.045721189461,	 2519.23293218565,	4294.87122699444} ///< cubic calibration for rudder
//#define PWMOUT_DA_L_CAL {-585.723108619247,	 131.344664590248,	-2187.59477454932,	3983.81329326738} ///< cubic calibration for left aileron
//#define PWMOUT_DA_R_CAL { 706.611899009660,	 30.1160387222872,	 2084.18729719452,	4224.48154557623} ///< cubic calibration for right aileron
//#define PWMOUT_DF_L_CAL { 669.922549029913,	-274.742499419611,	 2104.43391794454,	4084.46591981653} ///< cubic calibration for left flap
//#define PWMOUT_DF_R_CAL { 604.673566937238,	 30.9742821196296,	 2188.46811254913,	4086.38349458180} ///< cubic calibration for right flap
#define PWMOUT_DE_CAL  	{ -1020.3, 	-315.09,   -2288.7, 	4118.4} ///< cubic calibration for elevator
#define PWMOUT_DR_CAL   { -717.21, 	  52.22,   -2261.8, 	4177.7} ///< cubic calibration for rudder
#define PWMOUT_DA_L_CAL { -1331.0, 	 540.57,   -2185.0, 	4065.5} ///< cubic calibration for left aileron
#define PWMOUT_DA_R_CAL {  121.7, 	-444.08,    2447.3, 	4371.7} ///< cubic calibration for right aileron
#define PWMOUT_DF_R_CAL { 769.88, 	 -199.77,   2375.6, 	4094.6} ///< cubic calibration for right flap
#define PWMOUT_DF_L_CAL { 769.88, 	 -199.77,   2375.6, 	4094.6} ///< cubic calibration for right flap

// Pilot inceptor channels
#define THR_INCP_CH		1 ///<  input channel for pilot throttle inceptor
#define PITCH_INCP_CH	2 ///<  input channel for pilot pitch inceptor
#define YAW_INCP_CH		0 ///<  input channel for pilot yaw inceptor
#define ROLL_INCP_CH	3 ///<  input channel for pilot roll inceptor

// Pilot inceptor calibration parameters
#define PWMIN_SCALING 10000 	///< scaling parameter to apply to PWM readings prior to applying calibration
#define THR_INCP_CAL	{0.00098716683119, -2.527147087857848}	///<  linear calibration for pilot throttle inceptor
#define PITCH_INCP_CAL	{-111.529886096001,	96.8294668116000,	-21.5238268564487,	0.763949002413993}	///<  linear calibration for pilot pitch inceptor
#define YAW_INCP_CAL	{84.7756193670826,	-76.8786260771467,	17.1754736690082,	-0.535104948804940}	///<  linear calibration for pilot yaw inceptor
#define ROLL_INCP_CAL	{-42.3502385103704,	40.4850850262976,	-6.72738032331522,	-0.496271142735041}	///<  linear calibration for pilot roll inceptor


// Control surface positions calibration parameters
#define DE_SLOPE	1.0
#define DR_SLOPE	1.0 //0.00010534
#define DA_L_SLOPE	1.0
#define DA_R_SLOPE	1.0
#define DF_L_SLOPE	1.0
#define DF_R_SLOPE	1.0

#define DE_BIAS		0.0
#define DR_BIAS		0.0 //-4.7942
#define DA_L_BIAS	0.0
#define DA_R_BIAS	0.0
#define DF_L_BIAS	0.0
#define DF_R_BIAS	0.0

#endif	
