//=========================================================================
// 文件名称：USBHost.c                                                          
// 功能概要：usb底层驱动构件源文件
// 版权所有: 苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
// 版本更新: 2012-12-14     V1.0         USB构件初始版本
//           2013-2-20     V1.2         USB构件优化修改
//=========================================================================
#include "usb_host.h"

//定义全局变量
static uint_8 dbuffer[DBUFFER_SIZE];
//static rw_func_t *transfer;
lun_info_t lun;
extern uint_8 USBFlag;   //复位状态标记
std_error_t std_error;
tr_error_t tr_error;
DeviceConect my_device;
uint_8 tBDT_unaligned[1024];
tBDT * tBDTtable;
uint_8 *bdt;
MSTInfoStruct mst_info;
tr_error_t tr_error;

//==================================内部函数声明=================================
uint_8 USBHostScan(void);
void USBResetBus(void);
void USBDeviceDisConnect(void);
void USBDeviceConnect(void);
uint_8 USBCheckDeviceConnect(void);
uint_8 USBGetDeviceDesc(StructDevDesc *res);
uint_8 USBGetConfigDesc(StructConfigDesc *res,uint_8 index);
uint_8 USBGetInterfaceDesc(StructInterfaceDesc *res,uint_16 offset);
uint_8 USBGetEpDesc(StructEpDesc *res,uint_16 offset);
uint_8 USBAddEp(uint_8 type, uint_8 address, uint_8 interval, uint_16 psize);
uint_8 USBSetConfig(uint_8 index);
uint_16 USBFindInterface(uint_8 class, uint_8 sclass, uint_8 protocol);
void USBFillSetupPacket(uint_8 * dst, uint_8 dir, uint_8 type,uint_8 recipient,
        uint_8 req, uint_16 val, uint_16 ndx, uint_16 len);
uint_16 USBTokenIN(uint_8 *setup, uint_8* buffer, uint_8 ep);
uint_16 USBTokenOUT(uint_8 *setup, uint_8* buffer, uint_8 ep);
uint_16 USBStartTransaction(uint_8 type, uint_8 *buffer, uint_16 length,
        uint_8 ep);
uint_8 USBWaitTokenFinish();
void USBHostSleep(void);
void USBModifyEps(uint_8 ep,uint_8 type, uint_8 address, uint_8 interval,
        uint_16 psize);
uint_8 USBSetEp0psize(void);
uint_8 USBSetAddress(uint_8 address);
int scsi_init(void);
int scsi_open_device();
int scsi_close_device(void);
int scsi_read(uint_32 lba, uint_32 length, uint_8 *buffer);
int scsi_write(uint_32 lba, uint_32 length, const uint_8 *buffer);
int usb_write_sector(uint_32 lba, const uint_8 *buffer);
int scsi_reset_lun(void);
int scsi_get_sectors_no(void);
int scsi_get_sectors_size(void);
int scsi_get_device_string(uint_8 *buffer, uint_8 len);
void Delay(uint_32 time);
static volatile uint_8  Stat = 0x01;
static int scsi_cmd_inquiry(void);
static int scsi_cmd_read_capacity(void);
static int scsi_cmd_test_unit_ready(void);
int scsi_cmd_request_sense(void);
int usb_mst_reset(void);
int usb_mst_getnlun(void);
int usb_device_transfer(uint_8 cmd_length, void *cmd, uint_8 dir, uint_32 buf_length, const uint_8 *buf);
int usb_mst_init(void);
uint_8 GetMSTStat(void);
void SetMSTStat(uint_8 state);


//==========================================================================
//函数名:USBHostInit
//功  能: USB模块初始化，配置为USB主机模式
//参  数: 无
//返  回: 0=成功；非0=异常
//==========================================================================
uint_8 USBHostInit(void)
{  
    uint_8 ep;
    uint_16 i;
    
    //指向BDT，避免占用rom区
    tBDTtable = (tBDT *)((( uint_32 ) tBDT_unaligned & 0xFFFFFE00UL) + 0x200UL);
    bdt = (uint_8 *)tBDTtable;
    //设备相关信息
    my_device.address = INVALID_ADDRESS;   //无设备时是一个无效地址
    ep_info.next_tx   = 0;
    ep_info.next_rx   = 0;

    for(i = 0;i < 512;i++)
    {
        bdt[i] = 0;     //将512个DB清零
    }
    //端点相关信息
    for(ep=0;ep<MAX_EP_PER_DEVICE;ep++)
    {
        my_device.eps[ep].address = INVALID_ADDRESS;   //端点地址
        my_device.eps[ep].last_due = 0;       //最近到期
        my_device.eps[ep].interval = 74;      //间隔
    }

    SIM_SOPT2 |= SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK;
    
    SIM_SCGC4 |= SIM_SCGC4_USBOTG_MASK;

    enable_irq(USB_INTERRUPT_IRQ);

    USB0_USBTRC0 |= USB_USBTRC0_USBRESET_MASK;
    while (USB0_USBTRC0 & USB_USBTRC0_USBRESET_MASK){}

    USB0_USBCTRL = 0x40;  //若D+，D-上的弱下拉使能
    
    USB0_ISTAT = 0xFF;

    USB0_CTL |= USB_CTL_ODDRST_MASK;  //清odd，指向even区
    
    USB0_BDTPAGE1 = (uint_8)(((uint_32)BDT_BASE) >> 8);
    USB0_BDTPAGE2 = (uint_8)(((uint_32)BDT_BASE) >> 16);
    USB0_BDTPAGE3 = (uint_8)(((uint_32)BDT_BASE) >> 24);
    
    USB0_SOFTHLD = USB_SOFTHLD_CNT_MASK;  //SOF计数器阀值
    
    USB0_OTGCTL = USB_OTGCTL_DPLOW_MASK | USB_OTGCTL_DMLOW_MASK | USB_OTGCTL_OTGEN_MASK;//上下拉OTG寄存器使能
    USB0_USBCTRL |= USB_USBCTRL_PDE_MASK;    //弱下拉使能，禁止上拉电阻
    USB0_USBCTRL &= ~USB_USBCTRL_SUSP_MASK;  //清挂起状态
    
    USB0_INTEN = USB_INTEN_ATTACHEN_MASK; //连接中断使能
    //USB0_CTL |= USB_CTL_USBENSOFEN_MASK; //禁止产生开始帧包
    
    USB0_USBTRC0|=0x40;
    USB0_CTL = USB_CTL_HOSTMODEEN_MASK;//使能主机模式
    return 0;
}

