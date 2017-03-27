/*! \file SX8724C_ADC.h
 *	\brief Semtech SX8724C ADC header file
 *
 *	\details Header file for the Semtech SX8724C ADC chip.
 *	\ingroup adc_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: SX8724C_ADC.h 970 2013-04-12 22:12:25Z lie $
 */
#ifndef SX8724C_ADC_H_
#define SX8724C_ADC_H_

/// Defualt Configuration for the SX8724C ADC chip
/// I2C slave address is 1001 0000 => 0x90 write, 1001 0101 => 0x91 read.
static cyg_i2c_device SX8724C_ADC_default = {
      .i2c_bus        = &mpc5200_i2c_bus0,
      .i2c_address    = 0x91,
      .i2c_flags      = 0x00,
      .i2c_delay      = CYG_I2C_DEFAULT_DELAY
  };

/// Configuration for the SX8724C ADC chip #1.
/// I2C slave address is 1 0 0 1 0 A1 A0  followed by R/W where R/W = 0 for write; = 1 for read.
/// A1 to high, A0 to ground; this makes the slave address 1001 0100 => 0x94 write, 1001 0101 => 0x95 read.
static cyg_i2c_device SX8724C_ADC_0 = {
      .i2c_bus        = &mpc5200_i2c_bus0,
      .i2c_address    = 0x95,
      .i2c_flags      = 0x00,            
      .i2c_delay      = CYG_I2C_DEFAULT_DELAY
  };
 
/// Configuration for the SX8724C ADC chip #2.
/// I2C slave address is 1 0 0 1 0 A1 A0  followed by R/W where R/W = 0 for write; = 1 for read.
/// A1 is tied to ground, A0 to high; this makes the slave address 1001 0010 => 0x92 write, 1001 0011 => 0x93 read.
static cyg_i2c_device SX8724C_ADC_1 = {
      .i2c_bus        = &mpc5200_i2c_bus0,
      .i2c_address    = 0x93,
      .i2c_flags      = 0x00,
      .i2c_delay      = CYG_I2C_DEFAULT_DELAY
  };

/// Configuration for the SX8724C ADC chip #3.
/// I2C slave address is 1 0 0 1 0 A1 A0  followed by R/W where R/W = 0 for write; = 1 for read.
/// A1 is tied to high, and A0 to high; this makes the slave address 1001 0110 => 0x96 write, 1001 0111 => 0x97 read.
static cyg_i2c_device SX8724C_ADC_2 = {
      .i2c_bus        = &mpc5200_i2c_bus0,
      .i2c_address    = 0x97,
      .i2c_flags      = 0x00,
      .i2c_delay      = CYG_I2C_DEFAULT_DELAY
  };

// Registers. Sec 7.2
#define RegACOutLsb	0x50	///< LSB of ADC result
#define RegACOutMsb	0x51	///< MSB of ADC result
#define RegACCfg0	0x52	///< ADC conversion control. Start, SetNelconv, SetOsr, Continuous, 0
#define RegACCfg1	0x53	///< ADC conversion control. IbAmpAdc, IbAmpPga, Enable
#define RegACCfg2	0x54	///< ADC conversion control. SetFs, Pga2Gain, Pga2Offset
#define RegACCfg3	0x55	///< ADC conversion control. Pga1Gain, Pga3Gain
#define RegACCfg4	0x56	///< ADC conversion control. 0, Pga3Offset
#define RegACCfg5	0x57	///< ADC conversion control. Busy, Def, Amux, Vmux
#define RegExtAdd	0x43	///< Register to set I2C address by external pins. Sec 9.2.1

// Specific settings for registers
#define Enable		0x01	///< Enable ADC, PGAs 1, 2, & 3 disabled. Sec 7.1.3
#define Amux		0x10	///< Analog input selection, bits 5:4. Sets reference voltage to be ground, positive input voltage. Sec 7.3
#define Pga1Gain	0x00<<7	///< Set PGA1 gain to 1. Sec 7.4
#define Pga2Gain	0x00<<4	///< Set PGA2 gain to 1. Sec 7.5
#define Pga2Offset	0x00	///< Set PGA2 offset to 0. Sec 7.5
#define Pga3Gain	0x0C	///< Set PGA3 gain to 1 (12/12). Sec 7.6
#define Pga3Offset	0x00	///< Set PGA3 offset to 0 * Vref. Sec 7.6
#define SetFs		0x03<<6	///< Set Sampling Frequency to 500 KHz. Sec 7.7.2
#define SetOSR		0x03<<2	///< Set Oversampling Ratio to 64. Sec 7.7.3
#define SetNelconv	0x01<<5	///< Set Number of Elementary Conversions to 2. Sec 7.7.4

#define SetRegACCfg0	(0x80 | SetNelconv | SetOSR | 0x00)	///< Setting for register RegACCfg0
#define SetRegACCfg1	(0xF0 | Enable)						///< Setting for register RegACCfg1
#define SetRegACCfg2	(SetFs | Pga2Gain | Pga2Offset )	///< Setting for register RegACCfg2
#define SetRegACCfg3	(Pga1Gain | Pga3Gain)				///< Setting for register RegACCfg3
#define SetRegACCfg4	(Pga3Offset)						///< Setting for register RegACCfg4
#define SetRegACCfg5	(Amux | 0x02)<<1					///< Setting for register RegACCfg5
#define SetRegExtAdd	0x96								///< Setting for register RegExtAdd, to use external address
#endif
