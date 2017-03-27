/*! \file chirp_sysid.c
 *	\brief System ID chirp inputs
 *
 *	\details  Inject a system id sequence on the elevator, aileron, rudder.
 *	\ingroup systemid_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: chirp_sysid.c 908 2012-10-04 20:40:18Z joh07594 $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "systemid_interface.h"


//#include "aircraft/thor_config.h"  // for SIL sim only
#include AIRCRAFT_UP1DIR


extern void get_system_id( double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr){

	controlData_ptr->de = controlData_ptr->de + doublet(3, time, 2, 20*D2R);

}

