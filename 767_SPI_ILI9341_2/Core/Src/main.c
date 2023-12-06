/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stm32f7xx_hal.h"
#include "am2320.h"
#include "ILI9341_Touchscreen.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#include <math.h>
#include <stdarg.h>
//#include "snow_tiger.h"

#include <toey_resize.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define print(x) HAL_UART_Transmit(&huart3, (uint8_t*)x, strlen(x),1000)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char ex[] = "\n\rBack";
char ex2[] = "\n\rEnter";
char ex3[] = "\n\rUp";
char ex4[] = "\n\rDown";
char ex5[] = "\n\rLeft";
char ex6[] = "\n\rRight";
int a = 0;
char x[100];
char ch1[1000];

// RGB variable
uint32_t count = 0;
int isLED[4];
int interval[4];

// rgb
int ispressed[8];
int intervalPreesed[8];

// Drum
volatile uint32_t adc_val[4];

uint32_t adc_hit[4];
uint32_t adcIntervalMillis[4];
uint32_t adcIntervalPrevios[4];

HAL_StatusTypeDef status;

UART_HandleTypeDef huart2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
uint16_t CRC16_2(uint8_t*, uint8_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define MAX_LED 35
#define USE_BRIGHTNESS 1

uint8_t datasentflag = 0;
uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];

void Set_LED(int LEDnum, int Red, int Green, int Blue) {
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

#define PI 3.14159265

void Set_Brightness(int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45)
		brightness = 45;
	for (int i = 0; i < MAX_LED; i++) {
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j = 1; j < 4; j++) {
			float angle = 90 - brightness;  // in degrees
			angle = angle * PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j]) / (tan(angle));
		}
	}

#endif

}

uint16_t pwmData[(24 * MAX_LED) + 50];

void WS2812_Send(void) {
	uint32_t indx = 0;
	uint32_t color;

	for (int i = 0; i < MAX_LED; i++) {
#if USE_BRIGHTNESS
		color =
				((LED_Mod[i][1] << 16) | (LED_Mod[i][2] << 8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i = 23; i >= 0; i--) {
			if (color & (1 << i)) {
				pwmData[indx] = 60;  // 2/3 of 90
			}

			else
				pwmData[indx] = 30;  // 1/3 of 90

			indx++;
		}

	}

	for (int i = 0; i < 50; i++) {
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*) pwmData, indx);
	while (!datasentflag) {
	};
	datasentflag = 0;
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	datasentflag = 1;
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	/* USER CODE END 1 */

	/* Enable I-Cache---------------------------------------------------------*/
	SCB_EnableICache();

	/* Enable D-Cache---------------------------------------------------------*/
	SCB_EnableDCache();

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SPI5_Init();
	MX_RNG_Init();
	MX_TIM2_Init();
	MX_I2C4_Init();
	MX_ADC1_Init();
	MX_TIM1_Init();
	MX_USART3_UART_Init();
	MX_TIM4_Init();
	MX_USB_OTG_FS_USB_Init();
	/* USER CODE BEGIN 2 */
	ILI9341_Init(); //initial driver setup to drive ili9341
	ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	ILI9341_Draw_Image((const char*) image_data_tot, SCREEN_VERTICAL_1);
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc_val, 4);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		// Part 1 RGB
		if (count >= 100) {
			if (isLED[0]) {
				interval[0]++;
			}
			if (isLED[1]) {
				interval[1]++;
			}
			if (isLED[2]) {
				interval[2]++;
			}
			if (isLED[3]) {
				interval[3]++;
			}
			count = 0;
		}

		//hit Upper Left

		if (adc_hit[0]) {
			isLED[0] = 1;
			for (int i = 0; i < 35; i++)
				Set_LED(i, 0, 0, 200);
			Set_Brightness(20);
			WS2812_Send();
		}

		if ((isLED[0] = 1) && (interval[0] >= 3)) {
			Set_Brightness(0);
			WS2812_Send();
			isLED[0] = 0;
			interval[0] = 0;
		}
		// hit center left
		if (adc_hit[1]) {
			isLED[1] = 1;
			for (int i = 0; i < 35; i++)
				Set_LED(i, 255, 0, 0);
			Set_Brightness(20);
			WS2812_Send();
		}

		if ((isLED[1] = 1) && (interval[1] >= 3)) {
			Set_Brightness(0);
			WS2812_Send();
			isLED[1] = 0;
			interval[1] = 0;
		}

		//hit center right
		if (adc_hit[2]) {
			isLED[2] = 1;
			for (int i = 0; i < 35; i++)
				Set_LED(i, 255, 0, 0);
			Set_Brightness(20);
			WS2812_Send();
		}

		if ((isLED[2] = 1) && (interval[2] >= 3)) {
			Set_Brightness(0);
			WS2812_Send();
			isLED[2] = 0;
			interval[2] = 0;
		}

		// Hit Upper right
		if (adc_hit[3]) {
			isLED[3] = 1;
			for (int i = 0; i < 35; i++)
				Set_LED(i, 0, 0, 200);
			Set_Brightness(20);
			WS2812_Send();
		}

		if ((isLED[3] = 1) && (interval[3] >= 3)) {
			Set_Brightness(0);
			WS2812_Send();
			isLED[3] = 0;
			interval[3] = 0;
		}

		// Part 2 Drum
