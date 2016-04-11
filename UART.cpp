/*
 * UART.cpp
 *
 * Copyright 2012 Germaneers GmbH
 * Copyright 2012 Hubert Denkmair (hubert.denkmair@germaneers.com)
 * Copyright 2012 Stefan Rupp (stefan.rupp@germaneers.com)
 *
 * This file is part of libopenstella.
 *
 * libopenstella is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * libopenstella is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libopenstella.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "UART.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "OS/Mutex.h"
#include "OS/Task.h"

#include "kybos.h"

#if defined (HAL_UART_MODULE_ENABLED)

UARTController *UARTController::_instances[] = { 0, };

UARTController *UARTController::get(controller_num_t num)
{
	if (!_instances[num]) {
		static Mutex mutex;
		MutexGuard guard(&mutex);
		_instances[num] = new UARTController(num);
	}
	return _instances[num];
}

UARTController::UARTController(controller_num_t num) :
	_num(num),
	_queue(32)
	//_enabled(false)
{
	switch (num) {
#if defined (UART1) || defined (USART1)
		case controller_1:
#if defined (UART1)
			_handle.Instance = UART1;
#else
			_handle.Instance = USART1;
#endif
			_queue.addToRegistry((char*)"UART1");
			break;
#endif
#if defined (UART2) || defined (USART2)
		case controller_2:
#if defined (UART2)
			_handle.Instance = UART2;
#else
			_handle.Instance = USART2;
#endif
			_queue.addToRegistry((char*)"UART2");
			break;
#endif
#if defined (UART3) || defined (USART3)
		case controller_3:
#if defined (UART3)
			_handle.Instance = UART3;
#else
			_handle.Instance = USART3;
#endif
			_queue.addToRegistry((char*)"UART3");
			break;
#endif
#if defined (UART4) || defined (USART4)
		case controller_4:
#if defined (UART4)
			_handle.Instance = UART4;
#else
			_handle.Instance = USART4;
#endif
			_queue.addToRegistry((char*)"UART4");
			break;
#endif
#if defined (UART5) || defined (USART5)
		case controller_5:
#if defined (UART5)
			_handle.Instance = UART5;
#else
			_handle.Instance = USART5;
#endif
			_queue.addToRegistry((char*)"UART5");
			break;
#endif
#if defined (UART6) || defined (USART6)
		case controller_6:
#if defined (UART6)
			_handle.Instance = UART6;
#else
			_handle.Instance = USART6;
#endif
			_queue.addToRegistry((char*)"UART6");
			break;
#endif
#if defined (UART7) || defined (USART7)
		case controller_7:
#if defined (UART7)
			_handle.Instance = UART7;
#else
			_handle.Instance = USART7;
#endif
			_queue.addToRegistry((char*)"UART7");
			break;
#endif
#if defined (UART8) || defined (USART8)
		case controller_8:
#if defined (UART4)
			_handle.Instance = UART8;
#else
			_handle.Instance = USART8;
#endif
			_queue.addToRegistry((char*)"UART8");
			break;
#endif
		default:
			while (1) { ; }
			break;
	}
}

void UARTController::handleInterrupt()
{
	_handle.pRxBuffPtr -= _handle.RxXferSize; // goto start of RX buffer
    for (int i=0; i<_handle.RxXferSize; i++){
    	uint8_t b = _handle.pRxBuffPtr[i];
    	if (!_queue.sendToBackFromISR(b)) {
    		static int queue_full_err = 0;
    		queue_full_err++;
    	}
    }
}

/*
void UARTController::enable()
{
	_enabled = true;
	//MAP_UARTEnable(_base);
}

void UARTController::disable()
{
	//MAP_UARTDisable(_base);
	_enabled = false;
}
*/

void UARTController::setup(GPIOPin rxpin, GPIOPin txpin, uint32_t baudrate, wordlength_t wordLength, parity_t parity, stopbits_t stopbits)
{
	RecursiveMutexGuard guard(&_mutex);


	_handle.Init.BaudRate = baudrate;
	_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	if (rxpin.isValid() && txpin.isValid()) {
		_handle.Init.Mode = UART_MODE_TX_RX;
	}
	else if (rxpin.isValid()) {
		_handle.Init.Mode = UART_MODE_RX;
	}
	else if (txpin.isValid()) {
		_handle.Init.Mode = UART_MODE_TX;
	}
	else {
		while (1) { ; }  // wth?
	}
	_handle.Init.OverSampling = UART_OVERSAMPLING_16;
	_handle.Init.Parity = parity;
	_handle.Init.StopBits = stopbits;
	_handle.Init.WordLength = wordLength;

	switch (_num) {
#if defined (UART1) || defined (USART1)
		case controller_1:
			if ( rxpin.isValid()) { rxpin.mapAsU1RX(); }
			if ( txpin.isValid()) { txpin.mapAsU1TX(); }
#if defined (UART1)
			__HAL_RCC_UART1_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART1_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART1_IRQn);

#else
			__HAL_RCC_USART1_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART1_IRQn);
