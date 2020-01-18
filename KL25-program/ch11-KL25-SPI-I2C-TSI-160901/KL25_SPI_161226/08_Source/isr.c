//=====================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//       2016-05-11   V3.0
//=====================================================================
#include "includes.h"

//========================�жϺ�����������=================================
//=====================================================================
//������: UART1_IRQHandler
//��  ��: ����1�����жϷ�������
//��  ��: ��
//��  ��: ��
//˵  ��: ��Ҫ�����жϲ�ע��ſ�ʹ��
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

//=====================================================================
//������: SPI1_IRQHandler
//��  ��: SPI1�����жϷ������
//��  ��: ��
//��  ��: ��
//˵  ��: ��Ҫ�����жϲ�ע��ſ�ʹ��
//=====================================================================
void SPI1_IRQHandler(void)
{
    uint_8 redata;
    DISABLE_INTERRUPTS;
    redata=SPI_receive1(SPI_1);    //�����������͹�����һ���ֽ����ݡ�
    if(redata!='0')
    {
    	uart_send1(UART_2,redata);
    	redata++;
    	SPI_send1(SPI_1,redata);
    }
    ENABLE_INTERRUPTS;
}

