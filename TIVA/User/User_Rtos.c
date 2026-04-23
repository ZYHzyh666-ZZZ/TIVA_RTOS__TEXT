#include "User_Rtos.h"
#include "Drv_Uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

static TimerHandle_t xTimer5ms = NULL;
static SemaphoreHandle_t xSem5ms = NULL;
static TaskHandle_t xPeriphTaskHandle = NULL;

static void Timer5msCallback(TimerHandle_t xTimer)
{
    (void)xTimer;
    if (xSem5ms != NULL)
    {
        xSemaphoreGive(xSem5ms);
    }
}

static void PeripheralTask(void *pvParameters)
{
    (void)pvParameters;
    for(;;)
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
    if (xSem5ms == NULL) return;

    xTimer5ms = xTimerCreate("T5ms", pdMS_TO_TICKS(5), pdTRUE, NULL, Timer5msCallback);
    if (xTimer5ms != NULL)
    {
        xTimerStart(xTimer5ms, 0);
    }

    xTaskCreate(PeripheralTask, "Periph5ms", configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 1, &xPeriphTaskHandle);
}