#endif
			break;
#endif
#if defined (UART2) || defined (USART2)
		case controller_2:
			if ( rxpin.isValid()) { rxpin.mapAsU2RX(); }
			if ( txpin.isValid()) { txpin.mapAsU2TX(); }
#if defined (UART2)
			__HAL_RCC_UART2_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART2_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART2_IRQn);
#else
			__HAL_RCC_USART2_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART2_IRQn);
#endif
			break;
#endif
#if defined (STM32F072)
		case controller_3:
			if ( rxpin.isValid()) { rxpin.mapAsU3RX(); }
			if ( txpin.isValid()) { txpin.mapAsU3TX(); }
			__HAL_RCC_USART3_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART3_4_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART3_4_IRQn);
		    break;
		case controller_4:
			if ( rxpin.isValid()) { rxpin.mapAsU4RX(); }
			if ( txpin.isValid()) { txpin.mapAsU4TX(); }
			__HAL_RCC_USART4_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART3_4_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART3_4_IRQn);
		    break;
#else // NOT defined (STM32F072)
#if defined (UART3) || defined (USART3)
		case controller_3:
			if ( rxpin.isValid()) { rxpin.mapAsU3RX(); }
			if ( txpin.isValid()) { txpin.mapAsU3TX(); }
#if defined (UART3)
			__HAL_RCC_UART3_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART3_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART3_IRQn);
#else
			__HAL_RCC_USART3_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART3_IRQn);
#endif
			break;
#endif
#if defined (UART4) || defined (USART4)
		case controller_4:
			if ( rxpin.isValid()) { rxpin.mapAsU4RX(); }
			if ( txpin.isValid()) { txpin.mapAsU4TX(); }
#if defined (UART4)
			__HAL_RCC_UART4_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART4_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART4_IRQn);
#else
			__HAL_RCC_USART4_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART4_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART4_IRQn);
#endif
			break;
#endif
#endif // defined (STM32F072)

#if defined (UART5) || defined (USART5)
		case controller_5:
			if ( rxpin.isValid()) { rxpin.mapAsU5RX(); }
			if ( txpin.isValid()) { txpin.mapAsU5TX(); }
#if defined (UART5)
			__HAL_RCC_UART5_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART5_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART5_IRQn);
#else
			__HAL_RCC_USART5_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART5_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART5_IRQn);
#endif
			break;
#endif
#if defined (UART6) || defined (USART6)
		case controller_6:
			if ( rxpin.isValid()) { rxpin.mapAsU6RX(); }
			if ( txpin.isValid()) { txpin.mapAsU6TX(); }
#if defined (UART6)
			__HAL_RCC_UART6_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART6_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART6_IRQn);
#else
			__HAL_RCC_USART6_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART6_IRQn);
#endif
			break;
#endif
#if defined (UART7) || defined (USART7)
		case controller_7:
			if ( rxpin.isValid()) { rxpin.mapAsU7RX(); }
			if ( txpin.isValid()) { txpin.mapAsU7TX(); }
#if defined (UART7)
			__HAL_RCC_UART7_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART7_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART7_IRQn);
#else
			__HAL_RCC_USART7_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART7_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART7_IRQn);
#endif
			break;
#endif
#if defined (UART8) || defined (USART8)
		case controller_8:
			if ( rxpin.isValid()) { rxpin.mapAsU8RX(); }
			if ( txpin.isValid()) { txpin.mapAsU8TX(); }
#if defined (UART8)
			__HAL_RCC_UART8_CLK_ENABLE();
		    HAL_NVIC_SetPriority(UART8_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(UART8_IRQn);
#else
			__HAL_RCC_USART8_CLK_ENABLE();
		    HAL_NVIC_SetPriority(USART8_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(USART8_IRQn);
#endif
			break;
#endif
		default:
			while (1) { ; }
			break;
	}

	_txCpltSema.take(); // Take once, so reads will block

	_handle.pRxBuffPtr = _rxBuf;
	_handle.pTxBuffPtr = _txBuf;

	HAL_UART_Init(&_handle);

	//__HAL_UART_ENABLE_IT(&_handle, UART_IT_RXNE);
	HAL_UART_Receive_IT(&_handle, _rxBuf, 1);

}