//		char buffer[100];
//		sprintf(buffer, "%d %d %d %d\n\r", adc_val[0], adc_val[1], adc_val[2],
//				adc_val[3]);
//		print(buffer);

		adcIntervalMillis[0] = HAL_GetTick();
		adcIntervalMillis[1] = HAL_GetTick();
		adcIntervalMillis[2] = HAL_GetTick();
		adcIntervalMillis[3] = HAL_GetTick();
		if (adc_val[0] >= 2800 && adc_hit[0] == 0) {
			adc_hit[0] = 1;

		}
		else if (adc_val[1] >= 1000 && adc_hit[1] == 0) {
			adc_hit[1] = 1;

		}
		else if (adc_val[2] >= 2000 && adc_hit[2] == 0) {
			adc_hit[2] = 1;

		}
		else if (adc_val[3] >= 2000 && adc_hit[3] == 0) {
			adc_hit[3] = 1;

		}

		if (adc_hit[0] == 1
				&& (adcIntervalMillis[0] - adcIntervalPrevios[0] > ((40)+(a*1000)))) {
			print("D");
			adc_hit[0] = 0;
			adcIntervalPrevios[0] = adcIntervalMillis[0];
		}

		if (adc_hit[1] == 1
				&& (adcIntervalMillis[1] - adcIntervalPrevios[1] > ((40)+(a*1000)))) {
			print("F");
			adc_hit[1] = 0;
			adcIntervalPrevios[1] = adcIntervalMillis[1];
		}

		if (adc_hit[2] == 1
				&& (adcIntervalMillis[2] - adcIntervalPrevios[2] > ((40)+(a*1000)))) {
			print("J");
			adc_hit[2] = 0;
			adcIntervalPrevios[2] = adcIntervalMillis[2];
		}

		if (adc_hit[3] == 1
				&& (adcIntervalMillis[3] - adcIntervalPrevios[3] > ((40)+(a*1000)))) {
			print("K");
			adc_hit[3] = 0;
			adcIntervalPrevios[3] = adcIntervalMillis[3];
		}

		// Part3 LCD
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
		sprintf(x, "%2d", a);
		ILI9341_Draw_Text(x, 145, 11, BLACK, 2, WHITE);
		//		HAL_Delay(1000);

		if (TP_Touchpad_Pressed()) {
			uint16_t position_array[2];
			uint16_t x_pos = 0;
			uint16_t y_pos = 0;

			if (TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK) {
				x_pos = position_array[0];
				y_pos = position_array[1];
				if ((x_pos >= 177 && x_pos <= 210)
						&& (y_pos >= 8 && y_pos <= 98)) //check back
						{
					ispressed[6] = 1;
				} else if ((x_pos >= 180 && x_pos <= 210)
						&& (y_pos >= 228 && y_pos <= 316)) //check enter
						{
					ispressed[7] = 1;
				}

				else if ((x_pos >= 206 && x_pos <= 240)
						&& (y_pos >= 105 && y_pos <= 138)) //dpi-
						{
					ispressed[0] = 1;
				}

				else if ((x_pos >= 208 && x_pos <= 236)
						&& (y_pos >= 182 && y_pos <= 215)) //dpi+
						{
					ispressed[1] = 1;

				}

				else if ((x_pos >= 135 && x_pos <= 196)
						&& (y_pos >= 129 && y_pos <= 189)) //check up
						{
					ispressed[2] = 1;
				}

				else if ((x_pos >= 8 && x_pos <= 71)
						&& (y_pos >= 128 && y_pos <= 191)) //check down
						{
					ispressed[3] = 1;
				}

				else if ((x_pos >= 74 && x_pos <= 136)
						&& (y_pos >= 59 && y_pos <= 120)) //check left
						{
					ispressed[4] = 1;
				}

				else if ((x_pos >= 76 && x_pos <= 135)
						&& (y_pos >= 205 && y_pos <= 265)) //check right
						{
					ispressed[5] = 1;
				}
//					ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
//					char counter_buff[30];
//					sprintf(counter_buff, "POS X: %.3d  ", x_pos);
//					ILI9341_Draw_Text(counter_buff, 100, 220, BLACK, 1, WHITE);
//					sprintf(counter_buff, "POS Y: %.3d", y_pos);
//					ILI9341_Draw_Text(counter_buff, 160, 220, BLACK, 1, WHITE);
			}
		}

		//timer!!!
		//check back
		if (ispressed[6]) {
			intervalPreesed[6] += count;
			count = 0;
		}

		if (intervalPreesed[6] >= 500) {
			while (__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {
			}
//			HAL_UART_Transmit(&huart3, (uint8_t*) ex, strlen(ex), 1000);
			print("B");
			intervalPreesed[6] = 0;
			ispressed[6] = 0;
		}
		//check enter
		if (ispressed[7]) {
			intervalPreesed[7] += count;
			count = 0;
		}

		if (intervalPreesed[7] >= 500) {
			while (__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {
			}
//			HAL_UART_Transmit(&huart3, (uint8_t*) ex2, strlen(ex2), 1000);
			print("E");
			intervalPreesed[7] = 0;
			ispressed[7] = 0;
		}

		//dpi-
		if (ispressed[0]) {
			intervalPreesed[0] += count;
			count = 0;
		}
		if (intervalPreesed[0] >= 500) {
			if (a >= 1) {
				a = a - 1;
				sprintf(x, "%2d ", a);
			}
			if (a <= 0) {
				a = 0;
				sprintf(x, "%2d ", a);
			}
			intervalPreesed[0] = 0;
			ispressed[0] = 0;
		}
		//dpi+
		if (ispressed[1]) {
			intervalPreesed[1] += count;
			count = 0;
		}

		if (intervalPreesed[1] >= 500) {
			if (a < 10) {
				a = a + 1;
				sprintf(x, "%2d ", a);
			}
			if (a > 10) {
				a = 10;
				sprintf(x, "%2d ", a);
			}
			intervalPreesed[1] = 0;
			ispressed[1] = 0;
		}
		//check up
		if (ispressed[2]) {
			intervalPreesed[2] += count;
			count = 0;
		}

		if (intervalPreesed[2] >= 500) {
			while (__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {
			}
//			HAL_UART_Transmit(&huart3, (uint8_t*) ex3, strlen(ex3), 1000);
			print("U");
			intervalPreesed[2] = 0;
			ispressed[2] = 0;
		}

		////check down
		if (ispressed[3]) {
			intervalPreesed[3] += count;
			count = 0;
		}

		if (intervalPreesed[3] >= 500) {
			while (__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {
			}
//			HAL_UART_Transmit(&huart3, (uint8_t*) ex4, strlen(ex4), 1000);
			print("O");
			intervalPreesed[3] = 0;
			ispressed[3] = 0;
		}
		//check left
		if (ispressed[4]) {
			intervalPreesed[4] += count;
			count = 0;
		}

		if (intervalPreesed[4] >= 500) {
			while (__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {
			}
//			HAL_UART_Transmit(&huart3, (uint8_t*) ex5, strlen(ex5), 1000);
			print("L");
			intervalPreesed[4] = 0;
			ispressed[4] = 0;
		}
		//check right
		if (ispressed[5]) {
			intervalPreesed[5] += count;
			count = 0;
		}

		if (intervalPreesed[5] >= 500) {
			while (__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {
			}
//			HAL_UART_Transmit(&huart3, (uint8_t*) ex6, strlen(ex6), 1000);
			print("R");
			intervalPreesed[5] = 0;
			ispressed[5] = 0;
		}

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 216;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
