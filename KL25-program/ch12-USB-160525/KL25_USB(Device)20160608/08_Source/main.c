//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�

//USB���к�
//ע�⣺�޸�USB���к�ʱ��Ҫ���豸���ĵ�һ���ֽ����ݳ����ֶν����޸�
uint_8 Serial_String[]=
{
    0x10,      //�豸�������ֶ�(�������ֶα�����)
    0x03,      //�豸������
    //�������û��Զ����豸��
    'H',0x00,
    'W',0x00,
    'W',0x00,
    '_',0x00,
    'U',0x00,
    'S',0x00,
    'B',0x00,
};

int main(void)
{
    uint_32  mRuncount;     //��ѭ��������
    //uint_16  recv_bytes;
    uint_8 i;
    //2. �����ж�
    DISABLE_INTERRUPTS;
    //3. ��ʼ������ģ��
    light_init(RUN_LIGHT_BLUE, LIGHT_ON);       //���Ƴ�ʼ��
    usb_init(Serial_String);  //USB�豸��ʼ��
    //4. ���йر�������ֵ
    mRuncount=0;            //��ѭ��������
    g_USBRecvLength=0;      //USB�������ݳ��ȳ�ʼ��
    g_USBSendLength=0;      //USB�������ݳ��ȳ�ʼ��
    g_USBSendFlag=0;        //USBִ�з��ͱ�־��ʼ��
    //recv_bytes=0;
    //5. ʹ��ģ���ж�
    //6. �����ж�
    ENABLE_INTERRUPTS;
    //������ѭ��
    //��ѭ����ʼ==================================================================
    for(;;)
    {
        //����ָʾ�ƣ�RUN_LIGHT����˸---------------------------------------------
        mRuncount++;                       //��ѭ������������+1
        if (mRuncount >= RUN_COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
        {
            mRuncount=0;                   //��ѭ����������������
            light_change(RUN_LIGHT_BLUE);  //��ɫ����ָʾ�ƣ�RUN_LIGHT_BLUE��״̬�仯
        }
        //���¼����û�����--------------------------------------------------------
        //USB������USB�豸����Ҫ��������
        if(g_USBRecv[0]==cmdINTESTDATA && g_USBSendLength!=0)
        {
            g_USBRecv[0]=cmdNULL;
            g_USBSend[0]=cmdINTESTDATA;
            g_USBSendFlag=1;
        }
        //USB�����������ݣ�д�뵽���������У��Ա�����Ҫ����ʱ���з���
        else if(g_USBRecv[0]==cmdOUTTESTDATA && g_USBRecvLength!=0)
        {
            //��ֹUSB�ж�
            disable_irq(USB_INTERRUPT_IRQ);
            for(i=0;i<g_USBRecvLength;i++)
                g_USBSend[i]=g_USBRecv[i];
            g_USBSendLength=g_USBRecvLength;
            g_USBRecv[0]=cmdNULL;
            g_USBRecvLength=0;
            //ʹ��USB�ж�
            enable_irq(USB_INTERRUPT_IRQ);
        }

    }//��ѭ��end_for
    //��ѭ������==================================================================
}

