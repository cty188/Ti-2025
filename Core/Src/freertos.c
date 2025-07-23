/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
 #include "BSP_GPIO.h"
#include "Task10Hz.h"
#include "Task100Hz.h"
#include "Task200Hz.h"
#include "Task1000Hz.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* 任务句柄声明 */
osThreadId_t task10HzHandle;
osThreadId_t task100HzHandle;
osThreadId_t task200HzHandle;
osThreadId_t task1000HzHandle;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;

/* 10Hz任务属性结构体 */
const osThreadAttr_t task10Hz_attributes = {
  .name = "task10Hz",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityBelowNormal,
};

/* 100Hz任务属性结构体 */
const osThreadAttr_t task100Hz_attributes = {
  .name = "task100Hz",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};

/* 200Hz任务属性结构体 */
const osThreadAttr_t task200Hz_attributes = {
  .name = "task200Hz",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityAboveNormal,
};

/* 1000Hz任务属性结构体 */
const osThreadAttr_t task1000Hz_attributes = {
  .name = "task1000Hz",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityHigh,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void Task10Hz_Function(void);
void Task100Hz_Function(void);
void Task200Hz_Function(void);
void Task1000Hz_Function(void);

/* 任务入口函数声明 */
void StartTask10Hz(void *argument);
void StartTask100Hz(void *argument);
void StartTask200Hz(void *argument);
void StartTask1000Hz(void *argument);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* 创建10Hz任务 (100ms周期) - 低优先级 */
  task10HzHandle = osThreadNew(StartTask10Hz, NULL, &task10Hz_attributes);

  /* 创建100Hz任务 (10ms周期) - 普通优先级 */
  task100HzHandle = osThreadNew(StartTask100Hz, NULL, &task100Hz_attributes);

  /* 创建200Hz任务 (5ms周期) - 较高优先级 */
  task200HzHandle = osThreadNew(StartTask200Hz, NULL, &task200Hz_attributes);

  /* 创建1000Hz任务 (1ms周期) - 高优先级，但不是最高 */
  task1000HzHandle = osThreadNew(StartTask1000Hz, NULL, &task1000Hz_attributes);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for (;;)
  {
    /* 默认任务现在只是一个监控任务，低优先级运行 */
    /* 可以在这里添加系统监控、错误处理等功能 */

    /* 每秒执行一次简单的系统检查 */
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

  /**
   * @brief  10Hz任务函数 (每100ms执行一次)
   * @param  argument: Not used
   * @retval None
   */
  void StartTask10Hz(void *argument)
  {
    uint32_t tick_count = osKernelGetTickCount();
    const uint32_t TimeIncrement = 100; // 100ms周期，实现10Hz频率
    
    /* Infinite loop */
    for(;;)
    {
      LED_R(0);
      LED_G(1);
      LED_B(1);
      Task10Hz_Function();
      tick_count += TimeIncrement;
      osDelayUntil(tick_count);
    }
  }

  /**
   * @brief  100Hz任务函数 (每10ms执行一次)
   * @param  argument: Not used
   * @retval None
   */
  void StartTask100Hz(void *argument)
  {
    uint32_t tick_count = osKernelGetTickCount();
    const uint32_t TimeIncrement = 10; // 10ms周期，实现100Hz频率
    
    /* Infinite loop */
    for(;;)
    {
      LED_R(1);
      LED_G(0);
      LED_B(1);
      Task100Hz_Function();
      tick_count += TimeIncrement;
      osDelayUntil(tick_count);
    }
  }

  /**
   * @brief  200Hz任务函数 (每5ms执行一次)
   * @param  argument: Not used
   * @retval None
   */
  void StartTask200Hz(void *argument)
  {
    uint32_t tick_count = osKernelGetTickCount();
    const uint32_t TimeIncrement = 5; // 5ms周期，实现200Hz频率
    
    /* Infinite loop */
    for(;;)
    {
      LED_R(1);
      LED_G(1);
      LED_B(0);
      Task200Hz_Function();
      tick_count += TimeIncrement;
      osDelayUntil(tick_count);
    }
  }

  /**
   * @brief  1000Hz任务函数 (每1ms执行一次)
   * @param  argument: Not used
   * @retval None
   */
  void StartTask1000Hz(void *argument)
  {
    uint32_t tick_count = osKernelGetTickCount();
    const uint32_t TimeIncrement = 1; // 1ms周期，实现1000Hz频率
    
    /* Infinite loop */
    for(;;)
    {
      LED_R(0);
      LED_G(0);
      LED_B(0);
      Task1000Hz_Function();
      tick_count += TimeIncrement;
      osDelayUntil(tick_count);
    }
  }

  /**
   * @brief  空闲任务钩子函数
   * @note   当系统进入空闲状态时被调用，此时关闭红色LED
   * @param  None
   * @retval None
   */
  void vApplicationIdleHook(void)
  {
    /* 系统空闲时，关闭所有LED */
    LED_R(1);
    LED_G(1);
    LED_B(1);
  }


/* USER CODE END Application */

