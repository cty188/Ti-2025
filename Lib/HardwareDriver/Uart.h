#ifndef __UART_H
#define __UART_H

#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

// 函数声明
void UsartInit(void);
void uart_send_char(char ch);
void uart_send_string(const char *str);
void uart_printf(int data);
void uart_restart(void);
void pack_data(uint8_t ch);

// 全局变量声明
extern volatile uint8_t uart_rx_data;
extern volatile uint8_t new_data_flag;
extern uint8_t RxPacket[100];

// 为了兼容原有代码，保留旧函数名的宏定义
#define uart0_send_char uart_send_char
#define uart1_restart uart_restart

#endif



