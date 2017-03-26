/*! \file student_control.c
 *	\brief Student controller source code
 *
 *	\details Template for implementing a controller designed by students.
 *
 *	\ingroup control_fcns
 *
 *	\author University of Minnesota
 *	\author Aerospace Engineering and Mechanics
 *	\copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: student_control.c 967 2013-03-29 20:12:43Z dorob002 $
 */

#include <stdlib.h>
#include <math.h>
#include "../globaldefs.h"
#include "control_interface.h"


// ***********************************************************************************
// ***********************************************************************************
// ***********************************************************************************
#include "../aircraft/thor_config.h"  // for SIL_Sim
//#include AIRCRAFT_UP1DIR            // for Flight Code
// ***********************************************************************************
// ***********************************************************************************
// ***********************************************************************************


/// Definition of local functions and variables: *******************************************
static double yaw_damper (double yawrate);
static double roll_control (double phi_ref, double roll_angle, double rollrate, double delta_t);
static double pitch_control(double the_ref, double pitch, double pitchrate, double delta_t);

static double dr; // Delta rudder    
static double da; // Delta aileron
static double de; // Delta elevator



// Initialize pitch and roll angle tracking errors, integrators, and anti wind-up operators
// 0 values correspond to the roll tracker, 1 values correspond to the theta tracker
static double e[2] = {0,0};
static double integrator[2] = {0,0};
static short anti_windup[2]={1,1};   // integrates when anti_windup is 1



/// ****************************************************************************************
/// Yaw rate digital controller - parameters and variables

//   y_yaw(z)      b[0] + b[1]*z^(-1)
//   --------  =  --------------------
//   u_yaw(z)      a[0] + a[1]*z^(-1)

static const int k=1; 	//k = the order of the denominator of the Discrete Time Transfer
				        //function. k is used for calculating current and past time step values
static double u_yaw[2] = {0,0}; // input of filter { u(k), u(k-1) }
static double y_yaw[2] = {0,0}; // output of filter { y(k), y(k-1) }
static double a_yaw[2] = {1.0,-0.9608}; // Filter denominator coefficients
static double b_yaw[2] = {0.065, -0.065}; // Filter numerator coefficients


/// ****************************************************************************************
/// Roll and pitch angle digital controller - parameters and variables
static double roll_gain[3]  = {-0.64,-0.20,-0.07};  // PI gains for roll tracker and roll damper
static double pitch_gain[3] = {-0.90,-0.30,-0.08};  // PI gains for theta tracker and pitch damper

/// *****************************************************************************************








/// *****************************************************************************************
/// *****************************************************************************************
/// *****************************************************************************************
// BEGIN MAIN CONTROL FUNCTION
extern void get_control(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr) {
/// Return control outputs based on references and feedback signals.


	double base_pitch_cmd= 0.0872664;  // (Thor Trim value) use 5 deg (0.0872664 rad) for flight, use 3.082 deg (0.0537910 rad) in sim
	double phi   = navData_ptr->phi;
	double theta = navData_ptr->the - base_pitch_cmd; //subtract theta trim value to convert to delta coordinates
	double p     = sensorData_ptr->imuData_ptr->p; // Roll rate
	double q     = sensorData_ptr->imuData_ptr->q; // Pitch rate
	double r     = sensorData_ptr->imuData_ptr->r; // Yaw rate

    double phi_cmd = controlData_ptr->phi_cmd;
    double theta_cmd = controlData_ptr->theta_cmd;

    controlData_ptr->de = pitch_control(theta_cmd, theta, q, TIMESTEP); // Elevator deflection [rad]
    controlData_ptr->dr = yaw_damper(r); 								// Rudder deflection [rad]
    controlData_ptr->da_r = roll_control(phi_cmd, phi, p, TIMESTEP);    // Right Aileron deflection [rad]
	controlData_ptr->da_l = -controlData_ptr->da_r; 					// Left aileron deflection [rad]
	controlData_ptr->dthr = 0; // throttle
	controlData_ptr->df_l = 0; // left flap
	controlData_ptr->df_r = 0; // right flap
}
// END MAIN CONTROL FUNCTION
/// *****************************************************************************************
/// *****************************************************************************************
/// *****************************************************************************************







