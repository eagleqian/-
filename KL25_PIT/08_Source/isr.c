//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"
    
//=============================中断函数服务例程==============================
//==========================================================================
//函数名称：PIT_IRQHandler
//函数返回：无
//参数说明：无
//功能概要：PIT中断服务例程，清中断标志，并使用通道0完成计时，显示MCU运行时间
//调用举例：无
//==========================================================================
void PIT_IRQHandler(void)
{
    if(PIT_GET_FLAG(CH_0)
    {
        SecAdd1(g_time);        //g_time是时分秒全局变量数组
        PIT_CLEAR_FLAG(CH_0);                    //清标志
    }
    else if((PIT_GET_FLAG(CH_1))
    {
        PIT_CLEAR_FLAG(CH_1);                    //清标志
    }
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
            uart_send1(UART_0, ch);     //向原串口发回一个字节
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
            uart_send1(UART_2, ch);     //向原串口发回一个字节
        }
    }
    ENABLE_INTERRUPTS;
}
