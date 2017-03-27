/*! \file fault_interface.h
 *	\brief Surface and sensor fault interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with the sensor and surface faults.
 *	All fault codes must include this file and instantiate either the get_surface_fault() or get_sensor_fault() function.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: fault_interface.h 757 2012-01-04 21:57:48Z murch $
 */

#ifndef FAULT_INTERFACE_H_
#define FAULT_INTERFACE_H_

/// Standard function to call the surface fault
/*!
 * \sa get_sensor_fault()
 * \ingroup fault_fcns
*/
extern void get_surface_fault(double time, 		///< [sec], time since in autopilot mode
		struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr		///< pointer to controlData structure
		);

/// Standard function to call the sensor fault
/*!
 * \sa get_surface_fault()
 * \ingroup fault_fcns
*/
extern void get_sensor_fault(double time, 		///< [sec], time since in autopilot mode
		struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr		///< pointer to controlData structure
		);

/// Auxiliary function that implements a ramp fault
/*!
 * \ingroup fault_fcns
*/
extern void ramp_fault(double startTime,///< [sec], start time of ramp
		double currentTime,				///< [sec], current time
		double duration,				///< [sec], duration of ramp
		double amplitude,				///< [rad], maximum amplitude of ramp
		double *delta,					///< pointer to variable that will have fault applied
		int isAdditive					///< flag to indicate whether the ramp is additive (summed with *delta) or not (replaces *delta).
		);

#endif /* FAULT_INTERFACE_H_ */