void UARTController::putChar(uint8_t c)
{
	RecursiveMutexGuard guard(&_mutex);

	HAL_UART_Transmit_IT(&_handle, &c, 1);
	_txCpltSema.take();
}

uint8_t UARTController::getChar(void)
{
	uint8_t result = 0;
	while (!_queue.receive(&result)) {
		static int receive_err = 0;
		receive_err++;
	}
	return result;
}


int16_t UARTController::getCharNonBlocking()
{
	uint8_t data;
	if (_queue.receive(&data, 0)) {
		return data;
	} else {
		return -1;
	}
}

int16_t UARTController::getCharTimeout(uint32_t timeout) {
	uint8_t data;
	if (_queue.receive(&data, timeout)) {
		return data;
	} else {
		return -1;
	}
}




void UARTController::write(const void * const ptr, int len)
{
	uint8_t *s = (uint8_t *) ptr;
	int i = 0;

	while (len--) {
		putChar(s[i++]);
		//s++;
	}
}

void UARTController::write( const void * const string)
{
	uint8_t *s = (uint8_t *) string;
	while (s[0]!=0) {
		putChar(s[0]);
		s++;
	}
}

RecursiveMutex *UARTController::getMutex()
{
	return &_mutex;
}

/*
void UARTController::setupLinMaster(uint32_t baudrate, GPIOPin rxpin, GPIOPin txpin)
{
	setup(rxpin, txpin, baudrate, wordlength_8bit, parity_none, stopbits_1);
	enableFIFO();
	HWREG(_base + UART_O_LCTL) |= UART_LCTL_MASTER | UART_LCTL_BLEN_16T;
	HWREG(_base + UART_O_CTL)  |= UART_CTL_LIN;
}
*/

/*
void UARTController::setupLinSlave(uint32_t baudrate, GPIOPin rxpin, GPIOPin txpin)
{

	setup(rxpin, txpin, baudrate, wordlength_8bit, parity_none, stopbits_1, false);
	setFIFORxLevel(UARTController::fifo_rx_level_1_8);
	enableFIFO();
	HWREG(_base + UART_O_LCTL) |= UART_LCTL_BLEN_16T;
	HWREG(_base + UART_O_CTL)  |= UART_CTL_LIN;
}
*/


void UARTController::printf( const char* format, ... )
{
    va_list args;
    va_start( args, format );
    int size = vsniprintf(0, 0, format, args);
    char *buf = (char*) pvPortMalloc(size+1);
    vsiprintf(buf, format, args);
    va_end( args );
    write(buf);
    vPortFree(buf);
}

/// read a number of bytes from the UART controller
/**
 * @param buf The buffer the data shall be read into
 * @param bufSize size of the buffer in bytes
 * @return the requested CANController object. newly constructed, if not requested before.
 */
void UARTController::read(void *buf, int bufSize)
{
	uint8_t *data = (uint8_t *) buf;

	while (bufSize--) {
		*(data++) = getChar();
	}
}


/// read from the UART controller until a terminating character appears in the byte stream
/**
 * at maximum, bufSize number of bytes are read if the terminator sequence doesn't appear prior to that
 * @param buf The buffer the data shall be read into
 * @param bufSize Size of the buffer in bytes
 * @param terminator Stop reading and return when this character is found.
 * @return The number of bytes read from the UART.
 */
int UARTController::readUntil(const void *buf, int bufSize, uint8_t terminator)
{
	uint8_t *data = (uint8_t *) buf;
	int numRead;
	bool terminated = false;

	for ( numRead = 1; bufSize > 0; bufSize--) {
		data[numRead-1] = getChar();
		if (data[numRead-1] == terminator) terminated = true;
		numRead++;
		if (terminated) {
			break;
		}
	}

	return (numRead - 1);
}


/// read from the UART controller until a terminating sequence of bytes appears in the stream
/**
 * at maximum, bufSize number of bytes are read if the terminator sequence doesn't appear prior to that
 * @param buf The buffer the data shall be read into
 * @param bufSize Size of the buffer in bytes
 * @param terminator Stop reading and return when this byte sequence is found.
 * @param terminatorLength Size of the terminator sequence in bytes
 * @return The number of bytes read from the UART.
 */
