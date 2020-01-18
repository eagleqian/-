//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件

//USB相关全局变量定义
uint_8 USBHostStatus = USB_DEVICE_IDLE;  //USB设备状态
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
    //1. 声明主函数使用的变量
    uint_32  mRuncount;     //主循环计数器
    uint_32  Count = 1;
    uint_8 buf[14];
    uint_8 i;
    uint_8 err;
    //2. 关总中断
    DISABLE_INTERRUPTS;

    //3. 初始化外设模块
    light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
    uart_init(UART_1, 9600);               //使能串口1，波特率为9600
    USBHostInit();                         //USB主机初始化
    printf("----------------------USB主机测试!----------------\r\n");
    //4. 给有关变量赋初值
    mRuncount=0;            //主循环计数器
    for(i=0; i<13; i++)
        buf[13]=0;
    buf[12]='\0';
    //5. 使能模块中断
    uart_enable_re_int(UART_1);   //使能串口1接收中断
    //6. 开总中断
    ENABLE_INTERRUPTS;
    printf("System started, Please insert your USB MSD!\r\n");
    //初始化接入USB设备
    if(InitUSBDevice(Device_INF) == 0)
            USBHostStatus = USB_DEVICE_IDLE;   //没有设备连接
        else
        {
            USBHostStatus = USB_DEVICE_CONNETED;   //设备连接
            Count = 1;
            printf("Device connection detected.\r\n");
            printf("Mass-storage driver started.\r\n");
            printf("USB MSD information: %s\r\n",Device_INF);
        }

    //进入主循环
    //主循环开始==================================================================
    for(;;)
    {
        //运行指示灯（RUN_LIGHT）闪烁---------------------------------------------
        mRuncount++;                       //主循环次数计数器+1
        if (mRuncount >= RUN_COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
        {
            mRuncount=0;                   //主循环次数计数器清零
            light_change(RUN_LIGHT_BLUE);  //蓝色运行指示灯（RUN_LIGHT_BLUE）状态变化
        }

        if(Count > 1000000)
        {
            Count = 0;
            if(USBHostStatus == USB_DEVICE_CONNETED)
            {
                znFAT_Device_Init();
                znFAT_Select_Device(0,&Init_Args);
                err=znFAT_Init();   //znFAT初始化
                if(err)
                {
                    DeviceInserted = 0;
                    printf("\r\nFile system init failed!\r\n");
                    while(1);
                }
                printf("\r\nFile system init ok!\r\n");
                DeviceInserted = 1;   //连接的USB设备数目
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
            znFAT_Flush_FS();    //刷新文件系统
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
        //以下加入用户程序--------------------------------------------------------
    }//主循环end_for
    //主循环结束==================================================================
}


