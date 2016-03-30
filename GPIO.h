/*
 * GPIO.h
 *
 *  Created on: 13.12.2014
 *      Author: struppi
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "kybos.h"

#include <cmsis_device.h>

#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _gpio)
//#include <stm32l1xx_hal_gpio.h>


class GPIOPin;

class GPIOPort {
	friend class GPIO;
	friend class GPIOPin;

public:
	GPIOPin operator[] (uint8_t pin);

private:
	GPIOPort(uint8_t portNum);
	uint8_t _portNumber;
	GPIO_TypeDef* _base;

};


class GPIO {
	friend class GPIOPort;
public:

#ifdef HAS_GPIO_A
	static GPIOPort A;
#endif
#ifdef HAS_GPIO_B
	static GPIOPort B;
#endif
#ifdef HAS_GPIO_C
	static GPIOPort C;
#endif
#ifdef HAS_GPIO_D
	static GPIOPort D;
#endif
#ifdef HAS_GPIO_E
	static GPIOPort E;
#endif
#ifdef HAS_GPIO_F
	static GPIOPort F;
#endif
#ifdef HAS_GPIO_G
	static GPIOPort G;
#endif
#ifdef HAS_GPIO_H
	static GPIOPort H;
#endif
#ifdef HAS_GPIO_I
	static GPIOPort I;
#endif
#ifdef HAS_GPIO_J
	static GPIOPort J;
#endif
#ifdef HAS_GPIO_K
	static GPIOPort K;
#endif

private:
	GPIO();

};


class GPIOPin {
	friend class GPIOPort;
public:
	typedef enum {
		GPIO_IN = 0x00000000,
		GPIO_OUT_PP = 0x00000001,
		GPIO_OUT_OD = 0x00000011,
		GPIO_AF_PP = 0x00000002,
		GPIO_AF_OD = 0x00000012,
		GPIO_ANALOG = 0x00000003,
		GPIO_IT_RISING = 0x10110000,
		GPIO_IT_FALLING = 0x10210000,
		GPIO_IT_RISING_FALLING = 0x10310000,
		GPIO_EVT_RISING = 0x10120000,
		GPIO_EVT_FALLING = 0x10220000,
		GPIO_EVT_RISING_FALLING = 0x10320000
	} gpio_config_t;

	typedef enum {GPIO_SPD_VERY_LOW=0, GPIO_SPD_LOW=1, GPIO_SPD_MEDIUM=2, GPIO_SPD_HIGH=3 } gpio_speed_t;
	typedef enum {GPIO_NO_PULL=0, GPIO_PULL_UP=1, GPIO_PULL_DOWN=2} gpio_pull_t;

	typedef enum {AF_CONFIG_0, AF_CONFIG_1, AF_CONFIG_2, AF_CONFIG_3, AF_CONFIG_4, AF_CONFIG_5,
		AF_CONFIG_6, AF_CONFIG_7, AF_CONFIG_8, AF_CONFIG_9, AF_CONFIG_10, AF_CONFIG_11, AF_CONFIG_12, AF_CONFIG_13, AF_CONFIG_14, AF_CONFIG_15, AF_CONFIG_NONE} gpio_afconfig_t;

	void configureAsOutput();
	void configureAsInput();
	void configure(gpio_config_t config, gpio_pull_t pull=GPIO_NO_PULL, gpio_speed_t speed=GPIO_SPD_VERY_LOW, gpio_afconfig_t afConfig=AF_CONFIG_NONE);

	void set(bool state);
	void setHigh();
	void setLow();
	void toggle();

	bool isHigh();
	bool isLow();

	bool isValid();
	GPIOPin();

	static GPIOPin invalid;

private:
	GPIOPin(uint8_t port, uint8_t pin);

	uint8_t _portPin;

public:
	void mapAsSPI1CLK();
	void mapAsSPI1MISO();
	void mapAsSPI1MOSI();
	void mapAsSPI1NSS();
	void mapAsCAN1TX();
	void mapAsCAN1RX();
};


#endif /* GPIO_H_ */
