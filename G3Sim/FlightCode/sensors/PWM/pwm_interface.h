/*! \file pwm_interface.h
 *	\brief PWM interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with PWM I/O chips.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: pwm_interface.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

/// Standard function to initialize the PWM chip.
/*!
 * No input parameters or return value.
 * \sa read_pwm()
 * \ingroup pwm_fcns
*/
void init_pwm();

/// Standard function to read the PWM chip.
/*!
 * Returns a status bitfield.
 * \sa init_pwm()
 * \ingroup pwm_fcns
*/
int read_pwm(uint16_t *pwm_signal_ptr	///< pointer to array where signal values will be stored
		);


#endif



