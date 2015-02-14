/*
 * GPIO.cpp
 *
 *  Created on: 13.12.2014
 *      Author: struppi
 */

#include "GPIO.h"
#include "kybos.h"

//#include <stm32l1xx_hal_rcc.h>
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _rcc)

#ifdef HAS_GPIO_A
GPIOPort GPIO::A = GPIOPort(0);
#endif
#ifdef HAS_GPIO_B
GPIOPort GPIO::B = GPIOPort(1);
#endif
#ifdef HAS_GPIO_C
GPIOPort GPIO::C = GPIOPort(2);
#endif
#ifdef HAS_GPIO_D
GPIOPort GPIO::D = GPIOPort(3);
#endif
#ifdef HAS_GPIO_E
GPIOPort GPIO::E = GPIOPort(4);
#endif
#ifdef HAS_GPIO_F
GPIOPort GPIO::F = GPIOPort(5);
#endif
#ifdef HAS_GPIO_G
GPIOPort GPIO::G = GPIOPort(6);
#endif
#ifdef HAS_GPIO_H
GPIOPort GPIO::H = GPIOPort(7);
#endif
#ifdef HAS_GPIO_I
GPIOPort GPIO::I = GPIOPort(8);
#endif
#ifdef HAS_GPIO_J
GPIOPort GPIO::J = GPIOPort(9);
#endif
#ifdef HAS_GPIO_K
GPIOPort GPIO::K = GPIOPort(10);
#endif


GPIOPort::GPIOPort(uint8_t portNum)
: _portNumber(portNum)
{
	switch(portNum) {
#ifdef HAS_GPIO_A
	case 0:
		_base = GPIOA;
		break;
#endif
#ifdef HAS_GPIO_B
	case 1:
		_base = GPIOB;
		break;
#endif
#ifdef HAS_GPIO_C
	case 2:
		_base = GPIOC;
		break;
#endif
#ifdef HAS_GPIO_D
	case 3:
		_base = GPIOD;
		break;
#endif
#ifdef HAS_GPIO_E
	case 4:
		_base = GPIOE;
		break;
#endif
#ifdef HAS_GPIO_F
	case 5:
		_base = GPIOF;
		break;
#endif
#ifdef HAS_GPIO_G
	case 6:
		_base = GPIOG;
		break;
#endif
#ifdef HAS_GPIO_H
	case 7:
		_base = GPIOH;
		break;
#endif
#ifdef HAS_GPIO_I
	case 8:
		_base = GPIOI;
		break;
#endif
#ifdef HAS_GPIO_J
	case 9:
		_base = GPIOJ;
		break;
#endif
#ifdef HAS_GPIO_K
	case 10:
		_base = GPIOK;
		break;
#endif
	default:
		while (1) { ; }
	}
}


GPIO::GPIO()
{
}


GPIOPin GPIOPin::invalid(0xf, 0xf);

GPIOPin::GPIOPin()
: _portPin(0xff)
{
}


void GPIOPin::configureAsOutput()
{
	GPIOPin::configure(GPIOPin::GPIO_OUT_PP);
}


bool GPIOPin::isValid()
{
	return _portPin != 0xff;
}


void GPIOPin::set(bool state)
{
	uint8_t port = _portPin >> 4;
	uint8_t pin = _portPin & 0x0f;
	GPIO_PinState pinState = state?GPIO_PIN_SET:GPIO_PIN_RESET;

	HAL_GPIO_WritePin(GPIOPort(port)._base, (1<<pin), pinState);
}


void GPIOPin::setHigh()
{
	set(1);
}


void GPIOPin::setLow()
{
	set(0);
}


void GPIOPin::toggle()
{
	uint8_t port = _portPin >> 4;
	uint8_t pin = _portPin & 0x0f;

	HAL_GPIO_TogglePin(GPIOPort(port)._base, (1<<pin));

}


bool GPIOPin::isHigh()
{

	GPIO_PinState ret;
	uint8_t pin = _portPin & 0x0f;
	uint8_t port = _portPin >> 4;

	ret = HAL_GPIO_ReadPin(GPIOPort(port)._base, 1<<pin);

	return ret == GPIO_PIN_SET;
}


bool GPIOPin::isLow()
{
	GPIO_PinState ret;
	uint8_t pin = _portPin & 0x0f;
	uint8_t port = _portPin >> 4;

	ret = HAL_GPIO_ReadPin(GPIOPort(port)._base, 1<<pin);

	return ret == GPIO_PIN_RESET;
}


GPIOPin::GPIOPin(uint8_t port, uint8_t pin)
{
	_portPin = (port << 4) | (pin & 0x0f);
}


void GPIOPin::configureAsInput()
{
	configure(GPIO_IN);
}


GPIOPin GPIOPort::operator [](uint8_t pin)
{
	return GPIOPin( _portNumber, pin );
}


void GPIOPin::configure(gpio_config_t config, gpio_pull_t pull, gpio_speed_t speed, gpio_afconfig_t afConfig)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	uint8_t port = _portPin >> 4;
	uint8_t pin = _portPin & 0x0f;

	switch(port) {
#ifdef HAS_GPIO_A
	case 0:
		__GPIOA_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_B
	case 1:
		__GPIOB_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_C
	case 2:
		__GPIOC_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_D
	case 3:
		__GPIOD_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_E
	case 4:
		__GPIOE_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_F
	case 5:
		__GPIOF_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_G
	case 6:
		__GPIOG_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_H
	case 7:
		__GPIOH_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_I
	case 8:
		__GPIOI_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_J
	case 9:
		__GPIOJ_CLK_ENABLE();
		break;
#endif
#ifdef HAS_GPIO_K
	case 10:
		__GPIOK_CLK_ENABLE();
		break;
#endif
	default:
		while (1) { ; } // oops!
	}


	GPIO_InitStruct.Pin = (1<<pin);
	GPIO_InitStruct.Mode = config;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = speed;
	GPIO_InitStruct.Alternate = (afConfig != AF_CONFIG_NONE)?afConfig:0;

	HAL_GPIO_Init(GPIOPort(port)._base, &GPIO_InitStruct);

}

