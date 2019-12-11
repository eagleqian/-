//==========================================================================
// 文件名称：usb_host.h                                                          
// 功能概要：USB底层驱动构件头文件
// 版权所有: 苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
// 版本更新: 2012-12-14     V1.0        USB构件初始版本
//          2013-2-20     V1.2         USB构件优化修改
//==========================================================================
#include "common.h"

#ifndef _USB_HOST
#define _USB_HOST

#define USB_INTERRUPT_IRQ   (24)

#define USBCFG_THSLD_DELAY 0x65

#define MKDBG_TRACE(evnt, epndx)

extern uint_32 mcf5xxx_byterev(uint_32 val);

#define MIN(a,b)  ((a) < (b) ? (a) : (b)) 
#define WR_LE32(a, v) ((*(uint_32*)(a))=(v))
#define WR_LE16(a, v) ((*(uint_16*)(a))=(uint_16)((v) >> 16))
#define RD_LE32(a)    ((*(uint_32*)(a)))
#define RD_LE16(a)    (*(uint_16*)(a))
//===============================MST==================================
#define  USB_OK                              (0x00)
#define  USBERR_ALLOC                        (0x81)
#define  USBERR_BAD_STATUS                   (0x82)
#define  USBERR_CLOSED_SERVICE               (0x83)
#define  USBERR_OPEN_SERVICE                 (0x84)
#define  USBERR_TRANSFER_IN_PROGRESS         (0x85)
#define  USBERR_ENDPOINT_STALLED             (0x86)
#define  USBERR_ALLOC_STATE                  (0x87)
#define  USBERR_DRIVER_INSTALL_FAILED        (0x88)
#define  USBERR_DRIVER_NOT_INSTALLED         (0x89)
#define  USBERR_INSTALL_ISR                  (0x8A)
#define  USBERR_INVALID_DEVICE_NUM           (0x8B)
#define  USBERR_ALLOC_SERVICE                (0x8C)
#define  USBERR_INIT_FAILED                  (0x8D)
#define  USBERR_SHUTDOWN                     (0x8E)
#define  USBERR_INVALID_PIPE_HANDLE          (0x8F)
#define  USBERR_OPEN_PIPE_FAILED             (0x90)
#define  USBERR_INIT_DATA                    (0x91)
#define  USBERR_SRP_REQ_INVALID_STATE        (0x92)
#define  USBERR_TX_FAILED                    (0x93)
#define  USBERR_RX_FAILED                    (0x94)
#define  USBERR_EP_INIT_FAILED               (0x95)
#define  USBERR_EP_DEINIT_FAILED             (0x96)
#define  USBERR_TR_FAILED                    (0x97)
#define  USBERR_BANDWIDTH_ALLOC_FAILED       (0x98)
#define  USBERR_INVALID_NUM_OF_ENDPOINTS     (0x99)
#define  USBERR_ADDRESS_ALLOC_FAILED         (0x9A)
#define  USBERR_PIPE_OPENED_FAILED           (0x9B)

#define  USBERR_DEVICE_NOT_FOUND             (0xC0)
#define  USBERR_DEVICE_BUSY                  (0xC1)
#define  USBERR_NO_DEVICE_CLASS              (0xC3)
#define  USBERR_UNKNOWN_ERROR                (0xC4)
#define  USBERR_INVALID_BMREQ_TYPE           (0xC5)
#define  USBERR_GET_MEMORY_FAILED            (0xC6)
#define  USBERR_INVALID_MEM_TYPE             (0xC7)
#define  USBERR_NO_DESCRIPTOR                (0xC8)
#define  USBERR_NULL_CALLBACK                (0xC9)
#define  USBERR_NO_INTERFACE                 (0xCA)
#define  USBERR_INVALID_CFIG_NUM             (0xCB)
#define  USBERR_INVALID_ANCHOR               (0xCC)
#define  USBERR_INVALID_REQ_TYPE             (0xCD)
#define  USBERR_ERROR                        (0xFF)


