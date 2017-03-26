/*! \file IMU_iSensor.c
 *	\brief Analog Devices AD16405 IMU functions
 *
 	\details This file implements the init_imu() and read_imu() functions for the Analog Devices AD16405 IMU.
 *	\ingroup imu_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: IMU_iSensor.c 962 2013-03-19 01:32:29Z escobar $
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <cyg/io/serialio.h>
#include <cyg/io/io.h>
#include <cyg/kernel/kapi.h>
#include <cyg/io/spipsc.h>
#include <cyg/io/i2c_mpc5xxx.h>

#include "../../globaldefs.h"
#include "../../utils/misc.h"
#include "IMU_iSensor.h"
#include "imu_interface.h"


// Initialize SPI communication
int init_imu() {	
	// Open the SPI (PSC) device	
	Cyg_ErrNo ret;
	// Command to change internal dynamic filter
	uint32_t commandLength;
	uint16_t command[1]={0};
	uint8_t output[2];

	ret = cyg_io_lookup( SPIPSC_PORT1, &hSPI );

	if ( ENOERR != ret ) {
		#ifdef verbose
			fprintf( stderr, "init_imu: unable to open %s - %s\n",SPIPSC_PORT1, strerror(ret) );
		#endif
		return(-1);
	}

	// Set the blocking status of the SPI port to non-blocking (0)
	uint32_t read_blk_status = 0, write_blk_status = 0;
	uint32_t len;
	len = sizeof( uint32_t );

	// Set blocking status
	cyg_io_set_config( hSPI, CYG_IO_SET_CONFIG_READ_BLOCKING,
			&read_blk_status, &len );
	cyg_io_set_config( hSPI, CYG_IO_SET_CONFIG_WRITE_BLOCKING,
			&write_blk_status, &len );

	// Internal Digital Filter bandwidth setup
	//command[0] = 0xB803; // Cutoff 50 Hz
	command[0] = 0xB804; // Cutoff 16 Hz
	//command[0] = 0xB806; // Cutoff 1.6 Hz
	commandLength = 2; //bytes to write
		
	// Send command
	cyg_io_write( hSPI, command, &commandLength);
	cyg_thread_delay(5);
	cyg_io_read( hSPI, output, &commandLength);


	#ifdef verbose	
		// This section prints out the SPI register information. For debugging only
		uint32_t cr,sicr,clken,ccr,ctlr,ctur,rfalarm,tfalarm,cdm_mclk;
		byte *p8;
		uint16_t *p16;
		uint32_t *p32;

		p8=(byte *)(MPC5XXX_PSC1+MPC5XXX_PSC_CR);
		cr=*p8;

		p32=(uint32_t *)(MPC5XXX_PSC1+MPC5XXX_PSC_SICR);
		sicr=*p32;

		p32=(uint32_t *)(MPC5XXX_CDM+MPC5XXX_CDM_CLKEN);
		clken=*p32;

		p32=(uint32_t *)(MPC5XXX_PSC1+MPC5XXX_PSC_CCR);
		ccr=*p32;

		p8=(byte *)(MPC5XXX_PSC1+MPC5XXX_PSC_CTLR);
		ctlr=*p8;

		p8=(byte *)(MPC5XXX_PSC1+MPC5XXX_PSC_CTUR);
		ctur=*p8;

		p16=(uint16_t*)(MPC5XXX_PSC1+MPC5XXX_PSC_RFALARM);
		rfalarm=*p16;

		p16=(uint16_t *)(MPC5XXX_PSC1+MPC5XXX_PSC_TFALARM);
		tfalarm=*p16;

		p32=(uint32_t *)(MPC5XXX_CDM+MPC5XXX_CDM_PSC1_MCLK_EN);
		cdm_mclk=*p32;
		
		fprintf( stderr, "Initializing SPI.\n" );
		fprintf( stderr, " CR:%02X \n", cr);
		fprintf( stderr, " SICR:%08X \n", sicr);
		fprintf( stderr, " CLKEN:%08X \n", clken);
		fprintf( stderr, " CCR:%08X \n", ccr);
		fprintf( stderr, " CTLR:%02X \n", ctlr);
		fprintf( stderr, " CTUR:%02X \n", ctur);
		fprintf( stderr, " RFALARM:%04X \n", rfalarm);
		fprintf( stderr, " TFALARM:%04X \n", tfalarm);
		fprintf( stderr, " CDM_MCLK_EN:%08X \n", cdm_mclk);

		p8=(byte *)(MPC5XXX_PSC3+MPC5XXX_PSC_CR);
		cr=*p8;
		fprintf( stderr, " PSC3 CR:%02X \n", cr );
	
		// get SPI config info
		cyg_spipsc_info_t config;
		len = sizeof(config);
		cyg_io_get_config( hSPI, CYG_IO_GET_CONFIG_SPIPSC_INFO, &config, &len );	
		
		fprintf( stderr, "Open the SPI port successfully!\n" );
		fprintf( stderr, "CONFIG information dump:\n" );
		fprintf( stderr, " sclk_rate:%d\n", config.sclk_rate );
		fprintf( stderr, " master:%d\n", config.master );
		fprintf( stderr, " sclk_pol:%d\n", config.sclk_pol );
		fprintf( stderr, " sclk_phase:%d\n", config.sclk_phase );
		fprintf( stderr, " msb_first:%d\n", config.msb_first );
		fprintf( stderr, " reg_len:%d\n", config.reg_len );
		fprintf( stderr, " rxalarm_level:%d\n", config.rxalarm_level );
		fprintf( stderr, " txalarm_level:%d\n", config.txalarm_level );
		fprintf( stderr, " cs_dw_udly:%d\n", config.cs_dw_udly );
		fprintf( stderr, " tr_bt_udly:%d\n", config.tr_bt_udly );
	
		// Verify blocking status is set
		cyg_io_get_config( hSPI, CYG_IO_GET_CONFIG_READ_BLOCKING,
				&read_blk_status, &len );
		cyg_io_get_config( hSPI, CYG_IO_GET_CONFIG_WRITE_BLOCKING,
				&write_blk_status, &len);
		fprintf( stderr, "READ BLOCKING status:%d\n", read_blk_status );
		fprintf( stderr, "WRITE BLOCKING status:%d\n", write_blk_status );

		// get buffer info
		cyg_spipsc_buf_info_t buf_info;
		len = sizeof(buf_info);
		cyg_io_get_config( hSPI, CYG_IO_GET_CONFIG_SPIPSC_BUFFER_INFO,
				&buf_info, &len );	
		
		fprintf( stderr, "\nBUFFER INFO:\n" );
		fprintf( stderr, " rx_bufsize:%d\n", buf_info.rx_bufsize );
		fprintf( stderr, " rx_count:%d\n", buf_info.rx_count );
		fprintf( stderr, " tx_bufsize:%d\n", buf_info.tx_bufsize );
		fprintf( stderr, " tx_count:%d\n", buf_info.tx_count );
	#endif

	return 0;
}

int read_imu(struct imu *imuData_ptr) {

	//timestamp the results
	imuData_ptr->time = get_Time();

	int i;
	byte response[26]={0};
	double outputData[13];
	uint32_t commandLength, responseLength;
	uint16_t tmp;

	uint16_t command[26]={0};

	// burst mode output; request all 13 data registers
	command[0] = 0x3E00;
	commandLength = responseLength = 13*2; //bytes to read/write
	
	// Send command
	cyg_io_write( hSPI, command, &commandLength); 
	
	/* This pause is necessary to ensure that the sensor has time to respond before the read attempt.
	 * The SPI bit rate is 500kHz, with a 15 usec delay in between each 16-bit frame, and a 1 usec
	 * delay between the chip select down and clock start/stop. Thus, a 26-byte
	 * read/write will take at least 600 usec. This has been measured to be approximately 630 usec.
	 * Note 1 tick for cyg_thread_delay is 100 usec.
	 */
	cyg_thread_delay(10); 
	
	// read bytes from buffer into response
	cyg_io_read( hSPI, response, &responseLength );	
	
	#ifdef verbose
		fprintf( stderr,"Read %d SPI bytes\n",responseLength);
		for(i=0; i<responseLength;i++){
			printf("%2.2x ",response[i]) ;
		}
		printf("\n");
	#endif
	
	

	 // All inertial sensor outputs are in 14-bit, twos complement format
	 // Combine data bytes; each regsister covers two bytes, but uses only 14 bits.
	for ( i = 0; i < responseLength; i += 2 ) {
		 tmp = (response[i] & 0x3F) * 256 + response[i+1];
		
		if ( tmp > 0x1FFF ) {
			outputData[i/2] = (double)(-(0x4000 - tmp));
		}
		else
		outputData[i/2] = (double)tmp;		
	}
	
	// set status flag if supply voltage is within 4.75 to 5.25
	if ((outputData[1]*0.002418 > 4.25) && (outputData[1]*0.002418 < 5.25)){
	
		imuData_ptr->err_type = data_valid;
		// update imupacket
		// *IMP* IMU axis alignment is different: Z=-Z_body, Y=-Y_body
		imuData_ptr->Vs = outputData[1]*0.002418;	//unit: Volt
		imuData_ptr->p  = D2R * outputData[2]*0.05;		//unit: rad/s
		imuData_ptr->q  = -D2R * outputData[3]*0.05;
		imuData_ptr->r  = -D2R * outputData[4]*0.05;
		imuData_ptr->ax = -g * outputData[5]*0.00333;		//unit: m/s^2
		imuData_ptr->ay = g * outputData[6]*0.00333;
		imuData_ptr->az = g * outputData[7]*0.00333;
		imuData_ptr->hx = outputData[8]*0.0005;			//unit: Gauss
		imuData_ptr->hy = outputData[9]*0.0005;
		imuData_ptr->hz = outputData[10]*0.0005;
		imuData_ptr->T  = 25.0 + outputData[11]*0.14;
		imuData_ptr->adc = outputData[12]*0.000806;	//unit: Volt
	}
	else{
		imuData_ptr->err_type = got_invalid;
	}
	
	// output real units
#ifdef verbose
		fprintf( stderr, "\n" );
		fprintf( stderr, "power = %.2f V\n", imuData_ptr->Vs );
		fprintf( stderr, "X gyro = %.2f deg/s\n", imuData_ptr->p );
		fprintf( stderr, "Y gyro = %.2f deg/s\n", imuData_ptr->q );
		fprintf( stderr, "Z gyro = %.2f deg/s\n", imuData_ptr->r );
		fprintf( stderr, "X accel = %.2f G\n", imuData_ptr->ax );
		fprintf( stderr, "Y accel = %.2f G\n", imuData_ptr->ay );
		fprintf( stderr, "Z accel = %.2f G\n", imuData_ptr->az );
		fprintf( stderr, "X mag = %.2f mgauss\n", imuData_ptr->hx );
		fprintf( stderr, "Y mag = %.2f mgauss\n", imuData_ptr->hy );
		fprintf( stderr, "Z mag = %.2f mgauss\n", imuData_ptr->hz );
		fprintf( stderr, "Temp = %.1f C\n",	imuData_ptr->T );
		fprintf( stderr, "ADC = %.2f V\n",	imuData_ptr->adc );
#endif

	return 0;
}
