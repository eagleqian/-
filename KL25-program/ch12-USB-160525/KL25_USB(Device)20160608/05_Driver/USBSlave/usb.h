//==========================================================================
// 文件名称：usb.h                                                          
// 功能概要：USB底层驱动构件头文件
// 版权所有: 苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
// 版本更新: 2012-12-14     V1.0        USB构件初始版本
//          2012-12-20     V1.2        USB构件优化修改
//==========================================================================
#ifndef _USB_H
#define _USB_H

#include "common.h"

//USB中断类型宏定义
#define USB_TOKDNE_INT    (0)   //令牌中断
#define USB_RST_INT      (1)   //复位中断
#define USB_SOF_INT      (2)   //SOF中断
#define USB_STALL_INT    (3)   //STALL中断
#define USB_SLEEP_INT    (4)   //SLEEP中断
#define USB_ERROR_INT    (5)   //ERROR中断

#define USB_INTERRUPT_IRQ   (24)    //USB中断请求号

//寄存器操作
#define FLAG_SET(BitNumber, Register)   (Register |=(1<<BitNumber))
#define FLAG_CLR(BitNumber, Register)   (Register &=~(1<<BitNumber))
#define FLAG_CHK(BitNumber, Register)   (Register & (1<<BitNumber))


#define USB_FMC_ACC_ENABLE      FLAG_SET(FMC_PFAPR_M4AP_MASK,FMC_PFAPR)
#define USB_REG_SET_ENABLE      FLAG_SET(SIM_SOPT1_USBREGEN_SHIFT,SIM_SOPT1)
#define USB_REG_CLEAR_ENABLE    FLAG_CLR(SIM_SOPT1_USBREGEN_SHIFT,SIM_SOPT1)
#define USB_REG_SET_STDBY       FLAG_SET(SIM_SOPT1_USBSSTBY_SHIFT,SIM_SOPT1)
#define USB_REG_CLEAR_STDBY     FLAG_CLR(SIM_SOPT1_USBSSTBY_SHIFT,SIM_SOPT1)

#define EP_OUT          3      //端点号3，用于下行传输
#define EP_IN           2      //端点号2，用于上行传输

#define mEP2_IN       0x28     //状态寄存器，表示端点2   发送
#define mEP3_OUT      0x30     //状态寄存器，表示端点3   接收

#define USB_FARCTIONAL_VALUE    0x02

#define DISABLE_USB (USBCTL0 = 0x00)
#define ENDPOINTS   3

//EP0缓冲区设置
#define EP0_SIZE            32

//EP1设置
#define EP1_VALUE           _EP_IN      //端点1发送使能位
#define EP1_TYPE            INTERRUPT   //输入中断点
#define EP1_SIZE            32
#define EP1_BUFF_OFFSET     0x18

//EP2设置
#define EP2_VALUE           _EP_IN      //发送使能位 0x04
#define EP2_TYPE            BULK        //数据传输
#define EP2_SIZE            32
#define EP2_BUFF_OFFSET     0x20

//EP3设置
#define EP3_VALUE           _EP_OUT     //接收使能  0x08
#define EP3_TYPE            BULK        //数据传输
#define EP3_SIZE            32
#define EP3_BUFF_OFFSET     0x28

//EP4设置
#define EP4_VALUE           DISABLE
#define EP4_SIZE            1
#define EP4_BUFF_OFFSET     0x08

//EP5设置
#define EP5_VALUE           DISABLE
#define EP5_SIZE            1
#define EP5_BUFF_OFFSET     0x08

//EP6设置
#define EP6_VALUE           DISABLE
#define EP6_SIZE            1
#define EP6_BUFF_OFFSET     0x08

#define EP3_CTR   tBDTtable[4].Stat._byte= kSIE    //串行接口引擎 指BDT由USB模块控制 或者 MCU
                                                   //（USB设备接收到信息包，有SIE解包，并将数据放入
                                                   //指定端点的接受缓冲去？）

#define usbSIE_CONTROL(EP)   (tBDTtable[EP<<2].Stat._byte= kSIE)
#define usbMCU_CONTROL(EP)   (tBDTtable[EP<<2].Stat._byte= kMCU)
#define usbEP_Reset(EP)      (tBDTtable[EP<<2].Cnt=0x0020)

#define _EP_IN      USB_ENDPT_EPTXEN_MASK        //端点发送使能
#define _EP_OUT     USB_ENDPT_EPRXEN_MASK        //端点接收使能

#define DISABLE 0

#define INTERRUPT   0x03
#define BULK        0x05      //数据传输

//BDT状态信息
#define kMCU      0x00          //BD bit7 OWN为0 微处理器对BD拥有控制权
#define kSIE      0x80          //USB模块拥有，定义DATA0允许发送或接受

#define kUDATA0   0x88  //USB模块拥有控制权，DATA0 允许发送或接受，使能USB模块进行数据翻转同步  ACK包
#define kUDATA1   0xC8  //USB模块拥有控制权，DATA1 允许发送或接受，使能USB模块进行数据翻转同步

//USB事务中，BD控制信息中的PID类型
#define mSETUP_TOKEN    0x0D  //主机到设备，用于控制传输
#define mOUT_TOKEN      0x01  //主机向设备发数据
#define mIN_TOKEN       0x09  //主机向设备要数据

