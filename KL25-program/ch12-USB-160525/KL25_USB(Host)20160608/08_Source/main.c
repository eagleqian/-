//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�

//USB���ȫ�ֱ�������
uint_8 USBHostStatus = USB_DEVICE_IDLE;  //USB�豸״̬
uint_8 USBFlag = 0;
uint_8 UartBuff[128] = {0};
uint_8 UartBuffLength = 0;
uint_8 UartBuffFull = 0;
uint_8 DeviceInserted = 0;
struct znFAT_Init_Args Init_Args;
struct FileInfo fileinfo1,fileinfo2;
const char Text[]="KL25 USB Mass Storage Host Controller. Date: 2016.04.16";
uint_8 Device_INF[32];

int main(void)
{
    //1. ����������ʹ�õı���
    uint_32  mRuncount;     //��ѭ��������
    uint_32  Count = 1;
    uint_8 buf[14];
    uint_8 i;
    uint_8 err;
    //2. �����ж�
    DISABLE_INTERRUPTS;

    //3. ��ʼ������ģ��
    light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //���Ƴ�ʼ��
    uart_init(UART_1, 9600);               //ʹ�ܴ���1��������Ϊ9600
    USBHostInit();                         //USB������ʼ��
    printf("----------------------USB��������!----------------\r\n");
    //4. ���йر�������ֵ
    mRuncount=0;            //��ѭ��������
    for(i=0; i<13; i++)
        buf[13]=0;
    buf[12]='\0';
    //5. ʹ��ģ���ж�
    uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
    //6. �����ж�
    ENABLE_INTERRUPTS;
    printf("System started, Please insert your USB MSD!\r\n");
    //��ʼ������USB�豸
    if(InitUSBDevice(Device_INF) == 0)
            USBHostStatus = USB_DEVICE_IDLE;   //û���豸����
        else
        {
            USBHostStatus = USB_DEVICE_CONNETED;   //�豸����
            Count = 1;
            printf("Device connection detected.\r\n");
            printf("Mass-storage driver started.\r\n");
            printf("USB MSD information: %s\r\n",Device_INF);
        }

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

        if(Count > 1000000)
        {
            Count = 0;
            if(USBHostStatus == USB_DEVICE_CONNETED)
            {
                znFAT_Device_Init();
                znFAT_Select_Device(0,&Init_Args);
                err=znFAT_Init();   //znFAT��ʼ��
                if(err)
                {
                    DeviceInserted = 0;
                    printf("\r\nFile system init failed!\r\n");
                    while(1);
                }
                printf("\r\nFile system init ok!\r\n");
                DeviceInserted = 1;   //���ӵ�USB�豸��Ŀ
            }
        }
        if(Count)
        {
            Count++;
        }

        if(DeviceInserted == 1)
        {
            err= znFAT_Open_File(&fileinfo1,"/suda.txt",0,1);
            znFAT_ReadData(&fileinfo1,0,13,buf);
            printf("Read File OK!\n");
            printf("Udisk Data:%s\n",buf);
            znFAT_Close_File(&fileinfo1);
            printf("Close File OK!\r\n");
            znFAT_Flush_FS();    //ˢ���ļ�ϵͳ
            DeviceInserted=0;
        }
        if(USBFlag & USB_ISTAT_USBRST_MASK)
        {
            USBFlag &= ~USB_ISTAT_USBRST_MASK;
            if(CheckUSBDeviceStatus() == 1)
            {

            }
            else
            {
                if(USBHostStatus == USB_DEVICE_CONNETED)
                {
                    DeviceInserted = 0;
                    printf("Device removed.\r\n");
                    USBHostStatus = USB_DEVICE_DETACHED;
                    USBHostInit();
                }
            }
        }
        if(USBFlag & USB_ISTAT_ATTACH_MASK)
        {
            USBHostStatus &= ~USB_DEVICE_ATTACHED;
            if(InitUSBDevice(Device_INF) == 0)
            {
                USBHostStatus = USB_DEVICE_IDLE;
            }
            else
            {
                USBHostStatus = USB_DEVICE_CONNETED;
                Count = 1;
            }
        }
        //���¼����û�����--------------------------------------------------------
    }//��ѭ��end_for
    //��ѭ������==================================================================
}


