/*
 * SPIController.cpp
 *
 *  Created on: 18.03.2016
 *      Author: stefan.rupp
 */




#include "kybos.h"

#ifdef HAL_SPI_MODULE_ENABLED

#include "GPIO.h"
#include "SPIController.h"


SPIController* SPIController::_controllers[SPIController::SPICONTROLLER_COUNT] = {0, };


SPIController::SPIController(spicontroller_t controller)
: _controller(controller)
{

	switch (controller) {
#if defined (SPI1)
	case SPICONTROLLER_1:
		_handle.Instance = SPI1;
		break;
#endif
#if defined (SPI2)
	case SPICONTROLLER_2:
		_handle.Instance = SPI2;
		break;
#endif
#if defined (SPI3)
	case SPICONTROLLER_3:
		_handle.Instance = SPI3;
		break;
#endif
#if defined (SPI4)
	case SPICONTROLLER_4:
		_handle.Instance = SPI4;
		break;
#endif
#if defined (SPI5)
	case SPICONTROLLER_5:
		_handle.Instance = SPI5;
		break;
#endif
#if defined (SPI6)
	case SPICONTROLLER_6:
		_handle.Instance = SPI6;
		break;
#endif
	default:
		while (1) { ; }
	}

}


void SPIController::configure(protocol_t protocol, mode_t mode, baudrate_ps_t baudrate_prescaler, data_width_t data_width)
{
	_handle.Init.Mode = mode;
	_handle.Init.DataSize = data_width;
	_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	_handle.Init.CRCPolynomial = 7;
	//_handle.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	_handle.Init.Direction = SPI_DIRECTION_2LINES;
	if ( _nss.isValid() ) {
		_handle.Init.NSS = (mode==master)?SPI_NSS_HARD_OUTPUT:SPI_NSS_HARD_INPUT;
	}
	else {
		_handle.Init.NSS = SPI_NSS_SOFT;
	}
	_handle.Init.BaudRatePrescaler = baudrate_prescaler;
	_handle.Init.TIMode = SPI_TIMODE_DISABLED;


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

	HAL_SPI_Init(&_handle);

}

void SPIController::setup(GPIOPin clk, GPIOPin miso, GPIOPin mosi, GPIOPin nss)
{

	_clk = clk;
	_nss = nss;
	_miso = miso;
	_mosi = mosi;

	switch (_controller) {
#if defined (SPI1)
	case SPICONTROLLER_1:
		clk.isValid()  ? clk.mapAsSPI1CLK()   : void();
		miso.isValid() ? miso.mapAsSPI1MISO() : void();
		mosi.isValid() ? mosi.mapAsSPI1MOSI() : void();
		nss.isValid()  ? nss.mapAsSPI1NSS()   : void();
		break;
#endif
#if defined (SPI2)
	case SPICONTROLLER_2:
		clk.isValid()  ? clk.mapAsSPI2CLK()   : void();
		miso.isValid() ? miso.mapAsSPI2MISO() : void();
		mosi.isValid() ? mosi.mapAsSPI2MOSI() : void();
		nss.isValid()  ? nss.mapAsSPI2NSS()   : void();
		break;
#endif
#if defined (SPI3)
	case SPICONTROLLER_3:
		clk.isValid()  ? clk.mapAsSPI3CLK()   : void();
		miso.isValid() ? miso.mapAsSPI3MISO() : void();
		mosi.isValid() ? mosi.mapAsSPI3MOSI() : void();
		nss.isValid()  ? nss.mapAsSPI3NSS()   : void();
		break;
#endif
#if defined (SPI4)
	case SPICONTROLLER_4:
		clk.isValid()  ? clk.mapAsSPI4CLK()   : void();
		miso.isValid() ? miso.mapAsSPI4MISO() : void();
		mosi.isValid() ? mosi.mapAsSPI4MOSI() : void();
		nss.isValid()  ? nss.mapAsSPI4NSS()   : void();
		break;
#endif
#if defined (SPI5)
	case SPICONTROLLER_5:
		clk.isValid()  ? clk.mapAsSPI5CLK()   : void();
		miso.isValid() ? miso.mapAsSPI5MISO() : void();
		mosi.isValid() ? mosi.mapAsSPI5MOSI() : void();
		nss.isValid()  ? nss.mapAsSPI5NSS()   : void();
		break;
#endif
#if defined (SPI6)
	case SPICONTROLLER_6:
		clk.isValid()  ? clk.mapAsSPI6CLK()   : void();
		miso.isValid() ? miso.mapAsSPI6MISO() : void();
		mosi.isValid() ? mosi.mapAsSPI6MOSI() : void();
		nss.isValid()  ? nss.mapAsSPI6NSS()   : void();
		break;
#endif
	default:
		while (1) { ; } // something's wrong
		break;
	}

	return;
}


SPIController* SPIController::get(spicontroller_t num)
{
	if ( _controllers[num] == NULL ) {
		_controllers[num] = new SPIController(num);
	}

	return _controllers[num];
}


int SPIController::writeAndRead(const void* writeBuf, void* readBuf, int len)
{

	return 0;
}


#endif


