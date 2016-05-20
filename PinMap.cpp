/*
 * PinMap.cpp
 *
 *  Created on: 25.03.2016
 *      Author: struppi
 */


#include "GPIO.h"
#include <stdint.h>


#ifdef STM32F429xx

#if defined (HAL_UART_MODULE_ENABLED)

#if defined (UART1) || defined (USART1)
void GPIOPin::mapAsU1RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x0A:  // port A, pin 10
	case 0x17:  // port B, pin 7
#if defined (UART1)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_UART1;
#else // defined (USART1)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_USART1;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsU1TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x09:  // port A, pin 9
	case 0x16:  // port B, pin 6
#if defined (UART1)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_UART1;
#else // defined (USART1)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_USART1;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif

#if defined (UART2) || defined (USART2)
void GPIOPin::mapAsU2RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x03:  // port A, pin 3
	case 0x36:  // port D, pin 6
#if defined (UART2)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_UART2;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_USART2;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsU2TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x02:  // port A, pin 2
	case 0x35:  // port D, pin 5
#if defined (UART2)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_UART2;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_USART2;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif

#if defined (UART3) || defined (USART3)
void GPIOPin::mapAsU3RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x1B:  // port B, pin 11
	case 0x2B:  // port C, pin 11
	case 0x39:  // port D, pin 9
#if defined (UART3)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_UART3;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_USART3;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsU3TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x1A:  // port B, pin 10
	case 0x2A:  // port C, pin 10
	case 0x38:  // port D, pin 8
#if defined (UART3)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_UART3;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF7_USART3;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif


#if defined (UART4) || defined (USART4)
void GPIOPin::mapAsU4RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x01:  // port A, pin 1
	case 0x2B:  // port C, pin 11
#if defined (UART4)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART4;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART4;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsU4TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x00:  // port A, pin 0
	case 0x2A:  // port C, pin 10
#if defined (UART4)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART4;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART4;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif

#if defined (UART5) || defined (USART5)
void GPIOPin::mapAsU5RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x32:  // port D, pin 2
#if defined (UART5)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART5;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART5;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsU5TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x2C:  // port C, pin 12
#if defined (UART5)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART5;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART5;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif


#if defined (UART6) || defined (USART6)
void GPIOPin::mapAsU6RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x27:  // port C, pin 7
	case 0x69:  // port G, pin 9
#if defined (UART6)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART6;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART6;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsU6TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x26:  // port C, pin 6
	case 0x6E:  // port G, pin 14
#if defined (UART6)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART6;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART6;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif


#if defined (UART7) || defined (USART7)
void GPIOPin::mapAsU7RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x47:  // port E, pin 7
	case 0x56:  // port F, pin 6
#if defined (UART7)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART7;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART7;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
void GPIOPin::mapAsU7TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x48:  // port E, pin 8
	case 0x57:  // port F, pin 7
#if defined (UART7)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART7;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART7;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif


#if defined (UART8) || defined (USART8)
void GPIOPin::mapAsU8RX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x40:  // port E, pin 0
#if defined (UART8)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART8;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART8;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsU8TX()
{
	GPIOPin::gpio_afconfig_t afconfig;
	switch(_portPin) {
	case 0x41:  // port E, pin 1
#if defined (UART8)
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_UART8;
#else
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF8_USART8;
#endif
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif

#endif // defined (HAL_UART_MODULE_ENABLED)


#ifdef HAL_CAN_MODULE_ENABLED
void GPIOPin::mapAsCAN1RX()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x0B:  // port A, pin 11
	case 0x18:  // port B, pin 8
	case 0x30:  // port D, pin 0
	case 0x89:  // port I, pin 9
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF9_CAN1;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsCAN1TX()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x0C:  // port A, pin 12
	case 0x19:  // port B, pin 9
	case 0x31:  // port D, pin 1
	case 0x7D:  // port H, pin 13
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF9_CAN1;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);

}

void GPIOPin::mapAsCAN2RX()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x15:  // port B, pin 5
	case 0x1C:  // port B, pin 12
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF9_CAN2;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsCAN2TX()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x16:  // port B, pin 6
	case 0x1D:  // port B, pin 13
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF9_CAN2;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);

}
#endif // HAL_CAN_MODULE_ENABLED


#ifdef  HAL_I2C_MODULE_ENABLED
void GPIOPin::mapAsI2C1SDA()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x17:  // port B, pin 7
	case 0x19:  // port B, pin 9
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_I2C1;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_OD, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsI2C2SDA()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x1B:  // port B, pin 11
	case 0x50:  // port F, pin 0
	case 0x75:  // port H, pin 5
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_I2C2;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_OD, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsI2C3SDA()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x29:  // port C, pin 9
	case 0x78:  // port H, pin 8
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_I2C3;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_OD, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsI2C1SCL()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x16:  // port B, pin 6
	case 0x18:  // port B, pin 8
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_I2C1;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_OD, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsI2C2SCL()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x1A:  // port B, pin 10
	case 0x51:  // port F, pin 1
	case 0x74:  // port H, pin 4
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_I2C2;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_OD, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsI2C3SCL()
{
	GPIOPin::gpio_afconfig_t afconfig;

	switch(_portPin) {
	case 0x08:  // port A, pin 8
	case 0x29:  // port C, pin 9
		afconfig = (GPIOPin::gpio_afconfig_t) GPIO_AF4_I2C3;
		break;
	default:
		while (1) { ; }
	}
	this->configure(GPIOPin::GPIO_AF_OD, GPIOPin::GPIO_PULL_UP, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
#endif  // HAL_I2C_MODULE_ENABLED


#ifdef HAL_SPI_MODULE_ENABLED
void GPIOPin::mapAsSPI1CLK()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI1MISO()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI1MOSI()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI1NSS()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI2CLK()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI2MISO()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI2MOSI()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI2NSS()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
void GPIOPin::mapAsSPI3CLK()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI3MISO()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI3MOSI()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI3NSS()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
void GPIOPin::mapAsSPI4CLK()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI4MISO()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI4MOSI()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI4NSS()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
void GPIOPin::mapAsSPI5CLK()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI5MISO()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI5MOSI()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI5NSS()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}
void GPIOPin::mapAsSPI6CLK()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI6MISO()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI6MOSI()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

void GPIOPin::mapAsSPI6NSS()
{
	GPIOPin::gpio_afconfig_t afconfig;
	this->configure(GPIOPin::GPIO_AF_PP, GPIOPin::GPIO_NO_PULL, GPIOPin::GPIO_SPD_HIGH, afconfig);
}

#endif // HAL_SPI_MODULE_ENABLED



#endif // STM32F429xx

#ifdef STM32F072

#ifdef HAL_SPI_MODULE_ENABLED
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
#endif // HAL_SPI_MODULE_ENABLED

#ifdef HAL_CAN_MODULE_ENABLED
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
#endif // HAL_CAN_MODULE_ENABLED

#endif // STM32F072

