//=========================================================================
// 文件名称：usb.c                                                          
// 功能概要：usb底层驱动构件源文件
// 版权所有: 苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
// 版本更新: 2012-12-14     V1.0        USB构件初始版本
//           2012-12-20     V1.2        USB构件优化修改
//=========================================================================
#include "usb.h"

//设备描述符
static  uint_8 Device_Descriptor[18]=
{
     0x12,       //bLength域，描述符的长度：18字节
    0x01,       //bDescriptorType域，描述符类型：0x01表示本描述符为设备描述符）
    0x00,0x02, //bcdUSB域，USB规范版本号（采用BCD码）：2.0
    0x02,       //bDeviceClass域，设备类代码
    0x00,       //bDeviceSubClass域，设备子类代码
    0x00,       //bDeviceProtocol域，设备协议代码（0x00表示不使用任何设备类协议）
    0x20,       //bMaxPacketSize0域，端点0支持最大数据包的长度：32字节
    0xA2,0x15, //idVendor域，供应商ID（VID）
    0x0F,0xA5, //idProduct域，产品ID（PID）
    0x00,0x00, //bcdDevice域，设备版本号（采用BCD码）
    0x01,      //iManufacturer域，供应商的字符串描述符索引：1
    0x02,       //iProduct域，产品的字符串描述符索引：2
    0x03,       //iSerialNumber域，设备序号的字符串描述符索引：3
    0x01       //bNumConfigurations域，该USB设备支持的配置数目：1个
};


//配置描述符
static  uint_8 Configuration_Descriptor[0x20]=
{
    //配置描述符
    0x09,            //bLength域，配置描述符的长度：9字节
    0x02,            //bDescriptorType域：0x02表示本描述符为配置描述符
    0x20,0x00,        //wTotalLength域，配置信息的总长度（包括配置、接口和端点）：32字节
    0x01,            //bNumInterfaces域，该配置所支持的接口数（至少一个）：1
    0x01,            //bConfigurationValue域，配置值：1
    0x00,            //iConfiguration域，配置字符串描述符索引：0
    0xC0,            //bmAttibutes域，配置的属性(具有总线供电、自供电及过程唤醒的特性)
                     //位7：1-必须为1；位6：0-自供电；位5：0-不支持远程唤醒
    0x32,            //MaxPower域，设备从总线提取的最大电流以2mA为单位：50*2mA＝100mA

    //接口描述符
    0x09,           //bLength域，接口描述符长度：9字节
    0x04,           //bDescriptorType域：0x04表示本描述符为接口描述符
    0x00,           //bInterfaceNumber域，接口号
    0x00,           //bAlternateSetting域，接口的可替换设置值
    0x02,           //bNumEndpoints域，接口使用的端点数（除端点0）：2
    0xFF,           //bInterfaceClass域，接口所属的USB设备类：0xFF表示供应商自定义
    0xFF,           //bInterfaceSubClass域，接口所属的USB设备子类：0xFF表示供应商自定义
    0xFF,           //bInterfaceProtocol域，接口采用的USB设备类协议：0xFF表示供应商自定义
    0x01,           //iInterface域，接口字符串描述符的索引：1

     //端点OUT描述符
    0x07,           //bLength域，端点描述符长度：7字节
    0x05,           //bDescriptorType域：0x05表示本描述符为端点描述符
    0x82,           //bEndpointAddress域，端点号和传输方向：端点2、IN
    0x02,           //bmAttributes域，端点特性：数据端点、块传输
    0x20,0x00,      //wMaxPacketSize域，端点支持最大数据包长度：32字节
    0x00,           //bInterval域，轮询间隔，以ms为单位。

     //端点IN描述符
    0x07,           //bLength域，端点描述符长度：7字节
    0x05,           //bDescriptorType域：0x05表示本描述符为端点描述符
    0x03,           //bEndpointAddress域，端点号和传输方向：端点3、OUT
    0x02,           //bmAttributes域，端点特性：数据端点、块传输
    0x20,0x00,      //wMaxPacketSize域，端点支持最大数据包长度：32字节
    0x00,           //bInterval域，轮询间隔，以ms为单位。
};

//字符串描述符0
static  uint_8 String_Descriptor0[4] =
{
    0x04,           //bLength域，长度：4字节
    0x03,           //bDescriptorType域，字符串描述符
    0x09,0x04       //wLANDID0域，英语
};

//字符串描述符1
static  uint_8 String_Descriptor1[] =
{
    0x12,            //bLength域，长度：18字节
    0x03,            //bDescriptorType域，字符串描述符
    'S',0x00,        //                                       
    'U',0x00,        //
    'D',0x00,        //
    'A',0x00,        //
    '-',0x00,        //
    'N',0x00,        //
    'X',0x00,        //
    'P',0x00,        //
};     