#define  USBERR_ALLOC_EP_QUEUE_HEAD          (0xA8)
#define  USBERR_ALLOC_TR                     (0xA9)
#define  USBERR_ALLOC_DTD_BASE               (0xAA)
#define  USBERR_CLASS_DRIVER_INSTALL         (0xAB)



#define  USBOTGERR_INVALID_REQUEST           (0x70)


#define USB_CONTROL_PIPE                     (0x00)
#define USB_ISOCHRONOUS_PIPE                 (0x01)
#define USB_BULK_PIPE                        (0x02)
#define USB_INTERRUPT_PIPE                   (0x03)

#define  USB_STATE_UNKNOWN                   (0xff)
#define  USB_STATE_PENDING_ADDRESS           (0x04) 
#define  USB_STATE_POWERED                   (0x03)
#define  USB_STATE_DEFAULT                   (0x02)
#define  USB_STATE_ADDRESS                   (0x01)
#define  USB_STATE_CONFIG                    (0x00)
#define  USB_STATE_SUSPEND                   (0x80)

#define  USB_SELF_POWERED                    (0x01)
#define  USB_REMOTE_WAKEUP                   (0x02)

#define  USB_NO_OPERATION                    (0x00)
#define  USB_ASSERT_BUS_RESET                (0x01)
#define  USB_DEASSERT_BUS_RESET              (0x02)
#define  USB_ASSERT_RESUME                   (0x03)
#define  USB_DEASSERT_RESUME                 (0x04)
#define  USB_SUSPEND_SOF                     (0x05)
#define  USB_RESUME_SOF                      (0x06)

#define  USB_STATUS_IDLE                     (0)
#define  USB_STATUS_STALLED                  (1) 
#define  USB_STATUS_TRANSFER_PENDING         (2)
#define  USB_STATUS_TRANSFER_IN_PROGRESS     (3)
#define  USB_STATUS_ERROR                    (4)
#define  USB_STATUS_DISABLED                 (5)
#define  USB_STATUS_TRANSFER_ACCEPTED        (6)
#define  USB_STATUS_TRANSFER_QUEUED          (7)

#define  USB_RECV                            (0)
#define  USB_SEND                            (1)

#define  USB_DEVICE_DONT_ZERO_TERMINATE      (0x1)

#define  USB_SETUP_DATA_XFER_DIRECTION       (0x80)

#define  USB_SPEED_FULL                      (0)
#define  USB_SPEED_LOW                       (1)
#define  USB_SPEED_HIGH                      (2)

#define  USB_MAX_PKTS_PER_UFRAME             (0x6)

#define MEM_TYPE_USB_BASE                    ((IO_USB_COMPONENT) << (MEM_TYPE_COMPONENT_SHIFT))
#define MEM_TYPE_USB_HOST_DEVICE             (MEM_TYPE_USB_BASE+1)
#define MEM_TYPE_USB_HOST_STATE_STRUCT          (MEM_TYPE_USB_BASE+2)
#define MEM_TYPE_USB_ISO_PACKET_DESC_STRUCT    (MEM_TYPE_USB_BASE+3)
#define MEM_TYPE_USB_HOST_PIPE_DESCRIPTORS   (MEM_TYPE_USB_BASE+4)
#define MEM_TYPE_USB_HOST_PIPE_TR_STRUCT     (MEM_TYPE_USB_BASE+5)
#define MEM_TYPE_USB_FILESYSTEM_STRUCT       (MEM_TYPE_USB_BASE+6)
#define MEM_TYPE_USB_CALLBACK_STRUCT          (MEM_TYPE_USB_BASE+7)
#define MEM_TYPE_USB_MFS_STRUCT                (MEM_TYPE_USB_BASE+8)
#define MEM_TYPE_USB_HOST_SERVICE_STRUCT     (MEM_TYPE_USB_BASE+9)

#define USB_INVALID_PARAMETER               (0x0C)
#define USB_OUT_OF_MEMORY                   (0x04)
//==============================USBMST======================================
#ifdef NDEBUG
#define CMX_ASSERT(c) (void)0
#else
#define CMX_ASSERT(c)\
do {\
  if(!(c))\
  {\
    int a=1;\
    while(a)\
      ;\
  }\
}while(0)
#endif

