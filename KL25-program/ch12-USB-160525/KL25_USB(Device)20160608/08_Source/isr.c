//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"

extern void usb_isr_handler(uint_8 isr_type);
extern uint_8  usb_get_isr();
extern uint_8 vEP2State;
extern tBDT *BDTtable;

//========================中断函数服务例程===============================

//=====================================================================
//函数名称：USB0_IRQHandler（USB中断服务例程）
//函数功能：处理USB模块中断，包括数据收发、设备枚举等原因触发的中断请求。
//        需收发数据时，会通过对全局变量的操作完成，如需发送数据，需预先将
//        待发送数据写入全局变量g_USBSend，其长度写入g_USBSendLength，并置
//        发送标志g_USBSendFlag为1，中断会自动将数据发出；同时中断会自动接收
//        主机发来的数据，将数据放入全局变量g_USBRecv，并将接收数据长度写入
//        全局变量g_USBRecvLength
//=====================================================================

void USB0_IRQHandler(void)
{
    uint_8 isr_type;
    DISABLE_INTERRUPTS;    //关总中断
    //1. 获取中断类型
    isr_type=usb_get_isr();
    //2. 若不是令牌完成中断，调用相应处理程序
    if(isr_type!=USB_TOKDNE_INT)
    {
        usb_isr_handler(isr_type);    //调用非令牌完成中断的处理程序
        goto USB0_IRQ_exit;
    }
    //3. 是令牌完成中断，执行块数据传输或设备枚举
    //(3.1)清收发ODD区，并指定EVEN区
    FLAG_SET(USB_CTL_ODDRST_SHIFT,USB0_CTL);
    //(3.2)若是设备枚举请求，进行设备枚举
    if((USB0_STAT >> 4)==0)
    {
        usb_enumerate();
        goto USB0_IRQ_exit;
    }
    //(3.3)若不是设备枚举请求，进行数据收发操作
    if((USB0_STAT & 0xF8)==mEP2_IN)//从端点2发送数据至主机
    {
        //若执行发送标志被置1，则执行发送数据函数
        if(g_USBSendFlag==1)
        {
            usb_send(g_USBSend,&g_USBSendLength);//调用发送数据处理函数
            if(g_USBSendLength==0)
            {
                g_USBSendFlag=0;    //发送完成，执行发送标志清0
            }
            goto USB0_IRQ_exit;
        }
        //若无数据需要发送，则向USB主机发送一个确认包
        BDTtable[bEP2IN_ODD].Cnt =0;
        vEP2State ^= 0x40;
        BDTtable[bEP2IN_ODD].Stat._byte= vEP2State;
    }
    else if((USB0_STAT & 0xF8)==mEP3_OUT)//从端点3接收主机发来的数据
    {
        usb_recv(g_USBRecv,&g_USBRecvLength);
    }
USB0_IRQ_exit:
    //4. 清除中断标志，结束中断处理
    FLAG_SET(USB_ISTAT_TOKDNE_SHIFT,USB0_ISTAT);
    ENABLE_INTERRUPTS;    //开总中断
    return;
}

//=====================================================================
