/*
 * I2CController.h
 *
 *  Created on: 14.12.2014
 *      Author: struppi
 */

#ifndef KYBOS_I2CCONTROLLER_H_
#define KYBOS_I2CCONTROLLER_H_

#include <stdint.h>
#include <cmsis_device.h>
#include "OS/RecursiveMutex.h"
#include "GPIO.h"
#include "kybos.h"

#ifdef  HAL_I2C_MODULE_ENABLED

class I2CController {
public:
	typedef enum {
#ifdef HAS_I2C1
		I2CController1,
#endif
#ifdef HAS_I2C2
		I2CController2,
#endif
#ifdef HAS_I2C3
		I2CController3,
#endif
		numI2CControllers
	} i2cController_t;

	typedef enum {I2C7bitMode, I2C10bitMode, I2CNumAdressingModes} i2cAddressingMode_t;
	typedef enum {I2CModeMaster, I2CModeSlave} i2cMode_t;
	int setup(GPIOPin sda, GPIOPin scl);
	int configure (i2cMode_t mode, uint32_t speed=100000);
	int write(uint16_t address, void *data, uint32_t len, bool sendStart=true, bool sendStop=true);
	int read(uint16_t address, void * data, uint32_t len, bool sendStart=true, bool sendStop=true);
	RecursiveMutex* getLock();
	static I2CController *get(i2cController_t controller);

private:
	//I2CController(I2C_TypeDef *base);
	I2CController(i2cController_t controller);
	I2C_HandleTypeDef _handle;

	RecursiveMutex _lock;
	//HAL_StatusTypeDef statusDef;
	static I2CController* init(i2cController_t controller);
	static I2CController* _i2cControllers[numI2CControllers];

	i2cController_t _controller;

};

#endif // HAL_I2C_MODULE_ENABLED

#endif /* KYBOS_I2CCONTROLLER_H_ */