//字符串描述符2
static  uint_8 String_Descriptor2[] =
{
    0x38,            //bLength域，长度：56字节
    0x03,            //bDescriptorType域，字符串描述符
    'S',0x00,        
    'o',0x00,    
    'o',0x00,    
    'c',0x00,
    'h',0x00,        
    'o',0x00,    
    'w',0x00,
    'U',0x00,       
    'n',0x00,   
    'i',0x00,   
    'v',0x00,
    'e',0x00,       
    'r',0x00,  
    's',0x00,  
    'i',0x00,   
    't',0x00,       
    'y',0x00,   
    '-',0x00,
    'U',0x00,
    'S',0x00,
    'B',0x00,
    'D',0x00,
    'e',0x00,
    'v',0x00,
    'i',0x00,
    'c',0x00,
    'e',0x00,
};     

////设备限定描述符
//static  uint_8 Device_Qualifier[10]=
//{
//        0x0A,
//        0x06,
//        0x00,0x02,
//        0x00,
//        0x00,
//        0x00,
//        0x10,
//        0x01,
//        0x00
//};

uint_8 BDT[1024];   //BDT缓冲区，理论上只要申请512字节
tBDT *BDTtable;     //4个端点的BDT 16个BD
String_Table USB_String_Table;   //USB字符串列表

//定义端点0缓冲区
static uint_8 gu8EP0_OUT_ODD_Buffer[EP0_SIZE];
static uint_8 gu8EP0_OUT_EVEN_Buffer[EP0_SIZE];
static uint_8 gu8EP0_IN_ODD_Buffer[EP0_SIZE];
static uint_8 gu8EP0_IN_EVEN_Buffer[EP0_SIZE];
//定义端点1缓冲区
static uint_8 gu8EP1_OUT_ODD_Buffer[EP1_SIZE];
static uint_8 gu8EP1_OUT_EVEN_Buffer[EP1_SIZE];
static uint_8 gu8EP1_IN_ODD_Buffer[EP1_SIZE];
static uint_8 gu8EP1_IN_EVEN_Buffer[EP1_SIZE];
//定义端点2缓冲区
static uint_8 gu8EP2_OUT_ODD_Buffer[EP2_SIZE];
static uint_8 gu8EP2_OUT_EVEN_Buffer[EP2_SIZE];
static uint_8 gu8EP2_IN_ODD_Buffer[EP2_SIZE];
static uint_8 gu8EP2_IN_EVEN_Buffer[EP2_SIZE];
//定义端点3缓冲区
static uint_8 gu8EP3_OUT_ODD_Buffer[EP3_SIZE];
static uint_8 gu8EP3_OUT_EVEN_Buffer[EP3_SIZE];
static uint_8 gu8EP3_IN_ODD_Buffer[EP3_SIZE];
static uint_8 gu8EP3_IN_EVEN_Buffer[EP3_SIZE];

//定义各端点缓冲区的指针
uint_8 *BD_BufferPointer[]=    //指针数组，指向数组，缓冲区首地址
{
    gu8EP0_OUT_ODD_Buffer,
    gu8EP0_OUT_EVEN_Buffer,
    gu8EP0_IN_ODD_Buffer,
    gu8EP0_IN_EVEN_Buffer,
    gu8EP1_OUT_ODD_Buffer,
    gu8EP1_OUT_EVEN_Buffer,
    gu8EP1_IN_ODD_Buffer,
    gu8EP1_IN_EVEN_Buffer,
    gu8EP2_OUT_ODD_Buffer,
    gu8EP2_OUT_EVEN_Buffer,
    gu8EP2_IN_ODD_Buffer,
    gu8EP2_IN_EVEN_Buffer,
    gu8EP3_OUT_ODD_Buffer,
    gu8EP3_OUT_EVEN_Buffer,
    gu8EP3_IN_ODD_Buffer,
    gu8EP3_IN_EVEN_Buffer
};
//定义端点缓冲区的长度
static const uint_8 cEP_Size[]=
{
    EP0_SIZE,    
    EP0_SIZE,    
    EP0_SIZE,    
    EP0_SIZE,    
    EP1_SIZE,    
    EP1_SIZE,    
    EP1_SIZE,    
    EP1_SIZE,    
    EP2_SIZE,    
    EP2_SIZE,    
    EP2_SIZE,    
    EP2_SIZE,    
    EP3_SIZE,
    EP3_SIZE,
    EP3_SIZE,
    EP3_SIZE
};

//端点IN(2)状态
 uint_8 vEP2State = kUDATA1;  //端点2发送了DATA1，ACK包
//端点OUT(3)状态
 uint_8 vEP3State = kUDATA0;  //端点3接收了DATA0，ACK包


