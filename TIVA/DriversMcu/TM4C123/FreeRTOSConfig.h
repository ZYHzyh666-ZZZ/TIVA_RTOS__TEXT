
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

// For application specific definitions
#include "tasks_common.h"

#include <stdbool.h>
#include <stdlib.h>

// TivaWare system control definitions
#include "driverlib/sysctl.h"

/**
 * @brief Hardware Specific Definitions
 * @note Definitions which FreeRTOS uses sync to the hardware
 */
#define configCPU_CLOCK_HZ (SysCtlClockGet())
#define configTICK_RATE_HZ ((portTickType)100)
#define configUSE_16_BIT_TICKS 0

/* Be ENORMOUSLY careful if you want to modify these two values and make sure
   you read http://www.freertos.org/a00110.html#kernel_priority first! */
#define configKERNEL_INTERRUPT_PRIORITY                                                                                \
    (7 << 5) /* Priority 7, or 0xE0 as only the top three bits are implemented.                                        \
                This is the lowest priority. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY                                                                           \
    (5 << 5) /* Priority 5, or 0xA0 as only the top three bits are implemented. */

/* THE TM4C123 ONLY HAS 3 BITS DEFINED FOR INTERRUPT PRIORITY. THE ARM ARCHITECTURE DEFINES
   THAT THESE SHOULD START FROM THE MSB, THUS, THE BITS ARE LOCATED AT POSITION 7, 6 AND 5.
   THIS IS WHY THESE PRIORITY BITS ARE LEFT SHIFTED BY 5. */

/**
 * @brief OS Specific Definitions
 * @note Defnitions which dis/enable FreeRTOS API/utilities
 */
#define INCLUDE_vTaskPrioritySet 1
#define INCLUDE_uxTaskPriorityGet 1
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskCleanUpResources 1
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 1
#define INCLUDE_vTaskDelay 1

#define configUSE_PREEMPTION 1
#define configIDLE_SHOULD_YIELD 1
#define configUSE_CO_ROUTINES 0
#define configUSE_MUTEXES 1
#define configUSE_RECURSIVE_MUTEXES 1
#define configUSE_COUNTING_SEMAPHORES 1
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configSUPPORT_STATIC_ALLOCATION 1
#define configAPPLICATION_ALLOCATED_HEAP 0
#define configUSE_TIMERS 1

/**
 * @brief Initialization Specific Definitions
 * @note Definitions which require providing FreeRTOS code to use as callbacks
 */
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define configUSE_MALLOC_FAILED_HOOK 0

/**
 * @brief Application Specific Definitions
 * @note Definitions specific to the application functionality (tasks)
 */
// size (in words) of the IDLE task's stack; <size> * 4 (32bit size) = bytes
#define configMINIMAL_STACK_SIZE (100) // 400 Bytes

// defined in bytes
#define MAX_HEAP_SIZE (32768)

/* 25984 (non-optimized) */
#define REQUIRED_FROM_HEAP (3860 /* .data */ + 620 /* .vtable */ + 256 /* .stack */ + 2048 /* .sysmem */)

/* 4608 (non-optimized); defined for tasks */
#define REQUIRED_TASK_STACK_SIZE (tskStackSz_LED + tskStackSz_Switch)

/* Overhead needed for TM4C to boot, FreeRTOS,  & application */
#define FREERTOS_AND_APP_OVERHEAD (5200)

#define configTOTAL_HEAP_SIZE (MAX_HEAP_SIZE - REQUIRED_FROM_HEAP - FREERTOS_AND_APP_OVERHEAD)
#if (configTOTAL_HEAP_SIZE > (MAX_HEAP_SIZE - REQUIRED_FROM_HEAP)) || (REQUIRED_TASK_STACK_SIZE > configTOTAL_HEAP_SIZE)
#    error Cannot fit the required task memory in the available heap
#endif

#define configMAX_TASK_NAME_LEN (12)
#define configMAX_PRIORITIES 5
#define configMAX_CO_ROUTINE_PRIORITIES 2
#define configQUEUE_REGISTRY_SIZE 10

#define configTIMER_TASK_PRIORITY 4
#define configTIMER_QUEUE_LENGTH 3
#define configTIMER_TASK_STACK_DEPTH (256)

/**
 * @brief Debugging Definitions
 * TODO: Macro define "Debug" vs "Release" dis/enabling of these
 */
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#define configUSE_TRACE_FACILITY 1
#define configCHECK_FOR_STACK_OVERFLOW 2
#define configASSERT(x)                                                                                                \
    if ((x) == 0)                                                                                                      \
    {                                                                                                                  \
        taskDISABLE_INTERRUPTS();                                                                                      \
        for (;;)                                                                                                       \
            ;                                                                                                          \
    }

#endif /* FREERTOS_CONFIG_H */
