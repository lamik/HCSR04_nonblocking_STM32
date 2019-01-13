/*
 * hcsr04.h
 *
 *  Created on: 4 gru 2017
 *		Author: Mateusz Salamon
 *		www.msalamon.pl
 *		mateusz@msalamon.pl
 *
 *	https://msalamon.pl/tani-dalmierz-ultradzwiekowy-hc-sr04/
 *	https://github.com/lamik/HCSR04_nonblocking_STM32
 */

#ifndef HCSR04_H_
#define HCSR04_H_

#define HCSR04_PWM_CHANNEL TIM_CHANNEL_3
#define HCSR04_START_CHANNEL TIM_CHANNEL_1
#define HCSR04_STOP_CHANNEL TIM_CHANNEL_2

#define HCSR04_HIGH_PRECISION

typedef enum{
	HCSR04_OK 	 = 0,
	HCSR04_ERROR = 1
} HCSR04_STATUS;

HCSR04_STATUS HCSR04_Init(TIM_HandleTypeDef *htim);
#ifdef HCSR04_HIGH_PRECISION
HCSR04_STATUS HCSR04_Read(float *Result);
#else
HCSR04_STATUS HCSR04_Read(uint16_t *Result);
#endif

void HCSR04_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif /* HCSR04_H_ */
