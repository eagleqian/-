//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================中断函数服务例程===============================
//======================================================================
//函数名称：SysTick_Handler
//参数说明：无
//函数返回：无
//功能概要：SysTick定时器中断服务例程，根据初始化设置每5ms中断一次
//======================================================================
void SysTick_Handler(void)
{
    //LED显示
    LEDshow(g_LEDBuffer);
}
//串口0接收中断服务例程
void UART0_IRQHandler(void)
{

}


//串口1接收中断服务例程
void UART1_IRQHandler(void)
{

}

//串口2接收中断服务例程
void UART2_IRQHandler(void)
{

}
//======================================================================
//函数名称：PORTA_IRQHandler
//参数说明：无
//函数返回：无
//PORTA GPIO中断服务例程，此处用于处理键盘中断
//======================================================================
void PORTA_IRQHandler(void){
    DISABLE_INTERRUPTS;//关总中断
    //键盘中断处理，实际使用时请按照对应不同接线方式修改寄存器名称
    if(gpio_get_int(n1)==1 || gpio_get_int(n2)==1
       ||gpio_get_int(n3)==1 ||gpio_get_int(n4)==1)
    {
        g_kb_value=KBScanN(10);//扫描键盘，将键值赋给全局变量以便显示
        //将行线状态重新置0，以便下次按下某个键能产生下降沿引发中断
        gpio_set(m1, 0);
        gpio_set(m2, 0);
        gpio_set(m3, 0);
        gpio_set(m4, 0);
        //清中断标志位
        gpio_clear_int(n1);
        gpio_clear_int(n2);
        gpio_clear_int(n3);
        gpio_clear_int(n4);
    }
    if(g_kb_value!=0xFF)
    {
        //修改.成为按键值
        g_LCDBuffer[31] = KBDef(g_kb_value);
        //通过LCD显示出来
        LCDShow(g_LCDBuffer);
    }
    ENABLE_INTERRUPTS;//开总中断
}
