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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef unsigned char bool;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#define BUFFER_SIZE 256
#define NUMBER_OF_SLOT 32

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
bool SBUS2_get_Slot(uint8_t, uint8_t*, uint8_t*);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t debug_rxBuf[BUFFER_SIZE];
uint8_t debug_rxData[BUFFER_SIZE];
uint8_t debug_aRxBuf;
uint8_t debug_rx_cnt = 0;
bool debug_rx_flag = false;

uint8_t sbus_rxBuf[BUFFER_SIZE];
uint8_t sbus_rxData[BUFFER_SIZE];
uint8_t sbus_aRxBuf;
uint8_t sbus_rx_cnt = 0;
bool sbus_rx_flag = false;

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, &sbus_aRxBuf, 1);
  HAL_UART_Receive_IT(&huart2, &debug_aRxBuf, 1);

  uint8_t sbus_data[25];
  uint16_t data[16];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
//	if (debug_rx_flag == true) {
//		debug_rx_flag = false;
//		int var = atoi((char*)debug_rxData);
//		printf("[send] %d\n", var);
//		for(uint8_t i = 0; i < 16; i++) data[i] = var;
//		sbus_data[0] = 0xf0;
//		sbus_data[1] =  data[0] & 0x00ff;
//		sbus_data[2] = ((data[0] >> 8) & 0x07) | (data[1] << 3);
//		sbus_data[3] = ((data[1] >> 5) & 0x3f) | (data[2] << 6);
//		sbus_data[4] = ((data[2] >> 2) & 0xff);
//		sbus_data[5] = ((data[2] >> 10) & 0x01) | (data[3] << 1);
//		sbus_data[6] = ((data[3] >> 7) & 0x0f) | (data[4] << 4);
//		sbus_data[7] = ((data[4] >> 4) & 0x7f) | (data[5] << 7);
//		sbus_data[8] = ((data[5] >> 1) & 0xff);
//		sbus_data[9] = ((data[5] >> 9) & 0x03);
////		sbus_data[1] = data[0] >> 3;
////		sbus_data[2] = (data[0] << 5) | (data[1] >> 6);
////		sbus_data[3] = (data[1] << 2) | (data[2] >> 9);
////		sbus_data[4] = data[2] >> 1;
////		sbus_data[5] = (data[2] << 7) | (data[3] >> 4);
////		sbus_data[6] = (data[3] << 4) | (data[4] >> 7);
////		sbus_data[7] = (data[4] << 1) | (data[5] >> 10);
////		sbus_data[8] = data[5] >> 2;
////		sbus_data[9] = (data[5] << 6) | (data[6] >> 5);
//		sbus_data[10] = (data[6] << 3) | (data[7] >> 8);
//		sbus_data[11] = data[7];
//		sbus_data[12] = data[8] >> 3;
//		sbus_data[13] = (data[8] << 5) | (data[9] >> 6);
//		sbus_data[14] = (data[9] << 2) | (data[10] >> 9);
//		sbus_data[15] = data[10] >> 1;
//		sbus_data[16] = (data[10] << 7) | (data[11] >> 4);
//		sbus_data[17] = (data[11] << 4) | (data[12] >> 7);
//		sbus_data[18] = (data[12] << 1) | (data[13] >> 10);
//		sbus_data[19] = data[13] >> 2;
//		sbus_data[20] = (data[13] << 6) | (data[14] >> 5);
//		sbus_data[21] = (data[14] << 3) | (data[15] >> 8);
//		sbus_data[22] = data[15];
//		sbus_data[23] = 0x00;
//		sbus_data[24] = 0x00;
//		HAL_UART_Transmit(&huart1, (uint8_t*)sbus_data, 25, 0xffff);
//	}

	if (debug_rx_flag == true) {
		debug_rx_flag = false;
//		printf("[send] %s", (char*)debug_rxData);
//		char* str[BUFFER_SIZE];
//		sprintf((char*)str, "[from debug] %s", (char*)debug_rxData);
//		HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen((char*)str), 0xffff);

		printf("%s", debug_rxData);
//		HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen((char*)str), 0xffff);
	}
//	if (sbus_rx_flag == true) {
//		sbus_rx_flag = false;
////		printf("%s", (char*)sbus_rxData);
//		printf("sbus to debug\n");
//		char *str = "sbus to sbus\n";
//		HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen((char*)str), 0xffff);
//	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 100000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_2;
  huart1.Init.Parity = UART_PARITY_EVEN;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_DATAINVERT_INIT;
  huart1.AdvancedInit.DataInvert = UART_ADVFEATURE_DATAINV_ENABLE;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PB3_LED_GPIO_Port, PB3_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PB3_LED_Pin */
  GPIO_InitStruct.Pin = PB3_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PB3_LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart1) {
		sbus_rxBuf[sbus_rx_cnt++] = sbus_aRxBuf;
		if (sbus_aRxBuf == '\n') {
			sbus_rx_flag = true;
			memcpy(sbus_rxData, sbus_rxBuf, BUFFER_SIZE);
			memset(sbus_rxBuf, 0, BUFFER_SIZE);
			sbus_rx_cnt = 0;
		}
		HAL_UART_Receive_IT(huart, &sbus_aRxBuf, 1);
	} else if (huart == &huart2) {
		debug_rxBuf[debug_rx_cnt++] = debug_aRxBuf;
		if (debug_aRxBuf == '\n') {
			debug_rx_flag = true;
			memcpy(debug_rxData, debug_rxBuf, BUFFER_SIZE);
			memset(debug_rxBuf, 0, BUFFER_SIZE);
			debug_rx_cnt = 0;
		}
		HAL_UART_Receive_IT(huart, &debug_aRxBuf, 1);
	}
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