//USB模块内部全局变量
static uint_8 gu8USBClearFlags;     //检查是否可以发送数据的标志    USB复位后 gu8USBClearFlags == 0xFF
static uint_8 *pu8IN_DataPointer;
static uint_8 gu8IN_Counter;
static uint_8 gu8USB_Toogle_flags;  //切换奇、偶发送包   USB复位后 gu8USB_Toogle_flags==0
static uint_8 gu8Dummy;
static uint_8 gu8HALT_EP;     //用来判断端点是否处于停止状态
static uint_8 gu8USB_State;   //USB设备各种状态
static tUSB_Setup *Setup_Pkt; //定义setup数据包的指针


//内部函数声明
void usb_sub_isr(uint_8 isr_type);
uint_8  judge_usb();
void usb_handler(void);
void usb_stall_handler(void);
void usb_reset_handler(void);
static void usb_ep_in_transfer(uint_8 u8EP,uint_8 *pu8DataPointer,uint_8 u8DataSize);
static void usb_set_interface(void);
static void usb_stdReq_handler(void);
static void usb_setup_handler(void);
static void usb_endpoint_setup_handler(void);
static void usb_ep0_in_handler(void);
static void usb_ep0_stall(void);
static void usb_ep0_out_handler(void);

//=========================================================================
//函数名:usb_init
//功  能: USB模块初始
//参  数:str:设备序列号
//返  回: 无
//=========================================================================
void usb_init(uint_8 str[])
{
    //后面加0x200UL，防止占用rom区
    BDTtable = (tBDT *)((( uint_32 ) BDT & 0xFFFFFE00UL)+0x200UL);
    //USB相关字符串初始化
    USB_String_Table.String_Descriptor0=String_Descriptor0;
    USB_String_Table.String_Descriptor1=String_Descriptor1;
    USB_String_Table.String_Descriptor2=String_Descriptor2;
    USB_String_Table.Device_Name=str;
    //将端点0接收奇缓冲区的地址 存储到 setup数据包 的指针对象Setup_Pkt中
    //便于端点0将接收到的PC发来的setup包
    //指向端点0的接收奇缓冲区首地址
    Setup_Pkt=(tUSB_Setup*)BD_BufferPointer[bEP0OUT_ODD];
    gu8USB_State=uPOWER;   //USB设备处于上电状态
    //USB_FMC_ACC_ENABLE;
    USB_REG_SET_ENABLE;
    USB_REG_CLEAR_STDBY;
    //MPU_CESR=0;禁止MPU
    FLAG_SET(SIM_SOPT2_PLLFLLSEL_SHIFT,SIM_SOPT2);  // 使能PLL输出
    FLAG_SET(SIM_SOPT2_USBSRC_SHIFT,SIM_SOPT2);     // 使能PLL/FLL为时钟源
    //SIM_CLKDIV2|=USB_FARCTIONAL_VALUE;   //USB分频因子设置
    SIM_SCGC4|=(SIM_SCGC4_USBOTG_MASK);    //USB模块时钟门使能
    enable_irq(USB_INTERRUPT_IRQ);         //使能USB模块IRQ中断
    //USB模块寄存器配置、 USB0_USBTRC0：收发控制寄存器
    USB0_USBTRC0 |= USB_USBTRC0_USBRESET_MASK;
    //等待USB模块复位发生，发生就退出循环
    while(FLAG_CHK(USB_USBTRC0_USBRESET_SHIFT,USB0_USBTRC0)){};
    //配置BDTPAGE1，2,3 寄存器，设置BDT基址寄存器
    //( 低9位  是默认512 字节的偏移) 512 = 16 * 4 * 8
    //8位表示: 4个字节的控制状态，4 个字节的缓冲区地址
    USB0_BDTPAGE1=(uint_8)((uint_32)BDTtable>>8);
    USB0_BDTPAGE2=(uint_8)((uint_32)BDTtable>>16);
    USB0_BDTPAGE3=(uint_8)((uint_32)BDTtable>>24);
    //清除USB模块复位标志   （之前发生复位会使该位置1）
    //检测到USB复位，置1，通知MPU向地址寄存器写入0x00，
    //并使能端点0
    FLAG_SET(USB_ISTAT_USBRST_SHIFT,USB0_ISTAT);
    //使能USB模块复位中断
    FLAG_SET(USB_INTEN_USBRSTEN_SHIFT,USB0_INTEN);
    USB0_USBCTRL = 0x40;    //USB的SE0信号，两根数据线被拉低
    USB0_USBTRC0 |= 0x40;   //必须：强制设置第6位为1，USB收发控制寄存器
    //上拉使能，这样主机才能识别到设备并对其进行配置
    FLAG_SET(USB_CONTROL_DPPULLUPNONOTG_SHIFT,USB0_CONTROL);
    USB0_CTL |= 0x01;       //USB模块使能位
}
//=========================================================================
//函数名: usb_enumerate
//功  能: USB枚举，用于处理USB设备复位后USB主机发送来的设备请求
//参  数：无
//返  回: 无
//=========================================================================
void usb_enumerate()
{
    uint_8 u8IN;
    u8IN=USB0_STAT & 0x08;      //u8IN表示端点0，最后更改的BD位于BDT的偶数行
    //上行传输
    if(u8IN)
       usb_ep0_in_handler();
    //下行传输
    else
    {
        //接收到 0x0D，表示是SETUP包
        if(BDTtable[bEP0OUT_ODD].Stat.RecPid.PID == mSETUP_TOKEN)
            usb_setup_handler();
        else
            usb_ep0_out_handler();
    }
}

