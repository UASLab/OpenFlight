/*! \file heading_tracker.c
 *	\brief heading tracker source code
 *
 *	\details The heading tracker is a classical PI design that tracks pitch angle (theta), roll angle (phi),
 *	heading angle (psi), altitude (h), and airspeed (ias).
 *	A yaw damper and roll damper are used for the lateral axis, and a pitch damper is used for the longitudinal axis.
 *
 *	\ingroup control_fcns
 *
 *	\author University of Minnesota
 *	\author Aerospace Engineering and Mechanics
 *	\copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: baseline_control.c 845 2012-06-17 20:15:29Z joh07594 $
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "control_interface.h"


//////////////////////////////////////////////////////////////
#ifdef SIL_SIM
	#include "../aircraft/thor_config.h"  // for SIL sim only, use "thor" or "faser"
#else 
	#include AIRCRAFT_UP1DIR
#endif
//////////////////////////////////////////////////////////////


/// Definition of local functions: ****************************************************
static double yaw_damper (double yawrate);
static double heading_control (double head_ref, double head_angle, double roll_angle, double rollrate, double delta_t);
static double altitude_control(double alt_ref, double altitude, double pitch, double pitchrate, double delta_t);
static double speed_control(double speed_ref, double airspeed, double delta_t);
static double phase_wrapper(double psi, double psiDelta);
#ifdef SIL_SIM
	static double lp_filter(double signal, double *u, double *y);   //USE FOR SIL ONLY
#endif


// initialize pitch and roll angle tracking errors, integrators, and anti wind-up operators
// 0 values correspond to the roll tracker, 1 values correspond to the theta tracker, 2 values to altitude tracker, 3 to speed tracker
static double e[5] = {0,0,0,0,0};
static double integrator[4] = {0,0,0,0};
static short anti_windup[4]={1,1,1,1};   // integrates when anti_windup is 1
/// ****************************************************************************************
/// Phase wrapper variables
static int wrapCtr = 0;
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
static double dr; // Delta rudder
/// ****************************************************************************************
/// Roll, Pitch, Altitude, & Speed Controller Gains
#ifdef AIRCRAFT_THOR
	static double roll_gain[3]  = {-0.64,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.90,-0.30,-0.08};  // PI gains for theta tracker and pitch damper
	static double alt_gain[2] 	= {0.023,0.0010}; 		// PI gains for altitude tracker
	static double v_gain[2] 	= {0.15, 0.040};		// PI gains for speed tracker
	static double head_gain 	= 1.5;					// P gain for heading tracker
#endif
#ifdef AIRCRAFT_TYR
	static double roll_gain[3]  = {-0.64,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.90,-0.30,-0.08};  // PI gains for theta tracker and pitch damper
	static double alt_gain[2] 	= {0.023,0.0010}; 		// PI gains for altitude tracker
	static double v_gain[2] 	= {0.15, 0.040};		// PI gains for speed tracker
	static double head_gain 	= 1.5;					// P gain for heading tracker
#endif
#ifdef AIRCRAFT_FASER
	static double roll_gain[3]  = {-0.52,-0.20,-0.07};
	static double pitch_gain[3] = {-0.84,-0.23,-0.08};
	static double alt_gain[2] 	= {0.021,0.0017};
	static double v_gain[2] 	= {0.091, 0.020};
	static double head_gain 	= 1.2;
#endif
#ifdef AIRCRAFT_IBIS
	static double roll_gain[3]  = {-0.52,-0.20,-0.07};
	static double pitch_gain[3] = {-0.84,-0.23,-0.08};
	static double alt_gain[2] 	= {0.021,0.0017};
	static double v_gain[2] 	= {0.091, 0.020};
	static double head_gain 	= 1.2;
#endif
#ifdef AIRCRAFT_BALDR
	static double roll_gain[3]  = {-0.52,-0.20,-0.07};
	static double pitch_gain[3] = {-0.84,-0.23,-0.08};
	static double alt_gain[2] 	= {0.021,0.0017};
	static double v_gain[2] 	= {0.091, 0.020};
	static double head_gain 	= 1.2;
#endif
static double da; // Delta aileron
static double de; // Delta elevator
static double dthr; // Delta throttle


#ifdef SIL_SIM
	// USE FOR SIL ONLY
	/// Low Pass Filter for speed and altitude signals initialization
	static double u_alt[2] = {0,0}; //input of altitude low pass filter { u(k), u(k-1) }
	static double y_alt[2] = {0,0}; //output of altitude low pass filter { y(k), y(k-1) }

	static double u_speed[2] = {0,0}; //input of altitude low pass filter { u(k), u(k-1) }
	static double y_speed[2] = {0,0}; //output of altitude low pass filter { y(k), y(k-1) }
#endif


/// Return control outputs based on references and feedback signals.
extern void get_control(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr) {


	// PLACE OPTIONAL PHI BIAS HERE
	//navData_ptr->phi += DEG*pi/180;


#ifdef AIRCRAFT_THOR
	double base_pitch_cmd= 0.0872664;  	// (Trim value) use 5 deg (0.0872664 rad) for flight, use 3.082 deg (0.0537910 rad) in sim
#endif
#ifdef AIRCRAFT_TYR
	double base_pitch_cmd= 0.0872664;  	// (Trim value) use 5 deg (0.0872664 rad) for flight, use 3.082 deg (0.0537910 rad) in sim
#endif
#ifdef AIRCRAFT_FASER
	double base_pitch_cmd= 0.0872664;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
#endif
#ifdef AIRCRAFT_IBIS
	double base_pitch_cmd= 0.0872664;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
#endif
#ifdef AIRCRAFT_BALDR
	double base_pitch_cmd= 0.0872664;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
#endif

	double phi   = navData_ptr->phi;					    // Roll angle
	double theta = navData_ptr->the - base_pitch_cmd; 	    // Pitch angle: subtract theta trim value to convert to delta coordinates
	double psi	 = atan2(navData_ptr->ve,navData_ptr->vn);  // Ground Track Heading angle
	double p     = sensorData_ptr->imuData_ptr->p; 		    // Roll rate
	double q     = sensorData_ptr->imuData_ptr->q;		    // Pitch rate
	double r     = sensorData_ptr->imuData_ptr->r; 		    // Yaw rate

    double psi_cmd = controlData_ptr->psi_cmd;
    double h_cmd   = controlData_ptr->h_cmd;
    double ias_cmd = controlData_ptr->ias_cmd;

#ifdef SIL_SIM
  // Filter altitude and airspeed signals FOR SIL ONLY
	sensorData_ptr->adData_ptr->h_filt = lp_filter(sensorData_ptr->adData_ptr->h, u_alt, y_alt);  	    // filtered ALTITUDE
	sensorData_ptr->adData_ptr->ias_filt = lp_filter(sensorData_ptr->adData_ptr->ias, u_speed, y_speed);	// filtered AIRSPEED
#endif



    // Snapshots
	if(time <= 50*TIMESTEP){
		controlData_ptr->signal_1 = psi;  // store initial HEADING on dummy variable signal_1
		controlData_ptr->signal_0 = sensorData_ptr->adData_ptr->h_filt;   	// store initial ALTITUDE on dummy variable signal_0
	}

	// Phase wrap
	controlData_ptr->signal_2 = phase_wrapper(psi, controlData_ptr->signal_3 - psi);		// Store the wrapped psi value
	controlData_ptr->signal_3 = psi;


    controlData_ptr->de   = altitude_control(h_cmd, sensorData_ptr->adData_ptr->h_filt - controlData_ptr->signal_0, theta, q, TIMESTEP);
    controlData_ptr->dr   = yaw_damper(r);
    controlData_ptr->da_r = heading_control(psi_cmd, controlData_ptr->signal_2 - controlData_ptr->signal_1, phi, p, TIMESTEP);
	controlData_ptr->da_l = -controlData_ptr->da_r;
	controlData_ptr->dthr = speed_control(ias_cmd, sensorData_ptr->adData_ptr->ias_filt, TIMESTEP);
	controlData_ptr->df_l = 0;
	controlData_ptr->df_r = 0;


}

// PhaseWrap code to calculate actual heading angle
double phase_wrapper(double psi, double psiDelta)
{
		 double psiActual;

		 if(psiDelta > 3.14159){		//passing from quadrant two to three
			wrapCtr++;
		 }
		 if(psiDelta < -3.14159){		//passing from quadrant three to two
			wrapCtr--;
		 }
		 psiActual = psi + wrapCtr*2*3.1415926;
		 return psiActual;
}

#ifdef SIL_SIM
	//USE FOR SIL ONLY
double lp_filter(double signal, double *u, double *y)
	{
		const int m=1;  //m = order of denominator of low pass filter
	
		u[m] = signal;
	
		y[m] = 0.9608*y[m-1] + 0.0392*u[m-1];	// these coefficients come from a discretized low pass filter with a pole at 2 rad/sec
	
		u[m-1] = u[m];		// initialize past values for next frame
		y[m-1] = y[m];
	
		return y[m];
	}
#endif 


// Discrete time filter equation at time step k
// y_yaw(k) = b0*u(k) + b1*u(k-1) - a1*y(k-1)

double yaw_damper (double yawrate)
{

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


static double heading_control (double head_ref, double head_angle, double roll_angle, double rollrate, double delta_t)
{
	// Heading tracking controller implemented here
	double roll_limit = 0.785398; // Roll angle saturation limit (45 degrees)
	double head_out;

	e[4] = head_ref - head_angle;
	head_out = head_gain*e[4];

	if	(abs(head_out) >= roll_limit){
		head_out = sign(head_out)*roll_limit;
	}

	// roll attitude tracker
	e[0] = head_out - roll_angle;
	integrator[0] += e[0]*delta_t*anti_windup[0]; //roll error integral (rad)

	    //proportional term + integral term              - roll damper term
	da  = roll_gain[0]*e[0] + roll_gain[1]*integrator[0] - roll_gain[2]*rollrate;

	//eliminate windup
	if      (da >= AILERON_AUTH_MAX && e[0] > 0) {anti_windup[0] = 1; da = AILERON_AUTH_MAX;}
	else if (da >= AILERON_AUTH_MAX && e[0] < 0) {anti_windup[0] = 0; da = AILERON_AUTH_MAX;}    //stop integrating
	else if (da <= -AILERON_AUTH_MAX && e[0] > 0) {anti_windup[0] = 0; da = -AILERON_AUTH_MAX;}  //stop integrating
	else if (da <= -AILERON_AUTH_MAX && e[0] < 0) {anti_windup[0] = 1; da = -AILERON_AUTH_MAX;}
	else {anti_windup[0] = 1;}

    return da;
}


static double altitude_control(double alt_ref, double altitude, double pitch, double pitchrate, double delta_t)
{
	double pitch_limit = 0.349066; // Pitch angle saturation limit (20 degrees)
	double h_out;

	// Altitude tracker
	e[2] = alt_ref - altitude;
	integrator[2] += e[2]*delta_t*anti_windup[2]; // altitude error integral

		//	proportional term + integral term   (output of altitude PI block)
	h_out = alt_gain[0]*e[2] + alt_gain[1]*integrator[2];

	if	(abs(h_out) >= pitch_limit){
		h_out = sign(h_out)*pitch_limit;
	}

	// pitch attitude tracker
	e[1] = h_out - pitch;
	integrator[1] += e[1]*delta_t*anti_windup[1]; //pitch error integral

       //proportional term + integral term               - pitch damper term
    de = pitch_gain[0]*e[1] + pitch_gain[1]*integrator[1] - pitch_gain[2]*pitchrate;    // Elevator output

	//eliminate wind-up on theta integral
	if      (de >= ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] < 0) {anti_windup[1] = 0; de = ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}  //stop integrating
	else if (de >= ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] > 0) {anti_windup[1] = 1; de = ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}
	else if (de <= -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] < 0) {anti_windup[1] = 1; de = -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}
	else if (de <= -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[1] > 0) {anti_windup[1] = 0; de = -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM;}  //stop integrating
	else {anti_windup[1] = 1;}

	//eliminate wind-up on altitude integral
	if      (de >= ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[2] < 0) {anti_windup[2] = 1;}
	else if (de >= ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[2] > 0) {anti_windup[2] = 0;}  //stop integrating
	else if (de <= -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[2] < 0) {anti_windup[2] = 0;}  //stop integrating
	else if (de <= -ELEVATOR_AUTH_MAX-ELEVATOR_TRIM && e[2] > 0) {anti_windup[2] = 1;}
	else {anti_windup[2] = 1;}

	return de;  //rad
}

static double speed_control(double speed_ref, double airspeed, double delta_t)
{
	// Speed tracker
	e[3] = speed_ref - airspeed;
	integrator[3] += e[3]*delta_t*anti_windup[3]; // altitude error integral

		// proportional term  + integral term
	dthr = v_gain[0]*e[3] + v_gain[1]*integrator[3];    // Throttle output

	//eliminate wind-up on airspeed integral
	if      (dthr >= THROTTLE_AUTH_MAX-THROTTLE_TRIM && e[3] < 0) {anti_windup[3] = 1; dthr = THROTTLE_AUTH_MAX-THROTTLE_TRIM;}
	else if (dthr >= THROTTLE_AUTH_MAX-THROTTLE_TRIM && e[3] > 0) {anti_windup[3] = 0; dthr = THROTTLE_AUTH_MAX-THROTTLE_TRIM;}  //stop integrating
	else if (dthr <= THROTTLE_AUTH_MIN-THROTTLE_TRIM && e[3] < 0) {anti_windup[3] = 0; dthr = THROTTLE_AUTH_MIN-THROTTLE_TRIM;}  //stop integrating
	else if (dthr <= THROTTLE_AUTH_MIN-THROTTLE_TRIM && e[3] > 0) {anti_windup[3] = 1; dthr = THROTTLE_AUTH_MIN-THROTTLE_TRIM;}
	else {anti_windup[3] = 1;}

	return dthr; // non dimensional
}


// Reset parameters to initial values
extern void reset_control(struct control *controlData_ptr){

	integrator[0] = integrator[1] = integrator[2] = integrator[3] = 0;
	anti_windup[0] = anti_windup[1] = anti_windup[2] = anti_windup[3] = 1;
	e[0] = e[1] = e[2] = e[3] = e[4] = 0;
	u_yaw[0] = u_yaw[1] = y_yaw[0] = y_yaw[1] = 0;

	controlData_ptr->dthr = 0; // throttle
	controlData_ptr->de   = 0; // elevator
	controlData_ptr->dr   = 0; // rudder
	controlData_ptr->da_l = 0; // left aileron
	controlData_ptr->da_r = 0; // right aileron
	controlData_ptr->df_l = 0; // left flap
	controlData_ptr->df_r = 0; // right flap

	controlData_ptr->signal_1 = 0; // heading snapshot
	controlData_ptr->signal_0 = 0; 	 // altitude snapshot

	controlData_ptr->signal_2 = 0; 	 // wrapped psi
	controlData_ptr->signal_3 = 0;  // previous psi measurement

	wrapCtr = 0;					 // phase wrapping counter

	controlData_ptr->psi_cmd = 0; 	 // psi command

}

