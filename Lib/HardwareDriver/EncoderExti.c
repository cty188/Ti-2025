
#include "EncoderExti.h"

extern Car_t Car;

void GROUP1_IRQHandler(void)//Group1���жϷ�����
{
    //��ȡGroup1���жϼĴ���������жϱ�־λ
    switch( DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1) )
    {
        //����Ƿ���KEY��GPIOA�˿��жϣ�ע����INT_IIDX������PIN_18_IIDX
        case Encoder1_INT_IIDX:
            //����������±�Ϊ�ߵ�ƽ
            if( DL_GPIO_readPins(Encoder1_PORT, Encoder1_Encoder1A_PIN) > 0 )
            {
                //����LED����״̬��ת
                Car.Motors->EncoderLeftFront->EncoderCount ++ ;
            }
						else
								Car.Motors->EncoderLeftFront->EncoderCount -- ;
        break;
				
				case Encoder2_INT_IIDX:
            //����������±�Ϊ�ߵ�ƽ
            if( DL_GPIO_readPins(Encoder2_PORT, Encoder2_Encoder2A_PIN) > 0 )
            {
                //����LED����״̬��ת
                Car.Motors->EncoderRightFront->EncoderCount -- ;
            }
						else
								Car.Motors->EncoderRightFront->EncoderCount ++ ;
        break;
    }
}
