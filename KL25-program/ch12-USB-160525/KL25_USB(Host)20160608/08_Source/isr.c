//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================�жϺ�����������===============================

//����1�����жϷ�������
void UART1_IRQHandler(void)
{
    uint_8 ch;
    uint_8 flag = 1;
    __disable_irq();    //�����ж�

    ch = uart_re1(UART_1, &flag);
    if (0 == flag)
    {
        uart_send1(UART_1, ch);
    }
    __enable_irq();     //�����ж�
}

extern uint_8 USBFlag;
//============================================================================
//������: USB0_IRQHandler
//��  ��: USB�ж�
//��  ��: ��
//��  ��: ��
//============================================================================
void USB0_IRQHandler(void)
{
    uint_8 status;

    while (1)
    {
        status = (uint_8)(USB0_ISTAT & USB0_INTEN);

        if (!status)  //û��USB�жϣ�������
            break;

        USB0_ISTAT = status;

        if (status & USB_ISTAT_ATTACH_MASK)  //������ATTACH�ж�
        {

            USB0_INTEN &= ~USB_INTEN_ATTACHEN_MASK; //���ж�λ
            USB0_INTEN |= USB_ISTAT_USBRST_MASK;
            USB0_INTEN |= USB_ISTAT_TOKDNE_MASK;

            USBFlag |= USB_ISTAT_ATTACH_MASK;
        }

        if (status & USB_ISTAT_TOKDNE_MASK)   //��������������ж�
        {
            USBFlag |= USB_ISTAT_TOKDNE_MASK;
        }

        if (status & USB_ISTAT_USBRST_MASK)   //�����˸�λ�ж�
        {
            USBFlag |= USB_ISTAT_USBRST_MASK; //w1c
        }

    };
}
