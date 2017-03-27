/*! \file MAX127_ADC.h
 *	\brief MaximIC MAX127 ADC header file
 *
 *	\details Header file for the MaximIC MAX127 ADC chip.
 *	\ingroup adc_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: MAX127_ADC.h 756 2012-01-04 18:51:43Z murch $
 */
#ifndef MAX127_ADC_H_
#define MAX127_ADC_H_

static cyg_i2c_device MAX127_ADC = {
      .i2c_bus        = &mpc5200_i2c_bus0,
      .i2c_address    = 0x51,            
      .i2c_flags      = 0x00,            
      .i2c_delay      = CYG_I2C_DEFAULT_DELAY
  };
  
// Slave address is 0 1 0 1 A2 A1 A0  followed by R/W where R/W = 0 for write; = 1 for read.
// A2 A1 A0 are all tied to ground; this makes the slave address 0101 0000 => 0x50 write, 0101 0001 => 0x51 read. 

//Next the master sends a control byte. MSB = start (1) followed by the binary number of the 
//channel you wish to read; ch0=>000, ch7=>111. The next bit scelects the input voltage range
//should be 0 for 0v-5v and then another 0 bit to make it uni-polar. Finally there are 
//two bits that select the power down mode; use 00 for normal operation.
//The first control byte we want to read (ch0) is then = 1000 0000 or 0x80
	
static uint8_t    controlByte[8] = {0x80,0x90,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0};	//Control bytes for all 8 channels

#endif
