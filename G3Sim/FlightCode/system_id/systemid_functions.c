/*! \file systemid_functions.c
 *	\brief Auxiliary System ID functions
 *
 *	\details  Auxiliary system ID functions. Doublets and multisines.
 *	\ingroup systemid_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: systemid_functions.c 756 2012-01-04 18:51:43Z murch $
 */
#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "systemid_interface.h"


double doublet(double t0, double currentTime, double duration, double amplitude) {
	double t = currentTime; // simulink current time

	if (t < t0)
		return 0;
	else if ((t >= t0) && (t < t0 + 0.5 * duration))
		return amplitude;
	else if ((t >= t0 + 0.5 * duration) && (t < t0 + duration))
		return -amplitude;
	if (t >= t0 + duration)
		return 0;

	return 0;
}
/*****************************************************************************/
double doublet121(double t0, double currentTime, double dur1, double dur2,
		double dur3, double amplitude) {
	double t = currentTime; // simulink current time

	if (t < t0) {
		return 0;
	} else {
		if ((t >= t0) && (t <= t0 + dur1)) {
			return amplitude;
		}

		if ((t >= t0 + dur1 + dur2) && (t <= t0 + dur1 + dur2 + dur3)) {
			return -amplitude;
		}

		if ((t >= t0 + dur1 + 2 * dur2 + dur3) && (t <= t0 + 2 * dur1 + 2
				* dur2 + dur3)) {
			return amplitude;
		}

	}

	return 0;
}

void one_multi_sine(double t, double *dsurf, double amp) {
	// frequencies, phase shifts, and amplitude
	static double freq[19] = { 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
			1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0 };
	static double phase[19] = { -1.27957909013141, 0.348919604845833,
			1.55845288184890, 2.33381811735615, -2.64342812535867,
			-1.67389505727660, -1.14853051767376, -2.02216246930373,
			-2.23926930233022, -2.13146859961157, 2.12830296200715,
			1.05375292070553, -1.20359723220569, -2.76268622179216,
			0.761666786086764, -1.36337190551698, 0.702943945363515,
			-2.04688882119523, 0.191156846541546 };

	double dtmp = 0.0;
	int i;

	for (i = 0; i < 19; i++) {
		dtmp += cos(freq[i] * 2 * PI * t + phase[i]) * sqrt(1.0 / 19) * amp; //rad, multi-sine signal
	}
	// assign control surface command to pointers
	*dsurf = dtmp;

}

void two_multi_sine(double t, double *dsurf1, double *dsurf2, double amp1,
		double amp2) {
	// frequencies, phase shifts, and amplitude
	static double freq1[9] = { 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8 };
	static double phase1[9] = { -0.137821438846238, -1.08680859297711,
			2.84479381592806, -0.802006213664591, -2.53910175103649,
			-2.42015912163347, 2.83051687898700, -1.18873893747093,
			-0.282979519213328 };

	static double freq2[9] = { 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9 };
	static double phase2[9] = { 3.09701787648288, 0.702903781602135,
			-2.79553911432363, 1.21228624745064, 1.26880068387565,
			-0.247242270325405, 0.257811486280133, 2.03325959168130,
			2.87014496403833 };

	double dtmp1 = 0.0;
	double dtmp2 = 0.0;
	int i;

	for (i = 0; i < 9; i++) {
		dtmp1 += cos(freq1[i] * 2 * PI * t + phase1[i]) * sqrt(1.0 / 9) * amp1; //rad, multi-sine signal
		dtmp2 += cos(freq2[i] * 2 * PI * t + phase2[i]) * sqrt(1.0 / 9) * amp2; //rad, multi-sine signal
	}
	// assign control surface command to pointers
	*dsurf1 = dtmp1;
	*dsurf2 = dtmp2;

}

void three_multi_sine(double t, double *de, double *da, double*dr) {
	// elevator frequencies and phase shifts
	static double freq_e[6] = { 0.2, 0.5, 0.8, 1.1, 1.4, 1.7 };
	static double phase_e[6] = { 1.58451760333862, -0.258368383798533,
			0.320626859635127, -2.79550026546313, 2.91618215748278,
			-1.55693424076394 };
	static double amp_e = 2.0; // amplitude, in degrees
	// aileron frequencies and phase shifts
	static double freq_a[6] = { 0.3, 0.6, 0.9, 1.2, 1.5, 1.8 };
	static double phase_a[6] = { 1.43549689823698, -1.24587349532040,
			-0.282364765506209, -2.87394881269454, -1.80524182936679,
			-1.79022442236836 };
	static double amp_a = 2.0; // amplitude, in degrees
	// rudder frequencies and phase shifts
	static double freq_r[6] = { 0.4, 0.7, 1.0, 1.3, 1.6, 1.9 };
	static double phase_r[6] = { 0.102843043899529, 2.93051441701122,
			2.50176467719111, 1.58251088240054, 0.158685053706918,
			1.76461734166891 };
	static double amp_r = 1.0; // amplitude, in degrees
	double detmp = 0;
	double datmp = 0;
	double drtmp = 0; // dummy variables
	int i;

	// Create multi sine inputs. There are 6 frequencies in each signal.
	for (i = 0; i < 6; i++) {
		detmp += cos(freq_e[i] * 2 * PI * t + phase_e[i]) * sqrt(1.0 / 6) * amp_e;//rad, elevator multi-sine
		datmp += cos(freq_a[i] * 2 * PI * t + phase_a[i]) * sqrt(1.0 / 6) * amp_a;//rad, aileron multi-sine
		drtmp += cos(freq_r[i] * 2 * PI * t + phase_r[i]) * sqrt(1.0 / 6) * amp_r;//rad, rudder multi-sine
	}
	// assign control surface commands to pointers
	*de = detmp;
	*da = datmp;
	*dr = drtmp;

}

