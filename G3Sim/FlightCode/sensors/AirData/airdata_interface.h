/*! \file airdata_interface.h
 *	\brief Air data sensor interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with air data sensors.
 *	All air data sensor code must include this file and implement the init_airdata() and read_airdata() functions.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: telemetry_interface.h 749 2011-12-19 18:49:35Z murch $
 */

#ifndef AIRDATA_INTERFACE_H_
#define AIRDATA_INTERFACE_H_

/// Standard function to initialize the air data sensors.
/*!
 * No input parameters or return value.
 * \sa read_airdata()
 * \ingroup airdata_fcns
*/
void init_airdata();

/// Standard function to read the air data sensors.
/*!
 * Returns a status bitfield.
 * \sa read_airdata()
 * \ingroup airdata_fcns
*/
int read_airdata(struct airdata *adData_ptr	///< pointer to adData structure
		);

/// Auxiliary function to estimate biases on air data sensors. Implemented in airdata_bias.c
/*!
 *	\ingroup airdata_fcns
*/
void airdata_bias_estimate(struct airdata *adData_ptr	///< pointer to adData structure
		);

#endif

