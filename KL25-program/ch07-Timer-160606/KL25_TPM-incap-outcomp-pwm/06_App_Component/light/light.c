//=====================================================================
//文件名称：light.c
//功能概要：小灯构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2013-02-02   V2.0
//=====================================================================

#include "light.h"

//=====================================================================
//函数名称：light_init
//函数参数：port_pin：(端口号)|(引脚号)（如：(PORTB)|(5) 表示为B口5号脚）
//       state：设定小灯状态。由light.h中宏定义。
//函数返回：无
//功能概要：指示灯驱动初始化。
//=====================================================================
void light_init(uint_16 port_pin, uint_8 state)
{
    gpio_init(port_pin, GPIO_OUTPUT, state);
}

//=====================================================================
//函数名称：light_control
//函数参数：port_pin：(端口号)|(引脚号)（如：(PORTB)|(5) 表示为B口5号脚）
//       state：设定小灯状态。由light.h中宏定义。
//函数返回：无
//功能概要：控制指示灯亮暗。
//=====================================================================
void light_control(uint_16 port_pin, uint_8 state)
{
    gpio_set(port_pin, state);
}

//=====================================================================
//函数名称：light_change
//函数参数：port_pin：(端口号)|(引脚号)（如：(PORTB)|(5) 表示为B口5号脚）
//函数返回：无
//功能概要：切换指示灯亮暗。
//=====================================================================
void light_change(uint_16 port_pin)
{
    gpio_reverse(port_pin);
}
