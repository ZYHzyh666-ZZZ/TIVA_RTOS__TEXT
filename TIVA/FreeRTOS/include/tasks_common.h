#ifndef _TASKS_COMMON_H_
#define _TASKS_COMMON_H_

// Common definitions and macros used in tasks
#ifndef SEMAPHORE_WRAP_PRINTF
#    define SEMAPHORE_WRAP_PRINTF 1
#endif
#if SEMAPHORE_WRAP_PRINTF
#    define SEM_WRAP(...) \
        xSemaphoreTake(g_printSemaphore, portMAX_DELAY); \
        __VA_ARGS__; \
        xSemaphoreGive(g_printSemaphore)
#else
#    define SEM_WRAP(...) __VA_ARGS__
#endif
#ifndef printf
#    define printf(...) UARTprintf(__VA_ARGS__)
#endif

// The priorities of the various tasks
// Note: Be consistent, use (configMAX_PRIORITIES - val) or (tskIDLE_PRIORITY + val)
#define tskPriority_LED (tskIDLE_PRIORITY + 1)
#define tskPriority_Switch (tskIDLE_PRIORITY + 2)

// Task's "stack" size of the various tasks
#define tskStackSz_LED (128)
#define tskStackSz_Switch (512)

#endif // _TASKS_COMMON_H_
