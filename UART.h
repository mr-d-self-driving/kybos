/*
 * UART.h
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


#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "OS/Queue.h"
#include "OS/RecursiveMutex.h"
#include "OS/Semaphore.h"
#include "GPIO.h"
#include "kybos.h"

#if defined (HAL_UART_MODULE_ENABLED)

extern "C" {
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#if defined (UART1)
void UART1_IRQHandler(void);
#elif defined (USART1)
void USART1_IRQHandler(void);
#endif

#if defined (UART2)
void UART2_IRQHandler(void);
#elif defined (USART2)
void USART2_IRQHandler(void);
#endif

# if defined (STM32F072)
void USART3_4_IRQHandler(void);
#else // NOT defined (STM32F072)
#if defined (UART3)
void UART3_IRQHandler(void);
#elif defined (USART3)
void USART3_IRQHandler(void);
#endif

#if defined (UART4)
void UART4_IRQHandler(void);
#elif defined (USART4)
void USART4_IRQHandler(void);
#endif
#endif // defined (STM32F072)

#if defined (UART5)
void UART5_IRQHandler(void);
#elif defined (USART5)
void USART5_IRQHandler(void);
#endif

#if defined (UART6)
void UART6_IRQHandler(void);
#elif defined (USART6)
void USART6_IRQHandler(void);
#endif

#if defined (UART7)
void UART7_IRQHandler(void);
#elif defined (USART7)
void USART7_IRQHandler(void);
#endif

#if defined (UART8)
void UART8_IRQHandler(void);
#elif defined (USART8)
void USART8_IRQHandler(void);
#endif

}  // extern "C"


class UARTController
{

	friend void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
	friend void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

	#if defined (UART1)
	friend void UART1_IRQHandler(void);
	#elif defined (USART1)
	friend void USART1_IRQHandler(void);
	#endif

	#if defined (UART2)
	friend void UART2_IRQHandler(void);
	#elif defined (USART2)
	friend void USART2_IRQHandler(void);
	#endif

#if defined (STM32F072)
	friend void USART3_4_IRQHandler(void);
#else // NOT defined (STM32F072)
	#if defined (UART3)
	friend void UART3_IRQHandler(void);
	#elif defined (USART3)
	friend void USART3_IRQHandler(void);
	#endif

	#if defined (UART4)
	friend void UART4_IRQHandler(void);
	#elif defined (USART4)
	friend void USART4_IRQHandler(void);
	#endif
#endif // defined (STM32F072)

	#if defined (UART5)
	friend void UART5_IRQHandler(void);
	#elif defined (USART5)
	friend void USART5_IRQHandler(void);
	#endif

	#if defined (UART6)
	friend void UART6_IRQHandler(void);
	#elif defined (USART6)
	friend void USART6_IRQHandler(void);
	#endif

	#if defined (UART7)
	friend void UART7_IRQHandler(void);
	#elif defined (USART7)
	friend void USART7_IRQHandler(void);
	#endif

	#if defined (UART8)
	friend void UART8_IRQHandler(void);
	#elif defined (USART8)
	friend void USART8_IRQHandler(void);
	#endif

	public:

		void handleInterrupt();

		typedef enum {
#if defined (UART1) || defined (USART1)
			controller_1,
#endif
#if defined (UART2) || defined (USART2)
			controller_2,
#endif
#if defined (UART3) || defined (USART3)
			controller_3,
#endif
#if defined (UART4) || defined (USART4)
			controller_4,
#endif
#if defined (UART5) || defined (USART5)
			controller_5,
#endif
#if defined (UART6) || defined (USART6)
			controller_6,
#endif
#if defined (UART7) || defined (USART7)
			controller_7,
#endif
#if defined (UART8) || defined (USART8)
			controller_8,
#endif
			num_uart_controllers
		} controller_num_t;

		typedef enum {
#if defined (UART_WORDLENGTH_5B)
			wordlength_5bit = UART_WORDLENGTH_5B,
#endif
#if defined (UART_WORDLENGTH_6B)
			wordlength_6bit = UART_WORDLENGTH_6B,
#endif
#if defined (UART_WORDLENGTH_7B)
			wordlength_7bit = UART_WORDLENGTH_7B,
#endif
#if defined (UART_WORDLENGTH_8B)
			wordlength_8bit = UART_WORDLENGTH_8B,
#endif
#if defined (UART_WORDLENGTH_9B)
			wordlength_9bit = UART_WORDLENGTH_9B,
#endif
		} wordlength_t;

		typedef enum {
			parity_none = UART_PARITY_NONE,
			parity_even = UART_PARITY_EVEN,
			parity_odd  = UART_PARITY_ODD,
/*
			parity_one  = 0x82,
			parity_zero = 0x86
*/
		} parity_t;

		typedef enum {
#if defined (UART_STOPBITS_1)
			stopbits_1 = UART_STOPBITS_1,
#endif
#if defined (UART_STOPBITS_2)
			stopbits_2 = UART_STOPBITS_2,
#endif
#if defined (UART_STOPBITS_1_5)
			stopbits_1_5 = UART_STOPBITS_1_5,
#endif
		} stopbits_t;


	private:
		controller_num_t _num;

		Queue<uint8_t> _queue;
		RecursiveMutex _mutex;
		Semaphore _txCpltSema;

		static UARTController *_instances[num_uart_controllers];
		UARTController(controller_num_t num);

		//bool _enabled;

		UART_HandleTypeDef _handle;
		uint8_t _rxBuf[16];
		uint8_t _txBuf[16];

	public:

		static UARTController *get(controller_num_t num);

		RecursiveMutex *getMutex();
		//void enable();
		//void disable();

		void setup(GPIOPin rxpin=GPIOPin::invalid, GPIOPin txpin=GPIOPin::invalid, uint32_t baudrate=115200, wordlength_t wordLength=wordlength_8bit, parity_t parity=parity_none, stopbits_t stopbits=stopbits_1);

		//void setupLinMaster(uint32_t baudrate, GPIOPin rxpin, GPIOPin txpin);
		//void setupLinSlave(uint32_t baudrate, GPIOPin rxpin, GPIOPin txpin);

		//void setLineParameters(uint32_t baudrate, wordlength_t wordLength, parity_t parity, stopbits_t stopbits);
		//uint32_t getBaudrate();
		//wordlength_t getWordLength();
		//parity_t getParity();
		//stopbits_t getStopBits();


		//void setParityMode(parity_t parity);
		//parity_t getParityMode(void);

		//void setBreakState(bool breakState);
		//bool isTransmitting();

		void putChar(uint8_t c);
		uint8_t getChar();

		void putCharNonblocking(uint8_t c);
		int16_t getCharNonBlocking();
		int16_t getCharTimeout(uint32_t timeout);

		//void enableSIR(bool lowPower); // disable() enableSIR(); enable()
		//void disableSIR();
		//uint32_t getRxError();
		//void clearRxError();

		//void enableSmartCard();
		//void disableSmartCard();

		// todo: intEnable, intDisable, intRegister, intUnregister, intStatus, intClear, txIntMode
		// todo: dmaenable, DMAdisable

		// todo: ModemControl
		// TODO: Hardware Flow Control

		// TODO: loopback

		// TODO: scanf?

		void write( const void * const s);
		void write(const void * const s, int len);
		void printf( const char* format, ... );

		void read(void *buf, int bufSize);
		int readUntil(const void *buf, int bufSize, uint8_t terminator);
		int readUntil(const void *buf, int bufSize, const void * const terminator, int terminatorLength);
		int readLine(const void *buf, int bufSize);

};

#endif // defined (HAL_UART_MODULE_ENABLED)

#endif /* UART_H_ */
