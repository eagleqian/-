//===========================================================================
//文件名称：common.h
//功能概要：公共要素源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-10-12 V1.0
//         2013-02-02 V2.0(WYH)
//===========================================================================

#include "common.h"    //包含公共要素头文件

static  uint_32  int_disable_level; // 静态变量，当前中断嵌套层数

//=========================================================================
//函数名称：init_critical
//参数说明：无
//函数返回：无
//功能概要：初始化临界区访问控制
//=========================================================================
void  init_critical(void) 
{
    ENABLE_INTERRUPTS;
    int_disable_level = 0;
}

//=========================================================================
//函数名称：enter_critical
//参数说明：无
//函数返回：无
//功能概要：进入临界区
//=========================================================================
void  enter_critical(void)
{
    if (0 == int_disable_level)
    {
        DISABLE_INTERRUPTS;
    }
    int_disable_level++;
}

//=========================================================================
//函数名称：exit_critical
//参数说明：无
//函数返回：无
//功能概要：离开临界区
//=========================================================================
void  exit_critical(void) 
{
    if (int_disable_level)
    {
        int_disable_level--;
        if (0 == int_disable_level)
        {
            ENABLE_INTERRUPTS;
        }
    }
}

//============================================================================
//函数名称：enable_irq
//函数返回：无
//参数说明：irq：irq号, 各个模块的中断号定义在MKL25Z.h中
//功能概要：使能irq中断 
//============================================================================
void enable_irq (IRQn_Type irq)
{
    //确定irq号为有效的irq号
    if (irq > 32)    irq=32;
    
    NVIC_EnableIRQ(irq);

}

//============================================================================
//函数名称：disable_irq
//函数返回：无      
//参数说明：irq：irq号, 各个模块的中断号定义在MKL25Z.h中
//功能概要：禁止irq中断 
//============================================================================
void disable_irq (IRQn_Type irq)
{

    //确定irq号为有效的irq号
    if (irq > 32)    irq=32;
    
    NVIC_DisableIRQ(irq);
}
 
//============================================================================
//函数名称：set_irq_priority
//函数返回：无      
//参数说明：irq：irq号,各个模块的中断号定义在MKL25Z.h中
//         prio：优先级
//功能概要：设置irq中断和优先级 
//============================================================================
void set_irq_priority (IRQn_Type irq, uint_16 prio)
{   
    uint_8 err = 0;
   
    if (irq > 32)
    {    
        err = 1;
    }
    if (prio > 3)
    {     
        err = 1;
    }
    if (err != 1)
    {  
        NVIC_SetPriority(irq, prio);
    }
}


//===========================================================================
//函数名称：SecAdd1
//函数返回：无
//参数说明：*p:为指向一个时分秒数组p[3]
//功能概要：秒单元+1，并处理时分单元（00:00:00-23:59:59)
//===========================================================================
void SecAdd1(uint_8 *p)
{
     *(p+2)+=1;         //秒+1
     if(*(p+2)>=60)     //秒溢出
     {
        *(p+2)=0;       //清秒
        *(p+1)+=1;      //分+1
        if(*(p+1)>=60)  //分溢出
        {
           *(p+1)=0;    //清分
           *p+=1;       //时+1
           if(*p>=24)   //时溢出
           {
             *p=0;      //清时
           }
         }
      }
}
