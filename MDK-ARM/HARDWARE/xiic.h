#ifndef __XIIC_H
#define __XIIC_H
#include "stm32f1xx_hal.h" // Device header
#define hardware 0

#if hardware
#define IIC_SCL_CLK RCC_APB2Periph_GPIOB
#define IIC_SCL_PORT GPIOB
#define IIC_SCL_GPIO_Pin GPIO_PIN_9
#define IIC_SDA_CLK RCC_APB2Periph_GPIOB
#define IIC_SDA_PORT GPIOB
#define IIC_SDA_GPIO_Pin GPIO_PIN_8

#define IIC_CLK_Hz 200000
#define IIC_CLK RCC_APB1Periph_I2C1
#define IIC_PORT I2C1
void IIC_GPIO_INIT(void);
uint8_t IIC_Read_Byte(uint8_t device_addr, uint8_t register_addr);
void IIC_Write_Byte(uint8_t device_addr, uint8_t register_addr, uint8_t data);

#else
#define IIC_SCL_CLK RCC_APB2Periph_GPIOB
#define IIC_SCL_PORT GPIOB
#define IIC_SCL_GPIO_Pin GPIO_PIN_9
#define IIC_SDA_CLK RCC_APB2Periph_GPIOB
#define IIC_SDA_PORT GPIOB
#define IIC_SDA_GPIO_Pin GPIO_PIN_8

#define IIC_SCL_1 HAL_GPIO_WritePin(IIC_SCL_PORT, IIC_SCL_GPIO_Pin, GPIO_PIN_SET)
#define IIC_SCL_0 HAL_GPIO_WritePin(IIC_SCL_PORT, IIC_SCL_GPIO_Pin, GPIO_PIN_RESET)
#define IIC_SDA_1 HAL_GPIO_WritePin(IIC_SDA_PORT, IIC_SDA_GPIO_Pin, GPIO_PIN_SET)
#define IIC_SDA_0 HAL_GPIO_WritePin(IIC_SDA_PORT, IIC_SDA_GPIO_Pin, GPIO_PIN_RESET)
#define IIC_SDA_READ HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_GPIO_Pin)

void IIC_GPIO_INIT(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t byte);
void I2C_Ack(uint8_t a);
uint8_t IIC_Receive_Byte(void);

uint8_t IIC_Read_Byte(uint8_t device_addr, uint8_t register_addr);
uint8_t IIC_Write_Byte(uint8_t device_addr, uint8_t register_addr, uint8_t data);

uint8_t IIC_Read_Array(uint8_t device_addr, uint16_t register_addr, uint8_t *Data, uint16_t Num);
uint8_t IIC_Write_Array(uint8_t device_addr, uint16_t register_addr, uint8_t *Data, uint16_t Num);

extern uint8_t ack;
#endif

#endif
