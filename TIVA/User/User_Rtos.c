#include "User_Rtos.h"
#include "Drv_Uart.h"

/* 句柄定义（在头文件中声明为 extern） */
TimerHandle_t xTimer5ms = NULL;
SemaphoreHandle_t xSem5ms = NULL;
TaskHandle_t xPeriphTaskHandle = NULL;

static void Timer5msCallback(TimerHandle_t xTimer)
{
    (void)xTimer;
    if (xSem5ms != NULL)
    {
        /* 软件定时器回调在定时器守护任务中执行，可使用 xSemaphoreGive */
        xSemaphoreGive(xSem5ms);
    }
}

static void PeripheralTask(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        if (xSemaphoreTake(xSem5ms, portMAX_DELAY) == pdTRUE)
        {
            DrvUartDataCheck();
        }
    }
}

void RtosUser_Init(void)
{
    xSem5ms = xSemaphoreCreateBinary();
    if (xSem5ms == NULL)
        return;

    xTimer5ms = xTimerCreate(USER_5MS_TIMER_NAME, pdMS_TO_TICKS(USER_5MS_TIMER_PERIOD_MS), pdTRUE, NULL, Timer5msCallback);
    if (xTimer5ms != NULL)
    {
        xTimerStart(xTimer5ms, 0);
    }

    xTaskCreate(PeripheralTask, USER_PERIPH_TASK_NAME, USER_PERIPH_TASK_STACK, NULL, USER_PERIPH_TASK_PRIORITY, &xPeriphTaskHandle);
}
