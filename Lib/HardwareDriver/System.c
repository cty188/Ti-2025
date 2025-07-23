
#include "system.h"


volatile uint32_t sysTickUptime = 0;
//void SysTick_Handler(void)
//{
//  sysTickUptime++;
//}




//���� us
uint32_t micros(void)
{
  uint32_t systick_period = CPUCLK_FREQ / 1000U;
  return sysTickUptime * 1000 + (1000 * (systick_period - SysTick->VAL)) / systick_period;
}

//���� ms
uint32_t millis(void) {
	return micros() / 1000UL;
}

//��ʱus
void delayMicroseconds(uint32_t us) {
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;

    // ������Ҫ��ʱ���� = �ӳ�΢���� * ÿ΢���ʱ����
    ticks = us * (80000000 / 1000000);

    // ��ȡ��ǰ��SysTickֵ
    told = SysTick->VAL;

    while (1)
    {
        // �ظ�ˢ�»�ȡ��ǰ��SysTickֵ
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;

            told = tnow;

            // ����ﵽ����Ҫ��ʱ���������˳�ѭ��
            if (tcnt >= ticks)
                break;
        }
    }
}

void delay(uint32_t ms) {
  delayMicroseconds(ms * 1000UL);
}


void delay_ms(uint32_t x)
{
  delay(x);
}

void delay_us(uint32_t x)
{
  delayMicroseconds(x);
}

void Delay_Ms(uint32_t time)  //��ʱ����  
{   
	delay_ms(time);
}  

void Delay_Us(uint32_t time)  //��ʱ����  
{   
	delay_us(time);
}  


float get_systime_ms(void)
{
  return millis();//��λms
}

uint32_t get_systick_ms(void)
{
  return (uint32_t)(sysTickUptime);//��λms
}




