/******************************************************************************
 * FILE: control_manager_SIL.c
 * DESCRIPTION:
 * Software in the loop simulation (SILS) environment for V&V of onboard flight program (OFP).
 *
 *
 * University of Minnesota 
 * Aerospace Engineering and Mechanics 
 * Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: control_SIL.c 880 2012-08-14 18:38:14Z dorob002 $
 ******************************************************************************/

#define S_FUNCTION_NAME ControlSIL
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include "mex.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

// Include flightcode interfaces
#include "globaldefs.h"
#include "guidance/guidance_interface.h"
#include "control/control_interface.h"
#include "system_id/systemid_interface.h"
#include "faults/fault_interface.h"


#define NIN  2				/* number of input ports */
#define IP0_SIZE  24		/* size of input port 0*/
#define IP1_SIZE  2		/* size of input port 1*/
#define NOUT 1				/* number of output ports */
#define OP0_SIZE  7		    /* size of output port 0*/
#define NPAR 1				/* number of S-function parameters */

// #define NIN  2				/* number of input ports */S
// #define IP0_SIZE  19		/* size of input port 0*/
// #define IP1_SIZE  12		/* size of input port 1*/
// #define NOUT 2				/* number of output ports */
// #define OP0_SIZE  7		    /* size of output port 0*/
// #define OP1_SIZE  12	    /* size of output port 1*/
// #define NPAR 1				/* number of S-function parameters */

#define dt        		*mxGetPr(ssGetSFcnParam(S,0))		// Software sample TIME, as an input parameter
#define TIME			ssGetT(S)							// Current simulation TIME		



// Data Structures 
struct  imu   imuData;
struct  gps   gpsData;
struct  nav   navData;
struct  control controlData;
struct  airdata adData;
// sensor data 
static struct sensordata sensorData;

/*========================================================================*
 *                          Initialization                                *
 *========================================================================*/

static void mdlInitializeSizes(SimStruct *S) {
    ssSetNumSFcnParams(S, NPAR);
    if(ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))   return;
    
    if(!ssSetNumInputPorts(S, NIN)) return;
    
    {
        int_T   i;
        for(i = 0; i < NIN; i++){
            ssSetInputPortDirectFeedThrough(S, i, 1);
            ssSetInputPortDataType(S, i, DYNAMICALLY_TYPED);
        }
        
        ssSetInputPortWidth(S, 0, IP0_SIZE);
        ssSetInputPortWidth(S, 1, IP1_SIZE);
    }
    
    if(!ssSetNumOutputPorts(S, NOUT))    return;
    {
            ssSetOutputPortWidth(S, 0, OP0_SIZE);
			//ssSetOutputPortWidth(S, 1, OP1_SIZE);
    }
    
    ssSetNumSampleTimes(S, 1);   
    
    sensorData.imuData_ptr = &imuData;
	sensorData.gpsData_ptr = &gpsData;
	sensorData.adData_ptr = &adData;
}

 static void mdlInitializeSampleTimes(SimStruct *S) {
     //ssSetSampleTime(S, 0, dt);
     ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
     ssSetOffsetTime(S, 0, 0.0);
 }

static void mdlStart(SimStruct *S) {
    static int run_num=0;
    run_num++;
    reset_control(&controlData); // reset any internal states in the controller
    //ScontrolData.run_num = run_num;
}

/*========================================================================*
 *                              Output                                    *
 *========================================================================*/
