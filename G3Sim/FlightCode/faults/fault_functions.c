/*! \file fault_functions.c
 *	\brief Functions for fault emulation
 *
 *	\details
 *	\ingroup fault_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: fault_functions.c 770 2012-02-14 15:32:39Z murch $
 */
#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "fault_interface.h"

extern void ramp_fault(double startTime, double currentTime, double duration, double amplitude, double *delta, int isAdditive){
	// ramp or step fault injection on control signal 'delta'. set isAdditive = 1 if fault is additive (ie delta + fault)
	// When duration = 0, fault becomes a step fault instead of a ramp
	static double d_last;
	
	// If fault is additive, then put current control command in d_last
	if(isAdditive == TRUE)
		d_last = *delta;
		
	// Fault signal	
	if ( currentTime >= startTime && currentTime-startTime < duration && duration != 0 ) // ramp phase of fault
		*delta = d_last + amplitude/duration * (currentTime-startTime);
		
	else if(currentTime-startTime >= duration) // fault at full amplitude
		*delta = d_last + amplitude;
		
	else{	// prior to fault injection
		d_last = *delta;

	}
}
