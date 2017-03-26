/*! \file fault_onesurf.c
 *	\brief Fault on one control surface.
 *
 *	\details Inject a ramp fault on one control surface. Eight different variations.
 *	\ingroup fault_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: fault_onesurf.c 907 2012-09-28 15:48:12Z joh07594 $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "fault_interface.h"

extern void get_surface_fault(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr){
	double *cmd;
	int state = 0;
	
	cmd = &controlData_ptr->da_r;// pointer to right aileron


	state = controlData_ptr->run_num;



	switch(state){
		case 1:
		case 2:
			// Do nothing, unfaulted scenario
			break;
		case 3:	
			// Additive ramp fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,13,5* D2R,cmd,1);
			break;
		case 4:
			// Additive ramp fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,13,10* D2R,cmd,1);
			break;	
		case 5:
			// Additive step fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,0,5* D2R,cmd,1);
			break;	
		case 6:
			// Additive step fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,0,10* D2R,cmd,1);
			break;	

		case 7:
		case 8:
			// Do nothing, unfaulted scenario
			break;
		case 9:
			// Additive ramp fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,13,5* D2R,cmd,1);
			break;
		case 10:
			// Additive ramp fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,13,10* D2R,cmd,1);
			break;
		case 11:
			// Additive step fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,0,5* D2R,cmd,1);
			break;
		case 12:
			// Additive step fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,0,10* D2R,cmd,1);
			break;


		case 13:
		case 14:
			// Do nothing, unfaulted scenario
			break;
		case 15:
			// Additive ramp fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,13,5* D2R,cmd,1);
			break;
		case 16:
			// Additive ramp fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,13,10* D2R,cmd,1);
			break;
		case 17:
			// Additive step fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,0,5* D2R,cmd,1);
			break;
		case 18:
			// Additive step fault on right aileron, starting at 7 sec after control is engaged,
			ramp_fault(7,time,0,10* D2R,cmd,1);
			break;






	}
}
