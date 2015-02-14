/*
 * AD8557.cpp
 *
 *  Created on: 29.12.2014
 *      Author: struppi
 */

#include "AD8557.h"

#include <FreeRTOS.h>
#include <task.h>
#include "../OS/Task.h"

extern "C" {
void SysCtlDelay(unsigned long ulCount);
}

AD8557::AD8557()
: _pinDigIn(GPIOPin::invalid), _pinDigOut(GPIOPin::invalid)
{ }


AD8557::AD8557(GPIOPin in)
: _pinDigIn(in), _pinDigOut(GPIOPin::invalid)
{ }


AD8557::AD8557(GPIOPin in, GPIOPin out)
: _pinDigIn(in), _pinDigOut(out)
{ }


int AD8557::setGain(uint8_t firstStageCode, uint8_t secondStageCode)
{

	int ret = 1;

	/*
	 * Datasheet for AD8557 says:
	 * A short pulse at DIGIN from low to high and back to low again,
	 * such as between 50 ns and 10 μs long, loads a 0 into a shift
	 * register. A long pulse at DIGIN, such as 50 μs or longer, loads a
	 * 1 into the shift register. The time between pulses should be at
	 * least 10 μs.
	 */

	if ( ! _pinDigIn.isValid() ) {
		return -1;
	}

	if (firstStageCode > 127) {
		return -2;
	}
	if (secondStageCode > 7) {
		return -3;
	}

	ret = sendPacket(AD8857_FCT_SIMULATE, AD8857_PARAM_SECOND_STAGE, secondStageCode); // gain2
	if (ret >= 0) {
		Task::delay_ms(3);
		ret = sendPacket(AD8857_FCT_SIMULATE, AD8857_PARAM_FIRST_STAGE, firstStageCode); // gain2
	}

	return ret;
}


int AD8557::sendPacket(ad8857_function_t function, ad8857_parameter_t parameter, uint8_t &value)
{
	uint8_t f;
	uint8_t p;
	uint8_t buf[5];

	uint32_t p1;
	uint8_t p2;

	f = (uint8_t) function;
	f &= 0x03;

	p = (uint8_t) parameter;
	p &= 0x03;

	if (function == AD8857_FCT_PROGRAM || function == AD8857_FCT_SIMULATE) {
		if (parameter == AD8857_PARAM_SECOND_STAGE) {
			if (value > 0x07) {
				return -1;
			}
		}
		else if (parameter == AD8857_PARAM_FIRST_STAGE) {
			if (value > 0x7f) {
				return -1;
			}
		}
		else {
			// NOT implemented!
			return -127;
		}
	}
	else if (function != AD8857_FCT_READ) {
		// NOT implemented!
		return -127;
	}

	// b0: 0-7 -> sof #1
	// b1: 8-15 -> sof #2 + f + p
	// b2: 16-23 -> 10 + value >> 2
	// b3: 24-31 -> value << 2 + eof#1
	// b4: 32-39 -> eof #2
	buf[0] = 0x80;
	buf[1] = 0x10 | (f<<2) | p;
	buf[2] = 0x80 | (value >> 2);
	buf[3] = (value << 6) | 0x1f;
	buf[4] = 0xf8;

	p1  = ((uint32_t)buf[0]) << 24;
	p1 |= ((uint32_t)buf[1]) << 16;
	p1 |= ((uint32_t)buf[2]) <<  8;
	p1 |= (uint32_t)buf[3] <<  0;
	p2 = buf[4];

	for (int bit=31; bit >= 0; bit--) {
		if (p1 & (1<<bit)) {
			send1();
		}
		else {
			send0();
		}
		SysCtlDelay(100);
	}
	for (int bit=7; bit >= 2; bit--) {
		if (p2 & (1<<bit)) {
			send1();
		}
		else {
			send0();
		}
		SysCtlDelay(100);
	}

	return 1;
}


int AD8557::send1()
{
	taskENTER_CRITICAL();
	_pinDigIn.set(1);
	SysCtlDelay(1000); // 100us -> 1
	_pinDigIn.set(0);
	taskEXIT_CRITICAL();

	return 1;
}

int AD8557::setup()
{
	if (_pinDigIn.isValid()) {
		_pinDigIn.configure(GPIOPin::GPIO_OUT_OD);
		_pinDigIn.setLow();
	}
	else {
		return -1;
	}

	if (_pinDigOut.isValid()) {
		_pinDigOut.configure(GPIOPin::GPIO_IN, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH);
	}

	return 1;
}

int AD8557::send0()
{
	taskENTER_CRITICAL();
	_pinDigIn.set(1);
	SysCtlDelay(10); // 1us   -> 0
	_pinDigIn.set(0);
	taskEXIT_CRITICAL();

	return 1;
}

#if 0
int AD8557::readGain(uint8_t& firstStage, uint8_t& secondStage)
{
	// right now we're just doing a dummy read to. real data is only visible on logic analyzer :)

	firstStage = 0;
	secondStage = 0;

	sendPacket(AD8857_FCT_READ, AD8857_PARAM_FIRST_STAGE, firstStage);
	Task::delay_ms(3);
	sendPacket(AD8857_FCT_READ, AD8857_PARAM_SECOND_STAGE, secondStage);

	return 1;
}
#endif
