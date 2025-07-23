/* ͷ�ļ����� ----------------------------------------------------------------*/
    // TI MSPϵ��оƬ�ײ�������
#include "uart.h"              // ϵͳ������


/* ȫ�ֱ������� --------------------------------------------------------------*/

volatile unsigned char uart_data = 0;

volatile uint8_t new_data_flag = 0;  

uint8_t RxPacket[HiPnuc_PACKET_SIZE] = {0};

/* �Զ���ͨ��Э��֡���� -------------------------------------------------------*/


/* �������� ----------------------------------------------------------------*/

/**
  * @brief  UART�ж����ú���
  * @note   ��������UARTͨ�����ж�ʹ�ܺ�״̬���
  *         ������TI MSPM0ϵ��оƬ��UART����
  */
void UsartInit(void)
{
  // �������UARTͨ�����жϹ���״̬
  NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
  NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
//  NVIC_ClearPendingIRQ(UART_3_INST_INT_IRQN);

  // ʹ������UARTͨ���Ľ����ж�
  NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
  NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
//  NVIC_EnableIRQ(UART_3_INST_INT_IRQN);

  // �������UART�����жϱ�־����ֹ�����жϣ�
  DL_UART_clearInterruptStatus(UART_0_INST,DL_UART_INTERRUPT_RX);
  DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);
  DL_UART_clearInterruptStatus(UART_2_INST,DL_UART_INTERRUPT_RX);
//  DL_UART_clearInterruptStatus(UART_3_INST,DL_UART_INTERRUPT_RX);
	

}
//���ڷ��͵����ַ�
extern Car_t Car;
extern uint16_t BeginProtectFlag;
extern uint16_t BeginProtectCount;

void UART_0_INST_IRQHandler(void)
{
    //��������˴����ж�
    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
    {
        case DL_UART_IIDX_RX://����ǽ����ж�
					
          uart_data = DL_UART_Main_receiveData(UART_0_INST);
					CarStart(Car);
					uart0_send_char(uart_data);
					break;

        default://�����Ĵ����ж�
            break;
    }
}

void UART_1_INST_IRQHandler(void)
{

  if(DL_UART_getEnabledInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX) == DL_UART_INTERRUPT_RX)
  {
		DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);
		uint8_t ch = DL_UART_receiveData(UART_1_INST);
		pack_data(ch);
    
  }

}

void UART_2_INST_IRQHandler(void)
{
  // �����жϴ���
  if(DL_UART_getEnabledInterruptStatus(UART_2_INST,DL_UART_INTERRUPT_RX) == DL_UART_INTERRUPT_RX)
  {
    uint8_t ch = DL_UART_receiveData(UART_2_INST);
    DL_UART_clearInterruptStatus(UART_2_INST,DL_UART_INTERRUPT_RX);
  }
}


void uart1_restart(void)
{
	DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);
	DL_UART_reset(UART_1_INST);
	DL_UART_disable(UART_1_INST);
	DL_UART_disablePower(UART_1_INST);
	DL_UART_enablePower(UART_1_INST);
	SYSCFG_DL_UART_1_init();
}


void uart0_send_char(char ch)
{
    //������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
    while( DL_UART_isBusy(UART_0_INST) == true );
    //���͵����ַ�
    DL_UART_Main_transmitData(UART_0_INST, ch);
}

void uart_printf(int data)
{
	char temp[64];
	sprintf(temp, "%d\n", data);
	int a ,b = strlen((const char*)temp) ;
	for(a = 0;a<b;a++)
	uart0_send_char(temp[a]);
}
