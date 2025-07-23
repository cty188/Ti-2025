
#include "HiPnuc.h"

extern uint8_t new_data_flag;  
extern uint8_t RxPacket[HiPnuc_PACKET_SIZE];

static uint8_t data_state_flag = 0 ;
static uint8_t 	count = 0;
static uint16_t length = 0;
static uint16_t uartcrc = 0;


#define I2(p) (*((int16_t *)(p)))                 /* �ӻ�������ȡ�з���16λ���� */
static uint16_t U2(uint8_t *p) {                  /* �ӻ�������ȡ�޷���16λ���� */
    uint16_t u;
    memcpy(&u, p, 2);
    return u;
}
static uint16_t U4(uint8_t *p) {                  /* �ӻ�������ȡ�޷���16λ���� */
    uint32_t u;
    memcpy(&u, p, 4);
    return u;
}
static float R4(uint8_t *p) {                     /* �ӻ�������ȡ32λ������ */
    float r;
    memcpy(&r, p, 4);
    return r;
}


void HiPnucInit(HiPnuc_t** HiPnuc){
	static HiPnuc_t hipnuc;
	hipnuc.tag 					=0;
	hipnuc.sttaus 			=0;
	hipnuc.temp 				= 0;
	hipnuc.air_pressure =0;
	hipnuc.system_time 	= 0;
	
	hipnuc.acc[0] 	=	0;
	hipnuc.acc[1] 	=	0;
	hipnuc.acc[2] 	=	0;
	hipnuc.gyr[0] 	=	0;
	hipnuc.gyr[1] 	=	0;
	hipnuc.gyr[2] 	=	0;
	hipnuc.mag[0] 	=	0;
	hipnuc.mag[1] 	=	0;
	hipnuc.mag[2] 	=	0;
	hipnuc.roll   	=	0;
	hipnuc.pitch   	=	0;
	hipnuc.yaw   	 	=	0;
	hipnuc.quat[0] 	=	0;
	hipnuc.quat[1] 	=	0;
	hipnuc.quat[2] 	=	0;
	hipnuc.quat[3] 	=	0;
	*HiPnuc = &hipnuc;
}
void pack_data(uint8_t ch){
		if(data_state_flag==Frame_header)
		{
				if(ch == 0x5A)	count = 1;
				else if(count == 1&&ch == 0xA5){count = 0;data_state_flag = 1;}
				else count = 0;
			}
		else{
				RxPacket[count++] = ch;
				if(count>=HiPnuc_PACKET_SIZE){count = 0;data_state_flag=0;new_data_flag = 1;}
			}
		}

void HipnucDataUpdate(HiPnuc_t* hipnuc)
{
	static uint16_t Errorflag = 0;
    if (new_data_flag)
    {
				Errorflag = 0;
        new_data_flag = 0;
				if(pack_check(RxPacket))
				{
					pack_decode(RxPacket,hipnuc);
				}
    }
		
		else
		{ 
			Errorflag++;
			if(Errorflag == 20)
			{
				uart1_restart();
				uart0_send_char(Errorflag);
				Errorflag = 0;
				
			}
		}
}

static void pack_decode(uint8_t* data,HiPnuc_t* hipnuc){
//	hipnuc->tag 					= data[4];
//	hipnuc->sttaus 				= U2(data+5);
	hipnuc->temp 					= (int8_t) data[7];
//	hipnuc->air_pressure 	= R4(data+8);
//	hipnuc->system_time 	= U4(data+12);
	
	hipnuc->acc[0] 	= R4(data + 16);
	hipnuc->acc[1] 	= R4(data + 20);
	hipnuc->acc[2] 	= R4(data + 24);
	hipnuc->gyr[0] 	= R4(data + 28);
	hipnuc->gyr[1] 	= R4(data + 32);
	hipnuc->gyr[2] 	= R4(data + 36);
//	hipnuc->mag[0] 	= R4(data + 40);
//	hipnuc->mag[1] 	= R4(data + 44);
//	hipnuc->mag[2] 	= R4(data + 48);
	hipnuc->roll   	= R4(data + 52);
	hipnuc->pitch   = R4(data + 56);
	hipnuc->yaw   	= R4(data + 60);
//	hipnuc->quat[0] = R4(data + 64);
//	hipnuc->quat[1] = R4(data + 68);
//	hipnuc->quat[2] = R4(data + 72);
//	hipnuc->quat[3] = R4(data + 76);
}

static int pack_check(uint8_t* data) {
    uint16_t crc = 0x043B;

    /* CRCУ����㣺ͷ���������2�ֽ�CRC�� + ��Ч�غ� */
    hipnuc_crc16(&crc, data, (CH_HDR_SIZE-4));
    hipnuc_crc16(&crc, data + CH_HDR_SIZE-2, HiPnuc_PACKET_SIZE - CH_HDR_SIZE +2);
    
    /* У��ʧ�ܴ��� */
    if (crc != U2(data + (CH_HDR_SIZE-4))) {
        return 0;
    }

    /* У��ͨ������������ */
    return 1;
}
/**
 * @brief HiPNUCЭ��CRC16У�����
 * @param initial ��ʼֵ���贫��0xFFFF��
 * @param buf ��У������ָ��
 * @param len ���ݳ���
 * 
 * �㷨���ԣ�
 * - ����ʽ��0x1021��CCITT��׼��
 * - ��ʼֵ��0xFFFF
 * - ���뷴ת����
 * - �����ת����
 * - ������0x0000
 * ���͵��÷�ʽ��
 * uint16_t crc = 0xFFFF;
 * hipnuc_crc16(&crc, data, len);
 * crc ^= 0xFFFF; // ����Э������Ƿ���Ҫȡ��
 */
static void hipnuc_crc16(uint16_t *initial, const uint8_t *buf, uint32_t len)
{
    uint32_t crc = *initial;  // ���س�ʼֵ
    for (uint32_t j = 0; j < len; ++j)
    {
        crc ^= (uint16_t)buf[j] << 8;  // �ֽ�������8λ���
        /* ��λ���� */
        for (uint32_t i = 0; i < 8; ++i)
        {
            uint32_t temp = crc << 1;  // ����һλ
            if (crc & 0x8000)          // ������λ
                temp ^= 0x1021;        // ������ʽ
            crc = temp;                // ����CRC
        }
    } 
    *initial = (uint16_t)crc;  // ��д���
}
