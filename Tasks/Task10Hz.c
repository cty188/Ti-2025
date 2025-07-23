// Task10Hz.c
// 用于10Hz任务的实现

#include "Task10Hz.h"
#include "Oled.h"
void Task10Hz_Function(void)
{
    // 这里实现10Hz任务的具体内容
	OLED_ShowMap();
  OLED_ClearMap(0x00);
}
