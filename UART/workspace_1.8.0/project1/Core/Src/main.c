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
#include "usart.h"
#include "gpio.h"
#include "jsmn.h"

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
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t debug_rxBuf[BUFFER_SIZE];
uint8_t debug_rxData[BUFFER_SIZE];
uint8_t debug_aRxBuf;
uint8_t debug_rx_cnt = 0;
bool debug_rx_flag = false;
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
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, &debug_aRxBuf, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  printf("start\n");
  static const char *JSON_STRING =
      "{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
      "\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";
  jsmn_parser p;
  jsmntok_t t[128];
  jsmn_init(&p);
  int r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
  for (int i = 1; i < r; i++)
  {
      if (jsoneq(JSON_STRING, &t[i], "user") == 0)
      {
          /* We may use strndup() to fetch string value */
          printf("- User: %.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
          i++;
      }
      else if (jsoneq(JSON_STRING, &t[i], "admin") == 0)
      {
           /* We may additionally check if the value is either "true" or "false" */
          printf("- Admin: %.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
          i++;
      }
  }
//  char text[]="{\"mode\":\"nest\",\"move\":0.7,\"turn\":-0.123,\"rc_servo\":{\"0\":125,\"3\":75,\"1\":0,\"11\":75},\"adc\":\"\",\"rc_request\":\"\"}";
//  cJSON *json,*result;
//  json = cJSON_Parse(text);
//  printf("json type = %d\n",json->type);
//  result  = cJSON_GetObjectItem(json,"mode");
//  printf("result type = %d\n",result->type);
//  printf("%s\n",result->valuestring);
//  result = cJSON_GetObjectItem(json,"rc_servo");
//  result = cJSON_GetObjectItem(result,"0");
//  printf("%d\n",result->valueint);
//  cJSON_Delete(json);
//  cJSON_Delete(result);

  while(1);
  while (1)
  {
	if (debug_rx_flag == true) {
		debug_rx_flag = false;
		char *msg = (char*)debug_rxData;
//		printf("recv: %s", msg);
		if (strcmp(msg, "adc")) {
			int adc = 87;
			printf("%d\n", adc);
		} else if (strcmp(msg, "adc")) {
			int adc = 87;
			printf("%d\n", adc);
		}
	}
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	debug_rxBuf[debug_rx_cnt++] = debug_aRxBuf;
	if (debug_aRxBuf == '\n') {
		debug_rx_flag = true;
		memcpy(debug_rxData, debug_rxBuf, BUFFER_SIZE);
		memset(debug_rxBuf, 0, BUFFER_SIZE);
		debug_rx_cnt = 0;
	}
	HAL_UART_Receive_IT(huart, &debug_aRxBuf, 1);
//	HAL_UART_Receive_DMA(huart, &debug_aRxBuf, 1);
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

