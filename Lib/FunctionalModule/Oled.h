#ifndef _OLED_H_
#define _OLED_H_

#include "headfile.h"
#include "stdlib.h"
#include "IIC.h"

//�ֺ�
#define SIZE16	16
#define SIZE12	12

#define Add0				1	//����λ��0
#define NoAdd0			0	//����λ����0

//ͼ���ַ���ʾģʽ
#define Normal						0x00	//������ʾ
#define Transparent				0x01	//��ʾ͸������
#define Reverse						0x02	//��ɫ��ת��ʾ
#define L2R								0x04	//���ҷ�ת
#define U2D								0x08	//���·�ת
#define Span							0x10	//һ�������е����ַ���ת
#define SpanSingle				0x20	//һ��������Ϊ������ת

#define Max_Column	128     //�������
#define Max_Row			64      //�������
#define	Brightness	0xFF    //�Ҷȣ����ȣ�
#define X_WIDTH 		128     //����
#define Y_WIDTH 		64	    //����
#define Y_PAGE			8				//ҳ��

//OLEDָ��
#define OLED_CMD  MYIIC_CMD		//д����0
#define OLED_DATA MYIIC_DATA	//д����1

//��
typedef struct{
	float x;
	float y;
}	POINT;

//IIC��������
void OLED_Write_IIC_Command(u8 IIC_Command);
void OLED_Write_IIC_Data(u8 IIC_Data);
void OLED_WR_Byte(u8 dat,u8 cmd);           //д������
//OLED��������
void OLED_SetSpanAng(float ang);												//������ת�Ƕ�
void OLED_SetSpan(float x, float y);										//��������ת����
void OLED_SetSpanZero(float x, float y);								//���þ���ת����
POINT OLED_SetSpanCenter(float xBef, float yBef, float xSet, float ySet);	//������ת���ģ�(ԭ��ͼ���꣬���õ���ת��������)�������ú����ͼ����(��ͼ���Ͻ�����)
void OLED_WriteMap(u8 bit, int xpose, int ypose);				//��Map��д������
void OLED_ShowMap(void);																//Map�����Դ�
void OLED_ClearMap(u8 data);														//���Map����,ȫ���滻Ϊdata
u8 	 reversedata(u8 data);															//����������ת
void OLED_Set_Pos(u8 x, u8 y);													//��������
void OLED_Display_On(void);                             //����OLED��ʾ  
void OLED_Display_Off(void);	   												//�ر�OLED��ʾ  
void OLED_Init(void);                                   //��ʼ��SSD1306
void OLED_Clear(void);                                  //��������
void OLED_Clear_page(u8 i);                             //��ҳ����,�����i(1<=i<=8)ҳ
//��ʾ����
//void OLED_DrawPoint(u8 x,u8 y,u8 t);
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_Reverse(int x, int y, u8 width, u8 height);													//��ѡ���������
void OLED_ShowChar(int x, int y, u8 ch, u8 Size, u8 mode);      							//��ʾ�ַ�(x����,y����,ch�ַ�,size�����С,mode��ʾģʽ)
void OLED_ShowNum(int x,int y,u32 num, u8 length, u8 Size, u8 if0, u8 mode);	//��ʾ����(x����,y����,num����,size�����С,mode��ʾģʽ)
void OLED_ShowInt(int x, int y, int num, u8 size, u8 mode);										//��ʾ������(x����,y����,num����,size�����С,mode��ʾģʽ)
void OLED_ShowBinNum(int x, int y, int num, u8 size, u8 mode);
void OLED_ShowFloat(int x, int y, float num, u8 len, u8 size, u8 mode);				//��ʾ������(x����,y����,num����,len����С��λ��,size�����С,mode��ʾģʽ)
void OLED_ShowString(int x,int y, u8 *ch,u8 Size, u8 mode);										//��ʾ�ַ��Ŵ�(x����,y����,ch�ַ�ָ��,size�����С,mode��ʾģʽ)
void OLED_ShowChinese(int x, int y, u8 num, u8 mode);                 				//��ʾ����(x����,y����,num���ֱ��,mode��ʾģʽ)
void OLED_ShowChineseStr(int x, int y, u8* nums, u8 len, u8 mode);						//��ʾһ�仰(x����,y����,nums���ֱ������,mode��ʾģʽ)
void OLED_ShowBMP(int x0, int y0, int x1, int y1, const u8* BMP, u8 mode);		//��ʾλͼ(x0y0���Ͻ�����,x1y1���½�����,BMPͼƬ����,mode��ʾģʽ)
void OLED_ShowPNG(int x0, int y0, int x1, int y1, const u8* Mask, const u8* PNG, u8 mode);	//��ʾ��ͼ(x0y0���Ͻ�����,x1y1���½�����,MaskͼƬ����,PNGͼƬ����,mode��ʾģʽ)
//��ͼ����
void OLED_line(int xpose1, int ypose1, int xpose2, int ypose2, u8 width);	//����ֱ��(�������,�յ�����,�߿�)
void OLED_DrawLine(int x, int y, float ang, u8 length, u8 width);			//����ֱ��(�������,�Ƕ�,����,�߿�)
void OLED_circle(int xpose, int ypose, u8 r);													//����Բ��(Բ������,�뾶)
void OLED_circleunfilled(int xpose, int ypose, u8 r, u8 width);				//����Բ�β����(Բ������,�뾶,�߿�)
void OLED_rectangle(int xpose, int ypose, u8 width, u8 height);				//���ƾ���(�������,���)
void OLED_rectangleunfilled(int xpose, int ypose, u8 width, u8 height, u8 linewidth);		//���ƾ��β����(�������,���,�߿�)
//void OLED_rectangle(u8 xpose1, u8 ypose1, u8 xpose2, u8 ypose2,u8 xpose3, u8 ypose3);	//���ƾ���
//void OLED_triangle(u8 xpose1, u8 ypose1, u8 xpose2, u8 ypose2,u8 xpose3, u8 ypose3);	//����������
void OledDataUpdate(void);

#endif