#define RD_BE32(X) (uint_32)(((uint_32)X[0]) << 24 | ((uint_32)X[1]) << 16 |((uint_32)X[2]) << 8 |((uint_32)X[3]) << 0)
#define WR_BE32(x,y) x[0] = (uint_8)((0xFF000000 & y)>>24);x[1] = (uint_8)((0x00FF0000 & y)>>16);x[2] = (uint_8)((0x0000FF00 & y)>>8);x[3] = (uint_8)((0x000000FF & y)>>0);
#define WR_BE16(x,y) x[0] = (uint_8)((0xFF00 & y)>>8);x[1] = (uint_8)((0x00FF & y)>>0);
#define K60_USB_FRM_NUM (USB0_ISTAT = USB_ISTAT_SOFTOK_MASK , USB0_FRMNUML | (((uint_16)USB0_FRMNUMH)<<8))
#define RETRY_WAIT_MS  10

#define SCSI_PDT_DA       0x0    
#define SCSI_PDT_CD       0x5    
#define SCSI_PDT_OM       0x7    
#define SCSI_PDT_SDA      0x0e   

#define SCSI_CMD_INQUIRY            0x12u
#define SCSI_CMD_REQUEST_SENSE      0x03u
#define SCSI_CMD_SEND_DIAGNOSTIC    0x1du
#define SCSI_CMD_TEST_UNIT_READY    0x00u

#define SCSI_CMD_FORMAT_UNIT        0x04u
#define SCSI_CMD_READ_10            0x28u
#define SCSI_CMD_READ_12            0xa8u
#define SCSI_CMD_READ_CAPACITY      0x25u
#define SCSI_CMD_RELEASE            0x17u
#define SCSI_CMD_RESERVE            0x16u
#define SCSI_CMD_WRITE_10           0x2au
#define SCSI_CMD_WRITE_12           0xaau
#define SCSI_CMD_START_STOP         0x1bu
#define SCSI_CMD_TOCPMAATIP         0x43u

#define SCSI_SK_NO_SENSE          0x00  
#define SCSI_SK_RECOVERED_ERROR   0x01  
#define SCSI_SK_NOT_READY         0x02  
#define SCSI_SK_MEDIUM_ERROR      0x03  
#define SCSI_SK_HARDWARE_ERROR    0x04  
#define SCSI_SK_ILLEGAL_REQUEST   0x05  
#define SCSI_SK_UNIT_ATTENTION    0x06  
#define SCSI_SK_ABORTED_COMMAND   
#define SCSI_SK_DATA_PROTECT            

#define LERR_NONE            0x0u   
#define LERR_INVALID_DEVICE  0x1u   
#define LERR_CRITICAL_ERROR  0x2u   
#define LERR_IOWRITE_ERROR   0x3u   
#define LERR_IOREAD_ERROR    0x4u   

#define ERR_IO_NONE     0
#define ERR_IO_CHECK    1
#define ERR_IO_REMOVED  2
#define ERR_IO_READ     3
#define ERR_IO_WRITE    4

#define DIR_NONE 2
#define DIR_IN   1
#define DIR_OUT  0

typedef struct {
    char pdt;
    char vendor[8];
    char prod_id[16];
    char rev[4];
    uint_32 no_of_sectors;
    uint_32 sector_size;
    int error_code;
    uint_8 sense_key;
    uint_8 sense_data;
    uint_8 sense_qualifyer;
    uint_32 sense_info;
} lun_info_t;
    
typedef struct {
    uint_8 rx_bd;
    uint_8 tx_bd;
} EP_STRUCT, * EP_STRUCT_PTR;

//===========================USBMST================================
typedef enum {
  msterr_none,
  msterr_comunication_error
} mst_error_t;