// Roll get_control law: angles in radians. Rates in rad/s. Time in seconds
/*                _______________                __________
  phi_cmd  _     |               |    _     da  |          |  phi
    ----->|+|--->|  roll tracker |-->|+|------->|          |---------
           -     |_______________|    -         |          |  p      |
           ^           (PI)           ^     dr  | Aircraft |-------  |
           |                        - |  ------>|          |  r    | |
           |                          | |       |          |-----  | |
         - |                          | |       |__________|     | | |
           |                          | |       ______________   | | |
           |                          | |      |              |  | | |
           |                          |  ------| yaw   damper |<-  | |
           |                          |        |______________|    | |
           |                          |        ________________    | |
           |                           -------| roll damper (P)|<--  |
           |                                   ----------------      |
            ---------------------------------------------------------     */

double yaw_damper (double yawrate)
{
// Discrete time filter equation at time step k
// y_yaw(k) = b0*u(k) + b1*u(k-1) - a1*y(k-1)
    
    
	u_yaw[k] = yawrate;  //current time step input (r)

	// Filter:
	// y_yaw(k) = b0*u(k) 	+	   b1*u(k-1)   		 + - a1*y(k-1)
	y_yaw[k] = b_yaw[0]*u_yaw[k] + b_yaw[1]*u_yaw[k-1] - a_yaw[1]*y_yaw[k-1];

	// Update past time step input/output for next frame
	u_yaw[k-1] = u_yaw[k];
	y_yaw[k-1] = y_yaw[k];


    //Output rudder command
    dr = y_yaw[k];


    // Saturation
	if (fabs(dr) > RUDDER_AUTH_MAX) {
		dr = sign(dr)*RUDDER_AUTH_MAX;		// yawdamper authority limited to +/-25 deg
	}
	return dr;
}



static double roll_control (double phi_ref, double roll_angle, double rollrate, double delta_t)
{
	// ROLL tracking controller implemented here


	// roll attitude tracker
	e[0] = phi_ref - roll_angle;
	integrator[0] += e[0]*delta_t*anti_windup[0]; //roll error integral (rad)

	    //proportional term + integral term              - roll damper term
	da  = roll_gain[0]*e[0] + roll_gain[1]*integrator[0] - roll_gain[2]*rollrate;

	//eliminate windup
	if      (da >= AILERON_AUTH_MAX && e[0] > 0) {anti_windup[0] = 1; da = AILERON_AUTH_MAX;}
	else if (da >= AILERON_AUTH_MAX && e[0] < 0) {anti_windup[0] = 0; da = AILERON_AUTH_MAX;}  //stop integrating
	else if (da <= -AILERON_AUTH_MAX && e[0] > 0) {anti_windup[0] = 0; da = -AILERON_AUTH_MAX;}  //stop integrating
	else if (da <= -AILERON_AUTH_MAX && e[0] < 0) {anti_windup[0] = 1; da = -AILERON_AUTH_MAX;}
	else {anti_windup[0] = 1;}

    return da;
}










// Pitch get_control law: angles in radians. Rates in rad/s. Time in seconds
/*                                                  __________
                   _______________                 |          |  theta
theta_cmd  _      |               |       _   de   |          |---------
    ----->|+|---->| Theta Tracker |----->|+|------>| Aircraft |  q      |
           -      |_______________|       -        |          |-----    |
           ^            (PI)              ^        |__________|     |   |
         - |                            - |        ______________   |   |
           |                              |       |              |  |   |
           |                               -------| Pitch Damper |<-    |
           |                                      |______________|      |
            ------------------------------------------------------------     */
static double pitch_control(double the_ref, double pitch, double pitchrate, double delta_t)
{
	// pitch attitude tracker
	e[1] = the_ref - pitch;
	integrator[1] += e[1]*delta_t*anti_windup[1]; //pitch error integral

       // proportional term + integral term               - pitch damper term
    de = pitch_gain[0]*e[1] + pitch_gain[1]*integrator[1] - pitch_gain[2]*pitchrate;    // Elevator output

	//eliminate wind-up
	if      (de >= ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] < 0) {anti_windup[1] = 0; de = ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}  //stop integrating
	else if (de >= ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] > 0) {anti_windup[1] = 1; de = ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}
	else if (de <= -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] < 0) {anti_windup[1] = 1; de = -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}
	else if (de <= -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] > 0) {anti_windup[1] = 0; de = -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}  //stop integrating
	else {anti_windup[1] = 1;}

	return de;  //rad
}








// Reset of controller
extern void reset_control(struct control *controlData_ptr){
	// Here: code to reset the controller
	controlData_ptr->dthr = 0; // throttle
	controlData_ptr->de   = 0; // elevator
	controlData_ptr->dr   = 0; // rudder
	controlData_ptr->da_l = 0; // left aileron
	controlData_ptr->da_r = 0; // right aileron
	controlData_ptr->df_l = 0; // left flap
	controlData_ptr->df_r = 0; // right flap

}
