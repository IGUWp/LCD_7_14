#include "xiic.h"
#include "usart.h"
uint8_t ack;

void IIC_GPIO_INIT(void)
{

	// RCC_APB2PeriphClockCmd(IIC_SCL_CLK | IIC_SDA_CLK, ENABLE);
	// GPIO_InitTypeDef GPIO_InitStruct;
	// GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	// GPIO_InitStruct.GPIO_Pin = IIC_SCL_GPIO_Pin;
	// GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_Init(IIC_SCL_PORT, &GPIO_InitStruct);

	// GPIO_InitStruct.GPIO_Pin = IIC_SDA_GPIO_Pin;
	// GPIO_Init(IIC_SDA_PORT, &GPIO_InitStruct);
}

void IIC_Delay(void)
{
	uint8_t i = 6; // i=10延时1.5us//这里可以优化速度 ，经测试最低到5还能写入
	while (i--)
		;
}

void IIC_Start(void)
{
	IIC_SCL_1;
	IIC_SDA_1; // 启始信号建立时间 0.6us 400KHz
	IIC_Delay();
	IIC_SDA_0;
	IIC_Delay(); // 启始信号保持时间0.6us
	IIC_SCL_0;
	IIC_Delay(); // 时钟低电平时间1.3us
}

void IIC_Stop(void)
{
	IIC_SDA_0;
	IIC_SCL_1;
	IIC_Delay(); // 结束信号建立时间0.6us
	IIC_SDA_1;
	IIC_Delay(); // 总线空闲时间时间1.3us
}

void IIC_Send_Byte(uint8_t byte)
{
	uint8_t i; // 先发送高位
	for (i = 0; i < 8; i++)
	{
		if (byte & 0x80)
		{
			IIC_SDA_1;
		}
		else
		{
			IIC_SDA_0;
		}
		IIC_Delay();
		IIC_SCL_1;
		IIC_Delay();
		IIC_SCL_0;
		IIC_Delay();
		byte <<= 1;
	}
	IIC_SDA_1;
	IIC_Delay();
	IIC_SCL_1;
	IIC_Delay();
	if (IIC_SDA_READ)
	{
		ack = 1;
	}
	else
	{
		ack = 0;
	}
	IIC_SCL_0;
	IIC_Delay();
}

uint8_t IIC_Receive_Byte(void)
{
	uint8_t receive = 0;
	uint8_t i; // 置数据线为输入方式
	for (i = 0; i < 8; i++)
	{
		receive <<= 1;
		IIC_SCL_1; // 置时钟线为高使数据线上数据有效
		IIC_Delay();
		if (IIC_SDA_READ)
		{
			receive++; // 读数据位,接收的数据位放入retc中
		}
		IIC_SCL_0;
		IIC_Delay();
	}
	return receive;
}

uint8_t IIC_Write_Byte(uint8_t device_addr, uint8_t register_addr, uint8_t data)
{
	IIC_Start();
	IIC_Send_Byte(device_addr + 0);
	if (ack == 1)
		return 0;
	IIC_Send_Byte(register_addr);
	if (ack == 1)
		return 0;
	IIC_Send_Byte(data);
	if (ack == 1)
		return 0;
	IIC_Stop();
	return 1;
}

void I2C_Ack(uint8_t a)
{
	if (a)
	{
		IIC_SDA_1; // 非应答
		IIC_Delay();
		IIC_SCL_1;
		IIC_Delay();
		IIC_SCL_0;
		IIC_Delay();
	}
	else
	{
		IIC_SDA_0; // 应答
		IIC_Delay();
		IIC_SCL_1;
		IIC_Delay();
		IIC_SCL_0;
		IIC_Delay();
		IIC_SDA_1;
	}
}

uint8_t IIC_Read_Byte(uint8_t device_addr, uint8_t register_addr)
{
	uint8_t read_data;
	IIC_Start();
	IIC_Send_Byte(device_addr + 0);
	if (ack == 1)
		return 0;
	IIC_Send_Byte(register_addr);
	if (ack == 1)
		return 0;
	IIC_Start();
	IIC_Send_Byte(device_addr + 1);
	if (ack == 1)
		return 0;
	read_data = IIC_Receive_Byte();
	I2C_Ack(1);
	IIC_Stop();
	return read_data;
}

uint8_t IIC_Write_Array(uint8_t device_addr, uint16_t register_addr, uint8_t *Data, uint16_t Num)
{
	uint16_t i;
	IIC_Start();
	IIC_Send_Byte(device_addr + 0);
	if (ack == 1)
		return 0;
	IIC_Send_Byte(register_addr);
	if (ack == 1)
		return 0;
	IIC_Start();
	IIC_Send_Byte(device_addr + 1);
	if (ack == 1)
		return 0;
	for (i = 0; i < Num; i++)
	{
		IIC_Send_Byte(*Data++);
		if (ack == 1)
			return 0;
	}
	IIC_Stop();
	return 1;
}

uint8_t IIC_Read_Array(uint8_t device_addr, uint16_t register_addr, uint8_t *Data, uint16_t Num)
{
	uint16_t i;
	IIC_Start();
	IIC_Send_Byte(device_addr + 0);
	if (ack == 1)
		return 0;
	IIC_Send_Byte(register_addr);
	if (ack == 1)
		return 0;
	IIC_Start();
	IIC_Send_Byte(device_addr + 1);
	if (ack == 1)
		return 0;
	for (i = 0; i < Num; i++)
	{
		*Data++ = IIC_Receive_Byte();
		if (i == Num - 1)
			I2C_Ack(1);
		else
			I2C_Ack(0);
	}
	IIC_Stop();
	return 1;
}
