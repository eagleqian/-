//=====================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//       2016-05-11   V3.0
//=====================================================================
#include "includes.h"

//========================中断函数服务例程=================================
//=====================================================================
//函数名: UART1_IRQHandler
//功  能: 串口1接收中断服务例程
//参  数: 无
//返  回: 无
//说  明: 需要启动中断并注册才可使用
//=====================================================================
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

//=====================================================================
//函数名: SPI1_IRQHandler
//功  能: SPI1接收中断服务程序
//参  数: 无
//返  回: 无
//说  明: 需要启动中断并注册才可使用
//=====================================================================
void SPI1_IRQHandler(void)
{
    uint_8 redata;
    DISABLE_INTERRUPTS;
    redata=SPI_receive1(SPI_1);    //接收主机发送过来的一个字节数据。
    if(redata!='0')
    {
    	uart_send1(UART_2,redata);
    	redata++;
    	SPI_send1(SPI_1,redata);
    }
    ENABLE_INTERRUPTS;
}