typedef struct {
  uint_16 ifcd_offset;
  uint_8 cfg_ndx;   //配置
  uint_8 ifc_ndx;   //接口
  uint_8 alt_set;
  uint_8 in_ep;
  uint_8 out_ep;
  uint_8 nlun;
  mst_error_t mst_error;  
} MSTInfoStruct;
//============================USBMST===============================
#define  USB_DEVICE_IDLE                   (0)
#define  USB_DEVICE_ATTACHED               (1)
#define  USB_DEVICE_CONFIGURED             (2)
#define  USB_DEVICE_SET_INTERFACE_STARTED  (3)
#define  USB_DEVICE_INTERFACED             (4)
#define  USB_DEVICE_DETACHED               (5)
#define  USB_DEVICE_OTHER                  (6)
#define  USB_DEVICE_CONNETED               (0x11)
#define  USB_RERTY_COUNT                    3
#define  RQMST_MASS_STORAGE_RESET           0xffu
#define  RQMST_GET_MAX_LUN                  0xfeu
////////////////
#define  USB_SPEED_FULL                      (0)
#define  USB_SPEED_LOW                       (1)
#define  USB_SPEED_HIGH                      (2)
////////////////

#define kUDATA0   0x88
#define kUDATA1   0xC8

// BDT status value
#define kMCU      0x00
#define kSIE      0x80

typedef union _tBDT_STAT
{
    uint_8 _byte;
    struct{
        uint_8 :1;
        uint_8 :1;
        uint_8 BSTALL:1;             
        uint_8 DTS:1;              
        uint_8 NINC:1;          
        uint_8 KEEP:1;              
        uint_8 DATA:1;           
        uint_8 UOWN:1;          
    }McuCtlBit;
       
    struct{
        uint_8    :2;
        uint_8 PID:4;           
        uint_8    :2;
    }RecPid;
} tBDT_STAT;                         
//缓冲区描述符表
typedef struct _tBDT
{
    tBDT_STAT Stat;
    uint_8  dummy;
    uint_16 Cnt;
    uint_32 Addr;
} tBDT; 

#define BDT_BASE              ((uint_32*)(tBDTtable))
#define BDT_CTL_RX(ep, b)     (BDT_BASE[((ep)<<3)+((b)<<1)+0])
#define BDT_ADR_RX(ep, b)     (BDT_BASE[((ep)<<3)+((b)<<1)+1])
#define BDT_CTL_TX(ep, b)     (BDT_BASE[((ep)<<3)+((b)<<1)+4])
#define BDT_ADR_TX(ep, b)     (BDT_BASE[((ep)<<3)+((b)<<1)+5])

#define BITX(x) (1U<<x)
#define BIT0    BITX(0)
#define BIT1    BITX(1)
#define BIT2    BITX(2)
#define BIT3    BITX(3)
#define BIT4    BITX(4)
#define BIT5    BITX(5)
#define BIT6    BITX(6)
#define BIT7    BITX(7)
#define BIT8    BITX(8)
#define BIT9    BITX(9)
#define BIT10   BITX(10)
#define BIT11   BITX(11)
#define BIT12   BITX(12)
#define BIT13   BITX(13)
#define BIT14   BITX(14)
#define BIT15   BITX(15)
#define BIT16   BITX(16)
#define BIT17   BITX(17)
#define BIT18   BITX(18)
#define BIT19   BITX(19)
#define BIT20   BITX(20)
#define BIT21   BITX(21)
#define BIT22   BITX(22)
#define BIT23   BITX(23)
#define BIT24   BITX(24)
#define BIT25   BITX(25)
#define BIT26   BITX(26)
#define BIT27   BITX(27)
#define BIT28   BITX(28)
#define BIT29   BITX(29)
#define BIT30   BITX(30)
#define BIT31   BITX(31)

#define BDT_CTL_STALL (BIT2)
#define BDT_CTL_DTS   (BIT3)
#define BDT_CTL_DATA  (BIT6)
#define BDT_CTL_OWN   (BIT7)

//令牌类型
#define TOKEN_SETUP   0xd
#define TOKEN_IN      0x9
#define TOKEN_OUT     0x1
#define TOKEN_NAK     0xa
#define TOKEN_STALL   0xe
#define TOKEN_ACK     0x2

#define INVALID_ADDRESS  ((uint_8)-1u)
#define MAX_EP_PER_DEVICE  16  

