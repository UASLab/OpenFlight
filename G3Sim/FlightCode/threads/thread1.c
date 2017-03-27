/*! \file thread1.c
 *	\brief Thread 1 functions
 *
 *	\details
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: thread1.c 770 2012-02-14 15:32:39Z murch $
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <cyg/kernel/kapi.h>

#include "../globaldefs.h"
#include "../extern_vars.h"
#include "../utils/misc.h"
#include "../utils/scheduling.h"
#include "../threads/threads.h"

pthread_cond_t trigger_thread1;

void *thread1(void * thread_id){
	pthread_mutex_t	mutex_thread1;
	
	pthread_mutex_init(&mutex_thread1, NULL);
	pthread_mutex_lock(&mutex_thread1);
	while(1){
		pthread_cond_wait(&trigger_thread1,&mutex_thread1);
//		printf("\nthread1, t = %f",get_Time());
	}
	return thread_id;
}
