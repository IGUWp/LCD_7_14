/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

	typedef int32_t s32;
	typedef int16_t s16;
	typedef int8_t s8;

	typedef const int32_t sc32; /*!< Read Only */
	typedef const int16_t sc16; /*!< Read Only */
	typedef const int8_t sc8;	/*!< Read Only */

	typedef __IO int32_t vs32;
	typedef __IO int16_t vs16;
	typedef __IO int8_t vs8;

	typedef __I int32_t vsc32; /*!< Read Only */
	typedef __I int16_t vsc16; /*!< Read Only */
	typedef __I int8_t vsc8;   /*!< Read Only */

	typedef uint32_t uint32_t;
	typedef uint16_t uint16_t;
	typedef uint8_t uint8_t;

	typedef const uint32_t uc32; /*!< Read Only */
	typedef const uint16_t uc16; /*!< Read Only */
	typedef const uint8_t uc8;	 /*!< Read Only */

	typedef __IO uint32_t vuint32_t;
	typedef __IO uint16_t vuint16_t;
	typedef __IO uint8_t vuint8_t;

	typedef __I uint32_t vuc32; /*!< Read Only */
	typedef __I uint16_t vuc16; /*!< Read Only */
	typedef __I uint8_t vuc8;	/*!< Read Only */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOA
#define SPI_SCK_Pin GPIO_PIN_5
#define SPI_SCK_GPIO_Port GPIOA
#define SPI_MOSI_Pin GPIO_PIN_7
#define SPI_MOSI_GPIO_Port GPIOA
#define RES_Pin GPIO_PIN_2
#define RES_GPIO_Port GPIOD
#define DC_Pin GPIO_PIN_5
#define DC_GPIO_Port GPIOB
#define BLK_Pin GPIO_PIN_6
#define BLK_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
