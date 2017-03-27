/*! \file AMS_pressure.h
 *	\brief Header file for AMS pressure sensors.
 *
 *	\details This file defines parameters for reading the AMS pressure sensors
 *	\ingroup airdata_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: AMS_pressure.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef AMS_PRESSURE_H_
#define AMS_PRESSURE_H_

/// Local generic function for reading AMS pressure sensors. Returns 1 if successful, 0 otherwise.
static int	read_AMS_sensor(cyg_i2c_device* device,	///< Pointer to I2C device structure
		double* pressure_data,	///< Pointer to variable where pressure data will be returned.
		double p_min,	///< [PSI], Minimum pressure
		double p_max	///< [PSI], Maximum pressure
);

#define P_MIN_COUNTS  3277 	 ///< 10% of full scale digital range
#define P_MAX_COUNTS  29491  ///< 90% of full scale digital range

//The addresses labeled on the sensors need to have a 1 tacked onto the end; or shift once and add one
/// Differential pressure sensor, unidirectional
static	cyg_i2c_device AMS5812_0003D = {
		.i2c_bus		  = &mpc5200_i2c_bus0,
		.i2c_address	  = 0x07,
		.i2c_flags      = 0x00,
		.i2c_delay      = CYG_I2C_DEFAULT_DELAY
};
/// Absolute pressure sensor
static	cyg_i2c_device AMS5812_0150B = {
		.i2c_bus		  = &mpc5200_i2c_bus0,
		.i2c_address	  = 0x05,
		.i2c_flags      = 0x00,
		.i2c_delay      = CYG_I2C_DEFAULT_DELAY
};

/// Differential pressure sensor, bidirectional, for angle of attack (aoa)
static	cyg_i2c_device AMS5812_0003DB_1 = {
		.i2c_bus		  = &mpc5200_i2c_bus0,
		.i2c_address	  = 0x09,
		.i2c_flags      = 0x00,
		.i2c_delay      = CYG_I2C_DEFAULT_DELAY
};
/// Differential pressure sensor, bidirectional, for sideslip (aos)
static	cyg_i2c_device AMS5812_0003DB_2 = {
		.i2c_bus		  = &mpc5200_i2c_bus0,
		.i2c_address	  = 0x0B,
		.i2c_flags      = 0x00,
		.i2c_delay      = CYG_I2C_DEFAULT_DELAY
};

#endif