//=========================================================================
//函数名: usb_send
//功  能: USB发送数据
//参  数: buf：待发数据缓冲区，并在函数返回时保留未发送的数据
//      len：待发数据长度,并在函数返回时带出剩余未发送的数据长度
//返  回: 实际发送的数据长度
//备  注：一次性传输的数据长度是端点所支持的最大数据长度（32字节），如果发送的数据长度
//      大于32字节，则分为多次传输。
//=========================================================================
uint_8 usb_send(uint_8 *buf,uint_8 *len)
{
    uint_16 i,counter;
    uint_8 *pBuffer;
    uint_32 vEP2Idx = 0;
    pBuffer = gu8EP2_IN_ODD_Buffer;
    //判断发送的数据长度是否大于端点所支持的最大数据长度
    if(*len > EP2_SIZE)
      counter = EP2_SIZE;
    else
      counter = *len;

    for(i=0; i<counter; i++, vEP2Idx++)
      //将待发送数据拷贝到对应端点发送缓冲区
      pBuffer[i] = buf[vEP2Idx];

    BDTtable[bEP2IN_ODD].Cnt = counter;
    //异或 同0异1  vEP2State = kUDATA0  0x88
    vEP2State ^= 0x40;
    //表示USB拥有操控权，接收了DATA0包，当前作为ACK握手包
    BDTtable[bEP2IN_ODD].Stat._byte= vEP2State;

    //将未处理的数据存放到待发缓冲区
    *len = *len - counter;
    for(i = 0;i <(*len);i++)
    {
        buf[i] = buf[i + counter];
    }

    //延时一会等待数据发送完成
    for(i=0;i<5000;i++);

    if(counter)
        return counter;
    else
        return 0;
}

//=========================================================================
//函数名: usb_recv
//功  能: USB接收数据
//参  数: buf:接收数据缓冲区
//      len:函数返回时，带出接收的数据长度
//返  回: 成功：返回接收数据的长度；失败：返回0
//=========================================================================
uint_8 usb_recv(uint_8 *buf,uint_8 *len)
{
    uint_8 i;
    uint_8 *pBuffer;
    *len=0;
    pBuffer = gu8EP3_OUT_ODD_Buffer;
    //接收到数据后，BD的BC字段是接收到数据的长度
    if(BDTtable[bEP3OUT_ODD].Cnt != 0)
    {
        for(i = 0;i < BDTtable[bEP3OUT_ODD].Cnt;i++)
        {
            //将对应端点接收缓冲区数据拷贝到接收数据区
            buf[(*len)] = pBuffer[i];
            (*len)+=1;
        }
    }
    //异或 同0异1  vEP2State = kUDATA1  0xC8
    vEP3State ^=0x40;
    //表示USB拥有操控权，接收了DATA1包，作为ACK握手包
    BDTtable[bEP3OUT_ODD].Stat._byte=vEP3State;
    BDTtable[bEP3OUT_ODD].Cnt = EP3_SIZE;
    if(*len>0)  //接收数据成功
        return (uint_8)*len;
    else
        return 0;

}

//=============================内部函数实现-==================================
//=========================================================================
//函数名:usb_isr_handler
//功  能: 处理非令牌完成中断
//参  数: isr_type：USB中断类型
//返  回: 无
//=========================================================================
void usb_isr_handler(uint_8 isr_type)
{
    switch(isr_type)
    {
        //复位中断
        case USB_RST_INT:
            //复位中断处理函数
            usb_reset_handler();
        break;
        //SOF中断
        case USB_SOF_INT:
            USB0_ISTAT = USB_ISTAT_SOFTOK_MASK;
        break;
        //STALL中断
        case USB_STALL_INT:
            //STALL中断处理函数
            usb_stall_handler();
        break;
        //SLEEP中断
        case USB_SLEEP_INT:
            //清SLEEP标志
            FLAG_SET(USB_ISTAT_SLEEP_SHIFT,USB0_ISTAT);
        break;
        //ERROR中断
        case USB_ERROR_INT:
            //清错误标志
            FLAG_SET(USB_ISTAT_ERROR_SHIFT,USB0_ISTAT);
    }
}


