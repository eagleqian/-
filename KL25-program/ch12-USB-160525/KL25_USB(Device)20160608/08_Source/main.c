//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件

//USB序列号
//注意：修改USB序列号时，要将设备名的第一个字节数据长度字段进行修改
uint_8 Serial_String[]=
{
    0x10,      //设备名长度字段(包含该字段本身长度)
    0x03,      //设备名索引
    //以下是用户自定义设备名
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
    uint_32  mRuncount;     //主循环计数器
    //uint_16  recv_bytes;
    uint_8 i;
    //2. 关总中断
    DISABLE_INTERRUPTS;
    //3. 初始化外设模块
    light_init(RUN_LIGHT_BLUE, LIGHT_ON);       //蓝灯初始化
    usb_init(Serial_String);  //USB设备初始化
    //4. 给有关变量赋初值
    mRuncount=0;            //主循环计数器
    g_USBRecvLength=0;      //USB接收数据长度初始化
    g_USBSendLength=0;      //USB发送数据长度初始化
    g_USBSendFlag=0;        //USB执行发送标志初始化
    //recv_bytes=0;
    //5. 使能模块中断
    //6. 开总中断
    ENABLE_INTERRUPTS;
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
        //以下加入用户程序--------------------------------------------------------
        //USB主机向USB设备发送要数据命令
        if(g_USBRecv[0]==cmdINTESTDATA && g_USBSendLength!=0)
        {
            g_USBRecv[0]=cmdNULL;
            g_USBSend[0]=cmdINTESTDATA;
            g_USBSendFlag=1;
        }
        //USB主机发送数据，写入到发送数组中，以便主机要数据时进行发送
        else if(g_USBRecv[0]==cmdOUTTESTDATA && g_USBRecvLength!=0)
        {
            //禁止USB中断
            disable_irq(USB_INTERRUPT_IRQ);
            for(i=0;i<g_USBRecvLength;i++)
                g_USBSend[i]=g_USBRecv[i];
            g_USBSendLength=g_USBRecvLength;
            g_USBRecv[0]=cmdNULL;
            g_USBRecvLength=0;
            //使能USB中断
            enable_irq(USB_INTERRUPT_IRQ);
        }

    }//主循环end_for
    //主循环结束==================================================================
}

