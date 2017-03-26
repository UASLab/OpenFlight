/*! \file gps_sirf.h
 *	\brief SiRFIII GPS receiver header
 *
 *	\details Header file for SiRFIII GPS receiver.
 *	\ingroup gps_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gps_sirf.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef GPS_SIRF_H_
#define GPS_SIRF_H_

//#define verbose

/* these are independent of byte order */
#define getsb(buf, off)	((int8_t)buf[(off)])
#define getub(buf, off)	((uint8_t)buf[(off)])

/* SiRF and most other GPS protocols use big-endian (network byte order) */
#define getbesw(buf, off)	((int16_t)(((uint16_t)getub(buf, (off)) << 8) | (uint16_t)getub(buf, (off)+1)))
#define getbeuw(buf, off)	((uint16_t)(((uint16_t)getub(buf, (off)) << 8) | (uint16_t)getub(buf, (off)+1)))
#define getbesl(buf, off)	((int32_t)(((uint16_t)getbeuw(buf, (off)) << 16) | getbeuw(buf, (off)+2)))
#define getbeul(buf, off)	((uint32_t)(((uint16_t)getbeuw(buf, (off)) << 16) | getbeuw(buf, (off)+2)))
#define getbesL(buf, off)	((int64_t)(((uint64_t)getbeul(buf, (off)) << 32) | getbeul(buf, (off)+4)))
#define getbeuL(buf, off)	((uint64_t)(((uint64_t)getbeul(buf, (off)) << 32) | getbeul(buf, (off)+4)))
/* float and double */
#define getbef(buf, off)	(i_f.i = getbesl(buf, off), i_f.f)
#define getbed(buf, off)	(l_d.l = getbesL(buf, off), l_d.d)


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

#endif /* GPS_SIRF_H_ */
