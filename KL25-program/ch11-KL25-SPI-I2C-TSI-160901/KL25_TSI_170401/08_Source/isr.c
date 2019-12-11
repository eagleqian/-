//=====================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2016-03-18   V1.0
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
//=====================================================================
//函数名: TSI0_IRQHandler
//功  能: tsi中断响应函数
//参  数: 无
//返  回: 无
//说  明: 需要启动中断并注册才可使用
//=====================================================================
void TSI0_IRQHandler(void)
{
    //存放数值的临时变量
    uint_16 i;
   static uint_8 j=0;    //为中断次数
    //关总中断
    DISABLE_INTERRUPTS;
    if(TSI0_GENCS & TSI_GENCS_OUTRGF_MASK)//为超值中断
    {
       //获取计数值
       i = tsi_get_value16();
       j++;
       printf("%d ",j);
       PIT_CLEAR_FLAG(CH_0);      //清除中断标志
       //并且将红灯点亮
		light_control(RUN_LIGHT_RED, LIGHT_ON);

		while(i>(TSI0_TSHD>>16))   //判断计数值是否超出上限阈值
		{
			i=tsi_get_value16();
		    if(PIT_GET_FLAG(CH_0)    //获取中断标志
		    { printf("你已长按，请松手!\n");}
		    PIT_CLEAR_FLAG(CH_0);     //清除中断标志
		}
     }

    //写1清溢出中断位
    TSI0_GENCS |=  TSI_GENCS_OUTRGF_MASK;//写1清除该位
    //开总中断
    ENABLE_INTERRUPTS;
}
