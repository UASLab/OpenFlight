/*! \file telemetry_interface.h
 *	\brief Telemetry interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with the telemetry.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: telemetry_interface.h 761 2012-01-19 17:23:49Z murch $
 */
#ifndef TELEMETRY_INTERFACE_H_
#define TELEMETRY_INTERFACE_H_
	
/// Standard function to initialize the send_telemetry.
/*!
 * No input parameters or return value.
 * \sa send_telemetry()
 * \ingroup telemetry_fcns
*/
void init_telemetry();

/// Standard function to call the send_telemetry.
/*!
 *
 * \sa init_telemetry()
 * \ingroup telemetry_fcns
*/
void send_telemetry(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr,	///< pointer to controlData structure
		struct mission *missionData_ptr,	///< pointer to missionData structure
		uint16_t cpuLoad					///< current CPU load measurement
		);

#endif	

