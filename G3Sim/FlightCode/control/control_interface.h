/*! \file control_interface.h
 *	\brief Control law interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with control laws.
 *	\ingroup control_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: control_interface.h 860 2012-07-18 18:27:25Z joh07594 $
 */

#ifndef CONTROL_INTERFACE_H_
#define CONTROL_INTERFACE_H_

/// Standard function to call the control law
/*!
 * \sa reset_control()
 * \ingroup control_fcns
 */
extern void get_control(double time, 			///< [sec], time since in autopilot mode
		struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr,		///< pointer to controlData structure
		struct mission *missionData_ptr		///< pointer to missionData structure
);

/// Standard function to reset internal states of the control law
/*!
 * \sa get_control()
 * \ingroup control_fcns
 */
extern void reset_control(struct control * controlData_ptr	///< pointer to controlData structure
);

///Standard function to add trim biases to the control law outputs. Implemented in control_functions.c
/*!
 * \sa get_control(), reset_control(), subtract_trim_bias()
 * \ingroup control_fcns
 */
extern void add_trim_bias(struct control * controlData_ptr	///< pointer to controlData structure
);

///Standard function to subtract trim biases to the control law outputs. Implemented in control_functions.c
/*!
 * \sa get_control(), reset_control(), add_trim_bias()
 * \ingroup control_fcns
 */
extern void subtract_trim_bias(struct control * controlData_ptr	///< pointer to controlData structure
);

// Limits placed on the get_control law outputs
#define		RUDDER_AUTH_MAX		0.4363		///< [rad], 25 deg, limit on get_control law output
#define		ELEVATOR_AUTH_MAX	0.4363		///< [rad], 25 deg, limit on get_control law output
#define 	AILERON_AUTH_MAX	0.4363		///< [rad], 25 deg, limit on get_control law output
#define		THROTTLE_AUTH_MAX	1.0			///< [ND],  1.0, limit on get_control law output
#define		THROTTLE_AUTH_MIN	0			///< [ND],  0, limit on get_control law output

#endif /* CONTROL_LAW_INTERFACE_H_ */