#define USBDSC_LENGTH(p)       (((uint_8*)(p))[0])
#define USBDSC_TYPE(p)         (((uint_8*)(p))[1])
//1.1 设备描述符
typedef struct {  
        uint_8  clas;    
        uint_8  sclas;   
        uint_8  protocol;
        uint_16 vid;     
        uint_16 pid;     
        uint_16 rev;     
        uint_8  ncfg;    
}StructDevDesc, * StructDevDescPtr;

#define DEVDESC_BCDUSB(p)      RD_LE16(((uint_8*)(p))+2)  
#define DEVDESC_CLASS(p)       (((uint_8*)(p))[4])        
#define DEVDESC_SCLASS(p)      (((uint_8*)(p))[5])        
#define DEVDESC_PROTOCOL(p)    (((uint_8*)(p))[6])        
#define DEVDESC_PACKET_SIZE(p) (((uint_8*)(p))[7])        
#define DEVDESC_VID(p)         RD_LE16(((uint_8*)(p))+8)  
#define DEVDESC_PID(p)         RD_LE16(((uint_8*)(p))+10) 
#define DEVDESC_REV(p)         RD_LE16(((uint_8*)(p))+12) 
#define DEVDESC_MANUFACT(p)    (((uint_8*)(p))[14))       
#define DEVDESC_PRODUCT(p)     (((uint_8*)(p))[15])       
#define DEVDESC_SERNO(p)       (((uint_8*)(p))[16])       
#define DEVDESC_NCFG(p)        (((uint_8*)(p))[17])       

//配置描述符
typedef struct {
    uint_8 nifc;        
    uint_8 ndx;         
    uint_8 str;         
    uint_8 attrib;      
    uint_8 max_power;   
}StructConfigDesc;
#define CONFDESC_TOTLENGTH(p) RD_LE16(((uint_8*)(p))+2)   
#define CONFDESC_INTRFACES(p) (((uint_8*)(p))[4])         
#define CONFDESC_MY_NDX(p)    (((uint_8*)(p))[5])         
#define CONFDESC_MY_STR(p)    (((uint_8*)(p))[6])         
#define CONFDESC_ATTRIB(p)    (((uint_8*)(p))[7])         
#define CONFDESC_MAX_POW(p)   (((uint_8*)(p))[8])     

//1.3 接口描述符
typedef struct {        
    uint_8 ndx;        
    uint_8 alt_set;    
    uint_8 nep;        
    uint_8 clas;       
    uint_8 sclas;       
    uint_8 protocol;  
    uint_8 str;      
}StructInterfaceDesc;
#define IFCDESC_MY_NDX(p)     (((uint_8*)(p))[2])
#define IFCDESC_ALTERNATE(p)  (((uint_8*)(p))[3])
#define IFCDESC_ENDPONTS(p)   (((uint_8*)(p))[4])
#define IFCDESC_CLASS(p)      (((uint_8*)(p))[5])
#define IFCDESC_SCLASS(p)     (((uint_8*)(p))[6])
#define IFCDESC_PROTOCOL(p)   (((uint_8*)(p))[7])
#define IFCDESC_MY_STR(p)     (((uint_8*)(p))[8])

//端点描述符
typedef struct {
    uint_16 psize;     
    uint_8  address;
    uint_8  type;     
    uint_8  interval; 
} StructEpDesc;
#define EPDESC_ADDRESS(p)     (((uint_8*)(p))[2])
#define EPDESC_ATTRIB(p)      (((uint_8*)(p))[3])
#define EPDESC_PSIZE(p)       (((uint_8*)(p))[4])
#define EPDESC_INTERVAL(p)    (((uint_8*)(p))[6])

//端点信息
typedef struct {
    uint_16 last_due;
    uint_16 psize; 
    uint_8  type;
    uint_8  address;
    uint_8  interval;   //间隔
    uint_8  tgl_rx;     //触发
    uint_8  tgl_tx;
}EPInfo;

//设备连接信息
typedef struct {
    uint_8  address;
    uint_8  low_speed;
    EPInfo eps[MAX_EP_PER_DEVICE];
}DeviceConect;

struct {
  uint_8 next_rx;
  uint_8 next_tx;
} ep_info;