//==========================================================================
//函数名:InitUSBDevice
//功  能: 初始化接入的USB设备
//参  数: device_inf:函数返回时带回初始化的USB设备信息
//返  回: 0=成功；1=异常
//==========================================================================
uint_8 InitUSBDevice(uint_8 *device_inf)
{
    uint_8 lun = 0;

    for(;;) //等待发生ATTACH中断，设备连接检测到
    {
        if((USBFlag & USB_ISTAT_ATTACH_MASK) != 0)
        {
            USBFlag &= ~USB_ISTAT_ATTACH_MASK;
            break;
        }
    }

    USBFlag = 0;

    lun=(uint_8)usb_mst_init();
    if (lun)
    {
        scsi_open_device();
        scsi_get_device_string(device_inf, 32);
    }
    else
    {
        return 0;
    }
    return 1;
}

//============================================================================
//函数名: USBReadData
//功   能: USB数据读取
//参   数: ep:USB端点号
//        length:读的数据长度
//        ReadBuffer:存放读数据的缓冲区
//返  回: 0=成功；1=失败
//备  注：调用内部函数USBStartTransaction执行数据的读取，读取的数据可以在多个事
//       务处理中，因此需要根据端点所支持的最大数据包的长度决定执行多少次事务处理
//============================================================================
uint_16 USBReadData(uint_8 ep, uint_16 length,uint_8* ReadBuffer)
{
    uint_32 curr=0;
    uint_16 got,psize;

    MKDBG_TRACE(ev_receive, ep);

    if ((USB0_CTL & USB_CTL_HOSTMODEEN_MASK) == 0)
    {
        tr_error=tre_not_running;
        return(0);
    }

    while(curr < length)
    {
        psize=(uint_16)(MIN(my_device.eps[ep].psize, length));
        //开始执行USB事务处理函数，进行数据的读取
        got  = USBStartTransaction(TRT_IN, ReadBuffer+curr, psize, ep);
        if (got == ((uint_16)-1u))
        {
            break;
        }
        curr += got;
        if (got != my_device.eps[ep].psize)
        {
            break;
        }
    }
    return(curr);
}

//============================================================================
//函数名: USBWriteData
//功  能:  向USB设备(U盘)写入数据
//参  数: ep:USB端点号
//       length:要写入的数据长度
//       buff:存放要写入的数据的缓冲区
//返  回: 0=成功；1=失败
//备  注：调用内部函数USBStartTransaction执行数据的写入，写入的数据可以在多个事
//       务处理中，因此需要根据端点所支持的最大数据包的长度决定执行多少次事务处理
//============================================================================
uint_8 USBWriteData(uint_8 ep,uint_16 length,uint_8 *WriteBuffer)
{
    uint_32 curr=0;
    uint_16 psize,r;

    MKDBG_TRACE(ev_send, ep);

    if ((USB0_CTL & USB_CTL_HOSTMODEEN_MASK) == 0)
    {
        tr_error=tre_not_running;
        return(0);
    }

    if(length > 512)
        return 0;

    while(curr<length)
    {
        psize = (uint_16)(MIN(my_device.eps[ep].psize, length));
        //开始执行USB事务处理函数，进行数据的写入
        r = USBStartTransaction(TRT_OUT, WriteBuffer+curr, psize, ep);
        if (r!=psize)
        {
            CMX_ASSERT(r==((uint_16)-1u));
            break;
        }
        curr += psize;
    }
    return(curr);
}

