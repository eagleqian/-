//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================中断函数服务例程===============================

//串口1接收中断服务例程
void UART1_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    __disable_irq();    //关总中断

    ch = uart_re1(UART_1, &flag);
    if (0 == flag)
    {
        uart_send1(UART_1, ch);
    }
    __enable_irq();     //开总中断
}

extern uint_8 USBFlag;
//============================================================================
//函数名: USB0_IRQHandler
//功  能: USB中断
//参  数: 无
//返  回: 无
//============================================================================
void USB0_IRQHandler(void)
{
    uint_8 status;

    while (1)
    {
        status = (uint_8)(USB0_ISTAT & USB0_INTEN);

        if (!status)  //没有USB中断，不处理
            break;

        USB0_ISTAT = status;

        if (status & USB_ISTAT_ATTACH_MASK)  //发生了ATTACH中断
        {

            USB0_INTEN &= ~USB_INTEN_ATTACHEN_MASK; //清中断位
            USB0_INTEN |= USB_ISTAT_USBRST_MASK;
            USB0_INTEN |= USB_ISTAT_TOKDNE_MASK;

            USBFlag |= USB_ISTAT_ATTACH_MASK;
        }

        if (status & USB_ISTAT_TOKDNE_MASK)   //发生了令牌完成中断
        {
            USBFlag |= USB_ISTAT_TOKDNE_MASK;
        }

        if (status & USB_ISTAT_USBRST_MASK)   //发生了复位中断
        {
            USBFlag |= USB_ISTAT_USBRST_MASK; //w1c
        }

    };
}
