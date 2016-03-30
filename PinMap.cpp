/*
 * PinMap.cpp
 *
 *  Created on: 23.03.2016
 *      Author: Stefan Rupp
 */


#include "GPIO.h"

#ifdef STM32F072

void GPIOPin::mapAsSPI1CLK()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch (_portPin) {
	case 0x05:  // port A, pin 5
	case 0x13:  // port B, pin 3
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF0_SPI1;
		break;
	default: while (1);
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI1MISO()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch (_portPin) {
	case 0x06:  // port A, pin 6
	case 0x14:  // port B, pin 4
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF0_SPI1;
		break;
	default: while (1);
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI1MOSI()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch (_portPin) {
	case 0x07:  // port A, pin 7
	case 0x15:  // port B, pin 5
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF0_SPI1;
		break;
	default: while (1);
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI1NSS()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch (_portPin) {
	case 0x04:  // port A, pin 4
	case 0x0F:  // port A, pin 15
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF0_SPI1;
		break;
	default: while (1);
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsCAN1TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch (_portPin) {
	case 0x0C:  // port A, pin 12
	case 0x19:  // port B, pin 9
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_CAN;
		break;
	case 0x31:  // port D, pin 1
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF0_CAN;
		break;
	default: while (1);
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);

}

void GPIOPin::mapAsCAN1RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch (_portPin) {
	case 0x0B:  // port A, pin 11
	case 0x18:  // port B, pin 8
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_CAN;
		break;
	case 0x30:  // port D, pin 0
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF0_CAN;
		break;
	default: while (1);
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);

}

#endif // STM32F072
