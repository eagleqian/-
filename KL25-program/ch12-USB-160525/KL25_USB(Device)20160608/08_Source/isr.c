//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"

extern void usb_isr_handler(uint_8 isr_type);
extern uint_8  usb_get_isr();
extern uint_8 vEP2State;
extern tBDT *BDTtable;

//========================�жϺ�����������===============================

//=====================================================================
//�������ƣ�USB0_IRQHandler��USB�жϷ������̣�
//�������ܣ�����USBģ���жϣ����������շ����豸ö�ٵ�ԭ�򴥷����ж�����
//        ���շ�����ʱ����ͨ����ȫ�ֱ����Ĳ�����ɣ����跢�����ݣ���Ԥ�Ƚ�
//        ����������д��ȫ�ֱ���g_USBSend���䳤��д��g_USBSendLength������
//        ���ͱ�־g_USBSendFlagΪ1���жϻ��Զ������ݷ�����ͬʱ�жϻ��Զ�����
//        �������������ݣ������ݷ���ȫ�ֱ���g_USBRecv�������������ݳ���д��
//        ȫ�ֱ���g_USBRecvLength
//=====================================================================

void USB0_IRQHandler(void)
{
    uint_8 isr_type;
    DISABLE_INTERRUPTS;    //�����ж�
    //1. ��ȡ�ж�����
    isr_type=usb_get_isr();
    //2. ��������������жϣ�������Ӧ�������
    if(isr_type!=USB_TOKDNE_INT)
    {
        usb_isr_handler(isr_type);    //���÷���������жϵĴ������
        goto USB0_IRQ_exit;
    }
    //3. ����������жϣ�ִ�п����ݴ�����豸ö��
    //(3.1)���շ�ODD������ָ��EVEN��
    FLAG_SET(USB_CTL_ODDRST_SHIFT,USB0_CTL);
    //(3.2)�����豸ö�����󣬽����豸ö��
    if((USB0_STAT >> 4)==0)
    {
        usb_enumerate();
        goto USB0_IRQ_exit;
    }
    //(3.3)�������豸ö�����󣬽��������շ�����
    if((USB0_STAT & 0xF8)==mEP2_IN)//�Ӷ˵�2��������������
    {
        //��ִ�з��ͱ�־����1����ִ�з������ݺ���
        if(g_USBSendFlag==1)
        {
            usb_send(g_USBSend,&g_USBSendLength);//���÷������ݴ�����
            if(g_USBSendLength==0)
            {
                g_USBSendFlag=0;    //������ɣ�ִ�з��ͱ�־��0
            }
            goto USB0_IRQ_exit;
        }
        //����������Ҫ���ͣ�����USB��������һ��ȷ�ϰ�
        BDTtable[bEP2IN_ODD].Cnt =0;
        vEP2State ^= 0x40;
        BDTtable[bEP2IN_ODD].Stat._byte= vEP2State;
    }
    else if((USB0_STAT & 0xF8)==mEP3_OUT)//�Ӷ˵�3������������������
    {
        usb_recv(g_USBRecv,&g_USBRecvLength);
    }
USB0_IRQ_exit:
    //4. ����жϱ�־�������жϴ���
    FLAG_SET(USB_ISTAT_TOKDNE_SHIFT,USB0_ISTAT);
    ENABLE_INTERRUPTS;    //�����ж�
    return;
}

//=====================================================================
