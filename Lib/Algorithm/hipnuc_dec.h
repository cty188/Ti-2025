/* 
 * Copyright (c) 2006-2024, HiPNUC
 * SPDX-License-Identifier: Apache-2.0
 *
 * HiPNUC Decoder Library
 * 
 * ���ܸ�����
 * 1. �ṩHiPNUCЭ����������ݽṹ����
 * 2. ����IMU��0x91/0x92������ϵ�����0x81�����ݰ��ṹ
 * 3. ����Э�����ӿں���
 * 
 * ������˵����
 * - ֧��C/C++��ϱ�̻���
 * - ���QT��ܽ����ڴ�����Ż�
 */

#ifndef __HIPNUC_DEC_H__
#define __HIPNUC_DEC_H__

#ifdef __cplusplus
extern "C" {  // ȷ��C++������ʹ��C�������ӹ淶
#endif

/* ������ */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "headfile.h"  // ��Ŀ�Զ���ͷ�ļ�

/* QT����ڴ�������ã�1�ֽڶ��룩 */
#ifdef QT_CORE_LIB
#pragma pack(push)
#pragma pack(1)
#endif

/* Э�鳣������ */
#define HIPNUC_MAX_RAW_SIZE     (256)   /* ԭʼ���ݻ����������������Э��ͷ�� */

/**
 * @struct hi91_t
 * @brief 0x91�������ݰ���������IMU���ݣ�
 * 
 * ����˵����
 * - ���д�����������ת��Ϊ����������
 * - ʱ�����λΪ����
 * - ��̬�ǵ�λΪ��
 * - ��Ԫ�����ñ�׼[w,x,y,z]˳��
 */
typedef struct __attribute__((__packed__)) {
    uint8_t  tag;            /* ����ʶ����0x91��ʾ��Ч���� */
    uint16_t sttaus;         /* �����ֶΣ�����statusƴд���� */
    int8_t   temp;           /* �¶�ֵ���棩 */
    float    air_pressure;   /* ��ѹֵ��Pa�� */
    uint32_t system_time;    /* ϵͳʱ�����ms�� */
    float    acc[3];         /* ������ٶȣ�m/s2�� */
    float    gyr[3];         /* ���������ǣ�deg/s�� */
    float    mag[3];         /* ��������ƣ���T�� */
    float    roll;           /* ����ǣ�-180~180�ȣ� */
    float    pitch;          /* �����ǣ�-90~90�ȣ� */
    float    yaw;            /* ����ǣ�0~360�ȣ� */
    float    quat[4];        /* ��Ԫ������һ���� */
} hi91_t;

/**
 * @struct hi92_t
 * @brief 0x92�������ݰ�������IMUԭʼ���ݣ�
 * 
 * ����˵����
 * - ԭʼ�����谴ϵ��ת����
 *   ���ٶȣ�0.0048828 m/s2/LSB����Ӧ��2000LSB/g��
 *   �����ǣ�0.001 rad/s/LSB �� 0.0573 deg/s/LSB
 *   �����ƣ�0.030517 ��T/LSB�����̡�4912��T��
 */
typedef struct __attribute__((__packed__)) {
    uint8_t  tag;            /* ����ʶ����0x92��ʾ��Ч���� */
    uint16_t status;         /* �豸״̬λͼ����Э���ĵ��� */
    int8_t   temperature;    /* �¶ȣ��棩 */
    uint16_t rev;            /* �����ֶ� */
    int16_t  air_pressure;   /* ԭʼ��ѹֵ����ת���� */
    int16_t  reserved;       /* �����ֶ� */
    int16_t  gyr_b[3];       /* ԭʼ������X/Y/Z��LSB�� */
    int16_t  acc_b[3];       /* ԭʼ���ٶ�X/Y/Z��LSB�� */
    int16_t  mag_b[3];       /* ԭʼ������X/Y/Z��LSB�� */
    int32_t  roll;           /* ԭʼ����ǣ�0.001��/LSB�� */
    int32_t  pitch;          /* ԭʼ�����ǣ�0.001��/LSB�� */
    int32_t  yaw;            /* ԭʼ����ǣ�0.001��/LSB�� */
    int16_t  quat[4];        /* ԭʼ��Ԫ����Q14��ʽ����/16384.0�� */
} hi92_t;

/**
 * @struct hi81_t
 * @brief 0x81�������ݰ�����ϵ������ݣ�
 * 
 * ����˵����
 * - ��λ���ݲ������ʹ洢����ת����
 *   ����/γ�ȣ�1e-7��/LSB������12345678 �� 1.2345678�ȣ�
 *   �̣߳�����ת�ף�1e-3��
 * - UTCʱ���ֶ�ΪBCD���루����0x21 �� 2021�꣩
 */
typedef struct __attribute__((__packed__)) {
    uint8_t  tag;            /* ����ʶ����0x81��ʾ��Ч���� */
    uint16_t status;         /* ϵͳ״̬�֣���Э���ĵ��� */
    uint8_t  ins_status;     /* INS״̬��0:��Ч 1:��Ч�� */
    uint16_t gpst_wn;        /* GPS������0-8191�� */
    uint32_t gpst_tow;       /* GPS�����루0-604799�� */
    uint16_t reserved;       /* �����ֶ� */
    int16_t  gyr_b[3];       /* ԭʼ������X/Y/Z��ͬhi92_t�� */
    int16_t  acc_b[3];       /* ԭʼ���ٶ�X/Y/Z��ͬhi92_t�� */
    int16_t  mag_b[3];       /* ԭʼ������X/Y/Z��ͬhi92_t�� */
    int16_t  air_pressure;   /* ԭʼ��ѹֵ��ͬhi92_t�� */
    int16_t  reserved1;      /* �����ֶ� */
    int8_t   temperature;    /* �¶ȣ��棩 */
    uint8_t  utc_year;       /* UTC�꣨BCD�룬��0x23��ʾ2023�� */
    uint8_t  utc_month;      /* UTC�£�BCD�룬1-12�� */
    uint8_t  utc_day;        /* UTC�գ�BCD�룬1-31�� */
    uint8_t  utc_hour;       /* UTCʱ��BCD�룬0-23�� */
    uint8_t  utc_min;        /* UTC�֣�BCD�룬0-59�� */
    uint16_t utc_msec;       /* UTC���루0-999�� */
    int16_t  roll;           /* ����ǣ�0.01��/LSB�� */
    int16_t  pitch;          /* �����ǣ�0.01��/LSB�� */
    uint16_t yaw;            /* ����ǣ�0.01��/LSB�� */
    int16_t  quat[4];        /* ��Ԫ����Q30��ʽ����/32768.0�� */
    int32_t  ins_lon;        /* INS���ȣ�1e-7�ȣ� */
    int32_t  ins_lat;        /* INSγ�ȣ�1e-7�ȣ� */
    int32_t  ins_msl;        /* INS���Σ����ף� */
    uint8_t  pdop;           /* λ�þ������ӣ�0.1/LSB�� */
    uint8_t  hdop;           /* ˮƽ�������ӣ�0.1/LSB�� */
    uint8_t  solq_pos;       /* ��λ������0:��Ч 1:���� 5:�̶��⣩ */
    uint8_t  nv_pos;         /* ��λ��������0-99�� */
    uint8_t  solq_heading;   /* ����������0:��Ч 4:�ز���λ�� */
    uint8_t  nv_heading;     /* ������������0-99�� */
    uint8_t  diff_age;       /* ������ڣ��룩 */
    int16_t  undulation;     /* ���ˮ׼����������ף� */
    uint8_t  ant_status;     /* ����״̬�������� */
    int16_t  vel_enu[3];     /* ENU�ٶȣ�cm/s�� */
    int16_t  acc_enu[3];     /* ENU���ٶȣ�ͬacc_b�� */
    int32_t  gnss_lon;       /* GNSS���ȣ�ͬins_lon�� */
    int32_t  gnss_lat;       /* GNSSγ�ȣ�ͬins_lat�� */
    int32_t  gnss_msl;       /* GNSS���Σ�ͬins_msl�� */
    uint8_t  reserved2[2];   /* �����ֶ� */
} hi81_t;

/**
 * @struct hipnuc_raw_t
 * @brief HiPNUCЭ�������״̬�ṹ��
 * 
 * �������̣�
 * 1. ͨ��hipnuc_input()���ֽ����buf
 * 2. ����֡���պ��Զ�������hi91/hi92/hi81�ṹ
 * 3. ʹ��hipnuc_dump_packet()����ɶ��ַ���
 */
typedef struct {
    int nbyte;          /* ��ǰ�������ѽ����ֽ��� */
    int len;            /* ��Ч�غɳ��ȣ���Э��ͷ��ȡ�� */
    uint8_t buf[HIPNUC_MAX_RAW_SIZE]; /* ԭʼ���ݻ����� */
    hi91_t hi91;        /* �������0x91���ݰ� */
    hi92_t hi92;        /* �������0x92���ݰ� */
    hi81_t hi81;        /* �������0x81���ݰ� */
} hipnuc_raw_t;

/* �ָ�Ĭ���ڴ���� */
#ifdef QT_CORE_LIB
#pragma pack(pop)
#endif

/******************** �������� ********************/

/**
 * @brief HiPNUCЭ����������봦��
 * @param raw ������״̬�ṹ��ָ��
 * @param data ����ĵ����ֽ�
 * @return ����״̬��
 *        1 = �ɹ���������֡
 *        0 = ��Ҫ��������
 *       -1 = У�����������쳣
 */
int hipnuc_input(hipnuc_raw_t *raw, uint8_t data);

/**
 * @brief �������������ת��ΪJSON��ʽ�ַ���
 * @param raw �����ѽ������ݵĽṹ��ָ��
 * @param buf ����������������512�ֽڣ�
 * @param buf_size ����������
 * @return �ɹ�д����ַ�����������ֹ����
 * 
 * ע�⣺
 * - ����tag�ֶ��Զ�ѡ�����ݰ�����
 * - ���ɱ�׼JSON��ʽ���������ͻ���
 */
int hipnuc_dump_packet(hipnuc_raw_t *raw, char *buf, size_t buf_size);

#ifdef __cplusplus
}
#endif

#endif /* __HIPNUC_DEC_H__ */
