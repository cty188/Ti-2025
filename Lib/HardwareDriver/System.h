#ifndef __system_H
#define __system_H

#include "datatype.h"

void SystickInit(void);

uint32_t micros(void);
uint32_t millis(void);
void Delay_Ms(uint32_t x);
void delay_ms(uint32_t x);
void delay_us(uint32_t x);
void Delay_Us(uint32_t x);

float get_systime_ms(void);
uint32_t get_systick_ms(void);

#endif