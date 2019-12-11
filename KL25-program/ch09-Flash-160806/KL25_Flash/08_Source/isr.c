//======================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//======================================================================
#include "includes.h"

//�ڲ���������
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//========================�жϺ�����������===============================
//����0�����жϷ�������
void UART0_IRQHandler(void)
{
    uint_8 flag;
    uint_8 i;
    
    DISABLE_INTERRUPTS;
    
    i = uart_re1(UART_0, &flag);
    if (0 == flag)
    {
        uart_send1(UART_0, i);
    }
    
    ENABLE_INTERRUPTS;
}


//����1�����жϷ�������
void UART1_IRQHandler(void)
{

    uint_8 flag;
    uint_8 i;
    
    DISABLE_INTERRUPTS;
    
    i = uart_re1(UART_1, &flag);
    if (0 == flag)
    {
        uart_send1(UART_1, i);
    }
 
    ENABLE_INTERRUPTS;
}

//======================================================================
//�������ƣ�isr_uart2_re
//����˵����user_isr_ptr���û��Զ���������˴�δ��
//���ܸ�Ҫ��UART_2������2���жϷ�������
//======================================================================
void UART2_IRQHandler(void)
{
    uint_8 i,flag;
    DISABLE_INTERRUPTS;                //�����ж�
    //-----------------------------------------------------------------------

    i=uart_re1(UART_2, &flag);             //����һ���ֽ�
    //�����ڲ�����CreateFrame������֡
    if(CreateFrame(i,g_uart_recvBuf)!=0)    //��֡�ɹ�
    {
        //g_uart_recvBuf[2]�������ֽ�
        if(g_uart_recvBuf[2] == 'C')    //��������
        {
            g_uart_sentBuf[0]=(uint_8)'M';     //
            g_uart_sentBuf[1]=5;               //
            g_uart_sentBuf[2]  = (uint_8)'C';  //
            g_uart_sentBuf[3]  = (uint_8)'K';  //"PCNode"
            g_uart_sentBuf[4]  = (uint_8)'L';
            g_uart_sentBuf[5]  = (uint_8)'2';
            g_uart_sentBuf[6]  = (uint_8)'5';
            g_uart_sentBuf[7]  = (uint_8)'U';  //
            uart_sendN(UART_2,8,&g_uart_sentBuf[0]);
            framestate=1;//��������֡
        }
        //
        else   //�������,�á�����0������������֡�¼�λ(EVENT_UART0_RE)��,����task_uart0_re������
        {
            framestate=0;//����������֡
        }
    }

    //-----------------------------------------------------------------------
    ENABLE_INTERRUPTS;                //�����ж�
}


//�ڲ����ú���

//======================================================================
//ISR���ƣ�Createbuffer
//���ܸ�Ҫ���齨����֡��������֡���ݼ��뵽����֡��
//����˵����Data��                            ����֡����
//          buffer:        ����֡����
//�������أ���֡״̬    0-��֡δ�ɹ���1-��֡�ɹ�
//��ע��ʮ����������֡��ʽ
//               ֡ͷ        + ���ݳ���          + ��Ч����    +  ֡β
//        FrameHead   +   len   + ��Ч����    + FrameTail
//======================================================================

#define FrameHead    (0x50)         //֡ͷ
#define FrameTail    (0x43)         //֡β
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
    static uint8_t frameLen=0;    //��֡������
    uint8_t frameFlag;              //��֡״̬
    frameFlag=0;            //��֡״̬ ��ʼ��
    //���ݾ�̬����frameCount��֡
    switch(frameLen)
    {
        case 0:    //��һ������
        {
            if (Data==FrameHead)    //�յ�������֡ͷFrameHead
            {
                buffer[0]=Data;
                frameLen++;
                frameFlag=0;        //��֡��ʼ
            }
            break;
        }
        case 1:    //�ڶ������ݣ��������������յ����ݸ���
        {
            buffer[1]=Data;
            frameLen++;
            break;
        }
        default:    //�������
        {
            //�ڶ�λ��������Ч���ݳ���,�������������µ�����ֱ��֡βǰһλ
            if(frameLen>=2 && frameLen<=(buffer[1] + 1))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //����ĩβ������ִ��
            if(frameLen>=(buffer[1]+2))
            {
                if (Data==FrameTail)    //����֡β
                {
                    buffer[frameLen]=Data;     //��֡β���뻺����
                    frameFlag=1;    //��֡�ɹ�
                }
                frameLen=0;     //������0��׼��������֡
                break;
            }
        }
    }     //switch_END
    return frameFlag;                 //������֡״̬
}

