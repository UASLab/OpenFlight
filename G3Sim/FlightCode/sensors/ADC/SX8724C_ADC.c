/*! \file SX8724C_ADC.c
 *	\brief Semtech SX8724C ADC source code
 *
 *	\details This file implements the code to read the Semtech SX8724C ADC chip.
 *	\ingroup adc_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: SX8724C_ADC.c 970 2013-04-12 22:12:25Z lie $
 */

#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
#include <cyg/io/i2c_mpc5xxx.h>

#include "../../utils/misc.h"
#include "adc_interface.h"
#include "SX8724C_ADC.h"


void init_adc(){
	unsigned char   command[2] = {RegExtAdd,SetRegExtAdd};

	// Set the I2C address to use external pins for lowest two bits. #0 should remain at default address.
	if(2 != cyg_i2c_tx(&SX8724C_ADC_default, &command[0], 2)){
		fprintf(stderr,"\n init_adc: 2 bytes not written");
	}
}

int read_adc(uint16_t *signal_counts_ptr){	
	int  i = 0, status = 0, k = 0;
	short tmp;
	unsigned char   DataBuf[2], command[8] = {RegACCfg0,SetRegACCfg0,SetRegACCfg1,SetRegACCfg2,SetRegACCfg3,SetRegACCfg4,SetRegACCfg5,RegACOutLsb};
	cyg_i2c_device * device;

	for(k = 0; k < 3; k++){			// Changed from  k < 2
		if(k == 1){
			device = &SX8724C_ADC_1;		// Changed from &SX8724C_ADC_1
		}else if(k == 2){
			device = &SX8724C_ADC_2;
		}else {
			device = &SX8724C_ADC_0;
		}

		// Loop over all of the channels on one chip - takes 3.6 msec with current settings
		// TODO: set actual number of channels used, make sure timing is set appropriately as well.
		for(i = 2; i < 8; i++){

			command[6] = (Amux | i)<<1;

			// Setup registers and trigger conversion
			if(7 != cyg_i2c_tx(device, &command[0], 7)){
				fprintf(stderr,"\n read_adc: 7 bytes not written");
				cyg_thread_delay(1);
				continue;
			}
			cyg_thread_delay(2); // delay to wait for conversion to complete

			cyg_i2c_transaction_begin(device); // start the transaction

			// set register to read from
			if(1 != cyg_i2c_transaction_tx(device, true, &command[7], 1, false)){
				status |= 1 << (8+i + k*8);
				fprintf(stderr,"\n read_adc: byte %x not written for channel %d",command[1],i + k*8);
			}
			else{
				// read ADC conversion result, two bytes
				if(2 != cyg_i2c_transaction_rx(device, true, &DataBuf[0], 2, true, true)){
					status |= 1 << (8+i + k*8);
					fprintf(stderr,"\n read_adc: 2 bytes not read from channel %d",i + k*8);
				}
				else{
					// Convert binary data into counts and store in pointer location
					//fprintf(stderr,"\n Data Buf = %X %X",DataBuf[1],DataBuf[0]);
					endian_swap(DataBuf,0,2);// data is a 16-bit word in two's complement format. Sec 7.7.8
					memcpy(&tmp,&DataBuf,2);
					//fprintf(stderr,"\n Tmp = %04X",tmp);
					*(signal_counts_ptr + i + k*8) = (uint16_t)(tmp >> 3); // convert to uint16_t
					//fprintf(stderr,"\n Signal Counts [%d] = %04X",i+k*8,*(signal_counts_ptr+i+k*8));
//					printf("\n Channel %d read = %d",i + k*8, tmp + 0x8000));
				}
			}
			cyg_i2c_transaction_end(device); // end the transaction

			cyg_thread_delay(1); // delay between i2c calls
		}

	}
	return status;
}

