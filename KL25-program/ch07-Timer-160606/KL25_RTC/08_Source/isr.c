//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"
    
//=============================�жϺ�����������==============================
//==========================================================================
//�������ƣ�RTC_IRQHandler
//�������أ���
//����˵������
//���ܸ�Ҫ��RTC�жϷ������̡��������Ч�жϼ�����жϣ����жϱ�־����λ
//������������Ǳ����жϣ���λ����ֵ
//���þ�������
//==========================================================================
void RTC_IRQHandler(void)
{
    if(RTC_GET_INVALID_FLAG)
    {
        printf("\r\n����RTC��ʱ��Ч�жϣ�ԭ��POR�������λ�ɵ���RTC��������Ч��");
        RTC_CLEAR_FLAG;
    }
    else if(RTC_GET_OVERFLOW_FLAG)
    {
        printf("\r\n����RTC��ʱ����жϣ�ԭ�����������ֵ��0xFFFFFFFF��һ��");
        RTC_CLEAR_FLAG;
    }
    else if(RTC_GET_ALAM_FLAG)
    {
        printf("\r\n����RTC�����жϣ�ԭ�����������ֵ���ڱ���ֵ��");
        rtc_reset_alarm_time(AlarmTimes = AlarmTimes + 1);
    }
    else
    {
        printf("\r\nRTC���ж��¼�������ԭ��POR�������λ���ж��źż���Ч��");
    }
}

//======================================================================
//�������ƣ�RTC_Seconds_IRQHandler
//�������أ���
//����˵������
//���ܸ�Ҫ��RTC���жϷ������̡�����ۼƼ�ʱ��������ʾMCU����ʱ�䡣���������жϣ�
//ÿ�����һ�Σ�����״̬λ����
//���þ�������
//======================================================================
void RTC_Seconds_IRQHandler(void)
{
    SecAdd1(g_time);        //g_time��ʱ����ȫ�ֱ�������
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
            uart_send1(UART_0, ch);      //��ԭ���ڷ���һ���ֽ�
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
            uart_send1(UART_2, ch);      //��ԭ���ڷ���һ���ֽ�
        }
    }
    ENABLE_INTERRUPTS;
}
