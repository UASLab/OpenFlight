/*! \file threads.c
 *	\brief Threading functions.
 *
 *	\details This file creates and starts threads
 *	\ingroup sched_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: threads.c 770 2012-02-14 15:32:39Z murch $
 */
#include <pthread.h>
#include <cyg/kernel/kapi.h>

#include "../globaldefs.h"
#include "../extern_vars.h"
#include "threads.h"

static pthread_t threads[NUM_THREADS];


void threads_create(void){
	pthread_attr_t attr;
//	struct sched_param param;

	/*initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	/*set scheduling policy */
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	
	/*set thread priority */
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);	

//	// Create and start thread1
//	param.sched_priority = sched_get_priority_max(SCHED_FIFO)-1;
//	pthread_attr_setschedparam(&attr, &param);
//	pthread_create(&threads[0], &attr, thread1, (void *) 1);

}

void threads_destroy(void){
	int i;

	for(i=0;i<NUM_THREADS;i++){
		pthread_join(threads[i], NULL);
	}

}


