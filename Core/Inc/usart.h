/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.h
 * @brief   This file contains all the function prototypes for
 *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */
#define USART_DEBUG USART1
#define UART_RX_MAX_LENGTH 4080
#define UART_TX_MAX_LENGTH 4080
#define UART_RX_TIMESPAN 10// ms

  extern uint8_t rx_temp;
  extern uint8_t tx_temp;

  extern uint16_t uart_rx_cnt;
  extern uint16_t uart_tx_cnt;
       
  extern uint8_t uart_rx_Buff[UART_RX_MAX_LENGTH];
  extern uint8_t uart_tx_Buff[UART_TX_MAX_LENGTH];
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
  void UsartPrintf(USART_TypeDef *USARTx, char *fmt, ...);
  void Uart_task(void);
  void Uart_Process(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

