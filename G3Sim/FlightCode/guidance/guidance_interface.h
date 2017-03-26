/*! \file guidance_interface.h
 *	\brief Guidance law interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with guidance laws.
 *	\ingroup guidance_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: guidance_interface.h 757 2012-01-04 21:57:48Z murch $
 */

#ifndef GUIDANCE_INTERFACE_H_
#define GUIDANCE_INTERFACE_H_

/// Standard function to call the guidance law
/*!
 * \ingroup guidance_fcns
*/
extern void get_guidance(double time, 			///< [sec], time since in autopilot mode
		struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr,		///< pointer to controlData structure
		struct mission *missionData_ptr		///< pointer to missionData structure
		);

#endif /* GUIDANCE_INTERFACE_H_ */
