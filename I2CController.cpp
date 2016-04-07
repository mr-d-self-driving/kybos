/*
 * I2CController.cpp
 *
 * Copyright 2014 Stefan Rupp (struppi@struppi.name)
 *
 * This file is part of kybos.
 *
 * kybos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * kybos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with kybos.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "I2CController.h"
#include "kybos.h"

#include "GPIO.h"

#ifdef HAL_I2C_MODULE_ENABLED

I2CController* I2CController::_i2cControllers[] = {0, };





int I2CController::write(uint16_t address, void* data, uint32_t len, bool sendStart, bool sendStop)
{
	RecursiveMutexGuard guard(&_lock);

	if (!sendStart || !sendStop) {
		// don't know how STM's HAL wants us to handle this :(
		return -1;
	}

	HAL_I2C_Master_Transmit(&_handle, address<<1, (uint8_t *)data, len, HAL_MAX_DELAY);

	return len;
}


int I2CController::read(uint16_t address, void* data, uint32_t len, bool sendStart, bool sendStop)
{
	RecursiveMutexGuard guard(&_lock);

	if (!sendStart || !sendStop) {
		// don't know how STM's HAL wants us to handle this :(
		return -1;
	}

	HAL_I2C_Master_Receive(&_handle, address<<1, (uint8_t *)data, len, HAL_MAX_DELAY);

	return len;
}


I2CController* I2CController::get(i2cController_t controller)
{
	if (controller >= numI2CControllers) {
		return 0;
	}

	if (_i2cControllers[controller] == 0) {
		_i2cControllers[controller] = I2CController::init(controller);
	}

	return _i2cControllers[controller];
}


I2CController::I2CController(i2cController_t controller)
: _controller(controller)
{
	I2C_TypeDef* base;

	switch (controller) {
#if defined (I2C1)
	case I2CController1:
		base = I2C1;
		break;
#endif
#if defined (I2C1)
	case I2CController2:
		base = I2C2;
		break;
#endif
#if defined (I2C1)
	case I2CController3:
		base = I2C3;
		break;
#endif
	default:
		while (1) { ; }
	}

	_handle.Instance = base;
}


RecursiveMutex* I2CController::getLock()
{
	return &_lock;
}


int I2CController::setup(GPIOPin sda, GPIOPin scl)
{
	RecursiveMutexGuard guard(&_lock);
	int ret=1;

	//uint32_t af;

	switch (_controller) {
#ifdef I2C1
	case I2CController1:
		sda.mapAsI2C1SDA();
		scl.mapAsI2C1SCL();
		break;
#endif
#ifdef I2C2
	case I2CController2:
		sda.mapAsI2C2SDA();
		scl.mapAsI2C2SCL();
		break;
#endif
#ifdef I2C3
	case I2CController3:
		sda.mapAsI2C3SDA();
		scl.mapAsI2C3SCL();
		break;
#endif

	default:
		while (1) { ; } // something's really wrong!
		break;

	}

	return ret;
}


int I2CController::configure(i2cMode_t mode, uint32_t speed)
{
	int ret = 1;

	if (mode == I2CModeMaster) {
		if (speed > 400000) {
			return -1;
		}
	}
	else {
		return -1; // slave mode not implemented
	}

	//handle.Init.AddressingMode = (addressingMode==I2C7bitMode)?I2C_ADDRESSINGMODE_7BIT:I2C_ADDRESSINGMODE_10BIT;
	_handle.Init.ClockSpeed = speed;
	_handle.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
	_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	_handle.Init.OwnAddress1 = 0;
	_handle.Init.OwnAddress2 = 0;
	_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	_handle.State = HAL_I2C_STATE_RESET;
	_handle.Lock  = HAL_UNLOCKED;

/*
	RCC_PeriphCLKInitTypeDef RCC_PeripCLKInitStruct;         //Setze Clock
	RCC_PeripCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
	RCC_PeripCLKInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
	HAL_RCCEx_GetPeriphCLKConfig(&RCC_PeripCLKInitStruct);
*/

	switch (_controller) {
#if defined (I2C1)
	case I2CController1:
		__I2C1_CLK_ENABLE();
		break;
#endif
#if defined (I2C2)
	case I2CController2:
		__I2C2_CLK_ENABLE();
		break;
#endif
#if defined (I2C3)
	case I2CController3:
		__I2C3_CLK_ENABLE();
		break;
#endif
	default:
		while (1) { ; }
		break;
	}


	ret = HAL_I2C_Init(&_handle);

	if (ret != HAL_OK) {
		ret = -ret;
	}
	return ret;

}


I2CController* I2CController::init(i2cController_t controller)
{

	I2CController* c = new I2CController(controller);
	return c;
}

#endif // HAL_I2C_MODULE_ENABLED


