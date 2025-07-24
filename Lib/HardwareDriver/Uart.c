/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "uart.h"      // STM32 HAL���UARTͷ�ļ�
#include "usart.h"      // STM32 HAL���UARTͷ�ļ�
#include "stdio.h"
#include "string.h"


/* ȫ�ֱ������� --------------------------------------------------------------*/
extern UART_HandleTypeDef huart1; // ʹ��USART1����usart.c�ж���

volatile uint8_t uart_rx_data = 0;      // ���ֽڽ��ջ���
volatile uint8_t new_data_flag = 0;     // �����ݱ�־
uint8_t RxPacket[100] = {0}; // ���ݰ����棬�������СΪ100

/* �Զ���ͨ��Э��֡���� -------------------------------------------------------*/


/* �������� ----------------------------------------------------------------*/

/**
  * @brief  UART��ʼ��������STM32 HAL�ⷽʽ��
  * @note   ����main.c��CubeMX�е���MX_USART1_UART_Init
  */
void UsartInit(void)
{
    // HAL���ʼ������MX_USART1_UART_Init�����
    // ����ֻ�迪�������ж�
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_data, 1);
}
//���ڷ��͵����ַ�
extern uint16_t BeginProtectFlag;
extern uint16_t BeginProtectCount;

/**
  * @brief  UART������ɻص���STM32 HAL�ⷽʽ��
  * @note   ��stm32h7xx_it.c��USART1_IRQHandler�л��Զ�����
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        new_data_flag = 1;
        // ������յ�������
        // ���ڴ˵���ԭ����CarStart�Ⱥ���
        uart_send_char(uart_rx_data); // ���Խ��յ�������
        
        // ����������һ�ν���
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_data, 1);
    }
}

/**
  * @brief  ���͵����ַ�
  */
void uart_send_char(char ch)
{
    // ����1����ֱ�ӷ��ͣ�HAL���ڲ��ᴦ��״̬��
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
    
    // ����2�������Ҫ״̬��飬�ô���ʱ�ļ��
    /*
    uint32_t timeout = 1000;  // 1�볬ʱ
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
  * @brief  �����ַ���
  */
void uart_send_string(const char *str)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 100);
}

/**
  * @brief  ����ת�ַ�������ʵ�֣�����sprintf���⣩
  */
void int_to_string(int num, char *str)
{
    int i = 0;
    int is_negative = 0;
    
    // ������
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    // ����0���������
    if (num == 0) {
        str[i++] = '0';
    }
    
    // ת������Ϊ�ַ���������
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    // ��Ӹ���
    if (is_negative) {
        str[i++] = '-';
    }
    
    // �ַ���������
    str[i] = '\0';
    
    // ��ת�ַ���
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
  * @brief  UART printf���ܣ������������ݣ�
  */
void uart_printf(int data)
{
	char temp[64];
	sprintf(temp, "%d\n", data);
	HAL_UART_Transmit(&huart1, (const unsigned char*)temp, strlen((const char*)temp), 1000);
}

/**
  * @brief  UART����������STM32 HAL�ⷽʽ��
  */
void uart_restart(void)
{
    HAL_UART_DeInit(&huart1);
    MX_USART1_UART_Init();
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_rx_data, 1);
}

/**
  * @brief  ���ݰ�����������Ҫ���ݾ���Э��ʵ�֣�
  */
void pack_data(uint8_t ch)
{
    // ������Ҫ���ݾ�������ݰ�Э����ʵ��
    // ԭTI�����е�pack_data��������
    static uint16_t index = 0;
    if (index < sizeof(RxPacket))
    {
        RxPacket[index++] = ch;
    }
    else
    {
        index = 0; // ��������
    }
}
