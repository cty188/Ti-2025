/* 头文件包含 ----------------------------------------------------------------*/
#include "uart.h"      // STM32 HAL库的UART头文件
#include "usart.h"      // STM32 HAL库的UART头文件
#include "stdio.h"
#include "string.h"


/* 全局变量定义 --------------------------------------------------------------*/
extern UART_HandleTypeDef huart1; // 使用USART1，在usart.c中定义

volatile uint8_t uart_rx_data = 0;      // 单字节接收缓存
volatile uint8_t new_data_flag = 0;     // 新数据标志
uint8_t RxPacket[100] = {0}; // 数据包缓存，假设包大小为100

/* 自定义通信协议帧配置 -------------------------------------------------------*/


/* 函数定义 ----------------------------------------------------------------*/

/**
  * @brief  UART初始化函数（STM32 HAL库方式）
  * @note   需在main.c或CubeMX中调用MX_USART1_UART_Init
  */
void UsartInit(void)
{
    // HAL库初始化已在MX_USART1_UART_Init中完成
    // 这里只需开启接收中断
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_data, 1);
}
//串口发送单个字符
extern uint16_t BeginProtectFlag;
extern uint16_t BeginProtectCount;

/**
  * @brief  UART接收完成回调（STM32 HAL库方式）
  * @note   在stm32h7xx_it.c的USART1_IRQHandler中会自动调用
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        new_data_flag = 1;
        // 处理接收到的数据
        // 可在此调用原来的CarStart等函数
        uart_send_char(uart_rx_data); // 回显接收到的数据
        
        // 继续开启下一次接收
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_data, 1);
    }
}

/**
  * @brief  发送单个字符
  */
void uart_send_char(char ch)
{
    // 方法1：简单直接发送（HAL库内部会处理状态）
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
    
    // 方法2：如果需要状态检查，用带超时的检查
    /*
    uint32_t timeout = 1000;  // 1秒超时
    while((HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY) && timeout > 0)
    {
        HAL_Delay(1);
        timeout--;
    }
    if(timeout > 0)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
    }
    */
}

/**
  * @brief  发送字符串
  */
void uart_send_string(const char *str)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 100);
}

/**
  * @brief  整数转字符串（自实现，避免sprintf问题）
  */
void int_to_string(int num, char *str)
{
    int i = 0;
    int is_negative = 0;
    
    // 处理负数
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    // 处理0的特殊情况
    if (num == 0) {
        str[i++] = '0';
    }
    
    // 转换数字为字符串（逆序）
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    // 添加负号
    if (is_negative) {
        str[i++] = '-';
    }
    
    // 字符串结束符
    str[i] = '\0';
    
    // 反转字符串
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

/**
  * @brief  UART printf功能（发送整型数据）
  */
void uart_printf(int data)
{
	char temp[64];
	sprintf(temp, "%d\n", data);
	HAL_UART_Transmit(&huart1, (const unsigned char*)temp, strlen((const char*)temp), 1000);
}

/**
  * @brief  UART重启函数（STM32 HAL库方式）
  */
void uart_restart(void)
{
    HAL_UART_DeInit(&huart1);
    MX_USART1_UART_Init();
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_data, 1);
}

/**
  * @brief  数据包处理函数（需要根据具体协议实现）
  */
void pack_data(uint8_t ch)
{
    // 这里需要根据具体的数据包协议来实现
    // 原TI代码中的pack_data函数功能
    static uint16_t index = 0;
    if (index < sizeof(RxPacket))
    {
        RxPacket[index++] = ch;
    }
    else
    {
        index = 0; // 重置索引
    }
}
