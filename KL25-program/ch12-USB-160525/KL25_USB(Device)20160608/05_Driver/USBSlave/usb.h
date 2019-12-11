//==========================================================================
// �ļ����ƣ�usb.h                                                          
// ���ܸ�Ҫ��USB�ײ���������ͷ�ļ�
// ��Ȩ����: ���ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
// �汾����: 2012-12-14     V1.0        USB������ʼ�汾
//          2012-12-20     V1.2        USB�����Ż��޸�
//==========================================================================
#ifndef _USB_H
#define _USB_H

#include "common.h"

//USB�ж����ͺ궨��
#define USB_TOKDNE_INT    (0)   //�����ж�
#define USB_RST_INT      (1)   //��λ�ж�
#define USB_SOF_INT      (2)   //SOF�ж�
#define USB_STALL_INT    (3)   //STALL�ж�
#define USB_SLEEP_INT    (4)   //SLEEP�ж�
#define USB_ERROR_INT    (5)   //ERROR�ж�

#define USB_INTERRUPT_IRQ   (24)    //USB�ж������

//�Ĵ�������
#define FLAG_SET(BitNumber, Register)   (Register |=(1<<BitNumber))
#define FLAG_CLR(BitNumber, Register)   (Register &=~(1<<BitNumber))
#define FLAG_CHK(BitNumber, Register)   (Register & (1<<BitNumber))


#define USB_FMC_ACC_ENABLE      FLAG_SET(FMC_PFAPR_M4AP_MASK,FMC_PFAPR)
#define USB_REG_SET_ENABLE      FLAG_SET(SIM_SOPT1_USBREGEN_SHIFT,SIM_SOPT1)
#define USB_REG_CLEAR_ENABLE    FLAG_CLR(SIM_SOPT1_USBREGEN_SHIFT,SIM_SOPT1)
#define USB_REG_SET_STDBY       FLAG_SET(SIM_SOPT1_USBSSTBY_SHIFT,SIM_SOPT1)
#define USB_REG_CLEAR_STDBY     FLAG_CLR(SIM_SOPT1_USBSSTBY_SHIFT,SIM_SOPT1)

#define EP_OUT          3      //�˵��3���������д���
#define EP_IN           2      //�˵��2���������д���

#define mEP2_IN       0x28     //״̬�Ĵ�������ʾ�˵�2   ����
#define mEP3_OUT      0x30     //״̬�Ĵ�������ʾ�˵�3   ����

#define USB_FARCTIONAL_VALUE    0x02

#define DISABLE_USB (USBCTL0 = 0x00)
#define ENDPOINTS   3

//EP0����������
#define EP0_SIZE            32

//EP1����
#define EP1_VALUE           _EP_IN      //�˵�1����ʹ��λ
#define EP1_TYPE            INTERRUPT   //�����жϵ�
#define EP1_SIZE            32
#define EP1_BUFF_OFFSET     0x18

//EP2����
#define EP2_VALUE           _EP_IN      //����ʹ��λ 0x04
#define EP2_TYPE            BULK        //���ݴ���
#define EP2_SIZE            32
#define EP2_BUFF_OFFSET     0x20

//EP3����
#define EP3_VALUE           _EP_OUT     //����ʹ��  0x08
#define EP3_TYPE            BULK        //���ݴ���
#define EP3_SIZE            32
#define EP3_BUFF_OFFSET     0x28

//EP4����
#define EP4_VALUE           DISABLE
#define EP4_SIZE            1
#define EP4_BUFF_OFFSET     0x08

//EP5����
#define EP5_VALUE           DISABLE
#define EP5_SIZE            1
#define EP5_BUFF_OFFSET     0x08

//EP6����
#define EP6_VALUE           DISABLE
#define EP6_SIZE            1
#define EP6_BUFF_OFFSET     0x08

#define EP3_CTR   tBDTtable[4].Stat._byte= kSIE    //���нӿ����� ָBDT��USBģ����� ���� MCU
                                                   //��USB�豸���յ���Ϣ������SIE������������ݷ���
                                                   //ָ���˵�Ľ��ܻ���ȥ����

#define usbSIE_CONTROL(EP)   (tBDTtable[EP<<2].Stat._byte= kSIE)
#define usbMCU_CONTROL(EP)   (tBDTtable[EP<<2].Stat._byte= kMCU)
#define usbEP_Reset(EP)      (tBDTtable[EP<<2].Cnt=0x0020)

#define _EP_IN      USB_ENDPT_EPTXEN_MASK        //�˵㷢��ʹ��
#define _EP_OUT     USB_ENDPT_EPRXEN_MASK        //�˵����ʹ��

#define DISABLE 0

#define INTERRUPT   0x03
#define BULK        0x05      //���ݴ���

//BDT״̬��Ϣ
#define kMCU      0x00          //BD bit7 OWNΪ0 ΢��������BDӵ�п���Ȩ
#define kSIE      0x80          //USBģ��ӵ�У�����DATA0�����ͻ����

