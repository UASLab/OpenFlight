/*! \file adc_interface.h
 *	\brief ADC interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with Analog to Digital Converter (ADC) chips.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: adc_interface.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/// Standard function to initialize the ADC chip.
/*!
 * No input parameters or return value.
 * \sa read_adc()
 * \ingroup adc_fcns
*/
void init_adc();

/// Standard function to read the ADC chip.
/*!
 * Returns a status bitfield.
 * \sa init_adc()
 * \ingroup adc_fcns
*/
int read_adc(uint16_t *signal_counts_ptr	///< pointer to array where signal values in counts will be stored
		);


#endif



