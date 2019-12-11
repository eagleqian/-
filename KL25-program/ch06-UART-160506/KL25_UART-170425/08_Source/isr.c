//=====================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//         2016-03-27 V2.0(XD)
//=====================================================================
#include "includes.h"

//========================�жϺ�����������===============================
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
            uart_send1(UART_1, ch);     //��ԭ���ڷ���һ���ֽ�
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
            ch=ch+2;
        	uart_send1(UART_2, ch);     //��ԭ���ڷ���һ���ֽ�
        }
    }
    ENABLE_INTERRUPTS;
}

