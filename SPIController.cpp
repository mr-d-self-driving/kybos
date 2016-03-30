/*
 * SPIController.cpp
 *
 *  Created on: 18.03.2016
 *      Author: stefan.rupp
 */




#include "kybos.h"

#ifdef HAL_SPI_MODULE_ENABLED


#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _def)
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _spi)

#include <cmsis_device.h>

#include "GPIO.h"

#include "SPIController.h"



SPIController* SPIController::_controllers[SPIController::SPICONTROLLER_COUNT];


SPIController::SPIController(spicontroller_t controller)
// : .....
{

	SPI_TypeDef* base;

	switch (controller) {
	case SPICONTROLLER_1:
		base = SPI1;
		break;
	case SPICONTROLLER_2:
		base = SPI2;
		break;
	default:
		while (1) { ; }
	}

	_controller = controller;

	_handle.Instance = base;


}


void SPIController::configure(protocol_t protocol, mode_t mode, uint32_t baudrate_prescaler, data_width_t data_width)
{
	_handle.Init.Mode = mode;
	_handle.Init.DataSize = data_width;
	_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	_handle.Init.CRCPolynomial = 7;
	_handle.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;

	switch (protocol) {
	case motorola_0:
		_handle.Init.CLKPolarity = SPI_POLARITY_LOW;
		_handle.Init.CLKPhase = SPI_PHASE_1EDGE;
		break;
	case motorola_1:
		_handle.Init.CLKPolarity = SPI_POLARITY_LOW;
		_handle.Init.CLKPhase = SPI_PHASE_2EDGE;
		break;
	case motorola_2:
		_handle.Init.CLKPolarity = SPI_POLARITY_HIGH;
		_handle.Init.CLKPhase = SPI_PHASE_1EDGE;
		break;
	case motorola_3:
		_handle.Init.CLKPolarity = SPI_POLARITY_HIGH;
		_handle.Init.CLKPhase = SPI_PHASE_2EDGE;
		break;
	default:
		while (1) { ; }  // something's wrong!
	}

	_handle.Init.BaudRatePrescaler = baudrate_prescaler;
	_handle.Init.TIMode = SPI_TIMODE_DISABLED;

	HAL_SPI_Init(&_handle);

/*
	  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
	  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLED;
*/

}

void SPIController::setup(GPIOPin clk, GPIOPin miso, GPIOPin mosi, GPIOPin nss)
{

	_clk = clk;
	_fss = nss;
	_rx = miso;
	_tx = mosi;

	switch (_controller) {
	case SPICONTROLLER_1:
	case SPICONTROLLER_2:
		if (clk.isValid()) {
			clk.mapAsSPI1CLK();
		}
		if (miso.isValid()) {
			miso.mapAsSPI1MISO();
		}
		if (mosi.isValid()) {
			mosi.mapAsSPI1MOSI();
		}
		if (nss.isValid()) {
			nss.mapAsSPI1NSS();
		}
		break;
	default:
		while (1) { ; } // something's wrong
		break;
	}

	return;
}


SPIController* SPIController::get(spicontroller_t num)
{
	if (_controllers[num] == NULL) {
		_controllers[num] = new SPIController(num);
		// TODO FIXME: init?
	}


	return _controllers[num];
}


int SPIController::writeAndRead(const void* writeBuf, void* readBuf, int len)
{

	return 0;
}


#endif