//=========================================================================
//函数名: usb_get_isr
//功  能: 获取USB中断的类型
//参  数：无
//返  回: 0：令牌中断
//      1：复位中断
//      2:SOF中断
//      3:STALL中断
//      4:SLEEP中断
//      5:ERROR中断
//=========================================================================
uint_8  usb_get_isr()
{
    // 令牌完成中断（ USB_ISTAT_TOKDNE在令牌完成后被置1）
    if(FLAG_CHK(USB_ISTAT_TOKDNE_SHIFT,USB0_ISTAT))
        return USB_TOKDNE_INT;
    //检测USB模块是否解析到有效的复位
    else if(FLAG_CHK(USB_ISTAT_USBRST_SHIFT,USB0_ISTAT))
        return USB_RST_INT;
    //USB模块收到SOF包
    else if(FLAG_CHK(USB_ISTAT_SOFTOK_SHIFT,USB0_ISTAT))
        return USB_SOF_INT;
    // 检测STALL
    else if(FLAG_CHK(USB_ISTAT_STALL_SHIFT,USB0_ISTAT))
        return USB_STALL_INT;
    // SLEEP
    else if(FLAG_CHK(USB_ISTAT_SLEEP_SHIFT,USB0_ISTAT))
        return USB_SLEEP_INT;
    //ERROR中断，检测到错误
    else
        return USB_ERROR_INT;
}


//=========================================================================
//函数名:usb_stall_handler
//功  能: 处理stall中断
//参  数: 无
//返  回: 无
//=========================================================================
void usb_stall_handler(void)
{
    if(FLAG_CHK(USB_ENDPT_EPSTALL_SHIFT,USB0_ENDPT0))
    {
        FLAG_CLR(USB_ENDPT_EPSTALL_SHIFT,USB0_ENDPT0);
    }
    FLAG_SET(USB_ISTAT_STALL_SHIFT,USB0_ISTAT);
}