static void mdlOutputs(SimStruct *S, int_T tid) {
    // local variables
    real_T  *y0, *y1;

    // outputs
    y0 =  ssGetOutputPortRealSignal(S, 0);

    // outputs
    y1 =  ssGetOutputPortRealSignal(S, 1);	
    
    
    
    // Assign sensor data to feedback vector. 
    sensorData.imuData_ptr->phi = *ssGetInputPortRealSignalPtrs(S, 0)[0]; // phi
    sensorData.imuData_ptr->the = *ssGetInputPortRealSignalPtrs(S, 0)[1]; // theta
    sensorData.imuData_ptr->psi = *ssGetInputPortRealSignalPtrs(S, 0)[2]; // psi
    sensorData.imuData_ptr->p = *ssGetInputPortRealSignalPtrs(S, 0)[3]; // p
    sensorData.imuData_ptr->q = *ssGetInputPortRealSignalPtrs(S, 0)[4]; // q
    sensorData.imuData_ptr->r = *ssGetInputPortRealSignalPtrs(S, 0)[5]; // r
    sensorData.imuData_ptr->ax = 0; // ax
    sensorData.imuData_ptr->ay = 0; // ay
    sensorData.imuData_ptr->az = 0; // az
	sensorData.adData_ptr->h = 0; // h
	sensorData.adData_ptr->ias = 0; // ias
    sensorData.adData_ptr->aoa = 0; // alpha
    sensorData.adData_ptr->aos = 0; // beta  
	navData.lat = 0; // lat
    navData.lon = 0; // lon
    navData.alt = 0; // alt
    navData.vn = 0; // vn
    navData.ve = 0; // ve
    navData.vd = 0; // vd
    navData.phi = sensorData.imuData_ptr->phi ;
    navData.the = sensorData.imuData_ptr->the ;
    navData.psi = sensorData.imuData_ptr->psi ;
       
//     // Assign sensor data to feedback vector. 
//     sensorData.imuData_ptr->phi = *ssGetInputPortRealSignalPtrs(S, 0)[0]; // phi
//     sensorData.imuData_ptr->the = *ssGetInputPortRealSignalPtrs(S, 0)[1]; // theta
//     sensorData.imuData_ptr->psi = *ssGetInputPortRealSignalPtrs(S, 0)[2]; // psi
//     sensorData.imuData_ptr->p = *ssGetInputPortRealSignalPtrs(S, 0)[3]; // p
//     sensorData.imuData_ptr->q = *ssGetInputPortRealSignalPtrs(S, 0)[4]; // q
//     sensorData.imuData_ptr->r = *ssGetInputPortRealSignalPtrs(S, 0)[5]; // r
//     sensorData.imuData_ptr->ax = *ssGetInputPortRealSignalPtrs(S, 0)[6]; // ax
//     sensorData.imuData_ptr->ay = *ssGetInputPortRealSignalPtrs(S, 0)[7]; // ay
//     sensorData.imuData_ptr->az = *ssGetInputPortRealSignalPtrs(S, 0)[8]; // az
// 	sensorData.adData_ptr->h = *ssGetInputPortRealSignalPtrs(S, 0)[9]; // h
// 	sensorData.adData_ptr->ias = *ssGetInputPortRealSignalPtrs(S, 0)[10]; // ias
//     sensorData.adData_ptr->aoa = *ssGetInputPortRealSignalPtrs(S, 0)[11]; // alpha
//     sensorData.adData_ptr->aos = *ssGetInputPortRealSignalPtrs(S, 0)[12]; // beta  
// 	navData.lat = *ssGetInputPortRealSignalPtrs(S, 0)[13]; // lat
//     navData.lon = *ssGetInputPortRealSignalPtrs(S, 0)[14]; // lon
//     navData.alt = *ssGetInputPortRealSignalPtrs(S, 0)[15]; // alt
//     navData.vn = *ssGetInputPortRealSignalPtrs(S, 0)[16]; // vn
//     navData.ve = *ssGetInputPortRealSignalPtrs(S, 0)[17]; // ve
//     navData.vd = *ssGetInputPortRealSignalPtrs(S, 0)[18]; // vd
//     navData.phi = *ssGetInputPortRealSignalPtrs(S, 0)[0]; // phi
//     navData.the = *ssGetInputPortRealSignalPtrs(S, 0)[1]; // theta
//     navData.psi = *ssGetInputPortRealSignalPtrs(S, 0)[2]; // psi
    
    //**** GUIDANCE **********************************************************
    #ifdef SIMULINK_GUIDANCE
    
        // Assign doublet sequences to references vector from Simulink
        controlData.phi_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[0]; // roll command
        controlData.theta_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[1]; // pitch command
        controlData.psi_cmd = 0; // yaw command
        controlData.p_cmd = 0; // roll rate command
        controlData.q_cmd = 0; // pitch rate command
        controlData.r_cmd = 0; // yaw rate command
        controlData.ias_cmd = 0; // airspeed  command
        controlData.h_cmd = 0; // altitude  command
        controlData.gndtrk_cmd = 0; // grndtrck angle command
        controlData.aoa_cmd = 0; // angle of attack command
        controlData.aos_cmd = 0; // angle of sideslip command
        controlData.gamma_cmd = 0; // flight path angle command

//         // Assign doublet sequences to references vector from Simulink
//         controlData.phi_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[0]; // roll command
//         controlData.theta_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[1]; // pitch command
//         controlData.psi_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[2]; // yaw command
//         controlData.p_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[3]; // roll rate command
//         controlData.q_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[4]; // pitch rate command
//         controlData.r_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[5]; // yaw rate command
//         controlData.ias_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[6]; // airspeed  command
//         controlData.h_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[7]; // altitude  command
//         controlData.gndtrk_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[8]; // grndtrck angle command
//         controlData.aoa_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[9]; // angle of attack command
//         controlData.aos_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[10]; // angle of sideslip command
//         controlData.gamma_cmd = *ssGetInputPortRealSignalPtrs(S, 1)[11]; // flight path angle command

    #else
        // Compute guidance (reference) commands for the control law
         get_guidance(TIME, &sensorData, &navData, &controlData);   
    #endif  
    //************************************************************************		

    //**** SENSOR FAULT ******************************************************
    get_sensor_fault(TIME, &sensorData, &navData, &controlData);
    //************************************************************************

    //**** CONTROL ***********************************************************
    get_control(TIME, &sensorData, &navData, &controlData, &controlData); // hack the mission data pointer
    //************************************************************************

    //**** SYSTEM ID *********************************************************
    get_system_id(TIME, &sensorData, &navData, &controlData);
    //************************************************************************

    //**** SURACE FAULT ******************************************************
    get_surface_fault(TIME, &sensorData, &navData, &controlData);
    //************************************************************************

			
    // Assign to block outputs
    y0[0] = controlData.dthr; // Throttle deflection	
    y0[1] = controlData.de; // Elevator deflection
    y0[2] = controlData.dr; // Rudder deflection
	y0[3] = controlData.da_l; // Left Aileron deflection
    y0[4] = controlData.da_r; // Right Aileron deflection
	y0[5] = controlData.df_l; // Left flap deflection
    y0[6] = controlData.df_r; // Right flap deflection
	
// 	y1[0] = controlData.phi_cmd; // Roll angle command
// 	y1[1] = controlData.theta_cmd; // Pitch angle command
//     y1[2] = controlData.psi_cmd; // yaw command
//     y1[3] = controlData.p_cmd; // roll rate command
//     y1[4] = controlData.q_cmd; // pitch rate command
//     y1[5] = controlData.r_cmd; // yaw rate command
//     y1[6] = controlData.ias_cmd; // airspeed  command
//     y1[7] = controlData.h_cmd; // altitude  command
//     y1[8] = controlData.gndtrk_cmd; // grndtrck angle command
//     y1[9] = controlData.aoa_cmd; // angle of attack command
//     y1[10] = controlData.aos_cmd; // angle of sideslip command
//     y1[11] = controlData.gamma_cmd; // flight path angle command

  
}


/*========================================================================*
 *                              Termination                               *
 *========================================================================*/

static void mdlTerminate(SimStruct *S) {
    reset_control(&controlData);
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
// ========================================================================================================

