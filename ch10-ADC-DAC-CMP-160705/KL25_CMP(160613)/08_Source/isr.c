//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================�жϺ�����������===============================
//����0�����жϷ�������
void UART0_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_0, &flag);
    if (0 == flag)
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
    if (0 == flag)
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
    if (0 == flag)
    {
        uart_send1(UART_2, ch);
    }
        
    ENABLE_INTERRUPTS;
}

//===========================================================================
//������: CMP0_IRQHandler
//��  ��: �Ƚ�������������½����жϴ���
//˵  ��: ��
//===========================================================================
//�Ƚ����жϴ�����
void CMP0_IRQHandler(void)
{
    //�����������
    if ((CMP0_SCR & CMP_SCR_CFR_MASK)==CMP_SCR_CFR_MASK)
    {
        CMP0_SCR |= CMP_SCR_CFR_MASK;  // ���־
        uart_send_string(UART_1, "\r\nRising edge on HSCMP0\r\n");
    }
    //������½���
    if ( (CMP0_SCR & CMP_SCR_CFF_MASK) == CMP_SCR_CFF_MASK)
    {
        CMP0_SCR |= CMP_SCR_CFF_MASK;  // ���־
        uart_send_string(UART_1, "\r\nFalling edge on HSCMP0\r\n");
    }
}

