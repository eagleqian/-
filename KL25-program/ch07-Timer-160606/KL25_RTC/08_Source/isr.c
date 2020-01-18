//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"
    
//=============================中断函数服务例程==============================
//==========================================================================
//函数名称：RTC_IRQHandler
//函数返回：无
//参数说明：无
//功能概要：RTC中断服务例程。如果是无效中断及溢出中断，清中断标志并复位
//计数器，如果是报警中断，复位报警值
//调用举例：无
//==========================================================================
void RTC_IRQHandler(void)
{
    if(RTC_GET_INVALID_FLAG)
    {
        printf("\r\n进入RTC计时无效中断，原因：POR或软件复位可导致RTC计数器无效！");
        RTC_CLEAR_FLAG;
    }
    else if(RTC_GET_OVERFLOW_FLAG)
    {
        printf("\r\n进入RTC计时溢出中断，原因：秒计数器的值由0xFFFFFFFF加一！");
        RTC_CLEAR_FLAG;
    }
    else if(RTC_GET_ALAM_FLAG)
    {
        printf("\r\n进入RTC报警中断，原因：秒计数器的值等于报警值！");
        rtc_reset_alarm_time(AlarmTimes = AlarmTimes + 1);
    }
    else
    {
        printf("\r\nRTC无中断事件发生，原因：POR或软件复位后中断信号即有效！");
    }
}

//======================================================================
//函数名称：RTC_Seconds_IRQHandler
//函数返回：无
//参数说明：无
//功能概要：RTC秒中断服务例程。完成累计计时，用于显示MCU运行时间。边沿敏感中断，
//每秒产生一次，无需状态位清零
//调用举例：无
//======================================================================
void RTC_Seconds_IRQHandler(void)
{
    SecAdd1(g_time);        //g_time是时分秒全局变量数组
}


//串口0接收中断服务例程
void UART0_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag;
    DISABLE_INTERRUPTS;    //关总中断
    if(uart_get_re_int(UART_0))
    {
        ch = uart_re1(UART_0, &flag);    //调用接收一个字节的函数，清接收中断位
        if(flag)
        {
            uart_send1(UART_0, ch);      //向原串口发回一个字节
        }
    }
    ENABLE_INTERRUPTS;
}


//串口1接收中断服务例程
void UART1_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag;
    DISABLE_INTERRUPTS;    //关总中断
    if(uart_get_re_int(UART_1))
    {
        ch = uart_re1(UART_1, &flag);    //调用接收一个字节的函数，清接收中断位
        if(flag)
        {
            uart_send1(UART_1, ch);      //向原串口发回一个字节
        }
    }
    ENABLE_INTERRUPTS;
}

//串口2接收中断服务例程
void UART2_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag;
    DISABLE_INTERRUPTS;    //关总中断
    if(uart_get_re_int(UART_2))
    {
        ch = uart_re1(UART_2, &flag);    //调用接收一个字节的函数，清接收中断位
        if(flag)
        {
            uart_send1(UART_2, ch);      //向原串口发回一个字节
        }
    }
    ENABLE_INTERRUPTS;
}
