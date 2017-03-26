/*! \file imu_interface.h
 *	\brief IMU sensor interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with IMU sensors.
 *	All IMU sensor code must include this file and implement the init_imu() and read_imu() functions.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: imu_interface.h 756 2012-01-04 18:51:43Z murch $
 */

#ifndef IMU_INTERFACE_H_
#define IMU_INTERFACE_H_

/// Standard function to initialize the IMU sensors.
/*!
 * \sa read_imu()
 * \ingroup imu_fcns
*/
int init_imu();

/// Standard function to read the IMU sensors.
/*!
 * \sa init_imu()
 * \ingroup imu_fcns
*/
int read_imu(struct imu *imuData_ptr	///< pointer to imuData structure
		);

#endif /* IMU_INTERFACE_H_ */
