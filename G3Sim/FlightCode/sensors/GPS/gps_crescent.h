/*! \file gps_crescent.h
 *	\brief Hemisphere Crescent OEM GPS receiver header
 *
 *	\details Header file for the Hemisphere Crescent OEM GPS receiver.
 *	\ingroup gps_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gps_crescent.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef GPS_CRESCENT_H_
#define GPS_CRESCENT_H_

#define GPS_MAX_MSG_SIZE 300 ///< bytes, size of largest msg payload (for error checking)

/// Local function to parse the GPS packet.
/*!
 * \sa read_gps()
*/
static void parse_gps(struct gps *gpsData_ptr	///< pointer to gpsData structure
		);

/// Local function to clear the local buffer.
/*!
 * No inputs or outputs.
*/
static void reset_localBuffer();

#endif /* GPS_CRESCENT_H_ */
