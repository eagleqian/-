//===========================================================================
//文件名称：smc.c
//功能概要：smc底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2013-4-20   
//===========================================================================
#include "smc.h"

//===========================================================================
//函数名称：sleep
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入WAIT（sleep）模式，执行WFI指令进入该模式。
//===========================================================================
void sleep (void)
{
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    asm("WFI");
}

//===========================================================================
//函数名称：deepsleep
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入STOP（deepsleep）模式，执行WFI指令进入该模式。
//===========================================================================
void deepsleep (void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    asm("WFI");
}
//===========================================================================
//函数名称：enter_wait
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入wait模式。
//===========================================================================
void enter_wait(void)
{
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	asm("WFI");
}

//===========================================================================
//函数名称：enter_stop
//函数返回：无
//参数说明：
//  0x00 = STOP   - 正常停止模式
//  0x40 = PSTOP1 - 部分停止模式，系统时钟，总线时钟被关闭
//  0x80 = PSTOP2 - 部分停止模式，系统时钟关闭，总线时钟开启
//  0xC0 = 保留
//功能概要：配置ARM系统控制寄存器进入stop模式。
//===========================================================================
void enter_stop(unsigned char partial_stop_opt)
{
  SMC_PMPROT = 0;  

  SMC_PMCTRL &= ~SMC_PMCTRL_STOPM_MASK;
  SMC_PMCTRL |=  SMC_PMCTRL_STOPM(0); 
  SMC_STOPCTRL &= ~SMC_STOPCTRL_PSTOPO_MASK;
  SMC_STOPCTRL |= partial_stop_opt;
  
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  asm("WFI");
}

//===========================================================================
//函数名称：enter_vlpr
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入vlpr模式。
//===========================================================================
int enter_vlpr(void)
{
  int i; 
  unsigned int return_value;
  if ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK)== 4)
  {
     return_value = 0x14;
  }
  SMC_PMPROT = SMC_PMPROT_AVLP_MASK;  
    
  SMC_PMCTRL &= ~SMC_PMCTRL_RUNM_MASK; 
  SMC_PMCTRL  |= SMC_PMCTRL_RUNM(0x2);

  for (i = 0 ; i < 10000 ; i++)
  {     
      if ((PMC_REGSC & PMC_REGSC_REGONS_MASK) ==0x04)
      {
      }  
      else  break;
  }  
  if ((PMC_REGSC & PMC_REGSC_REGONS_MASK) ==0x04) 
  {  
      return_value = 0x24; 
  }

  if ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK) == 4)  
    {
      return_value = SMC_PMSTAT;
    }
  return (return_value);
}

//===========================================================================
//函数名称：exit_vlpr
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器退出vlpr模式。
//===========================================================================
void exit_vlpr(void)
{
    int i;
    if  ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK)== 4) 
    {
       SMC_PMCTRL &= ~SMC_PMCTRL_RUNM_MASK;
                     
       for (i=0;i<0xff;i++)
       {
           if ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK)== 1)
             if ((PMC_REGSC & PMC_REGSC_REGONS_MASK) == 1)
    	        break;
       }           
    } 
}

//===========================================================================
//函数名称：enter_vlps
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入vlps模式。
//===========================================================================
void enter_vlps(void)
{
  SMC_PMPROT = SMC_PMPROT_AVLP_MASK;           
  SMC_PMCTRL &= ~SMC_PMCTRL_STOPM_MASK; 
  SMC_PMCTRL |=  SMC_PMCTRL_STOPM(0x2); 
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  asm("WFI");
}

//===========================================================================
//函数名称：enter_lls
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入lls模式。
//===========================================================================
void enter_lls(void)
{
  SMC_PMPROT = SMC_PMPROT_ALLS_MASK;   
  SMC_PMCTRL &= ~SMC_PMCTRL_STOPM_MASK; 
  SMC_PMCTRL |=  SMC_PMCTRL_STOPM(0x3);  
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  asm("WFI");
}

//===========================================================================
//函数名称：enter_vlls3
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入vlls3模式。
//===========================================================================
void enter_vlls3(void)
{
  SMC_PMPROT = SMC_PMPROT_AVLLS_MASK;      
  SMC_PMCTRL &= ~SMC_PMCTRL_STOPM_MASK; 
  SMC_PMCTRL |=  SMC_PMCTRL_STOPM(0x4); 
  SMC_STOPCTRL =  SMC_STOPCTRL_VLLSM(3);            
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  asm("WFI");
}

//===========================================================================
//函数名称：enter_vlls1
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入vlls1模式。
//===========================================================================
void enter_vlls1(void)
{
  SMC_PMPROT = SMC_PMPROT_AVLLS_MASK;
  SMC_PMCTRL &= ~SMC_PMCTRL_STOPM_MASK; 
  SMC_PMCTRL |=  SMC_PMCTRL_STOPM(0x4); 
  SMC_STOPCTRL =  SMC_STOPCTRL_VLLSM(1);          
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  asm("WFI");
}

//===========================================================================
//函数名称：enter_vlls0
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入vlls0模式。
//===========================================================================
void enter_vlls0(unsigned char PORPO_value )
{
  int i;
  SMC_PMPROT = SMC_PMPROT_AVLLS_MASK;   
  if ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK)== 4){
     SMC_PMCTRL &= ~SMC_PMCTRL_RUNM_MASK;  
     for (i=0;i<0xff;i++)
       {
       if ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK)== 1)
    	 break;
       }
  }

  SMC_PMCTRL &= ~SMC_PMCTRL_STOPM_MASK; 
  SMC_PMCTRL |=  SMC_PMCTRL_STOPM(0x4); 

  SMC_STOPCTRL &= ~SMC_STOPCTRL_VLLSM_MASK;
  SMC_STOPCTRL &= ~SMC_STOPCTRL_PORPO_MASK;
  SMC_STOPCTRL |=  (PORPO_value <<SMC_STOPCTRL_PORPO_SHIFT) 
                 | SMC_STOPCTRL_VLLSM(0);          

  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  asm("WFI");
}

//===========================================================================
//函数名称：enter_vlls0_nopor
//函数返回：无
//参数说明：无
//功能概要：配置ARM系统控制寄存器进入vlls0模式，上电复位电路禁止。
//===========================================================================
void enter_vlls0_nopor(void)
{
  int i;
  SMC_PMPROT = SMC_PMPROT_AVLLS_MASK;   
  if ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK)== 4){
     SMC_PMCTRL &= ~SMC_PMCTRL_RUNM_MASK; 
     for (i=0;i<0xff;i++)
       {
       if ((SMC_PMSTAT & SMC_PMSTAT_PMSTAT_MASK)== 1)
    	 break;
       }
  }

  SMC_PMCTRL &= ~SMC_PMCTRL_STOPM_MASK; 
  SMC_PMCTRL |=  SMC_PMCTRL_STOPM(0x4); 
  SMC_STOPCTRL &= ~SMC_STOPCTRL_VLLSM_MASK;
  SMC_STOPCTRL =  SMC_STOPCTRL_VLLSM(0) | SMC_STOPCTRL_PORPO_MASK;  
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  asm("WFI");
}



