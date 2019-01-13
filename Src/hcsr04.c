/*
 * hcsr04.c
 *
 *  Created on: 4 gru 2017
 *		Author: Mateusz Salamon
 *		www.msalamon.pl
 *		mateusz@msalamon.pl
 *
 *	https://msalamon.pl/tani-dalmierz-ultradzwiekowy-hc-sr04/
 *	https://github.com/lamik/HCSR04_nonblocking_STM32
 */

#include "main.h"
#include "stm32l4xx_hal.h"
#include "tim.h"

#include "hcsr04.h"

TIM_HandleTypeDef *htim_hcsr04;
#ifdef HCSR04_HIGH_PRECISION
volatile float Hcsr04_Distance;
#else
volatile uint16_t  Hcsr04_Distance;
#endif

HCSR04_STATUS HCSR04_Init(TIM_HandleTypeDef *htim)
{
	htim_hcsr04 = htim;

	HAL_TIM_Base_Start(htim_hcsr04);
	HAL_TIM_PWM_Start(htim_hcsr04, HCSR04_PWM_CHANNEL);
	HAL_TIM_IC_Start(htim_hcsr04, HCSR04_START_CHANNEL);
	HAL_TIM_IC_Start_IT(htim_hcsr04, HCSR04_STOP_CHANNEL);

	return HCSR04_OK;
}

#ifdef HCSR04_HIGH_PRECISION
HCSR04_STATUS HCSR04_Read(float *Result)
{
	*Result =  Hcsr04_Distance;

	return HCSR04_OK;
}
#else
HCSR04_STATUS HCSR04_Read(uint16_t *Result)
{
	*Result =  Hcsr04_Distance;

	return HCSR04_OK;
}
#endif

void HCSR04_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim == htim_hcsr04)
	{
		uint16_t time;


		time = (uint16_t)((uint16_t)__HAL_TIM_GetCompare(htim_hcsr04, HCSR04_STOP_CHANNEL) - (uint16_t)__HAL_TIM_GetCompare(htim_hcsr04, HCSR04_START_CHANNEL));
#ifdef HCSR04_HIGH_PRECISION
		Hcsr04_Distance = (float)time / 2.0 * 0.0343;
#else
		Hcsr04_Distance = time / 58;
#endif
		HAL_TIM_IC_Start_IT(htim_hcsr04, HCSR04_STOP_CHANNEL);
	}
}

