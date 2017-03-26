/*! \file	serial_mpc5200.h
 *	\brief	Serial port handling for MPC5200B header file
 *
 *	\details
 *
 *	\author University of Minnesota
 *	\author Aerospace Engineering and Mechanics
 *	\copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: serial_mpc5200.h 752 2011-12-21 20:14:23Z murch $
 */

#ifndef SERIAL_MPC5200_H_
#define SERIAL_MPC5200_H_

/* Serial ports  */

// SERIAL_RS232
#define SERIAL_PORT0 "/dev/termios0"	///< RS232 I/O, TTL output only
#define SERIAL_PORT1 "/dev/termios1"	///< RS232 I/O, TTL output only
// SERIAL_TTL
#define SERIAL_PORT2 "/dev/termios2"	///< PSC5, TTL I/O
#define SERIAL_PORT3 "/dev/termios3"	///< PSC4, TTL I/O
#define SERIAL_PORT4 "/dev/termios4"   	///< PSC2, TTL I/O

/// Open serial port and return handle for read/write.
int  open_serial(char* serial_port,	///< Serial port to open.
		int baudrate				///< Baudrate of serial port. Use "B115200" format.
		);

#endif

