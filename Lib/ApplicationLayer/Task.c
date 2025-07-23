
#include "Task.h"

void TaskInit(Task_t** Task)
{
	static Task_t task;
	*Task = &task;
	task.TaskFlag = 0;
	task.TaskFlag = 0;
	task.TaskState = 0;
	task.LastTaskState = 0 ;
	task.StTrPreFlag = 0;
	task.AverageSpeed = 0;
	task.Deltayaw = 0 ;
	task.Datumyaw = 0 ;
}
void Task1(Car_t car)
{

}

void Task2(Car_t car)
{

}

void Task3(Car_t car)
{

}

uint16_t ProtectFlag = 0;        //����Ѳ��״̬����ֹ������߱���
uint16_t ProtectCount = 0;
uint16_t BeginProtectFlag = 0;		//����ʱ���ٶȹ��쳵����ͷ���Ҷȴ�������׼�����з�����������
uint16_t BeginProtectCount = 0;

void Task4StateUpdate(Car_t car)
{
	if(car.GraySensor->GraySensorNoData<=0x20&&car.Tasks->TaskState == 0&&BeginProtectFlag == 0)
		{car.Tasks->TaskState = 1;	ProtectFlag = 1;	ProtectCount = 100;	EncoderLengthClear(car.Motors);BuzzerBee(car.Buzzer);}
		
		
	else if(car.GraySensor->GraySensorNoData>=0x20&&car.Tasks->TaskState == 1&&ProtectFlag == 0)
		{car.Tasks->TaskState = 2;																				EncoderLengthClear(car.Motors);BuzzerBee(car.Buzzer);}
		
		
	else if(car.GraySensor->GraySensorNoData<=0x20&&car.Tasks->TaskState == 2)
		{car.Tasks->TaskState = 3;	ProtectFlag = 1;	ProtectCount = 100;	EncoderLengthClear(car.Motors);BuzzerBee(car.Buzzer);}
		
		
	else if(car.GraySensor->GraySensorNoData>=0x20&&car.Tasks->TaskState == 3&&ProtectFlag == 0)
		{car.Tasks->TaskState = 0;																				EncoderLengthClear(car.Motors);BuzzerBee(car.Buzzer);}
}

void Task4(Car_t car)
{
		Task4StateUpdate(car);
	
//	uart0_send_char(car.Tasks->TaskState);

		if(BeginProtectFlag) {
			BeginProtectCount--;
			car.Tasks->TaskState = 0;									//ǿ��ά��״̬0
			car.GraySensor->GraySensorNoData = 0xFF;	//ǿ�ƺ��ԻҶȴ���������
			if(BeginProtectCount == 0)
				BeginProtectFlag = 0 ;
		}
		
	if(car.Tasks->TaskState == 0){
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X <= 2*StaightWayLength)
		{
			car.Tasks->Deltayaw = car.HiPnuc->yaw  +Task34TurnAngle;				
			car.Tasks->AverageSpeed = 130;
		}
		
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X >= 2*StaightWayLength)
		{
			car.Tasks->Deltayaw = car.HiPnuc->yaw ;
			car.Tasks->AverageSpeed = 60;
		}
	}
	
	else if(car.Tasks->TaskState == 1&&car.GraySensor->GraySensorNoData==0x00){								//������ߺ������ڵ㣬����ʧ��˦�ɣ�ֻ�и����Ŷ�ʱ�����߼�
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X <= 2*BendWayLength)
		{
			car.Tasks->Deltayaw = GraySensorToTurnAngle(car.GraySensor); 	
			car.Tasks->AverageSpeed = 130;
		}
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X >= 2*BendWayLength)
		{
			car.Tasks->Deltayaw = GraySensorToTurnAngle(car.GraySensor); 	
			car.Tasks->AverageSpeed = 60;
		}
	}
	
	else if(car.Tasks->TaskState == 2){
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X <= 2*StaightWayLength)
		{
			car.Tasks->Deltayaw = car.HiPnuc->yaw  +180-Task34TurnAngle;		
			car.Tasks->AverageSpeed = 130;
		}
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X >= 2*StaightWayLength)
		{
			car.Tasks->Deltayaw = car.HiPnuc->yaw  +180;
			car.Tasks->AverageSpeed = 60;
		}
	}
	
	else if(car.Tasks->TaskState == 3&&car.GraySensor->GraySensorNoData==0x00){
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X <= 2*BendWayLength)
		{
			car.Tasks->Deltayaw = GraySensorToTurnAngle(car.GraySensor); 	
			car.Tasks->AverageSpeed = 130;
		}
		if(car.Motors->EncoderLeftFront->X + car.Motors->EncoderRightFront->X >= 2*BendWayLength)
		{
			car.Tasks->Deltayaw = GraySensorToTurnAngle(car.GraySensor); 	
			car.Tasks->AverageSpeed = 60;
		}
	}
	
	else
		car.Tasks->Deltayaw = 0 ;
	
	
	if(car.Tasks->Deltayaw >180)  car.Tasks->Deltayaw  -= 360;//����޷�
	if(car.Tasks->Deltayaw <-180) car.Tasks->Deltayaw  += 360;
	
	
	if(ProtectFlag)		//���䱣��
	{
		ProtectCount--;
		if(ProtectCount == 0)
			ProtectFlag = 0;
		if(car.GraySensor->BinaryData == 0xFF&&car.Tasks->TaskState == 1)//�����䱣��״̬�����޻Ҷȴ���������ʱ��ǿ��ת��Ѱ�Һ���
			car.Tasks->Deltayaw = -50;//uart0_send_char(0x05);
		if(car.GraySensor->BinaryData == 0xFF&&car.Tasks->TaskState == 3)
			car.Tasks->Deltayaw = 50;//uart0_send_char(0x06);
	}	
	
	
	car.Tasks->LastTaskState = car.Tasks->TaskState;
}

void CarStart(Car_t car)
{
	car.Tasks->CarStartFlag = !car.Tasks->CarStartFlag;
	BeginProtectFlag = 1;
	BeginProtectCount = 100;
	BuzzerBee(car.Buzzer);
}