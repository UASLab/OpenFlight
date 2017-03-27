/*! \file gps_crescent.h
 *	\brief NovaTel OEMStar GPS receiver header
 *
 *	\details Header file for the NovaTel OEMStar GPS receiver.
 *	\ingroup gps_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gps_crescent.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef GPS_OEMSTAR_H_
#define GPS_OEMSTAR_H_

#define GPS_MAX_MSG_SIZE 300 ///< bytes, size of largest msg payload (for error checking)
#define CRC32_POLYNOMIAL 0xEDB88320L

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

/// Local function to calculate GPS CRC
static unsigned long CRC32Value(int i);

static unsigned long CalculateBlockCRC32(unsigned long ulCount,unsigned char *ucBuffer);

#endif /* GPS_CRESCENT_H_ */
