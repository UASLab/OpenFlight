/*! \file MAX127_ADC.c
 *	\brief MaximIC MAX127 ADC source code
 *
 *	\details This file implements the code to read the MaximIC MAX127 ADC chip.
 *	\ingroup adc_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: MAX127_ADC.c 756 2012-01-04 18:51:43Z murch $
 */

#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
#include <cyg/io/i2c_mpc5xxx.h>

#include "adc_interface.h"
#include "MAX127_ADC.h"

// Slave address is 0 1 0 1 A2 A1 A0  followed by R/W where R/W = 0 for write; = 1 for read.
// A2 A1 A0 are all tied to ground; this makes the slave address 0101 0000 => 0x50 write, 0101 0001 => 0x51 read. 

//Next the master sends a control byte. MSB = start (1) followed by the binary number of the 
//channel you wish to read; ch0=>000, ch7=>111. The next bit scelects the input voltage range
//should be 0 for 0v-5v and then another 0 bit to make it uni-polar. Finally there are 
//two bits that select the power down mode; use 00 for normal operation.
//The first control byte we want to read (ch0) is then = 1000 0000 or 0x80
	
void init_adc(){
}


int read_adc(uint16_t *signal_counts_ptr){	
	int  i, status =0;
	uint8_t    DataBuf[2];

	// Loop over all of the channels
	for(i = 0; i < 8; i++){ 
	
		// Try to send out the Control byte
		if(1 != cyg_i2c_tx(&MAX127_ADC, &controlByte[i], 1)){
			status |= 1 << (8+i);
			//fprintf(stderr,"\n read_adc: Control byte %x not written",controlByte[i]);
			continue;
		}
		
		cyg_thread_delay(1);
		// Try to request two bytes of data from slave
		if(2 != cyg_i2c_rx(&MAX127_ADC, DataBuf, 2)){
			status |= 1 << (8+i);
			//fprintf(stderr,"\n read_adc: 2 bytes not read from channel %d",i);
			continue;
		}
		else{
			// Convert binary data into counts and store in pointer location
			*(signal_counts_ptr + i) = (((uint16_t) DataBuf[0]) << 4) + ((((uint16_t) (DataBuf[1]&0xF0))) >> 4); // data is a 12-bit word; 4 LSB of second byte are not used 
		}
		cyg_thread_delay(1);
	}	

	return status;
}

