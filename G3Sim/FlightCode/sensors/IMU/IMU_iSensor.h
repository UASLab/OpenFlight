/*! \file IMU_iSensor.h
 *	\brief Analog Devices AD16405 IMU interface header
 *
 *	\ingroup imu_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: IMU_iSensor.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef IMU_ISENSOR_H_
#define IMU_ISENSOR_H_


#define SPIPSC_PORT1 	"/dev/spipsc1"	///< SPI port for IMU

static cyg_io_handle_t hSPI;	///< handle to SPI port
//#define verbose		// enable spi, i2c debug messages


#endif /* IMU_ISENSOR_H_ */