//标准的SETUP请求命令， bRequest字节
#define mGET_STATUS           0
#define mCLR_FEATURE          1
#define mSET_FEATURE          3
#define mSET_ADDRESS          5
#define mGET_DESC             6
#define mSET_DESC             7
#define mGET_CONFIG           8
#define mSET_CONFIG           9
#define mGET_INTF             10
#define mSET_INTF             11
#define mSYNC_FRAME           12
#define    mGET_MAXLUN        0xFE

//获取描述符   描述符的类型 由get_descriptor请求的 wValue高字节
#define mDEVICE                     1
#define mCONFIGURATION              2
#define mSTRING                     3
#define mINTERFACE                  4
#define mENDPOINT                   5
#define mDEVICE_QUALIFIER           6
#define mOTHER_SPEED_CONFIGURATION  7   //速率配置描述符
#define mINTERFACE_POWER            8

#define mREPORT                     0x22

//SETUP请求类型    决定是针对设备，接口还是端点     bmRequestType字节 D[6:5]决定该请求所属类型
#define STANDARD_REQ    0x00
#define SPECIFIC_REQ    0x20
#define VENDORSPEC_REQ  0x40

#define DEVICE_REQ      0x00
#define INTERFACE_REQ   0x01
#define ENDPOINT_REQ    0x02

//针对端点（或接口）的bRequest
#define GET_STATUS              0x00
#define CLEAR_FEATURE           0x01
#define SET_FEATURE             0x03

typedef struct _String_Table
{
    uint_8 *String_Descriptor0;
    uint_8 *String_Descriptor1;
    uint_8 *String_Descriptor2;
    uint_8 *Device_Name;
}String_Table;

enum
{
    uSETUP,
    uDATA
};

enum
{
    EP0,
    EP1,
    EP2,
    EP3,
    EP4,
    EP5,
    DUMMY,
    LOADER
};

//5种状态
enum
{
    uPOWER,               //已供电状态
    uENUMERATED,          //已被枚举状态，已被配置状态
    uENABLED,             //使能
    uADDRESS,             //已设置地址状态
    uREADY                //就绪
};
enum
{
    fIN,
    fOUT
};

enum
{
    bEP0OUT_ODD,
    bEP0OUT_EVEN,
    bEP0IN_ODD,
    bEP0IN_EVEN,
    bEP1OUT_ODD,
    bEP1OUT_EVEN,
    bEP1IN_ODD,
    bEP1IN_EVEN,
    bEP2OUT_ODD,
    bEP2OUT_EVEN,
    bEP2IN_ODD,
    bEP2IN_EVEN,
    bEP3OUT_ODD,
    bEP3OUT_EVEN,
    bEP3IN_ODD,
    bEP3IN_EVEN
};

//缓冲区描述符表共用体，其中的三个内容都是同一个，便于操作
typedef union _tBDT_STAT
{
    uint_8 _byte;

    struct{
        uint_8 :1;
        uint_8 :1;
        uint_8 BSTALL:1;   //uint_8 :1  位段 ，结构体中以位为单位来指定其成员所占内存长度
        uint_8 DTS:1;
        uint_8 NINC:1;
        uint_8 KEEP:1;
        uint_8 DATA:1;
        uint_8 UOWN:1;    //BDT所有权      缓冲区描述符BD
    }McuCtlBit;
       
    struct{
        uint_8    :2;
        uint_8 PID:4;     //包标志
        uint_8    :2;
    }RecPid;
} tBDT_STAT;              //缓冲区描述符表共用体

//BDT：缓冲区描述符表
typedef struct _tBDT
{
    tBDT_STAT Stat;   //BD控制信息
    uint_8  dummy;    //为了与缓冲区描述符中的保留位相对应
    uint_16 Cnt;      //接收到数据长度
    uint_32 Addr;     //BD地址
} tBDT;

//SETUP数据结构体
typedef struct _tUSB_Setup 
{
       uint_8 bmRequestType;
       uint_8 bRequest;
       uint_8 wValue_l;
       uint_8 wValue_h;
       uint_8 wIndex_l;
       uint_8 wIndex_h;
       uint_8 wLength_l;
       uint_8 wLength_h;
}tUSB_Setup;


//=========================================================================
//函数名:usb_init
//功  能: USB模块初始
//参  数:str:设备序列号
//返  回: 无
//=========================================================================
void usb_init(uint_8 str[]);

//=========================================================================
//函数名: usb_enumerate
//功  能: USB枚举，用于处理USB设备复位后USB主机发送来的设备请求
//参  数：无
//返  回: 无
//=========================================================================
void usb_enumerate();

//=========================================================================
//函数名: usb_send
//功  能: USB发送数据
//参  数: buf：待发数据缓冲区，并在函数返回时保留未发送的数据
//      len：待发数据长度,并在函数返回时带出剩余未发送的数据长度
//返  回: 实际发送的数据长度
//备  注：一次性传输的数据长度是端点所支持的最大数据长度（32字节），如果发送的数据长度
//      大于32字节，则分为多次传输。
//=========================================================================
uint_8 usb_send(uint_8 *buf,uint_8 *len);

//=========================================================================
//函数名: usb_recv
//功  能: USB接收数据
//参  数: buf:接收数据缓冲区
//      len:函数返回时，带出接收的数据长度
//返  回: 成功：返回接收数据的长度；失败：返回0
//=========================================================================
uint_8 usb_recv(uint_8 *buf,uint_8 *len);

#endif 

//=========================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，不足之处，
//     欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏州大学飞思卡尔嵌入式中心（苏州华祥信息科技有限公司）
//技术咨询：0512-65214835  http://sumcu.suda.edu.cn
//业务咨询：0512-87661670,18915522016  http://www.hxtek.com.cn
