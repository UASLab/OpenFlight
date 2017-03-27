/*! \file systemid_interface.h
 *	\brief System ID interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with the system ID functions.
 *	All system ID codes must include this file and implement the get_system_id() function.
 *	Auxiliary functions are declared in this header file and implemented in systemid_functions.c.
  *	\ingroup systemid_fcns
  *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: systemid_interface.h 798 2012-04-19 20:04:44Z murch $
 */

#ifndef SYSTEMID_INTERFACE_H_
#define SYSTEMID_INTERFACE_H_

/// Standard function to call the system ID function.
/*!
 *	\ingroup systemid_fcns
*/
extern void get_system_id(double time, 			///< [sec], time since in autopilot mode
		struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
		struct nav *navData_ptr,			///< pointer to navData structure
		struct control *controlData_ptr		///< pointer to controlData structure
		);

// Auxiliary Functions

/// Auxiliary function that returns a standard doublet signal
/*!
 *	\sa doublet121()
 *	\ingroup systemid_fcns
*/
double doublet(double t0,		///< [sec], start time
		double currentTime,		///< [sec], current time
		double duration,		///< [sec], period of doublet pulse
		double amplitude		///< [rad], magnitude of doublet pulse
		);

/// Auxiliary function that returns a 1-2-1 doublet signal
/*!
 *	\sa doublet()
 *	\ingroup systemid_fcns
*/
double doublet121(double t0,	///< [sec], start time
		double currentTime,		///< [sec], current time
		double dur1,			///< [sec], duration of first pulse
		double dur2,			///< [sec], duration of second pulse
		double dur3,			///< [sec], duration of third pulse
		double amplitude		///< [rad], magnitude of pulse
		);

/// Auxiliary function that adds a orthogonal multi-sine to one surface
/*!
 *	\sa two_multi_sine(), three_multi_sine()
 *	\ingroup systemid_fcns
*/
void one_multi_sine (double t,	///< [sec], current time
		double *dsurf,			///< pointer to control surface
		double amp				///< [rad], amplitude of sine signal
		);

/// Auxiliary function that adds an orthogonal multi-sine to two surfaces
/*!
 *	\sa one_multi_sine(), three_multi_sine()
 *	\ingroup systemid_fcns
*/
void two_multi_sine (double t,	///< [sec], current time
		double *dsurf1,			///< pointer to control surface 1
		double *dsurf2,			///< pointer to control surface 2
		double amp1,			///< [rad], amplitude of sine signal 1
		double amp2				///< [rad], amplitude of sine signal 2
		);

/// Auxiliary function that adds an orthogonal multi-sine to three surfaces
/*!
 *	\sa two_multi_sine(), three_multi_sine()
 *	\ingroup systemid_fcns
*/
void three_multi_sine (double t,	///< [sec], current time
		double *de,					///< pointer to elevator control surface
		double *da,					///< pointer to aileron control surface
		double*dr					///< pointer to rudder control surface
		);

#endif /* SYSTEMID_INTERFACE_H_ */
