
/*!	\file waypoint_guidance.c
 *	\brief Waypoint tracker get_guidance law
 *
 *	\details Designed by Peter pinit. Waypoints specified as relative distances start (0,0) point is the point where autopilot is switched
 *	\ingroup guidance_fcns
 *
 * \author SZTAKI
 * \author Systems and Control Laboratory
 * \copyright Copyright 2012 
 *
 * $Id$
 */

#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "../system_id/systemid_interface.h"
#include "../utils/matrix.h"
#include "guidance_interface.h"




//////////////////////////////////////////////////////////////
//#include "../utils/matrix.c" //Required for SIL sim only. Also must comment out #include <unistd.h> and #include <termios.h> inside matrix.c

//#include "../aircraft/thor_config.h"  // for SIL sim only, use "thor" or "faser"
#include AIRCRAFT_UP1DIR
//////////////////////////////////////////////////////////////




//local function definition
void LatLonAltToEcef2(MATRIX vector, MATRIX position);
double distance2waypoint(MATRIX wp_curr, MATRIX pos_ned);
double wraparound(double dta);
double mysign(double v);

//////////////////////////////////////////////////////////////
// Waypoint definition
#define numofwaypoints 6
static short nextwaypoint=1;

// order: NO, EA, IAS, alt
// FISRT ROW MUST BE {0, 0, IAS, alt} !!!!

static double waypoints[numofwaypoints][4] =    {{0, 0, 20.0, 60.0},
{0, 200, 20.0, 60.0},
{120, 200, 20.0, 60.0},
{80, 170, 20.0, 60.0},
{160, 90, 20.0, 60.0},
{120, 0, 20.0, 60.0}
};




// Control parameters
#define LTOL    10.0        // tolerance of linear segment tracking [deg]
#define FTOL    20.0        // tolerance of feasability checking circle [m]
#define WPTOL   10.0        // tolerance for reaching waypoints [m]
#define PHI0    40*D2R  	// considered maximum bank angle [deg]
#define s       75.0      	// forward arc length in circular path tracking [m]
#define k_R     1    		// circle radius scaling


//local variables
static MATRIX pos_lla, pos_ecef, pos_ecef0, T_ecef2ned, v_ned, tmp31, pos_ned, WP_goal, WP_prev;

static short guide_init=0, guide_start=0;   // init for initialization of matrices, start for start of waypoint guidance

static short pinit=0, lc=10;  
static double d2WP, xA, yA, xT, yT, xC, yC, psiT, dpsi, psi, Rt, R2, psiC;


