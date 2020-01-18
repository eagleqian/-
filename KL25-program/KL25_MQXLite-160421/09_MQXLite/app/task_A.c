#include "app_inc.h"    //应用任务公共头文件

//===========================================================================
//任务名称：task_A
//功能概要：light red每4秒亮暗一次
//参数说明：未使用
//===========================================================================
void task_A(uint_32 initial)
{    
    while (TRUE)
    {
        light_change(RUN_LIGHT_RED);           // 改变红灯亮灭状态
        printf("lingt red change\r\n");
        _time_delay_ticks(DELAY_TIMES*4);// 延时DELAY_TIMES(放弃CPU控制权)
    }
}
