/*! \file	serial_mpc5200.c
 *	\brief	Serial port handling for MPC5200B
 *
 *	\details
 *
 *	\author University of Minnesota
 *	\author Aerospace Engineering and Mechanics
 *	\copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: serial_mpc5200.c 752 2011-12-21 20:14:23Z murch $
 */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

#include "serial_mpc5200.h"


/***************************************************************************
 * Open and configure serial port
 ***************************************************************************/
int open_serial(char* serial_port,int baudrate)
{
	int fd;
	struct termios tio_serial;

	/* open serial port */
	fd = open(serial_port, O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (fd == -1) {
			fprintf(stderr,"open serial: unable to open %s - %s\n",	serial_port, strerror(errno));
			exit(-1);
		}

	/* Serial port setting */
	bzero(&tio_serial, sizeof(tio_serial));
	tio_serial.c_cflag = CS8 | CLOCAL | CREAD;
	tio_serial.c_iflag = IGNBRK | IGNPAR;
	tio_serial.c_oflag = 0;

	cfsetispeed(&tio_serial, baudrate);
	cfsetospeed(&tio_serial, baudrate);

	/* Flush buffer; parameters take effect immediately */
	tcflush(fd, TCIOFLUSH);
	tcsetattr(fd, TCSANOW, &tio_serial);

	return (fd);
}
/************************* end initiallize serial port *******************/
