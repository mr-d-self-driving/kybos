/*
 * GPIO.h
 *
 *  Created on: 13.12.2014
 *      Author: struppi
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "kybos.h"

//#include <cmsis_device.h>
//#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _gpio)


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
		GPIO_IN = GPIO_MODE_INPUT,
		GPIO_OUT_PP = GPIO_MODE_OUTPUT_PP,
		GPIO_OUT_OD = GPIO_MODE_OUTPUT_OD,
		GPIO_AF_PP = GPIO_MODE_AF_PP,
		GPIO_AF_OD = GPIO_MODE_AF_OD,
		GPIO_ANALOG = GPIO_MODE_ANALOG,
		GPIO_IT_RISING = GPIO_MODE_IT_RISING,
		GPIO_IT_FALLING = GPIO_MODE_IT_FALLING,
		GPIO_IT_RISING_FALLING = GPIO_MODE_IT_RISING_FALLING,
		GPIO_EVT_RISING = GPIO_MODE_EVT_RISING,
		GPIO_EVT_FALLING = GPIO_MODE_EVT_FALLING,
		GPIO_EVT_RISING_FALLING = GPIO_MODE_EVT_RISING_FALLING
	} gpio_config_t;


	typedef enum {
#ifdef GPIO_SPEED_FREQ_VERY_LOW
		GPIO_SPD_LOW=GPIO_SPEED_FREQ_VERY_LOW,
#endif
#ifdef GPIO_SPEED_FREQ_LOW
		GPIO_SPD_LOW=GPIO_SPEED_FREQ_LOW,
#endif
#ifdef GPIO_SPEED_FREQ_MEDIUM
		GPIO_SPD_MEDIUM=GPIO_SPEED_FREQ_MEDIUM,
#endif
#ifdef GPIO_SPEED_FREQ_HIGH
		GPIO_SPD_HIGH=GPIO_SPEED_FREQ_HIGH,
#endif
#ifdef GPIO_SPEED_FREQ_VERY_HIGH
		GPIO_SPD_VERY_HIGH=GPIO_SPEED_FREQ_VERY_HIGH
#endif

	} gpio_speed_t;


	typedef enum {
#ifdef GPIO_NOPULL
		GPIO_NO_PULL=GPIO_NOPULL,
#endif
#ifdef GPIO_PULLUP
		GPIO_PULL_UP=GPIO_PULLUP,
#endif
#ifdef GPIO_PULLDOWN
		GPIO_PULL_DOWN=GPIO_PULLDOWN
#endif
	} gpio_pull_t;

	typedef enum {AF_CONFIG_0, AF_CONFIG_1, AF_CONFIG_2, AF_CONFIG_3, AF_CONFIG_4, AF_CONFIG_5,
		AF_CONFIG_6, AF_CONFIG_7, AF_CONFIG_8, AF_CONFIG_9, AF_CONFIG_10, AF_CONFIG_11, AF_CONFIG_12, AF_CONFIG_13, AF_CONFIG_14, AF_CONFIG_15, AF_CONFIG_NONE} gpio_afconfig_t;

	void configureAsOutput();
	void configureAsInput();
	void configure(gpio_config_t config, gpio_pull_t pull=GPIO_NO_PULL, gpio_speed_t speed=GPIO_SPD_LOW, gpio_afconfig_t afConfig=AF_CONFIG_NONE);

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
	void mapAsSPI2CLK();
	void mapAsSPI2MISO();
	void mapAsSPI2MOSI();
	void mapAsSPI2NSS();
	void mapAsSPI3CLK();
	void mapAsSPI3MISO();
	void mapAsSPI3MOSI();
	void mapAsSPI3NSS();
	void mapAsSPI4CLK();
	void mapAsSPI4MISO();
	void mapAsSPI4MOSI();
	void mapAsSPI4NSS();
	void mapAsSPI5CLK();
	void mapAsSPI5MISO();
	void mapAsSPI5MOSI();
	void mapAsSPI5NSS();
	void mapAsSPI6CLK();
	void mapAsSPI6MISO();
	void mapAsSPI6MOSI();
	void mapAsSPI6NSS();

	void mapAsCAN1RX();
	void mapAsCAN1TX();
	void mapAsCAN2RX();
	void mapAsCAN2TX();

	void mapAsI2C1SDA();
	void mapAsI2C2SDA();
	void mapAsI2C3SDA();
	void mapAsI2C1SCL();
	void mapAsI2C2SCL();
	void mapAsI2C3SCL();

	void mapAsU1RX();
	void mapAsU1TX();
	void mapAsU2RX();
	void mapAsU2TX();
	void mapAsU3RX();
	void mapAsU3TX();
	void mapAsU4RX();
	void mapAsU4TX();
	void mapAsU5RX();
	void mapAsU5TX();
	void mapAsU6RX();
	void mapAsU6TX();
	void mapAsU7RX();
	void mapAsU7TX();
	void mapAsU8RX();
	void mapAsU8TX();

};


#endif /* GPIO_H_ */