//=========================================================================
//函数名:usb_reset_handler
//功  能: USB复位中断服务例程，用于设置软件标志位，禁用所有端点寄存器，同时将EP0初始化为控制端点
//      并将EP0的输入输出 奇偶缓冲区进行初始化，开启USB令牌中断、USB第一帧传输中断、USB错误
//      中断,USB复位中断。    当USB复位完成后，USB通信将启动.
//参  数: 无
//返  回: 无
//=========================================================================
 void usb_reset_handler(void)
{      
    //清标志
    gu8USBClearFlags=0xFF;
    gu8USB_Toogle_flags=0;

    //禁止所有端点    EPRXEN 和 EPTXEN 均为0 禁用
    USB0_ENDPT1=0x00;
    USB0_ENDPT2=0x00;
    USB0_ENDPT3=0x00;
    USB0_ENDPT4=0x00;
    USB0_ENDPT5=0x00;
    USB0_ENDPT6=0x00;

    // EP0 BDT Setup
    // EP0 OUT BDT 设置
    BDTtable[bEP0OUT_ODD].Cnt = EP0_SIZE;
    BDTtable[bEP0OUT_ODD].Addr =(uint_32)gu8EP0_OUT_ODD_Buffer;
    BDTtable[bEP0OUT_ODD].Stat._byte = kUDATA1;
    // EP0 OUT BDT 设置
    BDTtable[bEP0OUT_EVEN].Cnt = EP0_SIZE;
    BDTtable[bEP0OUT_EVEN].Addr =(uint_32)gu8EP0_OUT_EVEN_Buffer;
    BDTtable[bEP0OUT_EVEN].Stat._byte = kUDATA1;
    // EP0 IN BDT 设置 
    BDTtable[bEP0IN_ODD].Cnt = EP0_SIZE;
    BDTtable[bEP0IN_ODD].Addr =(uint_32)gu8EP0_IN_ODD_Buffer;
    BDTtable[bEP0IN_ODD].Stat._byte = kUDATA0;
    // EP0 IN BDT 设置 
    BDTtable[bEP0IN_EVEN].Cnt = (EP0_SIZE);
    BDTtable[bEP0IN_EVEN].Addr =(uint_32)gu8EP0_IN_EVEN_Buffer;
    BDTtable[bEP0IN_EVEN].Stat._byte = kUDATA0;

    // 使能 EP0
    USB0_ENDPT0 = 0x0D;  //端点允许TX RX传输和执行握手

    // 清除所有的错误
    USB0_ERRSTAT = 0xFF;
    
    //清除所有的中断标志
    USB0_ISTAT = 0xFF;

    // USB设备地址
    USB0_ADDR = 0x00;

    // 使能所有的错误中断
    USB0_ERREN = 0xFF;

    // USB模块中断使能
    FLAG_SET(USB_INTEN_TOKDNEEN_SHIFT,USB0_INTEN);  //使能令牌中断
    FLAG_SET(USB_INTEN_SOFTOKEN_SHIFT,USB0_INTEN);  //使能帧中断
    FLAG_SET(USB_INTEN_ERROREN_SHIFT,USB0_INTEN);   //使能错误中断
    FLAG_SET(USB_INTEN_USBRSTEN_SHIFT,USB0_INTEN);  //使能复位中断
}


 //=========================================================================
 //函数名:usb_ep_in_transfer
 //功  能: USB发送IN包，作用是USB设备发送数据包
 //参  数: u8EP：端点0
 //       pu8DataPointer：用户存储区的待发数据缓冲区首地址
 //       u8DataSize：待发数据长度
 //返  回: 无
 //=========================================================================
 static void usb_ep_in_transfer(uint_8 u8EP,uint_8 *pu8DataPointer,
         uint_8 u8DataSize)
 {
     uint_8 *pu8EPBuffer;
     uint_8 u8EPSize;
     uint_16 u16Lenght=0;
     uint_8 u8EndPointFlag;

     //设置端点所对应的端点描述符
     u8EndPointFlag = u8EP;
     if(u8EP)    //貌似有点多余，该函数只针对ep0
         u8EP=(uint_8)(u8EP<<2);
     u8EP+=2;    //in_odd

     //指向端点的缓冲区
     pu8EPBuffer = BD_BufferPointer[u8EP];    //指向_IN_ODD_Buffer

     //检查是否可以发送数据
     if(FLAG_CHK(fIN,gu8USBClearFlags))
     {
         //待传输的数据
         pu8IN_DataPointer = pu8DataPointer;
         gu8IN_Counter = u8DataSize;
         //控制传输的数据阶段中传输数据的大小
         u16Lenght = (Setup_Pkt -> wLength_h<<8) + Setup_Pkt -> wLength_l ;
         //如果要发送in包的端点是端点0，并且待发送数据比要发送数据长
         //那么取低字节的传输字节大小
         if((u16Lenght < u8DataSize) && (u8EP==2))
         {
             gu8IN_Counter = Setup_Pkt->wLength_l;
         }
     }

     //看看待发送的数据是否大于端点所能发送数据的长度。
     if(gu8IN_Counter > cEP_Size[u8EP])     //cEP_Size[u8EP] == 32
     {
         u8EPSize = cEP_Size[u8EP];
         gu8IN_Counter -= cEP_Size[u8EP];   //剩余一些待发数据
         FLAG_CLR(fIN,gu8USBClearFlags);    //清标志，不能发送数据
     }
     else
     {
         u8EPSize = gu8IN_Counter;
         gu8IN_Counter=0;
         FLAG_SET(fIN,gu8USBClearFlags);
     }

     //把待发数据长度写入BDT
     BDTtable[u8EP].Cnt = (u8EPSize);

     // 把数据拷贝到BDT缓冲区   (把用户数据区待发送数据拷贝到指定端点的缓冲区)
     while(u8EPSize--)
          *pu8EPBuffer++=*pu8IN_DataPointer++;

     // gu8USB_Toogle_flags : 用Data0 和Data1 来跟USB 设备进行同步用的。
     // DATA0/DATA1 交替
     //检查gu8USB_Toogle_flags bit0是否为1
     if(FLAG_CHK(u8EndPointFlag,gu8USB_Toogle_flags))
     {
         //gu8USB_Toogle_flags : 表示是DATA0还是DATA1
         //1:表示发送DATA0, 0: 表示发送DATA1.
         BDTtable[u8EP].Stat._byte = kUDATA0;
         FLAG_CLR(u8EndPointFlag,gu8USB_Toogle_flags);
     }
     else
     {
         BDTtable[u8EP].Stat._byte= kUDATA1;
         FLAG_SET(u8EndPointFlag,gu8USB_Toogle_flags);
     }
 }

 //=========================================================================
 //函数名:usb_set_interface
 //功  能: USB设置接口函数
 //       通过设置端点控制寄存器将端点2配置为数据发送点，端点3配置为数据接收点
 //       并将端点缓冲区地址  以及   控制信息 存储到BDT中
 //参  数: 无
 //返  回: 无
 //=========================================================================
 static void usb_set_interface(void)
 {
     // 使能端点
     // 端点 Register 设置
     USB0_ENDPT1= EP1_VALUE | USB_ENDPT_EPHSHK_MASK;       //发送使能
     USB0_ENDPT2= EP2_VALUE | USB_ENDPT_EPHSHK_MASK;       //发送使能
     USB0_ENDPT3= EP3_VALUE | USB_ENDPT_EPHSHK_MASK;       //接收使能
     USB0_ENDPT4= EP4_VALUE | USB_ENDPT_EPHSHK_MASK;
     USB0_ENDPT5= EP5_VALUE | USB_ENDPT_EPHSHK_MASK;
     USB0_ENDPT6= EP6_VALUE | USB_ENDPT_EPHSHK_MASK;

     // 设置 1 BDT 设置
     BDTtable[bEP1IN_ODD].Stat._byte= kUDATA1;
     BDTtable[bEP1IN_ODD].Cnt = 0x00;
     BDTtable[bEP1IN_ODD].Addr =(uint_32)gu8EP1_IN_ODD_Buffer;

     // 设置 2 BDT 设置
     BDTtable[bEP2IN_ODD].Stat._byte= kUDATA1;
     BDTtable[bEP2IN_ODD].Cnt = 0x00;
     BDTtable[bEP2IN_ODD].Addr =(uint_32)gu8EP2_IN_ODD_Buffer;

     // 设置 3 BDT 设置
     BDTtable[bEP3OUT_ODD].Stat._byte= kUDATA0;
     BDTtable[bEP3OUT_ODD].Cnt = 0xFF;
     BDTtable[bEP3OUT_ODD].Addr =(uint_32)gu8EP3_OUT_ODD_Buffer;
 }


 //=========================================================================
 //函数名:usb_stdReq_handler
 //功  能: USB模块标准请求，针对设备（bmRequestType == 0x00）中断服务例程函数
 //       该函数根据setup数据包中的请求类型，进行相应处理，对应的是字段bRequest
 //参  数: 无
 //返  回: 无
 //=========================================================================
 static void usb_stdReq_handler(void)
 {
     uint_16 gu8Status;

     switch(Setup_Pkt->bRequest)
     {
         case mSET_ADDRESS:
             usb_ep_in_transfer(EP0,0,0);    //端点0发送ACK包
             gu8USB_State = uADDRESS;   //置USB设备为 已设置地址状态
             break;

         // PC 从芯片获取描述符
         case mGET_DESC:

             switch(Setup_Pkt->wValue_h)
             {
                 case mDEVICE:
                     // 发送设备描述符
                     usb_ep_in_transfer(EP0,(uint_8*) Device_Descriptor,sizeof(Device_Descriptor));
                     break;

                 case mCONFIGURATION:
                     // 发送配置描述符
                     usb_ep_in_transfer(EP0,(uint_8*)Configuration_Descriptor,
                             sizeof(Configuration_Descriptor));
                     break;

                 case mSTRING:
                     if(Setup_Pkt->wValue_l==0)
                         usb_ep_in_transfer(EP0,USB_String_Table.String_Descriptor0,
                              USB_String_Table.String_Descriptor0[0]);
                     else if(Setup_Pkt->wValue_l==1)
                         usb_ep_in_transfer(EP0,USB_String_Table.String_Descriptor1,
                             USB_String_Table.String_Descriptor1[0]);
                     else if(Setup_Pkt->wValue_l==2)
                        usb_ep_in_transfer(EP0,USB_String_Table.String_Descriptor2,
                                USB_String_Table.String_Descriptor2[0]);
                     else
                         usb_ep_in_transfer(EP0,USB_String_Table.Device_Name,
                             USB_String_Table.Device_Name[0]);

//                     // 发送字符串描述符
//                     usb_ep_in_transfer(EP0,(uint_8*)String_Table[Setup_Pkt->wValue_l],
//                             String_Table[Setup_Pkt->wValue_l][0]);
                     break;

                 default:
                     usb_ep0_stall();
                     break;
             }
             break;
         // 设置配置 Set Configuration
         case mSET_CONFIG:
             //选择配置值
             gu8Dummy=Setup_Pkt->wValue_h+Setup_Pkt->wValue_l; //wValue_h保留，wValue_l为配置值，
                                                               //为0或配置描述符中的配置值
             if(Setup_Pkt->wValue_h+Setup_Pkt->wValue_l) //判断setup的数据位wValue
                                                         //若非0调用usb_set_interface进行接口设置
             {
                 //使能1 、2 、3 端点
                 usb_set_interface();
                 usb_ep_in_transfer(EP0,0,0);   //端点0发送ACK
                 gu8USB_State = uENUMERATED;    //置USB设备为 已被枚举状态
             }
             break;
         // 获取配置信息 Get Configuration
         case mGET_CONFIG:
             //获取配置信息
             usb_ep_in_transfer(EP0,(uint_8*)&gu8Dummy,1);    //发送配置值
             break;
         // 获取状态 Get Status
         case mGET_STATUS:
             gu8Status = 0;
             usb_ep_in_transfer(EP0,(uint_8*)&gu8Status,2);
             gu8USB_State=uPOWER;    //置USB设备为 已供电状态
             break;

         default:
             usb_ep0_stall();
             break;
     }
 }

 //=========================================================================
 //函数名:usb_setup_handler
 //功  能: USB setup中断服务例程
 //      setup表示一次控制传输的开始。USB模块接收到PC发送的setup数据包后，
 //      若使能setup中断，则进入该函数。根据setup数据包中的bmRequestType进行相应处理
 //参  数: 无
 //返  回: 无
 //说  明:
 //   (1)只有接收到SETUP包才调用该函数
 //   (2)SETUP包中8字节数据
 //    bmRequestType:1
 //    bRequest:1
 //    wValue.H:1 :描述符的类型
 //    wValue.L:1 :描述符的索引
 //    wIndex:2
 //    wLength:2
 //=========================================================================
 static void usb_setup_handler(void)
 {
    // uint_8 u8State;

     // 从DATA0开始传输
     FLAG_CLR(0,gu8USB_Toogle_flags);
     switch(Setup_Pkt->bmRequestType & 0x1F)  //主机至设备 标准类   bmRequestType请求类
     {

         case DEVICE_REQ:
             // 设备
             if((Setup_Pkt->bmRequestType & 0x1F)== STANDARD_REQ)
                 usb_stdReq_handler();   // USB 设备的标准请求
             // 把BDT 的控制权交给USB 模块
             BDTtable[bEP0OUT_ODD].Stat._byte= kUDATA0;
             break;
         case INTERFACE_REQ:
         case ENDPOINT_REQ:
             // 端点
             usb_endpoint_setup_handler();
             BDTtable[bEP0OUT_ODD].Stat._byte= kUDATA0;
             break;

         default:
             usb_ep0_stall();
             break;
     }

     //从机时，该位为0: SIE继续处理令牌  （接收到setup令牌后SIE会将该位置1）
     FLAG_CLR(USB_CTL_TXSUSPENDTOKENBUSY_SHIFT,USB0_CTL);
 }



 //=========================================================================
 //函数名:usb_endpoint_setup_handler
 //功  能: USB端点setup中断服务例程，针对端点的bRequest（bmRequestType == 0x02）
 //参  数: 无
 //返  回: 无
 //=========================================================================
 static void usb_endpoint_setup_handler(void)
 {
     uint_16 u16Status;

     switch(Setup_Pkt->bRequest)
     {
         case GET_STATUS:  //获得端点状态
             //当针对一个接口或端点时，wIndex字段决定了是哪个接口或端点
             if(FLAG_CHK(Setup_Pkt->wIndex_h,gu8HALT_EP))
                 u16Status=0x0100;  //gu8HALT_EP用来判断端点是否处于停止状态，处于停滞状态，端点0发送0x0100
             else
                 u16Status=0x0000;
             usb_ep_in_transfer(EP0,(uint_8*)&u16Status,2);
             break;

         case CLEAR_FEATURE:  //清除端点特征
             FLAG_CLR(Setup_Pkt->wIndex_h,gu8HALT_EP);
             usb_ep_in_transfer(EP0,0,0);
             break;

         case SET_FEATURE:    //设置端点特征
             FLAG_SET(Setup_Pkt->wIndex_h,gu8HALT_EP);
             usb_ep_in_transfer(EP0,0,0);
             break;

         default:
             break;
     }
 }


 //=========================================================================
 //函数名:usb_ep0_in_handler
 //功  能: 端点0发送服务函数
 //      用于判断gu8USB_State是否已被 配置成地址状态 ,若已是，则将gu8USB_State设置成就绪状态
 //参  数: 无
 //返  回: 无
 //=========================================================================
 static void usb_ep0_in_handler(void)   //设置地址寄存器，即外设地址，在请求的状态阶段被完成，
                                 //而其他请求在状态阶段之前完成
 {
     if(gu8USB_State==uADDRESS)
     {
         USB0_ADDR = Setup_Pkt->wValue_l;   //设置USB设备地址  setup指向ep0_out_odd
         gu8USB_State=uREADY;               //USB设备变为就绪状态
         FLAG_SET(fIN,gu8USBClearFlags);    //允许发送数据
     }
     usb_ep_in_transfer(0,0,0);   //端点0发送ACK
 }

 //=========================================================================
 //函数名:usb_ep0_stall
 //功  能: 端点0 stall停止处理函数
 //       将端点0控制寄存器的Stall位置位，产生一个STALL包
 //       并将端点0的缓冲区描述符的控制信息设置成kUDATA0
 //参  数: 无
 //返  回: 无
 //=========================================================================
 static void usb_ep0_stall(void)
 {
     //产生一个STALL包
     FLAG_SET(USB_ENDPT_EPSTALL_SHIFT,USB0_ENDPT0); //返回一个STALL握手包
     //ENDPT0_EP_STALL = 1;
     BDTtable[bEP0OUT_ODD].Stat._byte = kUDATA0;
     BDTtable[bEP0OUT_ODD].Cnt = EP0_SIZE;
 }

 //=========================================================================
 //函数名:usb_ep0_out_handler
 //功  能: 端点0接收中断服务例程
 //参  数: 无
 //返  回: 无
 //=========================================================================
 static void usb_ep0_out_handler(void)
 {
     //tBDTtable[bEP0OUT_ODD].Cnt = EP0_SIZE;
     BDTtable[bEP0OUT_ODD].Stat._byte = kUDATA0;
     //tBDTtable[bEP0IN].Stat._byte = kUDATA1;

 }