extern void get_guidance(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr){

if (time>0.05){
	#ifdef AIRCRAFT_THOR
		controlData_ptr->ias_cmd = 17;				//Trim airspeed (m/s)
	#endif
	#ifdef AIRCRAFT_TYR
		controlData_ptr->ias_cmd = 17;				//Trim airspeed (m/s)
	#endif
	#ifdef AIRCRAFT_FASER
		controlData_ptr->ias_cmd = 23;
	#endif
	#ifdef AIRCRAFT_IBIS
		controlData_ptr->ias_cmd = 23;
	#endif
	#ifdef AIRCRAFT_BALDR
		controlData_ptr->ias_cmd = 23;
	#endif

	// Initialization of algorithm and variables	
    if (guide_init==0)  // init variables
    {
        pos_lla     = mat_creat(3,1,ZERO_MATRIX);
        pos_ecef    = mat_creat(3,1,ZERO_MATRIX);
        pos_ecef0   = mat_creat(3,1,ZERO_MATRIX);
        v_ned       = mat_creat(3,1,ZERO_MATRIX);
        pos_ned     = mat_creat(3,1,ZERO_MATRIX);
        tmp31       = mat_creat(3,1,ZERO_MATRIX);
        T_ecef2ned  = mat_creat(3,3,ZERO_MATRIX);        
        WP_goal     = mat_creat(2,1,ZERO_MATRIX);
        WP_prev     = mat_creat(2,1,ZERO_MATRIX);
        guide_init=1;
    }	    
    

	if (guide_start==0)		
	{
		pos_lla[0][0]=navData_ptr->lat;
		pos_lla[1][0]=navData_ptr->lon;
		pos_lla[2][0]=navData_ptr->alt;

		LatLonAltToEcef2(pos_ecef0, pos_lla);

		// transformation matrix for LaunchPoint ECEF |--> NED for initial point
		T_ecef2ned[0][0] = -sin(pos_lla[0][0])*cos(pos_lla[1][0]); T_ecef2ned[0][1] = -sin(pos_lla[0][0])*sin(pos_lla[1][0]); T_ecef2ned[0][2] =  cos(pos_lla[0][0]);
		T_ecef2ned[1][0] = -sin(pos_lla[1][0]);                    T_ecef2ned[1][1] =  cos(pos_lla[1][0]);                    T_ecef2ned[1][2] =  0.0;
		T_ecef2ned[2][0] = -cos(pos_lla[0][0])*cos(pos_lla[1][0]); T_ecef2ned[2][1] = -cos(pos_lla[0][0])*sin(pos_lla[1][0]); T_ecef2ned[2][2] = -sin(pos_lla[0][0]);

		//save next waypoint coordinates
		WP_goal[0][0]=waypoints[nextwaypoint][0];
		WP_goal[1][0]=waypoints[nextwaypoint][1];
		WP_prev[0][0]=0;
		WP_prev[1][0]=0;

		guide_start=1;
	}

	// current vehicle position/vel (computed at every iteration)
	pos_lla[0][0]=navData_ptr->lat;
	pos_lla[1][0]=navData_ptr->lon;
	pos_lla[2][0]=navData_ptr->alt;
	v_ned[0][0] = navData_ptr->vn;
	v_ned[1][0] = navData_ptr->ve;
	v_ned[2][0] = navData_ptr->vd;
	psi=atan2(v_ned[1][0],v_ned[0][0]);

	LatLonAltToEcef2(pos_ecef, pos_lla);
	mat_sub(pos_ecef, pos_ecef0, tmp31);
	mat_mul(T_ecef2ned, tmp31, pos_ned);

	d2WP=distance2waypoint(WP_goal, pos_ned);

	// change of target waypoint: check if vehicle is within x meters of the target waypoint
	if ((d2WP < WPTOL) && (guide_start==1)) {
		if(nextwaypoint == numofwaypoints-1) nextwaypoint = 0; // change back to first waypoint
		else  nextwaypoint++;

		// select new waypoint parameters
		WP_prev[0][0]=WP_goal[0][0];
		WP_prev[1][0]=WP_goal[1][0];
		WP_goal[0][0] = waypoints[nextwaypoint][0];
		WP_goal[1][0] = waypoints[nextwaypoint][1];

		pinit=0;		// begin tracking next waypoint
	}

	// actual aircraft position
	xA=pos_ned[0][0];   // North
	yA=pos_ned[1][0];   // East
	


	///////////////////////// DECIDE WHICH TRACKING METHOD TO DO /////////////////////////////////////////////////
	if (pinit==0)
	{
		if (sensorData_ptr->adData_ptr->ias_filt>10)		// make sure airspeed filter has initialized
		{
			xT=WP_goal[0][0];
			yT=WP_goal[1][0];
			psiT=atan2(yT-yA, xT-xA);    // Aircraft target azimuth angle

			// azimuth angle correction if required:
			if (fabs(psiT-wraparound(psi))>PI)
				psiT=psiT+mysign(wraparound(psi))*PI2;

			if (fabs(psiT-wraparound(psi))<LTOL*D2R)    // immediate linear path segment track
			{
				lc=1;			// begin linear segment tracking
				pinit=1;
			}
			else    // calculate and validate circular path tracking
			{
				Rt=pow(controlData_ptr->ias_cmd, 2)/g/tan(PHI0)/k_R;  // turn radius
				// center of circle:
				dpsi=mysign(v_ned[0][0]*(WP_goal[1][0]-WP_prev[1][0])-v_ned[1][0]*(WP_goal[0][0]-WP_prev[0][0]))*90*D2R;
				xC=xA+Rt*cos(psi+dpsi);
				yC=yA+Rt*sin(psi+dpsi);

				// check feasibility
				R2=sqrt(pow(WP_goal[0][0]-xC, 2)+pow(WP_goal[1][0]-yC, 2));

				if (R2<Rt+FTOL)   // infeasible problem calculate virtual, additional point
				{
					// virtual point to track (from there, the original point will be achievable)
					xT=xA+4*Rt*cos(psi);
					yT=yA+4*Rt*sin(psi);
					lc=8;
					pinit=1;
				}
				else    // feasible problem, track circular path
				{
					lc=0;		// begin tracking circular path to line up with waypoint
					pinit=1;
				}
			}
		} // end if nonzero velocity
		else
			controlData_ptr->psi_cmd=0;
	}   // end decide about tracking method



	///////////////////////////////TURNING MANEUVER//////////////////////////////////////////////////
	// turning maneuver
	if (lc==0)  //
	{
		xT=WP_goal[0][0];
		yT=WP_goal[1][0];
		psiT=atan2(yT-yA, xT-xA);    // Aircraft target azimuth angle
		// azimuth angle correction if required:
		if (fabs(psiT-wraparound(psi))>PI)
			psiT=psiT+mysign(wraparound(psi))*PI2;

		// check if the algorithm can change to linear segment tracking
		if (fabs(psiT-wraparound(psi))<LTOL*D2R)
		{
			lc=1;			// change to linear segment tracking
		}
		else    			// track circular path
		{
			// calculate azimuth angle along circle
			psiC=atan2(yA-yC, xA-xC);

			// calculate goal azimuth angle considering forward arc length
			psiC=psiC+mysign((xA-xC)*v_ned[1][0]-(yA-yC)*v_ned[0][0])*s/Rt;

			xT=xC+Rt*cos(psiC);
			yT=yC+Rt*sin(psiC);
		}
	}


	//////////////////////////REACHABILITY MANEUVER/////////////////////////////////////////////////////////
	if (lc==8)
	{
		// calculate actual circle parameters
		Rt=pow(controlData_ptr->ias_cmd, 2)/g/tan(PHI0)/k_R;  // turn radius
		// center of circle:
		dpsi=mysign(v_ned[0][0]*(WP_goal[1][0]-WP_prev[1][0])-v_ned[1][0]*(WP_goal[0][0]-WP_prev[0][0]))*90*D2R;

		xC=xA+Rt*cos(psi+dpsi);
		yC=yA+Rt*sin(psi+dpsi);

		// check feasibility
		R2=sqrt(pow(WP_goal[0][0]-xC, 2)+pow(WP_goal[1][0]-yC, 2));
		if (R2>=Rt+FTOL)   			// feasible problem, track circle
		{
			// calculate azimuth angle along circle
			psiC=atan2(yA-yC, xA-xC);

			// calculate goal azimuth angle considering forward arc length
			psiC=psiC+mysign((xA-xC)*v_ned[1][0]-(yA-yC)*v_ned[0][0])*s/Rt;

			xT=xC+Rt*cos(psiC);
			yT=yC+Rt*sin(psiC);

			lc=0;					// change to circular tracking maneuver
		}
	}

	// Aircraft target azimuth angle and heading angle difference
	psiT=atan2(yT-yA, xT-xA);

	// azimuth angle correction if required:
	if (fabs(psiT-wraparound(psi))>PI)
		psiT=psiT+mysign(wraparound(psi))*PI2;

		controlData_ptr->psi_cmd=(psiT-wraparound(psi));

		controlData_ptr->r_cmd=((nextwaypoint+1)*10+lc); 		// store the current waypoint and tracking mode on r_cmd.
																// lc=0 -> turning, lc=1 -> flying directly towards waypoint, lc=8 -> reachability maneuver
}
}
    
