//==========================================================================
//文件名称：pit.c
//功能概要：KL25 pit底层驱动程序文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2016-3-20   V4.0
//==========================================================================
#include "pit.h"             
//==========================================================================
//函数名称: pit_init                                                         
//函数返回: 无                                          
//参数说明: channel:PIT模块的通道号，0或1。
//         freq:系统总线时钟频率，单位KHz。例:系统总线时钟为24MHz，则freq=24000。
//         int_ms:中断周期，以ms为单位。系统总线时钟为24MHz，最大值为178956ms
//功能概要: PIT模块初始化。
//调用举例：pit_init(CH_0,PIT_WORK_FREQ,1000);即初始化PIT模块的0通道使用总线
//时钟频率，中断周期为1秒。
//==========================================================================
void pit_init(uint_8 channel,uint_16 freq,uint_32 int_ms)
{
    if(channel>1)
    {
        channel = 0;
    }
    if((int_ms<1)||(int_ms>178956))
        int_ms = 4000;
    BSET(SIM_SCGC6_PIT_SHIFT,SIM_SCGC6);            //开PIT时钟门
    BCLR(PIT_MCR_MDIS_SHIFT,PIT_MCR);               //使能PIT模块
    BSET(PIT_MCR_FRZ_SHIFT,PIT_MCR);                //调试模式下禁止
    PIT_LDVAL(channel) = int_ms*freq-1;
    PIT_TCTRL(channel) |= PIT_TCTRL_TEN_MASK;       //使能pit通道定时器
    PIT_TCTRL(channel) |= (PIT_TCTRL_TIE_MASK);
}
    
//==========================================================================
//函数名称: pit_enable_int
//参数说明: channel:PIT模块的通道号，0或1。
//函数返回: 无
//功能概要: 使能某一通道的PIT中断。
//调用举例：pit_enable_int(CH_0);使能PIT模块的通道0中断。
//==========================================================================
void pit_enable_int(uint_8 channel)
{
    if(channel>1)
    {
        channel = 0;
    }
    PIT_TCTRL(channel)|=(PIT_TCTRL_TIE_MASK);    //开PIT通道中断

    NVIC_EnableIRQ(PIT_IRQn);                      //开PIT的IRQ中断
}

//==========================================================================
//函数名称: pit_disable_int
//参数说明: channel:PIT模块的通道号，0或1。
//函数返回: 无
//功能概要: 禁止某一通道的PIT中断。
//调用举例：pit_disable_int(CH_0);禁止PIT模块的通道0中断。
//==========================================================================
void pit_disable_int(uint_8 channel)
{
    if(channel>1)
    {
        channel = 0;
    }
    PIT_TCTRL(channel)&=~(PIT_TCTRL_TIE_MASK);   //关PIT通道中断

    NVIC_DisableIRQ(PIT_IRQn);                     //关PIT的IRQ中断
}
