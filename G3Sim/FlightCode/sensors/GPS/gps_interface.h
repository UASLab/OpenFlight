/*! \file gps_interface.h
 *	\brief GPS sensor interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with GPS sensors.
 *	All GPS sensor code must include this file and implement the init_gps() and read_gps() functions.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gps_interface.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef GPS_INTERFACE_H_
#define GPS_INTERFACE_H_

/// Standard function to initialize the GPS sensors.
/*!
 * \sa read_gps()
 * \ingroup gps_fcns
*/
void init_gps(struct gps *gpsData_ptr	///< pointer to gpsData structure
		);

/// Standard function to read the GPS sensors.
/*!
 * \sa init_gps()
 * \ingroup gps_fcns
*/
int read_gps(struct gps *gpsData_ptr	///< pointer to gpsData structure
		);

#endif /* GPS_INTERFACE_H_ */
