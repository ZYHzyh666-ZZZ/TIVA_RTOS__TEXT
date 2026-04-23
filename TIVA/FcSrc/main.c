/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：主循环
**********************************************************************************/
#include "SysConfig.h"
#include "Ano_Scheduler.h"
#include "User_Rtos.h"
#include "FreeRTOS.h"
#include "task.h"

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
	while (1)
	{
		//当系统出错后，会进入这个死循环
	}
}
#endif
//=======================================================================================
//=======================================================================================
int main(void)
{
	//进行所有设备的初始化，并将初始化结果保存
	All_Init();

	// 初始化用户 RTOS 任务/定时器
	RtosUser_Init();

	// 启动 FreeRTOS 调度器
	vTaskStartScheduler();

	while (1)
	{
		// 如果调度器启动成功，这里应永远不会执行
	}
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
