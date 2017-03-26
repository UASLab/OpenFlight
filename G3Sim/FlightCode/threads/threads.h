/*! \file threads.h
 *	\brief Threading functions header
 *
 *	\details This file defines the number of threads
 *	\ingroup sched_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: threads.h 770 2012-02-14 15:32:39Z murch $
 */

#ifndef THREADS_H_
#define THREADS_H_

#define NUM_THREADS 1	///< Number of threads

/*! \addtogroup sched_fcns
 * @{*/
// Thread functions
void *thread1(void * thread_id);	///< Wrapper function for thread1

void threads_create(void);	///< Create and start additional threads.
void threads_destroy(void);	///< Delete additional threads.

/*! @}*/
#endif
