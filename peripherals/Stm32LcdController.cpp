/*
 * StmLcdController.cpp
 *
 *  Created on: 15.02.2015
 *      Author: struppi
 */

#include "Stm32LcdController.h"


//#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _def)
//#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _rcc)
//#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _pwr)


Stm32LcdController* Stm32LcdController::_instance = 0;



Stm32LcdController* Stm32LcdController::getInstance()
{
	if (_instance == 0) {
		_instance = new Stm32LcdController();
	}

	return _instance;
}


int Stm32LcdController::setup()
{
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LCD;
	PeriphClkInit.LCDClockSelection = RCC_RTCCLKSOURCE_LSE;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

	init();

	return 1;
}

int Stm32LcdController::init()
{
	HAL_StatusTypeDef status;

	_hlcd.Instance = LCD;
	_hlcd.Init.Prescaler = LCD_PRESCALER_1;
	_hlcd.Init.Divider = LCD_DIVIDER_16;
	_hlcd.Init.Duty = LCD_DUTY_1_4;
	_hlcd.Init.Bias = LCD_BIAS_1_3;
	_hlcd.Init.VoltageSource = LCD_VOLTAGESOURCE_INTERNAL;
	_hlcd.Init.Contrast = LCD_CONTRASTLEVEL_3;
	_hlcd.Init.DeadTime = LCD_DEADTIME_0;
	_hlcd.Init.PulseOnDuration = LCD_PULSEONDURATION_0;
	_hlcd.Init.MuxSegment = LCD_MUXSEGMENT_ENABLE;
	_hlcd.Init.BlinkMode = LCD_BLINKMODE_OFF;
	_hlcd.Init.BlinkFrequency = LCD_BLINKFREQUENCY_DIV8;
	status = HAL_LCD_Init(&_hlcd);

	if (status == HAL_OK) {
		return 1;
	}
	else {
		return -status;
	}

}


extern "C" {
void HAL_LCD_MspInit(LCD_HandleTypeDef* hlcd)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hlcd->Instance==LCD)
  {
  /* USER CODE BEGIN LCD_MspInit 0 */

  /* USER CODE END LCD_MspInit 0 */
    /* Peripheral clock enable */
    __LCD_CLK_ENABLE();

    /**LCD GPIO Configuration
    PC0     ------> LCD_SEG18
    PC1     ------> LCD_SEG19
    PC2     ------> LCD_SEG20
    PC3     ------> LCD_SEG21
    PA1     ------> LCD_SEG0
    PA2     ------> LCD_SEG1
    PA3     ------> LCD_SEG2
    PB10     ------> LCD_SEG10
    PB11     ------> LCD_SEG11
    PB12     ------> LCD_SEG12
    PB13     ------> LCD_SEG13
    PB14     ------> LCD_SEG14
    PB15     ------> LCD_SEG15
    PC6     ------> LCD_SEG24
    PC7     ------> LCD_SEG25
    PC8     ------> LCD_SEG26
    PC9     ------> LCD_SEG27
    PA8     ------> LCD_COM0
    PA9     ------> LCD_COM1
    PA10     ------> LCD_COM2
    PA15     ------> LCD_SEG17
    PC10     ------> LCD_SEG40
    PC11     ------> LCD_SEG41
    PB3     ------> LCD_SEG7
    PB4     ------> LCD_SEG8
    PB5     ------> LCD_SEG9
    PB8     ------> LCD_SEG16
    PB9     ------> LCD_COM3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_VERY_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_VERY_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_VERY_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN LCD_MspInit 1 */

  /* USER CODE END LCD_MspInit 1 */
  }

}

void HAL_LCD_MspDeInit(LCD_HandleTypeDef* hlcd)
{

  if(hlcd->Instance==LCD)
  {
  /* USER CODE BEGIN LCD_MspDeInit 0 */

  /* USER CODE END LCD_MspDeInit 0 */
    /* Peripheral clock disable */
    __LCD_CLK_DISABLE();

    /**LCD GPIO Configuration
    PC0     ------> LCD_SEG18
    PC1     ------> LCD_SEG19
    PC2     ------> LCD_SEG20
    PC3     ------> LCD_SEG21
    PA1     ------> LCD_SEG0
    PA2     ------> LCD_SEG1
    PA3     ------> LCD_SEG2
    PB10     ------> LCD_SEG10
    PB11     ------> LCD_SEG11
    PB12     ------> LCD_SEG12
    PB13     ------> LCD_SEG13
    PB14     ------> LCD_SEG14
    PB15     ------> LCD_SEG15
    PC6     ------> LCD_SEG24
    PC7     ------> LCD_SEG25
    PC8     ------> LCD_SEG26
    PC9     ------> LCD_SEG27
    PA8     ------> LCD_COM0
    PA9     ------> LCD_COM1
    PA10     ------> LCD_COM2
    PA15     ------> LCD_SEG17
    PC10     ------> LCD_SEG40
    PC11     ------> LCD_SEG41
    PB3     ------> LCD_SEG7
    PB4     ------> LCD_SEG8
    PB5     ------> LCD_SEG9
    PB8     ------> LCD_SEG16
    PB9     ------> LCD_COM3
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9);

  /* USER CODE BEGIN LCD_MspDeInit 1 */

  /* USER CODE END LCD_MspDeInit 1 */
  }

}


}

Stm32LcdController::Stm32LcdController()
{
}

