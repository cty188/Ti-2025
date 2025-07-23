// Task1000Hz.c
// 用于1000Hz任务的实现

#include "Task1000Hz.h"
#include "Oled.h"

void Task1000Hz_Function(void)
{
    // 这里实现1000Hz任务的具体内容
	static int count = 0;
	count++;
	OLED_ShowFloat(35,50,count,4,SIZE12,SpanSingle);		//OLED_ShowString(0,50,"Rspeed:",SIZE12,SpanSingle);

}
