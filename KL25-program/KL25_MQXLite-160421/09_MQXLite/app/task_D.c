#include "app_inc.h"    //应用任务公共头文件

//===========================================================================
//任务名称：task_E
//功能概要：将串口2中断接收的完整数据帧发送至PC机
//参数说明：未使用
//备       注：使用全局变量lwevent_group1, UART2_RecData_Event,g_UART_ISR_buffer
//===========================================================================
void task_D (uint32_t initial_data )
{ 
    int itemp;
    //进入主循环
    while (TRUE)
    {    
        //等待串口2接收完整数据帧事件位（Event_UART2_ReData）
        _lwevent_wait_ticks(&lwevent_group1, Event_UART2_ReData, FALSE, 0);
        g_UART_FrameCount++;         //接收的帧数加1       

        printf("串口2接收的完整数据帧：(--0x%02X--)",g_UART_FrameCount);
        
        //发送帧数据
        for(itemp=0;itemp<g_UART_ISR_buffer[1]+3;itemp++)
        {
            printf("%x",g_UART_ISR_buffer[itemp]);
        }
        printf("\r\n");
        //清除串口2接收完整数据帧事件位（Event_UART2_ReData）
        _lwevent_clear(&lwevent_group1, Event_UART2_ReData);
    }
}


