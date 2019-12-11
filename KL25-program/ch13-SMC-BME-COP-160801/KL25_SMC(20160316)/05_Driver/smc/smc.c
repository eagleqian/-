//===========================================================================
//�ļ����ƣ�smc.c
//���ܸ�Ҫ��smc�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2013-4-20   
//===========================================================================
#include "smc.h"

//===========================================================================
//�������ƣ�sleep
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������WAIT��sleep��ģʽ��ִ��WFIָ������ģʽ��
//===========================================================================
void sleep (void)
{
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    asm("WFI");
}

//===========================================================================
//�������ƣ�deepsleep
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������STOP��deepsleep��ģʽ��ִ��WFIָ������ģʽ��
//===========================================================================
void deepsleep (void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    asm("WFI");
}
//===========================================================================
//�������ƣ�enter_wait
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������waitģʽ��
//===========================================================================
void enter_wait(void)
{
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	asm("WFI");
}

//===========================================================================
//�������ƣ�enter_stop
//�������أ���
//����˵����
//  0x00 = STOP   - ����ֹͣģʽ
//  0x40 = PSTOP1 - ����ֹͣģʽ��ϵͳʱ�ӣ�����ʱ�ӱ��ر�
//  0x80 = PSTOP2 - ����ֹͣģʽ��ϵͳʱ�ӹرգ�����ʱ�ӿ���
//  0xC0 = ����
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������stopģʽ��
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
//�������ƣ�enter_vlpr
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������vlprģʽ��
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
//�������ƣ�exit_vlpr
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ����˳�vlprģʽ��
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
//�������ƣ�enter_vlps
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������vlpsģʽ��
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
//�������ƣ�enter_lls
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������llsģʽ��
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
//�������ƣ�enter_vlls3
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������vlls3ģʽ��
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
//�������ƣ�enter_vlls1
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������vlls1ģʽ��
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
//�������ƣ�enter_vlls0
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������vlls0ģʽ��
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
//�������ƣ�enter_vlls0_nopor
//�������أ���
//����˵������
//���ܸ�Ҫ������ARMϵͳ���ƼĴ�������vlls0ģʽ���ϵ縴λ��·��ֹ��
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



