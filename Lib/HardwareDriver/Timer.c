// ͷ�ļ�����
   // TI MSPM0�����������ļ�             // ϵͳ������ͺ���
#include "timer.h"             // ʱ����غ����Ͷ���


//systime timer_t1a,timer_t5a,timer_t6a,timer_t7a;
extern void duty_200hz(void);  // 200Hz����������
extern void duty_1000hz(void);       // 1000Hz����������
extern void duty_100hz(void);        // 100Hz����������
extern void duty_10hz(void);         // 10Hz����������

void TimerInit(void)
{
    // ����PWM��ʱ����TimerA��TimerG���ͣ�
    // ����TIMER1�жϲ�������ʱ��
    NVIC_EnableIRQ(TIMERA1_10hz_INST_INT_IRQN);  // ʹ��TIMER1��NVIC�ж�
    DL_TimerG_startCounter(TIMERA1_10hz_INST);    // ����TIMER1��Ӧ��TimerG

    // ����TIMER2�жϲ�������ʱ��
    NVIC_EnableIRQ(TIMERG7_200hz_INST_INT_IRQN);  // ʹ��TIMER2��NVIC�ж�
    DL_TimerG_startCounter(TIMERG7_200hz_INST);    // ����TIMER2��Ӧ��TimerG

    // ����TIMER_G8�жϲ�������ʱ��
    NVIC_EnableIRQ(TIMERG8_100hz_INST_INT_IRQN); // ʹ��TIMER_G8��NVIC�ж�
    DL_TimerG_startCounter(TIMERG8_100hz_INST);   // ����TIMER_G8��Ӧ��TimerG

    // ����TIMER_G12�жϲ�������ʱ��
    NVIC_EnableIRQ(TIMERG6_1000hz_INST_INT_IRQN); // ʹ��TIMER_G6��NVIC�ж�
    DL_TimerG_startCounter(TIMERG6_1000hz_INST);   // ����TIMER_G6��Ӧ��TimerG
}

void timer_pwm_config(void)
{
  //pwm
  DL_TimerA_startCounter(PWM_Motors_INST);//A0
}



void TIMERG6_1000hz_INST_IRQHandler(void)
{
  switch (DL_TimerG_getPendingInterrupt(TIMERG6_1000hz_INST))
  {
    case DL_TIMERG_IIDX_ZERO:
    {
			duty_1000hz();
    }
    break;
    default:
      break;
  }
}


void TIMERG7_200hz_INST_IRQHandler(void)
{
  switch (DL_TimerG_getPendingInterrupt(TIMERG7_200hz_INST))
  {
    case DL_TIMERG_IIDX_ZERO:
    {
      duty_200hz();
      static uint32_t _cnt = 0; _cnt++;
//      if(_cnt % 50 == 0)	
//			DL_GPIO_togglePins(LED1_PORT, LED1_PIN_14_PIN);
    }
    break;

    default:
      break;
  }
}



void TIMERG8_100hz_INST_IRQHandler(void)//����վ���ݷ����жϺ���
{
  switch (DL_TimerG_getPendingInterrupt(TIMERG8_100hz_INST))
  {
    case DL_TIMERG_IIDX_ZERO:
    {
   		duty_100hz();
    }
    break;

    default:
      break;
  }
}


void TIMERA1_10hz_INST_IRQHandler(void)//����վ���ݷ����жϺ���
{
  switch (DL_TimerG_getPendingInterrupt(TIMERA1_10hz_INST))
  {
    case DL_TIMERG_IIDX_ZERO:
    {
			duty_10hz();
    }
    break;
    default:
      break;
  }
}