int UARTController::readUntil(const void *buf, int bufSize, const void * const terminator, int terminatorLength)
{
	uint8_t *data = (uint8_t *) buf;
	uint8_t *t = (uint8_t *) terminator;
	bool terminated=false;
	int numRead;

	for ( numRead = 1; bufSize > 0; bufSize--) {
		data[numRead-1] = getChar();

		if (numRead >= terminatorLength) {
			terminated = true;
			for (int i = terminatorLength; i > 0; i--) {
				if (t[i-1] != data[numRead - terminatorLength + i - 1]) {
					terminated = false;
					break;
				}
			}
		}
		numRead++;
		if (terminated) {
			break;
		}
	}

	return numRead - 1;
}

int UARTController::readLine(const void *buf, int bufSize)
{
	int i;
	uint8_t *data = (uint8_t *) buf;
	for (i=0; i<bufSize-1; i++) {
		data[i] = getChar();
		if ( (i > 0) && (data[i-1]==13) && (data[i]==10) ) {
			break;
		}
	}
	data[i+1] = 0x00;
	return i;
}

extern "C" {

#if defined (UART1) || defined (USART1)
#if defined (UART1)
void UART1_IRQHandler(void)
#elif defined (USART1)
void USART1_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_1]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_1]->_handle), UARTController::_instances[UARTController::controller_1]->_rxBuf, 1);
}
#endif

#if defined (UART2) || defined (USART2)
#if defined (UART2)
void UART2_IRQHandler(void)
#elif defined (USART2)
void USART2_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_2]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_2]->_handle), UARTController::_instances[UARTController::controller_2]->_rxBuf, 1);
}
#endif

#if defined (STM32F072)
void USART3_4_IRQHandler(void)
{
	//For now, just try on both UARTs. I'm sure there must be a better way :)
	HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_3]->_handle);
	HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_3]->_handle), UARTController::_instances[UARTController::controller_3]->_rxBuf, 1);
	HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_4]->_handle);
	HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_4]->_handle), UARTController::_instances[UARTController::controller_3]->_rxBuf, 1);
}
#else // NOT defined (STM32F072)
#if defined (UART3) || defined (USART3)
#if defined (UART3)
void UART3_IRQHandler(void)
#elif defined (USART3)
void USART3_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_3]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_3]->_handle), UARTController::_instances[UARTController::controller_3]->_rxBuf, 1);
}
#endif

#if defined (UART4) || defined (USART4)
#if defined (UART4)
void UART4_IRQHandler(void)
#elif defined (USART4)
void USART4_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_4]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_4]->_handle), UARTController::_instances[UARTController::controller_4]->_rxBuf, 1);
}
#endif
#endif // defined (STM32F072)

#if defined (UART5) || defined (USART5)
#if defined (UART5)
void UART5_IRQHandler(void)
#elif defined (USART5)
void USART5_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_5]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_5]->_handle), UARTController::_instances[UARTController::controller_5]->_rxBuf, 1);
}
#endif

#if defined (UART6) || defined (USART6)
#if defined (UART6)
void UART6_IRQHandler(void)
#elif defined (USART6)
void USART6_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_6]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_6]->_handle), UARTController::_instances[UARTController::controller_6]->_rxBuf, 1);
}
#endif


#if defined (UART7) || defined (USART7)
#if defined (UART7)
void UART7_IRQHandler(void)
#elif defined (USART7)
void USART7_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_7]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_7]->_handle), UARTController::_instances[UARTController::controller_7]->_rxBuf, 1);
}
#endif

#if defined (UART8) || defined (USART8)
#if defined (UART8)
void UART8_IRQHandler(void)
#elif defined (USART8)
void USART8_IRQHandler(void)
#endif
{
  HAL_UART_IRQHandler(&UARTController::_instances[UARTController::controller_8]->_handle);
  HAL_UART_Receive_IT(&(UARTController::_instances[UARTController::controller_8]->_handle), UARTController::_instances[UARTController::controller_8]->_rxBuf, 1);
}
#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
#if defined (UART1)
	if (huart->Instance == UART1) { UARTController::_instances[UARTController::controller_1]->_txCpltSema.giveFromISR(); }
#elif defined (USART1)
	if (huart->Instance == USART1) { UARTController::_instances[UARTController::controller_1]->_txCpltSema.giveFromISR(); }
#endif

#if defined (UART2)
	if (huart->Instance == UART2) { UARTController::_instances[UARTController::controller_2]->_txCpltSema.giveFromISR(); }
