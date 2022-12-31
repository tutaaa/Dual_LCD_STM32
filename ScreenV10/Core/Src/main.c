/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
#include <string.h>
#include "st7735.h"
#include "fonts.h"
#include "testimg.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim11;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint16_t LP1 = 4000;  //Life points for player 1
uint8_t T1 = 1;		//Player turns for player 1
char C_P1[] = "MP";
uint8_t Time_init = 110;
uint8_t Time = 1;
char C_ins[] = "Battle START !!!!";
uint64_t _micro = 0;
GPIO_PinState SwitchState[2];
char C_LP1[4] = "0000";
char C_T1[] = " ";
char C_Time[3] = " ";
uint8_t size = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */
void GUI_P1();
void logic_demo();
void test_2LCD();
uint64_t micros();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void init() {
	ST7735_Init();
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_FillScreen1(ST7735_BLACK);
	const char ready[] = "Ready!\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)ready, sizeof(ready)-1, HAL_MAX_DELAY);

}

void loop() {
	// Check border
	ST7735_FillScreen(ST7735_BLACK);

	for(int x = 0; x < ST7735_WIDTH; x++) {
		ST7735_DrawPixel(x, 0, ST7735_RED);
		ST7735_DrawPixel(x, ST7735_HEIGHT-1, ST7735_RED);
	}

	for(int y = 0; y < ST7735_HEIGHT; y++) {
		ST7735_DrawPixel(0, y, ST7735_RED);
		ST7735_DrawPixel(ST7735_WIDTH-1, y, ST7735_RED);
	}

	HAL_Delay(3000);

	// Check fonts
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
	ST7735_WriteString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
	ST7735_WriteString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
	HAL_Delay(2000);

	// Check colors
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_BLUE);
	ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_RED);
	ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_GREEN);
	ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_CYAN);
	ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_MAGENTA);
	ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_YELLOW);
	ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_WHITE);
	ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
	HAL_Delay(500);

#ifdef ST7735_IS_128X128
	// Display test image 128x128
	ST7735_DrawImage(0, 0, ST7735_WIDTH, ST7735_HEIGHT, (uint16_t*)test_img_128x128);

	/*
    // Display test image 128x128 pixel by pixel
    for(int x = 0; x < ST7735_WIDTH; x++) {
        for(int y = 0; y < ST7735_HEIGHT; y++) {
            uint16_t color565 = test_img_128x128[y][x];
            // fix endiness
            color565 = ((color565 & 0xFF00) >> 8) | ((color565 & 0xFF) << 8);
            ST7735_DrawPixel(x, y, color565);
        }
    }
	 */
	HAL_Delay(15000);
#endif // ST7735_IS_128X128

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

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
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
	init();
	HAL_TIM_Base_Start_IT(&htim11);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//loop();
		logic_demo();
		GUI_P1();
		//test_2LCD();

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 99;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 65535;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|GPIO_PIN_7|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin PA7 PA9 */
  GPIO_InitStruct.Pin = LD2_Pin|GPIO_PIN_7|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void GUI_P1(){  	// Show information in each players :
	// Player Number , Life points , Turns , Phase , Timer , instructions

	ST7735_WriteString(5, 5, "Player 1: ", Font_7x10, ST7735_WHITE, ST7735_BLACK);

	ST7735_WriteString(5, 20, "Life points: ", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	sprintf(C_LP1, "%d", LP1);
	ST7735_WriteString( 90, 20, C_LP1, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	ST7735_WriteString(5, 35, "Turns: ", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	sprintf(C_T1, "%d", T1);
	ST7735_WriteString( 50, 35, C_T1, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	ST7735_WriteString(60, 35, "|Phase: ", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	ST7735_WriteString( 110, 35, C_P1, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	ST7735_WriteString(0, 50, "Remaining time: ", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	sprintf(C_Time, "%d", Time);
	for (int i = 0 ; i < 3 ; i++){
		if(C_Time[i] == 0){
			C_Time[i] = 'S';
			C_Time[i+1] = '.';
		}
	}
	ST7735_WriteString( 105, 50, C_Time, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	ST7735_WriteString(0, 60, "__________________", Font_7x10, ST7735_WHITE, ST7735_BLACK);

	ST7735_WriteString(5, 90, C_ins, Font_7x10, ST7735_WHITE, ST7735_BLACK);


}
void test_2LCD(){
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_FillScreen1(ST7735_BLACK);
//	ST7735_WriteString(50, 50, "4", Font_16x26, ST7735_BLUE, ST7735_BLACK);
//	ST7735_FillScreen1(ST7735_BLACK);
//	HAL_Delay(1000);
//
//	ST7735_FillScreen(ST7735_BLACK);
//
//	ST7735_WriteString1(50, 50, "3 ", Font_16x26, ST7735_WHITE, ST7735_BLACK);
//	HAL_Delay(1000);
//
//	ST7735_FillScreen1(ST7735_BLACK);
//
//	ST7735_WriteString(50, 50, "2 ", Font_16x26, ST7735_GREEN, ST7735_BLACK);
//	HAL_Delay(1000);
//	ST7735_FillScreen(ST7735_BLACK);
//	ST7735_WriteString1(50, 50, "1 ", Font_16x26, ST7735_RED, ST7735_BLACK);
//	HAL_Delay(1000);
//	ST7735_FillScreen1(ST7735_BLACK);
//	ST7735_FillScreen(ST7735_BLACK);
//	ST7735_WriteString(10, 20, "Happy", Font_16x26, ST7735_MAGENTA, ST7735_BLACK);
//	HAL_Delay(500);
//	ST7735_WriteString1(10, 20, "new", Font_16x26, ST7735_YELLOW, ST7735_BLACK);
//	HAL_Delay(500);
//	ST7735_WriteString(10, 50, "year", Font_16x26, ST7735_CYAN, ST7735_BLACK);
//	HAL_Delay(500);
//	ST7735_WriteString1(10, 50, "2", Font_16x26, ST7735_GREEN, ST7735_BLACK);
//	HAL_Delay(250);
//	ST7735_WriteString1(30, 50, "0", Font_16x26, ST7735_GREEN, ST7735_BLACK);
//	HAL_Delay(250);
//	ST7735_WriteString1(50, 50, "2", Font_16x26, ST7735_GREEN, ST7735_BLACK);
//	HAL_Delay(250);
//	ST7735_WriteString1(70, 50, "3", Font_16x26, ST7735_GREEN, ST7735_BLACK);
//	HAL_Delay(500);
//	ST7735_WriteString1(75, 90, "Dev By", Font_7x10, ST7735_WHITE, ST7735_BLACK);
//	ST7735_WriteString1(75, 105, "TinnZx", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	HAL_Delay(3000);
}

void logic_demo(){


	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	Time = Time_init - _micro/1000000;
	if (Time == 0){
		HAL_TIM_Base_Stop_IT(&htim11);
		Time = 0;
		//C_ins[] = "Game Over";

	}
	SwitchState[0] = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
	if (SwitchState[1] == GPIO_PIN_SET
			&& SwitchState[0] == GPIO_PIN_RESET)
	{
		T1++;
		LP1 = LP1 - 100;
	}
	SwitchState[1] = SwitchState[0];

}




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim11) {
		_micro += 65535;
	}
}

uint64_t micros() {
	return _micro + htim11.Instance->CNT;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
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
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