#define kUDATA0   0x88  //USBģ��ӵ�п���Ȩ��DATA0 �����ͻ���ܣ�ʹ��USBģ��������ݷ�תͬ��  ACK��
#define kUDATA1   0xC8  //USBģ��ӵ�п���Ȩ��DATA1 �����ͻ���ܣ�ʹ��USBģ��������ݷ�תͬ��

//USB�����У�BD������Ϣ�е�PID����
#define mSETUP_TOKEN    0x0D  //�������豸�����ڿ��ƴ���
#define mOUT_TOKEN      0x01  //�������豸������
#define mIN_TOKEN       0x09  //�������豸Ҫ����

//��׼��SETUP������� bRequest�ֽ�
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

//��ȡ������   ������������ ��get_descriptor����� wValue���ֽ�
#define mDEVICE                     1
#define mCONFIGURATION              2
#define mSTRING                     3
#define mINTERFACE                  4
#define mENDPOINT                   5
#define mDEVICE_QUALIFIER           6
#define mOTHER_SPEED_CONFIGURATION  7   //��������������
#define mINTERFACE_POWER            8

#define mREPORT                     0x22

//SETUP��������    ����������豸���ӿڻ��Ƕ˵�     bmRequestType�ֽ� D[6:5]������������������
#define STANDARD_REQ    0x00
#define SPECIFIC_REQ    0x20
#define VENDORSPEC_REQ  0x40

#define DEVICE_REQ      0x00
#define INTERFACE_REQ   0x01
#define ENDPOINT_REQ    0x02

//��Զ˵㣨��ӿڣ���bRequest
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

//5��״̬
enum
{
    uPOWER,               //�ѹ���״̬
    uENUMERATED,          //�ѱ�ö��״̬���ѱ�����״̬
    uENABLED,             //ʹ��
    uADDRESS,             //�����õ�ַ״̬
    uREADY                //����
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

//�����������������壬���е��������ݶ���ͬһ�������ڲ���
typedef union _tBDT_STAT
{
    uint_8 _byte;

    struct{
        uint_8 :1;
        uint_8 :1;
        uint_8 BSTALL:1;   //uint_8 :1  λ�� ���ṹ������λΪ��λ��ָ�����Ա��ռ�ڴ泤��
        uint_8 DTS:1;
        uint_8 NINC:1;
        uint_8 KEEP:1;
        uint_8 DATA:1;
        uint_8 UOWN:1;    //BDT����Ȩ      ������������BD
    }McuCtlBit;
       
    struct{
        uint_8    :2;
        uint_8 PID:4;     //����־
        uint_8    :2;
    }RecPid;
} tBDT_STAT;              //������������������

//BDT����������������
typedef struct _tBDT
{
    tBDT_STAT Stat;   //BD������Ϣ
    uint_8  dummy;    //Ϊ���뻺�����������еı���λ���Ӧ
    uint_16 Cnt;      //���յ����ݳ���
    uint_32 Addr;     //BD��ַ
} tBDT;

//SETUP���ݽṹ��
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
//������:usb_init
//��  ��: USBģ���ʼ
//��  ��:str:�豸���к�
//��  ��: ��
//=========================================================================
void usb_init(uint_8 str[]);

//=========================================================================
//������: usb_enumerate
//��  ��: USBö�٣����ڴ���USB�豸��λ��USB�������������豸����
//��  ������
//��  ��: ��
//=========================================================================
void usb_enumerate();

//=========================================================================
//������: usb_send
//��  ��: USB��������
//��  ��: buf���������ݻ����������ں�������ʱ����δ���͵�����
//      len���������ݳ���,���ں�������ʱ����ʣ��δ���͵����ݳ���
//��  ��: ʵ�ʷ��͵����ݳ���
//��  ע��һ���Դ�������ݳ����Ƕ˵���֧�ֵ�������ݳ��ȣ�32�ֽڣ���������͵����ݳ���
//      ����32�ֽڣ����Ϊ��δ��䡣
//=========================================================================
uint_8 usb_send(uint_8 *buf,uint_8 *len);

//=========================================================================
//������: usb_recv
//��  ��: USB��������
//��  ��: buf:�������ݻ�����
//      len:��������ʱ���������յ����ݳ���
//��  ��: �ɹ������ؽ������ݵĳ��ȣ�ʧ�ܣ�����0
//=========================================================================
uint_8 usb_recv(uint_8 *buf,uint_8 *len);

#endif 

//=========================================================================
//������
//��1�����ǿ�����Դ���룬�ڱ������ṩ��Ӳ��ϵͳ����ͨ������Ϸ��׸���ᣬ����֮����
//     ��ӭָ����
//��2������ʹ�÷Ǳ�����Ӳ��ϵͳ���û�����ֲ����ʱ������ϸ�����Լ���Ӳ��ƥ�䡣
//
//���ݴ�ѧ��˼����Ƕ��ʽ���ģ����ݻ�����Ϣ�Ƽ����޹�˾��
//������ѯ��0512-65214835  http://sumcu.suda.edu.cn
//ҵ����ѯ��0512-87661670,18915522016  http://www.hxtek.com.cn
