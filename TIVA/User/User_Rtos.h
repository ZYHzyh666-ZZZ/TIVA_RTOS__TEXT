#ifndef __USER_RTOS_H
#define __USER_RTOS_H

#include "SysConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/*
 * User RTOS configuration
 * -----------------------
 * 把优先级、任务名与句柄集中放在此处，便于查看与修改。
 * 使用重定义 (#define) 方便快速调整优先级、堆栈和名称。
 *
 * 可修改项：
 *  - USER_PERIPH_TASK_NAME        : 外设周期任务名称（字符串）
 *  - USER_PERIPH_TASK_PRIORITY    : 外设周期任务优先级（使用宏重定义便于修改）
 *  - USER_PERIPH_TASK_STACK       : 外设周期任务堆栈大小（单词数）
 *  - USER_5MS_TIMER_NAME          : 5ms 软件定时器名称（字符串）
 *  - USER_5MS_TIMER_PERIOD_MS     : 定时器周期（毫秒）
 */

#ifndef USER_PERIPH_TASK_NAME
#define USER_PERIPH_TASK_NAME    "Periph5ms"
#endif

#ifndef USER_PERIPH_TASK_PRIORITY
#define USER_PERIPH_TASK_PRIORITY    (tskIDLE_PRIORITY + 1)
#endif

#ifndef USER_PERIPH_TASK_STACK
#define USER_PERIPH_TASK_STACK       (configMINIMAL_STACK_SIZE + 200)
#endif

#ifndef USER_5MS_TIMER_NAME
#define USER_5MS_TIMER_NAME      "T5ms"
#endif

#ifndef USER_5MS_TIMER_PERIOD_MS
#define USER_5MS_TIMER_PERIOD_MS     (5)
#endif

/* 全局句柄（在此声明，供其他模块查看/使用） */
extern TimerHandle_t xTimer5ms;
extern SemaphoreHandle_t xSem5ms;
extern TaskHandle_t xPeriphTaskHandle;

/* API */
void RtosUser_Init(void);

#endif /* __USER_RTOS_H */
