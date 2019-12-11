//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================�жϺ�����������===============================
//======================================================================
//�������ƣ�SysTick_Handler
//����˵������
//�������أ���
//���ܸ�Ҫ��SysTick��ʱ���жϷ�������
//======================================================================
void SysTick_Handler(void)
{
    static uint_8 SysTickcount = 0;
    SysTickcount++;
    if(SysTickcount >= 100)   //1s��
    {
        SysTickcount = 0;
        //���ʱ����
        SecAdd1(g_time);      //g_time��ʱ����ȫ�ֱ�������
    }
}


//����0�����жϷ�������
void UART0_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_0, &flag);
    if (1 == flag)
    {
        uart_send1(UART_0, ch);
    }
    
    ENABLE_INTERRUPTS;
}


//����1�����жϷ�������
void UART1_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_1, &flag);
    if (1 == flag)
    {
        uart_send1(UART_1, ch);
    }
 
    ENABLE_INTERRUPTS;
}

//����2�����жϷ�������
void UART2_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_2, &flag);
    if (1 == flag)
    {
        uart_send1(UART_2, ch);
    }
        
    ENABLE_INTERRUPTS;
}

