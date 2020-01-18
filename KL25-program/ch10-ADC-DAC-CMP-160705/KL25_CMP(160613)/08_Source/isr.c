//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================中断函数服务例程===============================
//串口0接收中断服务例程
void UART0_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_0, &flag);
    if (0 == flag)
    {
        uart_send1(UART_0, ch);
    }
    
    ENABLE_INTERRUPTS;
}


//串口1接收中断服务例程
void UART1_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_1, &flag);
    if (0 == flag)
    {
        uart_send1(UART_1, ch);
    }
 
    ENABLE_INTERRUPTS;
}

//串口2接收中断服务例程
void UART2_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_2, &flag);
    if (0 == flag)
    {
        uart_send1(UART_2, ch);
    }
        
    ENABLE_INTERRUPTS;
}

//===========================================================================
//函数名: CMP0_IRQHandler
//功  能: 比较器输出上升沿下降沿中断触发
//说  明: 无
//===========================================================================
//比较器中断处理函数
void CMP0_IRQHandler(void)
{
    //如果是上升沿
    if ((CMP0_SCR & CMP_SCR_CFR_MASK)==CMP_SCR_CFR_MASK)
    {
        CMP0_SCR |= CMP_SCR_CFR_MASK;  // 清标志
        uart_send_string(UART_1, "\r\nRising edge on HSCMP0\r\n");
    }
    //如果是下降沿
    if ( (CMP0_SCR & CMP_SCR_CFF_MASK) == CMP_SCR_CFF_MASK)
    {
        CMP0_SCR |= CMP_SCR_CFF_MASK;  // 清标志
        uart_send_string(UART_1, "\r\nFalling edge on HSCMP0\r\n");
    }
}

