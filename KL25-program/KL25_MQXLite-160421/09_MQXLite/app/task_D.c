#include "app_inc.h"    //Ӧ�����񹫹�ͷ�ļ�

//===========================================================================
//�������ƣ�task_E
//���ܸ�Ҫ��������2�жϽ��յ���������֡������PC��
//����˵����δʹ��
//��       ע��ʹ��ȫ�ֱ���lwevent_group1, UART2_RecData_Event,g_UART_ISR_buffer
//===========================================================================
void task_D (uint32_t initial_data )
{ 
    int itemp;
    //������ѭ��
    while (TRUE)
    {    
        //�ȴ�����2������������֡�¼�λ��Event_UART2_ReData��
        _lwevent_wait_ticks(&lwevent_group1, Event_UART2_ReData, FALSE, 0);
        g_UART_FrameCount++;         //���յ�֡����1       

        printf("����2���յ���������֡��(--0x%02X--)",g_UART_FrameCount);
        
        //����֡����
        for(itemp=0;itemp<g_UART_ISR_buffer[1]+3;itemp++)
        {
            printf("%x",g_UART_ISR_buffer[itemp]);
        }
        printf("\r\n");
        //�������2������������֡�¼�λ��Event_UART2_ReData��
        _lwevent_clear(&lwevent_group1, Event_UART2_ReData);
    }
}


