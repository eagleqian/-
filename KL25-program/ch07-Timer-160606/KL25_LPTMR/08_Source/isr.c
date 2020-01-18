//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"
    
//=============================�жϺ�����������==============================
//==========================================================================
//�������ƣ�LPTMR0_IRQHandler
//����˵������
//�������أ���
//���ܸ�Ҫ��LPTMR0�жϷ������̡����жϱ�־������ɼ�ʱ��������ʾMCU����ʱ��
//���þ�������
//==========================================================================
void LPTMR0_IRQHandler(void)
{
    DISABLE_INTERRUPTS;           //��ֹ���ж�

    if(LPTMR_GET_FLAG)
    {
         SecAdd1(g_time);         //g_time��ʱ����ȫ�ֱ�������
         LPTMR_CLEAR_FLAG;        //���LPTMR�Ƚϱ�־
    }

    ENABLE_INTERRUPTS;            //�������ж�
}


//����0�����жϷ�������
void UART0_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag;
    DISABLE_INTERRUPTS;    //�����ж�
    if(uart_get_re_int(UART_0))
    {
        ch = uart_re1(UART_0, &flag);    //���ý���һ���ֽڵĺ�����������ж�λ
        if(flag)
        {
            uart_send1(UART_0, ch);     //��ԭ���ڷ���һ���ֽ�
        }
    }
    ENABLE_INTERRUPTS;
}


//����1�����жϷ�������
void UART1_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag;
    DISABLE_INTERRUPTS;    //�����ж�
    if(uart_get_re_int(UART_1))
    {
        ch = uart_re1(UART_1, &flag);    //���ý���һ���ֽڵĺ�����������ж�λ
        if(flag)
        {
            uart_send1(UART_1, ch);      //��ԭ���ڷ���һ���ֽ�
        }
    }
    ENABLE_INTERRUPTS;
}

//����2�����жϷ�������
void UART2_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag;
    DISABLE_INTERRUPTS;    //�����ж�
    if(uart_get_re_int(UART_2))
    {
        ch = uart_re1(UART_2, &flag);    //���ý���һ���ֽڵĺ�����������ж�λ
        if(flag)
        {
            uart_send1(UART_2, ch);     //��ԭ���ڷ���һ���ֽ�
        }
    }
    ENABLE_INTERRUPTS;
}

