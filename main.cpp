/*
 * main.cpp
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

#include <stdint.h>
#include "kybos.h"

//#include "stm32l1xx_hal.h"
#include GENERATE_HAL_INCLUDE(STM32_FAMILY,)

//#include "stm32l1xx_hal_rcc.h"
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _rcc)
//#include "stm32l1xx_hal_pwr.h"
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _pwr)
//#include "stm32l1xx_hal_flash.h"
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _flash)
//#include "cmsis_os.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifndef STM32F0
extern "C" {
	void __attribute__((naked))
	SysCtlDelay(unsigned long ulCount)
	{
		__asm("    subs    r0, #1\n"
			  "    bne     SysCtlDelay\n"
			  "    bx      lr");
	}
}
#endif


#pragma GCC diagnostic pop



#include "../src/MainTask.h"

extern "C" {

	// must be implemented outside of kybos, i.e. in the application code
	extern void SystemClock_Config(void);

	void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
	{
		/* This function will get called if a task overflows its stack.   If the
		parameters are corrupt then inspect pxCurrentTCB to find which was the
		offending task. */

		( void ) pxTask;
		( void ) pcTaskName;

		for( ;; );
	}

	void vApplicationTickHook( void )
	{

	}

	void vApplicationMallocFailedHook( void )
	{
		while(1);
	}

	extern void vPortSVCHandler(void);
	extern void xPortPendSVHandler(void);
	extern void xPortSysTickHandler( void );


	void EndIdleMonitor(void) { }
	void StartIdleMonitor(void) { }

	void SysTick_Handler( void )
	{
		HAL_IncTick();
		xPortSysTickHandler();
	}

	void vApplicationIdleHook( void )
	{

	}


}


int main(void)
{

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	/* This function has to be implemented in userspace */
	SystemClock_Config();

	MainTask *mt = new MainTask();
	mt->run();
	//osKernelStart(NULL, NULL);
	vTaskStartScheduler();


	while(1) { ; } // Just in case...

}
