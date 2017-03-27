/*! \file airdata_bias.c
 *	\brief Function to estimate biases on air data sensors.
 *
 *	\details Function to estimate biases on air data sensors.
 *	\ingroup airdata_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: airdata_bias.c 756 2012-01-04 18:51:43Z murch $
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "../../globaldefs.h"
#include "airdata_interface.h"

void airdata_bias_estimate(struct airdata *adData_ptr){
	static int count;
	int i;

	static double airdata_bias_prev[4];
	count++;
	adData_ptr->bias[0] = airdata_bias_prev[0]*(1-1/count) + adData_ptr->h*(1/count);
	adData_ptr->bias[1] = airdata_bias_prev[1]*(1-1/count) + adData_ptr->Pd*(1/count);
	adData_ptr->bias[2] = airdata_bias_prev[2]*(1-1/count) + adData_ptr->Pd_aoa*(1/count);
	adData_ptr->bias[3] = airdata_bias_prev[3]*(1-1/count) + adData_ptr->Pd_aos*(1/count);

	for(i=0;i<4;i++)
		airdata_bias_prev[i] = adData_ptr->bias[i]; 

}
