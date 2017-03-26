/*! \file gpio_interface.h
 *	\brief GPIO interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with the General Purpose Input/Output (GPIO) lines.
 *	All gpio code must include this file and implement the init_gpio() and read_gpio() functions.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: gpio_interface.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#define GPIO_ENABLE_CHANNEL		1
#define GPIO_DISABLE	0
#define GPIO_DR_INPUT	1
#define GPIO_DR_OUTPUT	0
#define GPIO_OUT_LOW	0
#define GPIO_OUT_HIGH	1
#define GPIO_IN_LOW		0
#define GPIO_IN_HIGH	1

/// Standard function to initialize the GPIO lines.
/*!
 * No input parameters or return value.
 * \sa read_gpio()
 * \ingroup gpio_fcns
*/
void init_gpio(void);

/// Standard function to read the GPIO lines.
/*!
 *
 * \sa init_gpio()
 * \ingroup gpio_fcns
*/
void read_gpio(struct mission *missionData_ptr	///< pointer to controlData structure
		);

#endif
