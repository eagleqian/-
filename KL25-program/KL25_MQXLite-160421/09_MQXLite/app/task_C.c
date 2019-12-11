#include "app_inc.h"

//===========================================================================
//任务名称：task_C
//功能概要：light blue每4秒亮暗一次，首次亮暗前延时2秒
//参数说明：未使用
//===========================================================================
void task_C(uint_32 initial_data)
{            
    _time_delay_ticks(DELAY_TIMES*2);
    while (TRUE) 
    {
        light_change(RUN_LIGHT_BLUE);            // 改变蓝灯亮灭状态
        printf("light blue change\r\n");
        _time_delay_ticks(DELAY_TIMES*4); // 延时DELAY_TIMES(放弃CPU控制权)
    }
}
