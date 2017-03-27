/*! \file thor_config.h
 *	\brief Configuration defines for the Thor aircraft.
 *
 *	\details This file contains the geometry, surface calibrations and limits, and serial port configuration for the Thor aircraft.
 *	\ingroup aircraft_cfg
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: thor_config.h 1010 2013-11-27 16:13:09Z brtaylor $
 */
#ifndef THOR_CONFIG_H_
#define THOR_CONFIG_H_

#define AIRCRAFT_THOR	///< Aircraft name. Used in daq() for sensor processing.

// GPS Sensor Configuration
#define GPS_PORT 		SERIAL_PORT2	///< Serial port for GPS receiver, used in init_daq()
//#define GPS_BAUDRATE	B57600			///< Baud rate of serial port for GPS receiver (sirf), used in init_daq()
#define GPS_BAUDRATE	B115200			///< Baud rate of serial port for GPS receiver (crescent), used in init_daq()

// Downlink telemetry configuration
#define TELEMETRY_PORT 		SERIAL_PORT3	///< Serial port for telemetry()
#define TELEMETRY_BAUDRATE	B115200			///< Baud rate of serial port for telemetry()

// Geometry Data for Air Data Probe
#define PITOT_ALPHA_BIAS	0.0611	///< [rad], pitch angular offset of 5-hole pitot probe. Positive downwards from level
#define PITOT_BETA_BIAS		0.0     ///< [rad], lateral angular offset of 5-hole pitot probe. Positive right from centerline
#define PITOT2CG_X      	0.18 	///< m, position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Y			0.36 	///< m, position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Z			0.00 	///< m, position of pitot probe relative to cg, in body axis frame

// Control Surface Trims, from Thor flight 26
#define THROTTLE_TRIM   0.7		///< [ND], approximate throttle trim value
#define ELEVATOR_TRIM  -0.0384 	///< [rad], approximate elevator trim value
#define RUDDER_TRIM     0.0 	///< [rad], approximate rudder trim value
#define AILERON_TRIM    0.0168 	///< [rad], approximate aileron trim value

// Control Surface limits, max and min
#define THROTTLE_MAX 	 1.0
#define	THROTTLE_MIN	 0.0
#define	RUDDER_MAX		 0.4363	///< [rad], 25deg
#define	RUDDER_MIN		-0.4363 ///< [rad],-25deg
#define	ELEVATOR_MAX	 0.4363	///< [rad], 25deg
#define	ELEVATOR_MIN	-0.4363 ///< [rad],-25deg
#define L_AILERON_MAX	 0.4363	///< [rad], 25deg
#define L_AILERON_MIN	-0.4363 ///< [rad],-25deg
#define R_AILERON_MAX	 0.4363	///< [rad], 25deg
#define R_AILERON_MIN	-0.4363 ///< [rad],-25deg
#define L_FLAP_MAX	 	 0.4363	///< [rad], 25deg
#define L_FLAP_MIN		-0.4363 ///< [rad],-25deg
#define R_FLAP_MAX	 	 0.4363	///< [rad], 25deg
#define R_FLAP_MIN		-0.4363	///< [rad],-25deg

// MPC5200 PWM output channel assignments
#define PWMOUT_DTHR_CH  0 ///<  PWM output channel for throttle
#define PWMOUT_DE_CH  	1 ///<  PWM output channel for elevator
#define PWMOUT_DR_CH 	2 ///<  PWM output channel for rudder
#define PWMOUT_DA_L_CH 	3 ///<  PWM output channel for left aileron
#define PWMOUT_DA_R_CH 	4 ///<  PWM output channel for right aileron
#define PWMOUT_DF_L_CH 	5 ///<  PWM output channel for left flap
#define PWMOUT_DF_R_CH	7 ///<  PWM output channel for right flap

// MPC5200 PWM output command calibration parameters
#define PWMOUT_DTHR_CAL {1382,3514} ///< linear calibration for throttle, pwm 1.292ms (motor off) to 1.800ms (100% pwr), from ESC data. Note motor on value is 1.307ms Register values from MPC Servo Calibration.xls
#define PWMOUT_DE_CAL  	{1075.63465824760,	 185.611960006573,	 2023.61918461103,	4108.79708439429} ///< cubic calibration for elevator
#define PWMOUT_DR_CAL   {-873.608474846767,	-76.7078079059140,	-2254.76860585121,	4061.11563331261} ///< cubic calibration for rudder
#define PWMOUT_DA_L_CAL { 448.065668067557,	-134.588413507546,	 2219.91395005105,	4097.07246134070} ///< cubic calibration for left aileron
#define PWMOUT_DA_R_CAL {-852.084014726818,	 388.761704211881, 	-2282.75508774737,	4213.26481947031} ///< cubic calibration for right aileron
#define PWMOUT_DF_L_CAL {-676.533744524781,	 62.7674173105140, 	-2347.35886059335,	4209.47518913451} ///< cubic calibration for left flap
#define PWMOUT_DF_R_CAL { 799.012085234482,	-539.710268536236,	 2170.91649412790,	4119.76211378153} ///< cubic calibration for right flap

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

#endif	