//============================================================================
//函数名: CheckUSBDeviceStatus
//功   能:  检测USB设备状态
//参   数: 无
//返   回: 0=成功；1=失败
//============================================================================
uint_8 CheckUSBDeviceStatus()
{
    int i = 0;
    USB0_ISTAT = USB_ISTAT_ATTACH_MASK;
    for(i = 0;i < 1000;i++)
    {
    }
    if(!(USB0_ISTAT & USB_ISTAT_ATTACH_MASK))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


//================================内部函数实现===================================

//============================================================================
//函数名:USBHostScan
//功  能: 检测是否有USB设备连接
//参  数: 无
//返  回: 0=成功；非0=异常
//============================================================================
uint_8 USBHostScan(void)
{
    if ((USB0_CTL & USB_CTL_HOSTMODEEN_MASK) == 0) //非主机模式，结束
    {
        my_device.address = INVALID_ADDRESS;
        my_device.low_speed = 0;
        return(0);
    }
    if(USBCheckDeviceConnect())
    {
        USBResetBus();  //复位总线
        return(1);
    }
    return(0);
}


//============================================================================
//函数名:USBResetBus
//功  能: 复位USB设备 
//参  数: 无
//返  回: 无
//============================================================================
void USBResetBus(void)
{
    uint_8 ep=0;

    if(USBWaitTokenFinish() != tre_none)
    {
        tr_error = tre_not_running;
        return;
    }

    //1 产生复位信号
    USB0_CTL |= USB_CTL_RESET_MASK;           //产生复位信号
    Delay(30);                                //适当延时
    USB0_CTL &= ~USB_CTL_RESET_MASK;

    
    USB0_ISTAT = USB_ISTAT_USBRST_MASK;
  
    if (my_device.address != INVALID_ADDRESS)
        my_device.address=0;
    
    USBModifyEps(0, EPTYPE_CTRL, 0, 0, MIN_EP0_PSIZE);
    
    for(ep=1;ep<MAX_EP_PER_DEVICE;ep++)
        my_device.eps[ep].address = INVALID_ADDRESS;
    
    if (USBCheckDeviceConnect())
    {        

        USB0_CTL |= USB_CTL_USBENSOFEN_MASK;
        USB0_ISTAT = USB_ISTAT_SLEEP_MASK | USB_ISTAT_RESUME_MASK; 

        Delay(100);          

        if (!USBSetEp0psize()) 
        {  
            return;
        }

        if (!USBSetAddress(1))
        {
            return;
        }
        my_device.address=1;    
    }  
}


//============================================================================
//函数名:USBCheckDeviceConnect
//功  能: USB设备移除 
//参  数: 无
//返  回: 无
//============================================================================
void USBDeviceDisConnect(void)
{
    MKDBG_TRACE(ev_disconnect, 0);
    

    my_device.address = INVALID_ADDRESS;  
    my_device.low_speed = 0;

    USB0_ISTAT = USB_ISTAT_USBRST_MASK | USB_ISTAT_ATTACH_MASK;  

    USBHostSleep();
}


//============================================================================
//函数名:USBDeviceConnect
//功  能: USB设备连接
//参  数: 无
//返  回: 无
//============================================================================
void USBDeviceConnect(void)
{
    uint_8 ep;

    USB0_ADDR = 0;

    Delay(100);

    //检测控制寄存器的JSTATE状态，为0说明所连接的设备是低速设备
    my_device.low_speed = (uint_8)((USB0_CTL & USB_CTL_JSTATE_MASK) ? USB_SPEED_FULL : USB_SPEED_LOW);

//    if (my_device.low_speed == USB_SPEED_LOW) //如果是低速设备，将ADDR[LSEN]置1
    if (my_device.low_speed == USB_SPEED_FULL) //如果是低速设备，将ADDR[LSEN]置1
    {
        USB0_ADDR |= USB_ADDR_LSEN_MASK;
    }
    else
    {
    }

    USB0_ISTAT = 0xFF;

    USB0_INTEN = USB_INTEN_TOKDNEEN_MASK | USB_INTEN_USBRSTEN_MASK;

    USB0_ENDPT0 |= USB_ENDPT_HOSTWOHUB_MASK;  //只能用于主机模式且端点0控制寄存器中有效

    USB0_CTL |= USB_CTL_RESET_MASK;
    USB0_CTL &= ~USB_CTL_RESET_MASK;//主机模式下，软件必须将RESET置1然后清零

    USB0_CTL |= USB_CTL_USBENSOFEN_MASK;  //使能SOF包以防止接入设备从运行转到挂起状态

    Delay(100);  //10毫秒？

    USB0_INTEN = USB_INTEN_TOKDNEEN_MASK | USB_INTEN_USBRSTEN_MASK;//使能 令牌完成和复位 中断

    my_device.address=0;  //设备地址设为0x00

    USBModifyEps(0, EPTYPE_CTRL, 0, 0, MIN_EP0_PSIZE); //设定端点0属性
    for(ep=1;ep<MAX_EP_PER_DEVICE;ep++)  //其他端点地址无效
    {
        my_device.eps[ep].address = INVALID_ADDRESS;
    }
}


//============================================================================
//函数名:USBCheckDeviceConnect
//功  能: 检测是否有USB设备连接
//参  数: 无
//返  回: 无
//============================================================================
uint_8 USBCheckDeviceConnect(void)
{
    volatile int x;

    if (my_device.address != INVALID_ADDRESS)
    {
        if (USB0_ISTAT & USB_ISTAT_USBRST_MASK)  //复位中断，进行断开设备
        {
            USBDeviceDisConnect();
        }
    }

    if (my_device.address == INVALID_ADDRESS)
    {

        USB0_ISTAT = USB_ISTAT_ATTACH_MASK;

        for(x=0; x< 10000; x++)   //加 延时
          ;

        if (USB0_ISTAT & USB_ISTAT_ATTACH_MASK)   //发生了ATTACH中断,进行连接设备
        {
            USBDeviceConnect();
        }
    }

    if(my_device.address != INVALID_ADDRESS)  //连接
        return 1;
    return 0;
}


//============================================================================
//函数名:USBModifyEps
//功  能: 设定端点属性
//参  数: 无
//返  回: 无
//============================================================================
void USBModifyEps(uint_8 ep,uint_8 type, uint_8 address, uint_8 interval, uint_16 psize)
{
    my_device.eps[ep].type    = type;
    my_device.eps[ep].address = address;
    my_device.eps[ep].interval= interval;
    my_device.eps[ep].psize   = psize;
}

//============================================================================
//函数名:USBSetEp0psize
//功  能: 设置SetupPacket包
//参  数: 无
//返  回: 无
//============================================================================
uint_8 USBSetEp0psize(void)
{    
    uint_8 setup[8];
   
    std_error = stderr_none;   

    USBFillSetupPacket(setup, STP_DIR_IN, STP_TYPE_STD, STP_RECIPIENT_DEVICE,
        STDRQ_GET_DESCRIPTOR, (STDDTYPE_DEVICE<<8) | 0, 0, 8);

    if (8 == USBTokenIN(setup, dbuffer, 0))
    {  
        if ((USBDSC_TYPE(dbuffer) == STDDTYPE_DEVICE)&& (USBDSC_LENGTH(dbuffer) <= 18))
        {
            USBModifyEps(0, EPTYPE_CTRL, 0, 0, DEVDESC_PACKET_SIZE(dbuffer));
            return(1);
        }    
    }

    std_error = stderr_host;  
    return(0);
}

//============================================================================
//函数名:USBSetAddress
//功  能: 设置USB地址 
//参  数: 无
//返  回: 无
//============================================================================
uint_8 USBSetAddress(uint_8 address)
{
    uint_8 setup[8];
    uint_8 retry=3;

    std_error = stderr_none;
    
    USBFillSetupPacket(setup, STP_DIR_OUT, STP_TYPE_STD, STP_RECIPIENT_DEVICE,
        STDRQ_SET_ADDRESS, address, 0, 0);
  
    do {    
        if (0 == USBTokenOUT(setup, dbuffer, 0))
        {
            Delay(45);    
            return(1);
        }
    }while(retry--); 
     
    std_error = stderr_host;  
    return(0);
}

//============================================================================
//函数名:USBSetConfig
//功  能: 设置SetupPacket包
//参  数: 无
//返  回: 0=成功；非0=异常
//============================================================================
uint_8 USBSetConfig(uint_8 index)
{
    uint_8 setup[8];
    uint_8 retry=3;
 
    std_error=stderr_none;
    
    USBFillSetupPacket(setup, STP_DIR_OUT, STP_TYPE_STD, STP_RECIPIENT_DEVICE,
        STDRQ_SET_CONFIGURATION, index, 0, 0);
    do {      
        if (0 == USBTokenOUT(setup, dbuffer, 0))
        {
            return(0);
        }
    } while(retry--);
    
    std_error=stderr_host;
    return(1);
}


//============================================================================
//函数名: USBGetDeviceDesc
//功  能: 获取USB设备描述符
//参  数: res 说明：SetPacket包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_8 USBGetDeviceDesc(StructDevDesc *res)
{
    uint_8 setup[8];
    uint_8 retry=3;
    USBFillSetupPacket(setup, STP_DIR_IN, STP_TYPE_STD, STP_RECIPIENT_DEVICE,
                      STDRQ_GET_DESCRIPTOR, (STDDTYPE_DEVICE<<8)|0, 0, 18);

    
    do
    {
        if (18 == USBTokenIN(setup, dbuffer, 0))
        {
            if ((USBDSC_TYPE(dbuffer) == STDDTYPE_DEVICE)
                && (USBDSC_LENGTH(dbuffer) <= 18))   
            {
                res->clas    = DEVDESC_CLASS(dbuffer);
                res->sclas   = DEVDESC_SCLASS(dbuffer); 
                res->protocol= DEVDESC_PROTOCOL(dbuffer); 
                res->rev     = DEVDESC_REV(dbuffer);      
                res->vid     = DEVDESC_VID(dbuffer);    
                res->pid     = DEVDESC_PID(dbuffer);     
                res->ncfg    = DEVDESC_NCFG(dbuffer);  
                
                return(1);
            }
        }
    } while(retry--);
            
    return(0);
}

//============================================================================
//函数名: USBGetConfigDesc
//功  能: 获取USB设备配置描述符
//参  数: res 说明：SetPacket包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_8 USBGetConfigDesc(StructConfigDesc *res,uint_8 index)
{    
    uint_8 setup[8];
    uint_16 length=5;
    uint_8 retry=3;

 
    do {
        USBFillSetupPacket(setup, STP_DIR_IN, STP_TYPE_STD, STP_RECIPIENT_DEVICE,
                   STDRQ_GET_DESCRIPTOR, (uint_16)((STDDTYPE_CONFIGURATION<<8)|index),
                   0, length);


        if (length == USBTokenIN(setup, dbuffer, 0))
        {

            if ((USBDSC_TYPE(dbuffer) == STDDTYPE_CONFIGURATION)
                && (USBDSC_LENGTH(dbuffer) <= 9))
            {
                length = RD_LE16(dbuffer+2);       
                USBFillSetupPacket(setup, STP_DIR_IN, STP_TYPE_STD, STP_RECIPIENT_DEVICE,
                        STDRQ_GET_DESCRIPTOR, (uint_16)((STDDTYPE_CONFIGURATION<<8)|index), 0, length);

    
                if (length == USBTokenIN(setup, dbuffer, 0))
                {
                    res->nifc  = CONFDESC_INTRFACES(dbuffer);
                    res->ndx   = CONFDESC_MY_NDX(dbuffer);
                    res->str   = CONFDESC_MY_STR(dbuffer);
                    res->attrib= CONFDESC_ATTRIB(dbuffer);
                    res->max_power=CONFDESC_MAX_POW(dbuffer);

                    return(0);    
                }                    
            }
        }
    }while(retry--);
   return(1);

}

uint_16 USBFindInterface(uint_8 class, uint_8 sclass, uint_8 protocol)
{
    int ifc;
    uint_8 *p=dbuffer;      

    CMX_ASSERT(class != 0);
    CMX_ASSERT(USBDSC_TYPE(dbuffer) == STDDTYPE_CONFIGURATION);

    for(ifc=0; ifc < CONFDESC_INTRFACES(dbuffer); ifc++)
    {
        while(USBDSC_TYPE(p) != STDDTYPE_INTERFACE)
            p += USBDSC_LENGTH(p);
        
        if (IFCDESC_CLASS(p) == class)
        {
            if (((sclass == 0) || (IFCDESC_SCLASS(p) == sclass))
                    && ((protocol == 0) || (IFCDESC_PROTOCOL(p) == protocol)))
            { 
                return((uint_8)((uint_32)p-(uint_32)dbuffer));
            }
        }
        p+=USBDSC_LENGTH(p);
    }
    return(0);
}
//============================================================================
//函数名: USBGetInterfaceDesc
//功  能: 获取USB接口描述符
//参  数: res 说明：SetPacket包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_8 USBGetInterfaceDesc(StructInterfaceDesc *res,uint_16 offset)
{
    res->ndx     = IFCDESC_MY_NDX(&dbuffer[offset]);  
    res->alt_set = IFCDESC_ALTERNATE(&dbuffer[offset]);
    res->nep     = IFCDESC_ENDPONTS(&dbuffer[offset]); 
    res->clas    = IFCDESC_CLASS(&dbuffer[offset]);  
    res->sclas   = IFCDESC_SCLASS(&dbuffer[offset]);  
    res->protocol= IFCDESC_PROTOCOL(&dbuffer[offset]);
    res->str     = IFCDESC_MY_STR(&dbuffer[offset]);  

    return(0);
}

//============================================================================
//函数名: USBGetEpDesc
//功  能: 获取USB端点描述符
//参  数: res 说明：SetPacket包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_8 USBGetEpDesc(StructEpDesc *res,uint_16 offset)
{

    res->address  = EPDESC_ADDRESS(&dbuffer[offset]);
    res->type     = EPDESC_ATTRIB(&dbuffer[offset]); 
    res->interval = EPDESC_INTERVAL(&dbuffer[offset]); 
    res->psize    = EPDESC_PSIZE(&dbuffer[offset]);    
    
    return(0);
}

//============================================================================
//函数名: USBAddEp
//功  能: 增加USB端点
//参  数: type     说明:类型
//       address  说明:地址
//       interval 说明:间隔
//       psize    说明:大小
//返  回: 0=成功；1=失败
//============================================================================
uint_8 USBAddEp(uint_8 type, uint_8 address, uint_8 interval, uint_16 psize)
{
    uint_8 x;
  

    if ((USB0_CTL & USB_CTL_HOSTMODEEN_MASK) == 0)
    {
        tr_error=tre_not_running;
        return(INVALID_ADDRESS);
    }

    for(x=0; x < MAX_EP_PER_DEVICE; x++)
    {
        if (my_device.eps[x].address == INVALID_ADDRESS)
        {
            my_device.eps[x].type    = type;
            my_device.eps[x].address = (uint_8)(address & 0x7f);
            my_device.eps[x].interval= interval;
            my_device.eps[x].psize   = psize;
            my_device.eps[x].tgl_rx  = 0;
            my_device.eps[x].tgl_tx  = 0;
            my_device.eps[x].last_due= 0;

            return(x);
        }
    }
    return(INVALID_ADDRESS);
}

//============================================================================
//函数名: USBFillSetupPacket
//功  能: 设置SetupPacket
//参  数: 详见SetupPack包的包结构
//返  回: 0=成功；1=失败
//============================================================================
void USBFillSetupPacket(uint_8 * dst, uint_8 dir, uint_8 type, uint_8 recipient,
                       uint_8 req, uint_16 val, uint_16 ndx, uint_16 len)
{
    dst[0] = (uint_8)(dir | type | recipient);
    dst[1] = req;
    dst[2] = (uint_8)val;
    dst[3] = (uint_8)(val>>8);
    dst[4] = (uint_8)ndx;
    dst[5] = (uint_8)(ndx>>8);
    dst[6] = (uint_8)(len);
    dst[7] = (uint_8)(len>>8);
}

//============================================================================
//函数名: USBTokenIN
//功  能: 令牌IN包
//参  数: 详见SetupPack包的包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_16 USBTokenIN(uint_8 *setup, uint_8* buffer, uint_8 ep)
{
    uint_32 curr=0;
    uint_16 length = RD_LE16(setup+6);


    if ((USB0_CTL & USB_CTL_HOSTMODEEN_MASK) == 0)
    {
        tr_error = tre_not_running;
        return((uint_16) -1u);
    }

    if (((uint_16)-1u) == USBStartTransaction(TRT_SETUP, setup, 8, ep))
    {
        return((uint_16)-1u);
    }

    while(curr < length)
    {
        uint_16 got,
        psize=(uint_16)(MIN(my_device.eps[ep].psize, length));
        got = USBStartTransaction(TRT_IN, buffer+curr, psize, ep);
        curr += got;
        if (got == ((uint_16)-1u))
        {
            return((uint_16)-1u);
        }
        if (got != my_device.eps[ep].psize)
        {
            break;
        }
    }

    my_device.eps[0].tgl_tx = BDT_CTL_DATA;
    if (((uint_16)-1u) == USBStartTransaction(TRT_OUT, (void *)0, 0, ep))
    {
        return((uint_16)-1u);
    }

    return((uint_16)curr);
}

//============================================================================
//函数名: USBTokenOUT
//功  能: 令牌OUT包
//参  数: 详见SetupPack包的包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_16 USBTokenOUT(uint_8 *setup, uint_8* buffer, uint_8 ep)
{
    uint_32 curr=0;
    uint_16 length=RD_LE16(setup+6);
  
    MKDBG_TRACE(ev_send_control, ep);
  

    if ((USB0_CTL & USB_CTL_HOSTMODEEN_MASK) == 0)
    {
        tr_error=tre_not_running;
        return((uint_16)-1u);
    }
  

    if (((uint_16)-1u) == USBStartTransaction(TRT_SETUP, setup, 8, ep))
    {
        return((uint_16)-1u);
    }

    while(curr<length)
    {
        uint_16 psize=(uint_16)(MIN(my_device.eps[ep].psize, length));
        uint_8 r=(uint_8)USBStartTransaction(TRT_OUT, buffer+curr, psize, ep);
        if (r != psize)
        {
            CMX_ASSERT(r==((uint_8)-1u));
            return((uint_16)-1u);
        }
        curr += psize;
    }

    my_device.eps[ep].tgl_rx = BDT_CTL_DATA;
    if (((uint_16)-1u)==USBStartTransaction(TRT_IN, (void *)0, 0, ep))
    {
        return((uint_16)-1u);
    }

    return((uint_16)curr);
}


//============================================================================
//函数名: USBWaitTokenFinish
//功  能: 等待令牌包结束
//参  数: 详见SetupPack包的包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_8 USBWaitTokenFinish()
{
    tr_error_t state;
    
    state = tre_none;
    while(USB0_CTL & USB_CTL_TXSUSPENDTOKENBUSY_MASK)  //该位置1，USB模块将处理USB令牌，此时不能向USB_STAT写令牌
    {
        if (USB0_ISTAT & USB_ISTAT_USBRST_MASK)//发生复位中断
        {
            USB0_CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
            USBDeviceDisConnect();
            state = tre_disconnected;            
        }
    }
    return(state);
}

//============================================================================
//函数名: USBHostSleep
//功  能:  USB休眠
//参  数: 详见SetupPack包的包结构
//返  回: 0=成功；1=失败
//============================================================================
void USBHostSleep(void)
{
    USB0_ISTAT = USB_ISTAT_RESUME_MASK | USB_ISTAT_SOFTOK_MASK;
    
    USB0_CTL &= ~USB_CTL_USBENSOFEN_MASK;//禁止USB模块
    Delay(3);                             
}

//============================================================================
//函数名: USBStartTransaction
//功  能: USB开始传输事务
//参  数: 详见SetupPack包的包结构
//返  回: 0=成功；1=失败
//============================================================================
uint_16 USBStartTransaction(uint_8 type, uint_8 *buffer, uint_16 length,
        uint_8 ep)
{
    uint_8 token,numcicli;
    uint_32* bdt_ctl;
    uint_8 retry=3;
    USB_MemMapPtr USBPTR = USB0_BASE_PTR;
    uint_16 elapsed;

    if ((USB0_CTL & USB_CTL_HOSTMODEEN_MASK) == 0)
    {
        tr_error = tre_not_running;
        return((uint_16) -1u);
    }

    if (my_device.address == INVALID_ADDRESS)
    {
        tr_error = tre_no_device;
        return((uint_16)-1u);
    }

    if (my_device.eps[ep].address == INVALID_ADDRESS)
    {
        tr_error = tre_no_ep;
        return((uint_16)-1u);
    }

    USB0_ADDR = (uint_8)((my_device.low_speed == USB_SPEED_FULL)?
                        my_device.address :
                        my_device.address | USB_ADDR_LSEN_MASK);

    USB0_ENDPT0 =
    (my_device.low_speed == USB_SPEED_LOW ? (USB_ENDPT_HOSTWOHUB_MASK) : 0) | (USB_ENDPT_RETRYDIS_MASK) |
        USB_ENDPT_EPTXEN_MASK | USB_ENDPT_EPRXEN_MASK | USB_ENDPT_EPHSHK_MASK;

        USB0_SOFTHLD = USBCFG_THSLD_DELAY;

    USB0_ISTAT = 0xFF;

    USB0_ISTAT |= USB_ISTAT_SOFTOK_MASK;
    USB0_ERRSTAT = 0xFF;

    do
    {
        tr_error=tre_none;
        retry--;
        switch(type)
        {
            case TRT_SETUP:
                USBPTR->ENDPOINT[0].ENDPT = 0x4d;
                USB0_ENDPT0 = 0x0d;


                my_device.eps[ep].tgl_tx=1;
                my_device.eps[ep].tgl_rx=1;

                WR_LE32(&BDT_ADR_TX(0, ep_info.next_tx), (uint_32)buffer);
                bdt_ctl = &BDT_CTL_TX(0, ep_info.next_tx);
                WR_LE32(bdt_ctl, (0x08<<16) | BDT_CTL_OWN | (0<<2));

                tr_error = (tr_error_t)USBWaitTokenFinish();
                if(tr_error == tre_disconnected)
                    return((uint_16)-1u);
                USB0_TOKEN = (uint_8)((TOKEN_SETUP<<4) | (my_device.eps[ep].address | (0<<7)));
                break;
            case TRT_IN:
                USB0_ENDPT0 = 0x0d;
                WR_LE32(&BDT_ADR_RX(0, ep_info.next_rx), (uint_32)buffer);

                bdt_ctl=&BDT_CTL_RX(0, ep_info.next_rx);
                WR_LE32(bdt_ctl, (length<<16) | BDT_CTL_OWN | my_device.eps[ep].tgl_rx);
                my_device.eps[ep].tgl_rx =(uint_8)(my_device.eps[ep].tgl_rx ? 0 : BDT_CTL_DATA);

                tr_error = (tr_error_t)USBWaitTokenFinish();
                if(tr_error == tre_disconnected)
                    return((uint_16)-1u);

                USB0_TOKEN=(uint_8)((TOKEN_IN<<4) | (my_device.eps[ep].address | (1<<7)));
                break;
            case TRT_OUT:

                USB0_ENDPT0 = 0x0d;
                WR_LE32(&BDT_ADR_TX(0, ep_info.next_tx), (uint_32)buffer);

                bdt_ctl=&BDT_CTL_TX(0, ep_info.next_tx);
                WR_LE32(bdt_ctl, (length<<16) | BDT_CTL_OWN | my_device.eps[ep].tgl_tx);
                my_device.eps[ep].tgl_tx = (uint_8)(my_device.eps[ep].tgl_tx ? 0 : BDT_CTL_DATA);

                tr_error = (tr_error_t)USBWaitTokenFinish();
                if(tr_error == tre_disconnected)
                {
                    return((uint_16)-1u);
                }

                USB0_TOKEN=(uint_8)((TOKEN_OUT<<4) | (my_device.eps[ep].address | (0<<7)));
                break;
            default:
                CMX_ASSERT(0);
        }

        if (type== TRT_SETUP || type == TRT_OUT)
            ep_info.next_tx ^= 0x1u;
        else
            ep_info.next_rx ^= 0x1u;

        numcicli=0;

        while((USB0_ISTAT & (USB_ISTAT_TOKDNE_MASK | USB_ISTAT_STALL_MASK | USB_ISTAT_ERROR_MASK)) ==0)
        {
            USB0_ISTAT = USB_ISTAT_TOKDNE_MASK | USB_ISTAT_STALL_MASK | USB_ISTAT_ERROR_MASK;

            do
            {
                numcicli++;
                elapsed=(uint_16)(K60_USB_FRM_NUM - my_device.eps[ep].last_due);
                elapsed &= ((1<<11)-1);
                if (USB0_ISTAT & USB_ISTAT_USBRST_MASK)
                {
                    USBDeviceDisConnect();
                    tr_error=tre_disconnected;
                    return((uint_16)-1u);
                }
            } while(elapsed < my_device.eps[ep].interval);

            my_device.eps[ep].last_due += my_device.eps[ep].interval;
            my_device.eps[ep].last_due &= ((1<<11)-1);

            if(numcicli<3)
            {
                Delay(my_device.eps[ep].interval);
                elapsed=(uint_16)(K60_USB_FRM_NUM);
                elapsed &= ((1<<11)-1);
                my_device.eps[ep].last_due=elapsed;
            }
            else
            {
                break;
            }
        }
        while((USBFlag & USB_ISTAT_TOKDNE_MASK) == 0){}

        USBFlag &= ~USB_ISTAT_TOKDNE_MASK;

        if(USB0_ERRSTAT & (USB_ERREN_PIDERREN_MASK |

                    USB_ERREN_CRC16EN_MASK |
                    USB_ERREN_DFN8EN_MASK |

                    USB_ERREN_DMAERREN_MASK |
                    USB_ERREN_BTSERREN_MASK))

        {
            USB0_ERRSTAT = 0xff;
            USB0_ISTAT |= USB_ISTAT_ERROR_MASK;

            tr_error=tre_data_error;
            continue;
        }

        USB0_ISTAT = USB_ISTAT_TOKDNE_MASK;
        USB0_CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;


        if (USB0_ISTAT & USB_ISTAT_STALL_MASK)
        {
            USB0_ISTAT=USB_ISTAT_STALL_MASK;
            tr_error = tre_stall;
            return((uint_16)-1u);
        }

        token=(uint_8)((RD_LE32(bdt_ctl) >> 2) & 0x0f);
        switch (token)
        {
            case TOKEN_NAK:
                if (my_device.eps[ep].type == EPTYPE_INT)
                    return(0);
                break;
            case TOKEN_STALL:
                tr_error=tre_stall;
                return((uint_16)-1u);
            case 0xf:
                MKDBG_TRACE(ev_got_data_error, ep);
                tr_error=tre_data_error;
                break;
            case 0:
                MKDBG_TRACE(ev_got_unknown, ep);
                tr_error=tre_silent;
                break;
            case 0x03:
            case 0x0b:
            case TOKEN_ACK:
            default:
                return((uint_16)((RD_LE32(bdt_ctl) >> 16u) & 0x3ffu));
        }
    }while(retry);
    return((uint_16)-1u);
}


#define ConuteTo1S 0x2DC6C00u
#define ConuteTo1MS 0xBB80u
#define ConuteTo1NS 0x30u
void PITInit(uint_8 PITChannel,uint_32 times,uint_8 timeType)
{
    uint_32 MAXCount;
    
    if(timeType == 0)
    {
        MAXCount = times * ConuteTo1NS;
    }
    else if(timeType == 1)
    {        
        MAXCount = times * ConuteTo1MS;        
    }
    else
    {
        MAXCount = times * ConuteTo1S;
    }
    
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
    
    PIT_MCR_REG(PIT_BASE_PTR) &= ~(
                                 PIT_MCR_MDIS_MASK | 
                                 PIT_MCR_FRZ_MASK
                                 );
    
    PIT_LDVAL_REG(PIT_BASE_PTR,PITChannel) = MAXCount;
    PIT_TCTRL_REG(PIT_BASE_PTR,PITChannel) = PIT_TCTRL_TIE_MASK;
}

void PITStart(uint_8 PITChannel)
{
    PIT_TCTRL_REG(PIT_BASE_PTR,PITChannel) |= PIT_TCTRL_TEN_MASK;
}

void PITStop(uint_8 PITChannel)
{
    PIT_TCTRL_REG(PIT_BASE_PTR,PITChannel) &= ~PIT_TCTRL_TEN_MASK;
}

uint_8 PITTimeCheck(uint_8 PITChannel)
{
    if((PIT_TFLG_REG(PIT_BASE_PTR,0) & PIT_TFLG_TIF_MASK) == PIT_TFLG_TIF_MASK)
    {
        PIT_TFLG_REG(PIT_BASE_PTR,0) |= PIT_TFLG_TIF_MASK;
        return 1;
    }
    else
    {
        return 0;
    }
}

void Delay(uint_32 time)
{
    PITInit(0,time,1);
    PITStart(0);
    while(PITTimeCheck(0) == 0)
    {
    }
    PITStop(0);
}
int scsi_init(void)
{
//    transfer = 0;
    lun.error_code = LERR_INVALID_DEVICE;
    lun.sector_size= 0;
    return(0);
}




int scsi_reset_lun(void)
{   
    lun.error_code=LERR_NONE;
    lun.pdt=0;
    lun.no_of_sectors=0;
    lun.prod_id[0]='\0';
    lun.rev[0]='\0';
    lun.vendor[0]='\0';
    lun.sector_size=0;
    lun.sense_data=0;
    lun.sense_info=0;


    if (scsi_cmd_inquiry())
    {
        return(1);
    }

    scsi_cmd_test_unit_ready();

    if (scsi_cmd_read_capacity())
        return(1);
    return(0);
}


int scsi_open_device()
{ 
    int r=0;
  
//    CMX_ASSERT(f != 0);
  
//    transfer=f;
    r=scsi_reset_lun();
    return(r);
}


int scsi_close_device()
{
//    transfer=0;
    lun.error_code=LERR_INVALID_DEVICE;
    lun.sector_size=0;
    return(0);
}

int scsi_get_sectors_no()
{
    return lun.no_of_sectors;
}


int scsi_get_sectors_size()
{
    return lun.sector_size;
}


static int scsi_cmd_inquiry(void)
{
    uint_8 i = 0;
    int err;
        union {
        uint_8 cmd[6];
        uint_8 resp[36];
    } data;
  
    data.cmd[0]=SCSI_CMD_INQUIRY;
    data.cmd[1]=0 << 5;
    data.cmd[2]=0;     
    data.cmd[3]=0;    
    data.cmd[4]=36; 
    data.cmd[5]=0;    

//    err=(*transfer)(6, &data.cmd[0], DIR_IN, 36, &data.resp[0]);
    err=usb_device_transfer(6, &data.cmd[0], DIR_IN, 36, &data.resp[0]);

    if (err)
    {
        switch(err)
        {
            case ERR_IO_NONE:   
                break;
            case ERR_IO_CHECK: 
                break;
            case ERR_IO_REMOVED:
                lun.error_code=LERR_CRITICAL_ERROR;
                return(1);
            case ERR_IO_READ:
                lun.error_code=LERR_IOREAD_ERROR;
                return(1);
            case ERR_IO_WRITE:
                lun.error_code=LERR_IOWRITE_ERROR;
                return(1);
        }
    }
    
    lun.pdt=(char)(data.resp[0] & 0x1f);

    for(i = 0;i < 8;i++)
    {
        lun.vendor[i] = data.resp[8+i];
    }

    
    for(i = 0;i < 16;i++)
    {
        lun.prod_id[i] = data.resp[16+i];
    }

    
    for(i = 0;i < 4;i++)
    {
        lun.rev[i] = data.resp[32+i];
    }

    
    lun.no_of_sectors = 0;

    lun.error_code=LERR_NONE;
    return(0);
}


static int scsi_cmd_read_capacity()
{
    uint_32 i= 0;
    struct {
        uint_8 cmd[10];
        uint_8 resp[8];
    } data;
    int err;

    lun.no_of_sectors=0;
    lun.sector_size=0;


    data.cmd[0]=SCSI_CMD_READ_CAPACITY;
    data.cmd[1]=0 << 5;
    data.cmd[2]=data.cmd[3]=data.cmd[4]=data.cmd[5]=0;
    data.cmd[6]=data.cmd[7]=0;
    data.cmd[8]=0;          
    data.cmd[9]=0;      
 
    while(1)
    {
//        err=(*transfer)(10, &data.cmd[0], DIR_IN, 8, &data.resp[0]);
        err=usb_device_transfer(10, &data.cmd[0], DIR_IN, 8, &data.resp[0]);
        if (err)
        {
            switch(err)
            {
                case ERR_IO_NONE:
                    break;
                case ERR_IO_CHECK:
                    if (scsi_cmd_request_sense()) 
                        return(1);      
                    for(i = 0;i < 100000;i++);
                    continue;
                case ERR_IO_REMOVED:
                    lun.error_code=LERR_CRITICAL_ERROR;
                    return(1);
                case ERR_IO_READ:
                    lun.error_code=LERR_IOREAD_ERROR;
                    return(1);
                case ERR_IO_WRITE:
                    lun.error_code=LERR_IOWRITE_ERROR;
                    return(1);
            }
        }
        break;
    }
    lun.no_of_sectors=RD_BE32(data.resp);
    lun.sector_size=(uint_32)(((uint_32)data.resp[4]) << 24 | ((uint_32)data.resp[5]) << 16
                             |((uint_32)data.resp[6]) << 8 |((uint_32)data.resp[7]) << 0);//RD_BE32(data.resp+4);
    return(0);
}


static int scsi_cmd_test_unit_ready()
{
    uint_8 cmd[6];    
    int err;


    cmd[0]=SCSI_CMD_TEST_UNIT_READY;
    cmd[1]=0<<5;
    cmd[2]=cmd[3]=cmd[4]=0; 
    cmd[5]=0;               
    
//    err=(*transfer)(6, &cmd[0], DIR_NONE, 0, 0);
    err=usb_device_transfer(6, &cmd[0], DIR_NONE, 0, 0);
    if (err)
    {
        switch(err)
        {
            case ERR_IO_NONE:
                break;
            case ERR_IO_CHECK:    
                break;
            case ERR_IO_REMOVED:
                lun.error_code=LERR_CRITICAL_ERROR;
                return(1);
            case ERR_IO_READ:
                lun.error_code=LERR_IOREAD_ERROR;
                return(1);
            case ERR_IO_WRITE:
                lun.error_code=LERR_IOWRITE_ERROR;
                return(1);
        }
    }
    return(0);
}


int scsi_cmd_request_sense()
{
    union {
        uint_8 cmd[6];
        uint_8 resp[18];
    } data;
    int err;


    data.cmd[0]=SCSI_CMD_REQUEST_SENSE;
    data.cmd[1]=0<<5;
    data.cmd[2]=data.cmd[3]=0;
    data.cmd[4]=18;
    data.cmd[5]=0;

//    err=(*transfer)(6, &data.cmd[0], DIR_IN, 18, &data.resp[0]);
    err=usb_device_transfer(6, &data.cmd[0], DIR_IN, 18, &data.resp[0]);
    if (err)
    {
        switch(err)
        {
            case ERR_IO_NONE:
                break;
            case ERR_IO_CHECK:
            case ERR_IO_REMOVED:
                lun.error_code=LERR_CRITICAL_ERROR;
                return(1);
            case ERR_IO_READ:
                lun.error_code=LERR_IOREAD_ERROR;
                return(1);
            case ERR_IO_WRITE:
                lun.error_code=LERR_IOWRITE_ERROR;
                return(1);
        }
    }

    CMX_ASSERT(data.resp[0] == 0x70);

    if (data.resp[0] == 0x70)
    {
        lun.sense_key = data.resp[2];
        lun.sense_data = data.resp[12];
        lun.sense_qualifyer = data.resp[13];
        lun.sense_info = (uint_32)(((uint_32)data.resp[3]) << 24 | ((uint_32)data.resp[4]) << 16
            |((uint_32)data.resp[5]) << 8 |((uint_32)data.resp[6]) << 0);//RD_BE32(&data.resp[3]);
    }
    else
    {
        CMX_ASSERT(0);
    }
    return(0);
}

int scsi_get_device_string(uint_8 *buffer, uint_8 len)
{
    int i = 0;
    
    if(len < 32)
    {
        return 1;
    }

    for(i = 0;i < 8;i++)
    {
        buffer[i] = lun.vendor[i];
    }
    buffer[i] = ' ';

    for(i = 0;i < 16;i++)
    {
        buffer[9 + i] = lun.prod_id[i];
    }

    buffer[25] = ' ';
    buffer[26] = 'V';
    for(i = 0;i < 4;i++)
    {
        buffer[27 + i] = lun.rev[i];
    }
    buffer[31] = 0;

    return 0;
}
int usb_mst_reset(void)
{
    unsigned char setup[8]={
        (0<<7) | (1<<5) | 1      
        ,RQMST_MASS_STORAGE_RESET
        ,0,0                   
        ,0,0                      
        ,0,0                   
    };

    mst_info.mst_error=msterr_none;
    if (0!=USBTokenOUT((uint_8 *)setup, 0, 0))
    {
        mst_info.mst_error=msterr_comunication_error;
        return(1);
    }

    return(0);
}

int usb_clear_stall_rd(void)
{
    uint_8 setup[8];
    mst_info.mst_error=msterr_none;
    USBFillSetupPacket(setup, STP_DIR_OUT, STP_TYPE_STD, STP_RECIPIENT_ENDPT
        ,STDRQ_CLEAR_FEATURE, 0, (uint_8)(mst_info.in_ep|0x80), 0);
    if (0!=USBTokenOUT((uint_8 *)setup, 0, 0))
    {
        mst_info.mst_error=msterr_comunication_error;
        return(1);
    }
    return(0);
}

int usb_clear_stall_wr(void)
{
    uint_8 setup[8];
    mst_info.mst_error=msterr_none;  
    USBFillSetupPacket(setup, STP_DIR_OUT, STP_TYPE_STD, STP_RECIPIENT_ENDPT
        ,STDRQ_CLEAR_FEATURE, 0, mst_info.out_ep, 0);
    if (0!=USBTokenOUT((uint_8 *)setup, 0, 0))
    {
        mst_info.mst_error=msterr_comunication_error;
        return(1);
    }
    return(0);
}

int usb_mst_getnlun(void)
{
    unsigned char nlun=0;

    unsigned char setup[8]={
        (1<<7) | (1<<5) | 1      
        ,RQMST_GET_MAX_LUN       
        ,0,0                     
        ,0,0                    
        ,1,0                      
    };
    mst_info.mst_error=msterr_none;
    if (1 != USBTokenIN((uint_8 *)setup, &nlun, 0))
    {
        if (tr_error != tre_stall)
        {        
            mst_info.mst_error=msterr_comunication_error;
            return(-1);
        }
        nlun=0;
    }
    return(nlun);
}


static int usb_mst_search_ifc(void)
{
    StructDevDesc dev_inf;             
    StructConfigDesc cfg_inf;          
    StructInterfaceDesc interface_inf; 
    StructEpDesc ep_inf;               
    uint_8 cfg;
    uint_16 ifc;
    uint_8 ep;
    uint_8 state;
    mst_info.ifcd_offset=0;
    
    if(!USBHostScan())   //检测是否有USB设备连接
    {
        return(0);
    }

    if(my_device.address != 1)
    {
        return(0);
    }


    if(!USBGetDeviceDesc(&dev_inf))//获取USB设备描述符
    {
        return(0);
    }


    for(cfg=0; cfg < dev_inf.ncfg; cfg++)
    {
        state = USBGetConfigDesc(&cfg_inf,0);//获取USB设备配置描述符
        if(state == 1)
        {
            continue;
        }
        
        ifc = USBFindInterface(0x08, 0, 0);

        if (!ifc)
        {
            continue;
        }


        USBGetInterfaceDesc(&interface_inf,9+0);//获取USB接口描述符

        if(interface_inf.sclas != 0x6 && interface_inf.protocol != 0x50)  //只支持SCSI命令和bulk传输类型
        {
            continue;
        }

        mst_info.cfg_ndx    = cfg_inf.ndx;
        mst_info.ifc_ndx    = interface_inf.ndx;
        mst_info.ifcd_offset= ifc;
        mst_info.alt_set    = interface_inf.alt_set;

        for(ep=0; ep < interface_inf.nep; ep++)
        {
            USBGetEpDesc(&ep_inf,9+9+ep*7);//获取USB端点描述符
            if (ep_inf.type==EPTYPE_BULK)
            {
                if (ep_inf.address > 0x80)
                {
                    mst_info.in_ep=USBAddEp(ep_inf.type, (uint_8)ep_inf.address, 0, ep_inf.psize);
                    
                }
                else
                {
                    mst_info.out_ep=USBAddEp(ep_inf.type, (uint_8)ep_inf.address, 0, ep_inf.psize);

                }
            }
        }
    
        if (mst_info.in_ep == 0 || mst_info.out_ep == 0)
        {
            continue;
        }

        USBSetConfig(mst_info.cfg_ndx);
        return(1);
    }
    return(0);  
}

int usb_mst_init(void)
{
    mst_info.mst_error = msterr_none;
    mst_info.nlun=0;
    if (usb_mst_search_ifc())
    {   
        mst_info.nlun=(uint_8)(usb_mst_getnlun()+1u);
  
        if (mst_info.nlun == 0)
            return(0);
    }
    return(mst_info.nlun);
}

int usb_mst_soft_reset_recovery(void)
{
    if (usb_mst_reset())
    {
        return(ERR_IO_REMOVED);
    }

    if (usb_clear_stall_rd())
    {
        return(ERR_IO_REMOVED);
    }

    if (usb_clear_stall_wr())
    {
        return(ERR_IO_REMOVED);
    }
    return(0);
}



uint_8 GetMSTStat(void)
{
  return Stat;
}

void SetMSTStat(uint_8 state)
{
  Stat = state;
}