#define MAX_EP0_PSIZE   64u
#define MIN_EP0_PSIZE   8u

#define DBUFFER_SIZE    255u

#define EPTYPE_INVALID        ((uint_8)-1u)
#define EPTYPE_CTRL           ((uint_8)0u)
#define EPTYPE_ISO            ((uint_8)1u)
#define EPTYPE_BULK           ((uint_8)2u)
#define EPTYPE_INT            ((uint_8)3u)

#define TRT_NONE  0u
#define TRT_IN    1u
#define TRT_OUT   2u
#define TRT_SETUP 3u

#define STDDTYPE_DEVICE        1u  
#define STDDTYPE_CONFIGURATION 2u   
#define STDDTYPE_STRING        3u   
#define STDDTYPE_INTERFACE     4u   
#define STDDTYPE_ENDPOINT      5u  

#define STP_DIR_IN            (1u<<7)
#define STP_DIR_OUT           (0u<<7)
#define STP_TYPE_STD          (0u<<5)
#define STP_TYPE_CLASS        (1u<<5)
#define STP_TYPE_VENDOR       (2u<<5)
#define STP_RECIPIENT_DEVICE  (0<<0)
#define STP_RECIPIENT_IFC     (1<<0)
#define STP_RECIPIENT_ENDPT   (2<<0)
#define STP_RECIPIENT_OTHER   (3<<0)

#define STDRQ_GET_STATUS         0u
#define STDRQ_CLEAR_FEATURE      1u
#define STDRQ_SET_FEATURE        3u
#define STDRQ_SET_ADDRESS        5u
#define STDRQ_GET_DESCRIPTOR     6u
#define STDRQ_SET_DESCRIPTOR     7u
#define STDRQ_GET_CONFIGURATION  8u
#define STDRQ_SET_CONFIGURATION  9u
#define STDRQ_GET_INTERFACE      10u
#define STDRQ_SET_INTERFACE      11u
#define STDRQ_SYNCH_FRAME        12u

typedef enum {
    stderr_none=0,
    stderr_host,
    stderr_bad_desc
} std_error_t;

typedef enum {
    tre_none=0,
    tre_not_running,
    tre_no_device,   
    tre_disconnected, 
    tre_stall,       
    tre_data_error, 
    tre_silent,      
    tre_no_ep      
} tr_error_t;     //错误的状态

extern MSTInfoStruct mst_info;
extern lun_info_t lun;

//==========================================================================
//函数名:USBHostInit
//功  能: USB模块初始 
//参  数: 无
//返  回: 0=成功；非0=异常
//==========================================================================
uint_8 USBHostInit(void);

//==========================================================================
//函数名:InitUSBDevice
//功  能: 初始化接入的USB设备
//参  数: device_inf:函数返回时带回初始化的USB设备信息
//返  回: 0=成功；1=异常
//==========================================================================
uint_8 InitUSBDevice(uint_8 *device_inf);

//============================================================================
//函数名: USBReadData
//功  能:  USB数据读取
//参  数:  ep:USB端点号
//        length:读的数据长度
//        ReadBuffer:存放读数据的缓冲区
//返  回: 0=成功；1=失败
////备  注：调用内部函数USBStartTransaction执行数据的读取，读取的数据可以在多个事
//       务处理中，因此需要根据端点所支持的最大数据包的长度决定执行多少次事务处理
//============================================================================
uint_16 USBReadData(uint_8 ep, uint_16 length,uint_8* ReadBuffer);

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
uint_8 USBWriteData(uint_8 ep,uint_16 length,uint_8 *WriteBuffer);

 //============================================================================
 //函数名: CheckUSBDeviceStatus
 //功   能:  检测USB设备状态
 //参   数: 无
 //返   回: 0=成功；1=失败
 //============================================================================
 uint_8 CheckUSBDeviceStatus();

#endif //USB_HOST

//===========================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，不足之处，
//     欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏州大学飞思卡尔嵌入式中心（苏州华祥信息科技有限公司）
//技术咨询：0512-65214835  http://sumcu.suda.edu.cn
//业务咨询：0512-87661670,18915522016  http://www.hxtek.com.cn