/////////////////////////////////////////////////////////////////////////////////////////
///// LOCAL FUNCTIONS ////////////////////////////

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// signum function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double mysign(double v) {
    double temp=0;
    
    if (v<0)
        temp = -1;
    else if (v>0)
        temp = 1;
    else
        temp = 0;
    
    return temp;
}

void LatLonAltToEcef2(MATRIX vector, MATRIX position) {
    
    #define EARTH_RADIUS 6378137         /* earth semi-major axis radius (m) */
            #define ECC2		 0.0066943799901 /* major eccentricity squared */
            double Rn, alt, denom;
    double sinlat, coslat, coslon, sinlon;
    
    
    sinlat = sin(position[0][0]);
    coslat = cos(position[0][0]);
    coslon = cos(position[1][0]);
    sinlon = sin(position[1][0]);
    alt = position[2][0];
    
    denom = (1.0 - (ECC2 * pow(sinlat, 2)));
    denom = fabs(denom);
    
    Rn = EARTH_RADIUS / sqrt(denom);
    
    vector[0][0] = (Rn + alt) * coslat * coslon;
    vector[1][0] = (Rn + alt) * coslat * sinlon;
    vector[2][0] = (Rn * (1.0 - ECC2) + alt) * sinlat;
}

double distance2waypoint(MATRIX wp_curr, MATRIX pos_ned) {
    return sqrt( pow((wp_curr[0][0]-pos_ned[0][0]), 2) + pow((wp_curr[1][0]-pos_ned[1][0]), 2) );
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// wrap around for -180 and + 180
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double wraparound(double dta) {
    
    //bound heading angle between -180 and 180
    if(dta >  PI) dta -= PI2;
    if(dta < -PI) dta += PI2;
    
    return dta;
}

void close_guidance(void){
	//free memory space
	mat_free(pos_lla);
	mat_free(pos_ecef);
	mat_free(pos_ecef0);
	mat_free(T_ecef2ned);
	mat_free(v_ned);
	mat_free(tmp31);
	mat_free(pos_ned);
	mat_free(WP_goal);
    mat_free(WP_prev);
}
