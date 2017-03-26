/*! \file actuator_interface.h
 *	\brief Actuator interface header
 *
 *	\details This file is used to declare the standard function prototypes for interfacing with the actuators.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: actuator_interface.h 757 2012-01-04 21:57:48Z murch $
 */

#ifndef ACTUATOR_INTERFACE_H_
#define ACTUATOR_INTERFACE_H_

/// Standard function to initialize the actuators
/*!
 * No input parameters or return value.
 * \sa set_actuators(), close_actuators()
 * \ingroup actuator_fcns
*/
extern void init_actuators();

/// Standard function to set the actuators
/*!
 * \sa init_actuators(), close_actuators()
 * \ingroup actuator_fcns
*/
extern void set_actuators(struct control * controlData_ptr ///< Pointer to control data structure
		);

/// Standard function to close the actuators
/*!
 * No input parameters or return value.
 * \sa set_actuators(), init_actuators()
 * \ingroup actuator_fcns
*/
extern void close_actuators();

#endif /* ACTUATOR_INTERFACE_H_ */
