#include "app_inc.h"

//===========================================================================
//任务名称：task_B
//功能概要：light green每4秒亮暗一次，首次亮暗前延时1秒
//参数说明：未使用
//===========================================================================
void task_B(uint_32 initial_data)
{
    _time_delay_ticks(DELAY_TIMES);
    while (TRUE) 
    {
        light_change(RUN_LIGHT_GREEN);            // 改变绿灯亮灭状态
        printf("light green change\r\n");
        _time_delay_ticks(DELAY_TIMES*4); // 延时DELAY_TIMES(放弃CPU控制权)
    }
}
