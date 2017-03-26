/*! \file airdata_constants.h
 *	\brief Constants for air data equations
 *
 *	\details This file defines constants needed for computing airspeed and altitude from measured pressures.
 *	\ingroup airdata_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: airdata_constants.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef AIRDATA_CONSTANTS_H_
#define AIRDATA_CONSTANTS_H_

// ****** AIR DATA CONSTANTS ***************************************************
#define AIR_DATA_P0  101.3251600806359 ///< [KPa], standard pressure
#define AIR_DATA_K1  44330.739888      ///< [m], constant for computing airspeed and altitude from pressures
#define AIR_DATA_K2  0.1903  	 	   ///< [ND], constant for computing airspeed and altitude from pressures
#define AIR_DATA_K3  760.4262731       ///< [m/s], constant for computing airspeed and altitude from pressures
#define AIR_DATA_K4  0.285714285714286 ///< [ND], constant for computing airspeed and altitude from pressures
#define PSI_TO_KPA  6.89475729  	   ///< [KPa], convert from PSI to KPa
// *****************************************************************************

#endif