#elif defined (USART2)
	if (huart->Instance == USART2) { UARTController::_instances[UARTController::controller_2]->_txCpltSema.giveFromISR(); }
#endif

#if defined (UART3)
	if (huart->Instance == UART3) { UARTController::_instances[UARTController::controller_3]->_txCpltSema.giveFromISR(); }
#elif defined (USART3)
	if (huart->Instance == USART3) { UARTController::_instances[UARTController::controller_3]->_txCpltSema.giveFromISR(); }
#endif

#if defined (UART4)
	if (huart->Instance == UART4) { UARTController::_instances[UARTController::controller_4]->_txCpltSema.giveFromISR(); }
#elif defined (USART4)
	if (huart->Instance == USART4) { UARTController::_instances[UARTController::controller_4]->_txCpltSema.giveFromISR(); }
#endif

#if defined (UART5)
	if (huart->Instance == UART5) { UARTController::_instances[UARTController::controller_5]->_txCpltSema.giveFromISR(); }
#elif defined (USART5)
	if (huart->Instance == USART5) { UARTController::_instances[UARTController::controller_5]->_txCpltSema.giveFromISR(); }
#endif

#if defined (UART6)
	if (huart->Instance == UART6) { UARTController::_instances[UARTController::controller_6]->_txCpltSema.giveFromISR(); }
#elif defined (USART6)
	if (huart->Instance == USART6) { UARTController::_instances[UARTController::controller_6]->_txCpltSema.giveFromISR(); }
#endif

#if defined (UART7)
	if (huart->Instance == UART7) { UARTController::_instances[UARTController::controller_7]->_txCpltSema.giveFromISR(); }
#elif defined (USART7)
	if (huart->Instance == USART7) { UARTController::_instances[UARTController::controller_7]->_txCpltSema.giveFromISR(); }
#endif

#if defined (UART8)
	if (huart->Instance == UART8) { UARTController::_instances[UARTController::controller_8]->_txCpltSema.giveFromISR(); }
#elif defined (USART8)
	if (huart->Instance == USART8) { UARTController::_instances[UARTController::controller_8]->_txCpltSema.giveFromISR(); }
#endif

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if defined (UART1)
	if (huart->Instance == UART1) { UARTController::_instances[UARTController::controller_1]->handleInterrupt(); }
#elif defined (USART1)
	if (huart->Instance == USART1) { UARTController::_instances[UARTController::controller_1]->handleInterrupt(); }
#endif

#if defined (UART2)
	if (huart->Instance == UART2) { UARTController::_instances[UARTController::controller_2]->handleInterrupt(); }
#elif defined (USART2)
	if (huart->Instance == USART2) { UARTController::_instances[UARTController::controller_2]->handleInterrupt(); }
#endif

#if defined (UART3)
	if (huart->Instance == UART3) { UARTController::_instances[UARTController::controller_3]->handleInterrupt(); }
#elif defined (USART3)
	if (huart->Instance == USART3) { UARTController::_instances[UARTController::controller_3]->handleInterrupt(); }
#endif

#if defined (UART4)
	if (huart->Instance == UART4) { UARTController::_instances[UARTController::controller_4]->handleInterrupt(); }
#elif defined (USART4)
	if (huart->Instance == USART4) { UARTController::_instances[UARTController::controller_4]->handleInterrupt(); }
#endif

#if defined (UART5)
	if (huart->Instance == UART5) { UARTController::_instances[UARTController::controller_5]->handleInterrupt(); }
#elif defined (USART5)
	if (huart->Instance == USART5) { UARTController::_instances[UARTController::controller_5]->handleInterrupt(); }
#endif

#if defined (UART6)
	if (huart->Instance == UART6) { UARTController::_instances[UARTController::controller_6]->handleInterrupt(); }
#elif defined (USART6)
	if (huart->Instance == USART6) { UARTController::_instances[UARTController::controller_6]->handleInterrupt(); }
#endif

#if defined (UART7)
	if (huart->Instance == UART7) { UARTController::_instances[UARTController::controller_7]->handleInterrupt(); }
#elif defined (USART7)
	if (huart->Instance == USART7) { UARTController::_instances[UARTController::controller_7]->handleInterrupt(); }
#endif

#if defined (UART8)
	if (huart->Instance == UART8) { UARTController::_instances[UARTController::controller_8]->handleInterrupt(); }
#elif defined (USART8)
	if (huart->Instance == USART8) { UARTController::_instances[UARTController::controller_8]->handleInterrupt(); }
#endif

}


} // extern "C"


#endif // defined (HAL_UART_MODULE_ENABLED)


