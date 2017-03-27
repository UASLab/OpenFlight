/*! \file daq_interface.h
 *	\brief Data acquisition interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with the data acquisition.
 *	All data acquisition codes must include this file and instantiate the init_daq() and get_daq() functions.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: daq_interface.h 869 2012-08-06 22:40:38Z joh07594 $
 */

#ifndef DAQ_INTERFACE_H_
#define DAQ_INTERFACE_H_
	
/// Standard function to initialize the data acquisition.
/*!
 * \sa get_daq()
 * \ingroup daq_fcns
*/
void init_daq(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr		///< pointer to controlData structure
		);

/// Standard function to call the data acquisition.
/*!
 * \sa init_daq()
 * \ingroup daq_fcns
*/
void get_daq(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr,		///< pointer to controlData structure
		struct mission *missionData_ptr		///< pointer to missionData structure
		);

/// Basic low pass filter used to filter altitude and airspeed signals
double lp_filter (double signal, double *u, double *y);

#endif	

