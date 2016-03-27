/*
 * PinMap.cpp
 *
 *  Created on: 25.03.2016
 *      Author: struppi
 */


#include "GPIO.h"
#include <stdint.h>


#ifdef STM32F429xx
void GPIOPin::mapAsCAN1RX()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x00:  // port A, pin 0
		break;
	default:
		while (1) { ; }
	}
}

void GPIOPin::mapAsCAN1TX()
{

}

void GPIOPin::mapAsCAN2RX()
{

}

void GPIOPin::mapAsCAN2TX()
{

}
#endif

