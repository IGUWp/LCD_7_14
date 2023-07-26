/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "lcd_init.h"
#include "pic.h"
#include "max30102.h"
#include "algorithm.h"
#include "xiic.h"
#include "blood.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint32_t i = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 定时器更新中断回调函数
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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */
  BloodData HP;
  extern uint8_t task_ms;
  extern uint16_t watch_dog;
  extern uint16_t task_s;
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
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  uint16_t i;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  // UsartPrintf(USART_DEBUG, " ??\r\n");
  MAX30102_GPIO();
  Max30102_reset();
  MAX30102_Config();

  for (i = 0; i < 128; i++)
  {
    while (MAX30102_INTPin_Read() == 0)
    {
      // ??FIFO
      max30102_read_fifo();
    }
  }

  LCD_Init();
  LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
  LCD_ShowChinese(60, 0, "心率血氧测量仪", RED, WHITE, 16, 0);
  LCD_ShowChinese(0, 40, "心率:", RED, WHITE, 16, 0);
  LCD_ShowChinese(80, 40, "血氧:", RED, WHITE, 16, 0);
  LCD_ShowChinese(0, 80, "经度:", RED, WHITE, 16, 0);
  LCD_ShowChinese(0, 120, "纬度:", RED, WHITE, 16, 0);
  LCD_ShowChinese(0, 150, "时间:", RED, WHITE, 24, 0);
  LCD_ShowChinese(0, 180, "日期:", RED, WHITE, 24, 0);
  HAL_UART_Receive_IT(&huart1, &rx_temp, 1);
  HAL_TIM_Base_Start_IT(&htim6);
  uint16_t cnt = 0;
  while (1)
  {
    if (task_ms == 1)
    {
      task_ms = 0;
      cnt++;
      cnt %= 1001; // 是用来定时到1s防止cnt无限增长
      Uart_task();
      if (watch_dog > 1)
      {
        watch_dog--;
      }
      else
      {
        watch_dog = 2000; // 看门狗观察到2s就重置串口，以及接收缓冲区
        MX_USART1_UART_Init();
        HAL_UART_Receive_IT(&huart1, &rx_temp, 1);
        uart_rx_cnt = 0;
      }
    }
    if (cnt % 100 == 0)
    {
      blood_Loop(&HP);
      LCD_ShowIntNum(48, 40, HP.heart, 3, RED, WHITE, 24);
      LCD_ShowFloatNum1(128, 40, HP.SpO2, 4, RED, WHITE, 24);
    }

    Uart_Process();

    // blood_Loop(&HP);
    //  LCD_ShowIntNum(48, 40, i++, 3, RED, WHITE, 24);
    // LCD_ShowFloatNum1(128, 40, 2, 4, RED, WHITE, 24);
    // LCD_ShowIntNum(48, 40, HP.heart, 3, RED, WHITE, 24);
    // LCD_ShowFloatNum1(128, 40, HP.SpO2, 4, RED, WHITE, 24);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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

#ifdef USE_FULL_ASSERT
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
