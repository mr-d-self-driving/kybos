/*
 * SPIController.h
 *
 *  Created on: 18.03.2016
 *      Author: stefan.rupp
 */

#ifndef SPICONTROLLER_H_
#define SPICONTROLLER_H_

#include <stdint.h>
#include "GPIO.h"
#include "OS/Queue.h"
#include "OS/Semaphore.h"
#include "OS/RecursiveMutex.h"


class SPIController {
public:

	typedef enum {
		SPICONTROLLER_1,
		SPICONTROLLER_2,
		SPICONTROLLER_COUNT
	} spicontroller_t;

	typedef enum {
		motorola_0 = 0x00000000, // polarity 0, phase 0
		motorola_1 = 0x00000002, // polarity 0, phase 1
		motorola_2 = 0x00000001, // polarity 1, phase 0
		motorola_3 = 0x00000003, // polarity 1, phase 1
	} protocol_t;

	typedef enum {
		slave  = SPI_MODE_SLAVE,
		master = SPI_MODE_MASTER,
	} mode_t;

	typedef enum {
		data_width_4bit = SPI_DATASIZE_4BIT,
		data_width_5bit = SPI_DATASIZE_5BIT,
		data_width_6bit = SPI_DATASIZE_6BIT,
		data_width_7bit = SPI_DATASIZE_7BIT,
		data_width_8bit = SPI_DATASIZE_8BIT,
		data_width_9bit = SPI_DATASIZE_9BIT,
		data_width_10bit = SPI_DATASIZE_10BIT,
		data_width_11bit = SPI_DATASIZE_11BIT,
		data_width_12bit = SPI_DATASIZE_12BIT,
		data_width_13bit = SPI_DATASIZE_13BIT,
		data_width_14bit = SPI_DATASIZE_14BIT,
		data_width_15bit = SPI_DATASIZE_15BIT,
		data_width_16bit = SPI_DATASIZE_16BIT
	} data_width_t;

private:
	spicontroller_t _controller;

	GPIOPin _clk;
	GPIOPin _fss;
	GPIOPin _rx;
	GPIOPin _tx;

	mode_t _mode;

	static SPIController* _controllers[SPICONTROLLER_COUNT];
	SPIController(spicontroller_t num);

	SPI_HandleTypeDef _handle;

	RecursiveMutex _lock;


public:
	void setup(GPIOPin clk=GPIOPin(), GPIOPin rx=GPIOPin(), GPIOPin tx=GPIOPin(), GPIOPin fss=GPIOPin());
	//void setup(GPIOPin clk, GPIOPin::gpio_afconfig_t afconfig_clk, GPIOPin rx, GPIOPin::gpio_afconfig_t afconfig_rx, GPIOPin tx, GPIOPin::gpio_afconfig_t afconfig_tx, GPIOPin fss, GPIOPin::gpio_afconfig_t afconfig_fss);
	void configure(protocol_t protocol, mode_t mode, uint32_t bitrate, data_width_t data_width);
	int writeAndRead(const void *writeBuf, void *readBuf, int len);

	static SPIController* get(spicontroller_t num);


};

#endif /* SPICONTROLLER_H_ */




/*
 *
 *

 public:

	typedef enum {
		CONTROLLER_0,
		CONTROLLER_1,
		CONTROLLER_COUNT
	} controller_num_t;

	typedef enum {
		motorola_0 = 0x00000000, // polarity 0, phase 0
		motorola_1 = 0x00000002, // polarity 0, phase 1
		motorola_2 = 0x00000001, // polarity 1, phase 0
		motorola_3 = 0x00000003, // polarity 1, phase 1
		ti         = 0x00000010,
		microwire  = 0x00000020
	} protocol_t;

	typedef enum {
		master = 0,
		slave  = 1,
		slave_no_output = 2
	} mode_t;

	typedef enum {
		data_width_4bit = 4,
		data_width_5bit = 5,
		data_width_6bit = 6,
		data_width_7bit = 7,
		data_width_8bit = 8,
		data_width_9bit = 9,
		data_width_10bit = 10,
		data_width_11bit = 11,
		data_width_12bit = 12,
		data_width_13bit = 13,
		data_width_14bit = 14,
		data_width_15bit = 15,
		data_width_16bit = 16
	} data_width_t;

private:
	controller_num_t _num;


 *
 */
