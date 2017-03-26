/*! \file datalog_interface.h
 *	\brief Data logging interface header
 *
 *	\details This file declares the standard function prototypes for interfacing with the data logger.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: datalog_interface.h 761 2012-01-19 17:23:49Z murch $
 */

#ifndef DATALOG_INTERFACE_H_
#define DATALOG_INTERFACE_H_
	
/// Standard function to initialize the data logging
/*!
 * No input parameters or return value.
 * \sa datalogger(), close_datalogger()
 * \ingroup datalog_fcns
*/
int init_datalogger();

/// Standard function to close the data logging and dump data.
/*!
 * No input parameters or return value.
 * \sa datalogger(), init_datalogger()
 * \ingroup datalog_fcns
*/
void close_datalogger();

/// Standard function to call the data logging
/*!
 * No input parameters or return value.
 * \sa init_datalogger(), close_datalogger()
 * \ingroup datalog_fcns
*/
void datalogger();

/// Function to add variables to be saved as doubles.
/*!
 * For use in auxiliary threads. For variables available in main.c, use the datalog config files.
 * No return value.
 * \sa add_float_datalog(), add_int_datalog(), add_short_datalog()
 * \ingroup datalog_fcns
*/
void add_double_datalog(double * vars[], 	///< Array of pointers to variables
		char * names[], 				///< Array of MATLAB names to variables
		int num_vars					///< Number of new variables to be added to datalogging
		);

/// Function to add variables to be saved as doubles.
/*!
 * For use in auxiliary threads. For variables available in main.c, use the datalog config files.
 * No return value.
 * \sa add_double_datalog(), add_int_datalog(), add_short_datalog()
 * \ingroup datalog_fcns
*/
void add_float_datalog(double * vars[], 	///< Array of pointers to variables
		char * names[], 				///< Array of MATLAB names to variables
		int num_vars					///< Number of new variables to be added to datalogging
		);

/// Function to add variables to be saved as doubles.
/*!
 * For use in auxiliary threads. For variables available in main.c, use the datalog config files.
 * No return value.
 * \sa add_double_datalog(), add_float_datalog(), add_short_datalog()
 * \ingroup datalog_fcns
*/
void add_int_datalog(int * vars[],			///< Array of pointers to variables
		char * names[], 				///< Array of MATLAB names to variables
		int num_vars					///< Number of new variables to be added to datalogging
		);


/// Function to add variables to be saved as doubles.
/*!
 * For use in auxiliary threads. For variables available in main.c, use the datalog config files.
 * No return value.
 * \sa add_double_datalog(), add_float_datalog(), add_int_datalog(),
 * \ingroup datalog_fcns
*/
void add_short_datalog(unsigned short * vars[], ///< Array of pointers to variables
		char * names[], 				///< Array of MATLAB names to variables
		int num_vars					///< Number of new variables to be added to datalogging
		);


#endif	

