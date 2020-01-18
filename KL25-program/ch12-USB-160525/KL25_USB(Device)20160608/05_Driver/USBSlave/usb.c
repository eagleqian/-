//=========================================================================
// �ļ����ƣ�usb.c                                                          
// ���ܸ�Ҫ��usb�ײ���������Դ�ļ�
// ��Ȩ����: ���ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
// �汾����: 2012-12-14     V1.0        USB������ʼ�汾
//           2012-12-20     V1.2        USB�����Ż��޸�
//=========================================================================
#include "usb.h"

//�豸������
static  uint_8 Device_Descriptor[18]=
{
     0x12,       //bLength���������ĳ��ȣ�18�ֽ�
    0x01,       //bDescriptorType�����������ͣ�0x01��ʾ��������Ϊ�豸��������
    0x00,0x02, //bcdUSB��USB�淶�汾�ţ�����BCD�룩��2.0
    0x02,       //bDeviceClass���豸�����
    0x00,       //bDeviceSubClass���豸�������
    0x00,       //bDeviceProtocol���豸Э����루0x00��ʾ��ʹ���κ��豸��Э�飩
    0x20,       //bMaxPacketSize0�򣬶˵�0֧��������ݰ��ĳ��ȣ�32�ֽ�
    0xA2,0x15, //idVendor�򣬹�Ӧ��ID��VID��
    0x0F,0xA5, //idProduct�򣬲�ƷID��PID��
    0x00,0x00, //bcdDevice���豸�汾�ţ�����BCD�룩
    0x01,      //iManufacturer�򣬹�Ӧ�̵��ַ���������������1
    0x02,       //iProduct�򣬲�Ʒ���ַ���������������2
    0x03,       //iSerialNumber���豸��ŵ��ַ���������������3
    0x01       //bNumConfigurations�򣬸�USB�豸֧�ֵ�������Ŀ��1��
};


//����������
static  uint_8 Configuration_Descriptor[0x20]=
{
    //����������
    0x09,            //bLength�������������ĳ��ȣ�9�ֽ�
    0x02,            //bDescriptorType��0x02��ʾ��������Ϊ����������
    0x20,0x00,        //wTotalLength��������Ϣ���ܳ��ȣ��������á��ӿںͶ˵㣩��32�ֽ�
    0x01,            //bNumInterfaces�򣬸�������֧�ֵĽӿ���������һ������1
    0x01,            //bConfigurationValue������ֵ��1
    0x00,            //iConfiguration�������ַ���������������0
    0xC0,            //bmAttibutes�����õ�����(�������߹��硢�Թ��缰���̻��ѵ�����)
                     //λ7��1-����Ϊ1��λ6��0-�Թ��磻λ5��0-��֧��Զ�̻���
    0x32,            //MaxPower���豸��������ȡ����������2mAΪ��λ��50*2mA��100mA

    //�ӿ�������
    0x09,           //bLength�򣬽ӿ����������ȣ�9�ֽ�
    0x04,           //bDescriptorType��0x04��ʾ��������Ϊ�ӿ�������
    0x00,           //bInterfaceNumber�򣬽ӿں�
    0x00,           //bAlternateSetting�򣬽ӿڵĿ��滻����ֵ
    0x02,           //bNumEndpoints�򣬽ӿ�ʹ�õĶ˵��������˵�0����2
    0xFF,           //bInterfaceClass�򣬽ӿ�������USB�豸�ࣺ0xFF��ʾ��Ӧ���Զ���
    0xFF,           //bInterfaceSubClass�򣬽ӿ�������USB�豸���ࣺ0xFF��ʾ��Ӧ���Զ���
    0xFF,           //bInterfaceProtocol�򣬽ӿڲ��õ�USB�豸��Э�飺0xFF��ʾ��Ӧ���Զ���
    0x01,           //iInterface�򣬽ӿ��ַ�����������������1

     //�˵�OUT������
    0x07,           //bLength�򣬶˵����������ȣ�7�ֽ�
    0x05,           //bDescriptorType��0x05��ʾ��������Ϊ�˵�������
    0x82,           //bEndpointAddress�򣬶˵�źʹ��䷽�򣺶˵�2��IN
    0x02,           //bmAttributes�򣬶˵����ԣ����ݶ˵㡢�鴫��
    0x20,0x00,      //wMaxPacketSize�򣬶˵�֧��������ݰ����ȣ�32�ֽ�
    0x00,           //bInterval����ѯ�������msΪ��λ��

     //�˵�IN������
    0x07,           //bLength�򣬶˵����������ȣ�7�ֽ�
    0x05,           //bDescriptorType��0x05��ʾ��������Ϊ�˵�������
    0x03,           //bEndpointAddress�򣬶˵�źʹ��䷽�򣺶˵�3��OUT
    0x02,           //bmAttributes�򣬶˵����ԣ����ݶ˵㡢�鴫��
    0x20,0x00,      //wMaxPacketSize�򣬶˵�֧��������ݰ����ȣ�32�ֽ�
    0x00,           //bInterval����ѯ�������msΪ��λ��
};

//�ַ���������0
static  uint_8 String_Descriptor0[4] =
{
    0x04,           //bLength�򣬳��ȣ�4�ֽ�
    0x03,           //bDescriptorType���ַ���������
    0x09,0x04       //wLANDID0��Ӣ��
};

//�ַ���������1
static  uint_8 String_Descriptor1[] =
{
    0x12,            //bLength�򣬳��ȣ�18�ֽ�
    0x03,            //bDescriptorType���ַ���������
    'S',0x00,        //                                       
    'U',0x00,        //
    'D',0x00,        //
    'A',0x00,        //
    '-',0x00,        //
    'N',0x00,        //
    'X',0x00,        //
    'P',0x00,        //
};     

//�ַ���������2
static  uint_8 String_Descriptor2[] =
{
    0x38,            //bLength�򣬳��ȣ�56�ֽ�
    0x03,            //bDescriptorType���ַ���������
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

////�豸�޶�������
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

uint_8 BDT[1024];   //BDT��������������ֻҪ����512�ֽ�
tBDT *BDTtable;     //4���˵��BDT 16��BD
String_Table USB_String_Table;   //USB�ַ����б�

//����˵�0������
static uint_8 gu8EP0_OUT_ODD_Buffer[EP0_SIZE];
static uint_8 gu8EP0_OUT_EVEN_Buffer[EP0_SIZE];
static uint_8 gu8EP0_IN_ODD_Buffer[EP0_SIZE];
static uint_8 gu8EP0_IN_EVEN_Buffer[EP0_SIZE];
//����˵�1������
static uint_8 gu8EP1_OUT_ODD_Buffer[EP1_SIZE];
static uint_8 gu8EP1_OUT_EVEN_Buffer[EP1_SIZE];
static uint_8 gu8EP1_IN_ODD_Buffer[EP1_SIZE];
static uint_8 gu8EP1_IN_EVEN_Buffer[EP1_SIZE];
//����˵�2������
static uint_8 gu8EP2_OUT_ODD_Buffer[EP2_SIZE];
static uint_8 gu8EP2_OUT_EVEN_Buffer[EP2_SIZE];
static uint_8 gu8EP2_IN_ODD_Buffer[EP2_SIZE];
static uint_8 gu8EP2_IN_EVEN_Buffer[EP2_SIZE];
//����˵�3������
static uint_8 gu8EP3_OUT_ODD_Buffer[EP3_SIZE];
static uint_8 gu8EP3_OUT_EVEN_Buffer[EP3_SIZE];
static uint_8 gu8EP3_IN_ODD_Buffer[EP3_SIZE];
static uint_8 gu8EP3_IN_EVEN_Buffer[EP3_SIZE];

//������˵㻺������ָ��
uint_8 *BD_BufferPointer[]=    //ָ�����飬ָ�����飬�������׵�ַ
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
//����˵㻺�����ĳ���
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

//�˵�IN(2)״̬
 uint_8 vEP2State = kUDATA1;  //�˵�2������DATA1��ACK��
//�˵�OUT(3)״̬
 uint_8 vEP3State = kUDATA0;  //�˵�3������DATA0��ACK��


//USBģ���ڲ�ȫ�ֱ���
static uint_8 gu8USBClearFlags;     //����Ƿ���Է������ݵı�־    USB��λ�� gu8USBClearFlags == 0xFF
static uint_8 *pu8IN_DataPointer;
static uint_8 gu8IN_Counter;
static uint_8 gu8USB_Toogle_flags;  //�л��桢ż���Ͱ�   USB��λ�� gu8USB_Toogle_flags==0
static uint_8 gu8Dummy;
static uint_8 gu8HALT_EP;     //�����ж϶˵��Ƿ���ֹͣ״̬
static uint_8 gu8USB_State;   //USB�豸����״̬
static tUSB_Setup *Setup_Pkt; //����setup���ݰ���ָ��


//�ڲ���������
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
//������:usb_init
//��  ��: USBģ���ʼ
//��  ��:str:�豸���к�
//��  ��: ��
//=========================================================================
void usb_init(uint_8 str[])
{
    //�����0x200UL����ֹռ��rom��
    BDTtable = (tBDT *)((( uint_32 ) BDT & 0xFFFFFE00UL)+0x200UL);
    //USB����ַ�����ʼ��
    USB_String_Table.String_Descriptor0=String_Descriptor0;
    USB_String_Table.String_Descriptor1=String_Descriptor1;
    USB_String_Table.String_Descriptor2=String_Descriptor2;
    USB_String_Table.Device_Name=str;
    //���˵�0�����滺�����ĵ�ַ �洢�� setup���ݰ� ��ָ�����Setup_Pkt��
    //���ڶ˵�0�����յ���PC������setup��
    //ָ��˵�0�Ľ����滺�����׵�ַ
    Setup_Pkt=(tUSB_Setup*)BD_BufferPointer[bEP0OUT_ODD];
    gu8USB_State=uPOWER;   //USB�豸�����ϵ�״̬
    //USB_FMC_ACC_ENABLE;
    USB_REG_SET_ENABLE;
    USB_REG_CLEAR_STDBY;
    //MPU_CESR=0;��ֹMPU
    FLAG_SET(SIM_SOPT2_PLLFLLSEL_SHIFT,SIM_SOPT2);  // ʹ��PLL���
    FLAG_SET(SIM_SOPT2_USBSRC_SHIFT,SIM_SOPT2);     // ʹ��PLL/FLLΪʱ��Դ
    //SIM_CLKDIV2|=USB_FARCTIONAL_VALUE;   //USB��Ƶ��������
    SIM_SCGC4|=(SIM_SCGC4_USBOTG_MASK);    //USBģ��ʱ����ʹ��
    enable_irq(USB_INTERRUPT_IRQ);         //ʹ��USBģ��IRQ�ж�
    //USBģ��Ĵ������á� USB0_USBTRC0���շ����ƼĴ���
    USB0_USBTRC0 |= USB_USBTRC0_USBRESET_MASK;
    //�ȴ�USBģ�鸴λ�������������˳�ѭ��
    while(FLAG_CHK(USB_USBTRC0_USBRESET_SHIFT,USB0_USBTRC0)){};
    //����BDTPAGE1��2,3 �Ĵ���������BDT��ַ�Ĵ���
    //( ��9λ  ��Ĭ��512 �ֽڵ�ƫ��) 512 = 16 * 4 * 8
    //8λ��ʾ: 4���ֽڵĿ���״̬��4 ���ֽڵĻ�������ַ
    USB0_BDTPAGE1=(uint_8)((uint_32)BDTtable>>8);
    USB0_BDTPAGE2=(uint_8)((uint_32)BDTtable>>16);
    USB0_BDTPAGE3=(uint_8)((uint_32)BDTtable>>24);
    //���USBģ�鸴λ��־   ��֮ǰ������λ��ʹ��λ��1��
    //��⵽USB��λ����1��֪ͨMPU���ַ�Ĵ���д��0x00��
    //��ʹ�ܶ˵�0
    FLAG_SET(USB_ISTAT_USBRST_SHIFT,USB0_ISTAT);
    //ʹ��USBģ�鸴λ�ж�
    FLAG_SET(USB_INTEN_USBRSTEN_SHIFT,USB0_INTEN);
    USB0_USBCTRL = 0x40;    //USB��SE0�źţ����������߱�����
    USB0_USBTRC0 |= 0x40;   //���룺ǿ�����õ�6λΪ1��USB�շ����ƼĴ���
    //����ʹ�ܣ�������������ʶ���豸�������������
    FLAG_SET(USB_CONTROL_DPPULLUPNONOTG_SHIFT,USB0_CONTROL);
    USB0_CTL |= 0x01;       //USBģ��ʹ��λ
}
//=========================================================================
//������: usb_enumerate
//��  ��: USBö�٣����ڴ���USB�豸��λ��USB�������������豸����
//��  ������
//��  ��: ��
//=========================================================================
void usb_enumerate()
{
    uint_8 u8IN;
    u8IN=USB0_STAT & 0x08;      //u8IN��ʾ�˵�0�������ĵ�BDλ��BDT��ż����
    //���д���
    if(u8IN)
       usb_ep0_in_handler();
    //���д���
    else
    {
        //���յ� 0x0D����ʾ��SETUP��
        if(BDTtable[bEP0OUT_ODD].Stat.RecPid.PID == mSETUP_TOKEN)
            usb_setup_handler();
        else
            usb_ep0_out_handler();
    }
}

//=========================================================================
//������: usb_send
//��  ��: USB��������
//��  ��: buf���������ݻ����������ں�������ʱ����δ���͵�����
//      len���������ݳ���,���ں�������ʱ����ʣ��δ���͵����ݳ���
//��  ��: ʵ�ʷ��͵����ݳ���
//��  ע��һ���Դ�������ݳ����Ƕ˵���֧�ֵ�������ݳ��ȣ�32�ֽڣ���������͵����ݳ���
//      ����32�ֽڣ����Ϊ��δ��䡣
//=========================================================================
uint_8 usb_send(uint_8 *buf,uint_8 *len)
{
    uint_16 i,counter;
    uint_8 *pBuffer;
    uint_32 vEP2Idx = 0;
    pBuffer = gu8EP2_IN_ODD_Buffer;
    //�жϷ��͵����ݳ����Ƿ���ڶ˵���֧�ֵ�������ݳ���
    if(*len > EP2_SIZE)
      counter = EP2_SIZE;
    else
      counter = *len;

    for(i=0; i<counter; i++, vEP2Idx++)
      //�����������ݿ�������Ӧ�˵㷢�ͻ�����
      pBuffer[i] = buf[vEP2Idx];

    BDTtable[bEP2IN_ODD].Cnt = counter;
    //��� ͬ0��1  vEP2State = kUDATA0  0x88
    vEP2State ^= 0x40;
    //��ʾUSBӵ�вٿ�Ȩ��������DATA0������ǰ��ΪACK���ְ�
    BDTtable[bEP2IN_ODD].Stat._byte= vEP2State;

    //��δ��������ݴ�ŵ�����������
    *len = *len - counter;
    for(i = 0;i <(*len);i++)
    {
        buf[i] = buf[i + counter];
    }

    //��ʱһ��ȴ����ݷ������
    for(i=0;i<5000;i++);

    if(counter)
        return counter;
    else
        return 0;
}

//=========================================================================
//������: usb_recv
//��  ��: USB��������
//��  ��: buf:�������ݻ�����
//      len:��������ʱ���������յ����ݳ���
//��  ��: �ɹ������ؽ������ݵĳ��ȣ�ʧ�ܣ�����0
//=========================================================================
uint_8 usb_recv(uint_8 *buf,uint_8 *len)
{
    uint_8 i;
    uint_8 *pBuffer;
    *len=0;
    pBuffer = gu8EP3_OUT_ODD_Buffer;
    //���յ����ݺ�BD��BC�ֶ��ǽ��յ����ݵĳ���
    if(BDTtable[bEP3OUT_ODD].Cnt != 0)
    {
        for(i = 0;i < BDTtable[bEP3OUT_ODD].Cnt;i++)
        {
            //����Ӧ�˵���ջ��������ݿ���������������
            buf[(*len)] = pBuffer[i];
            (*len)+=1;
        }
    }
    //��� ͬ0��1  vEP2State = kUDATA1  0xC8
    vEP3State ^=0x40;
    //��ʾUSBӵ�вٿ�Ȩ��������DATA1������ΪACK���ְ�
    BDTtable[bEP3OUT_ODD].Stat._byte=vEP3State;
    BDTtable[bEP3OUT_ODD].Cnt = EP3_SIZE;
    if(*len>0)  //�������ݳɹ�
        return (uint_8)*len;
    else
        return 0;

}

//=============================�ڲ�����ʵ��-==================================
//=========================================================================
//������:usb_isr_handler
//��  ��: �������������ж�
//��  ��: isr_type��USB�ж�����
//��  ��: ��
//=========================================================================
void usb_isr_handler(uint_8 isr_type)
{
    switch(isr_type)
    {
        //��λ�ж�
        case USB_RST_INT:
            //��λ�жϴ�����
            usb_reset_handler();
        break;
        //SOF�ж�
        case USB_SOF_INT:
            USB0_ISTAT = USB_ISTAT_SOFTOK_MASK;
        break;
        //STALL�ж�
        case USB_STALL_INT:
            //STALL�жϴ�����
            usb_stall_handler();
        break;
        //SLEEP�ж�
        case USB_SLEEP_INT:
            //��SLEEP��־
            FLAG_SET(USB_ISTAT_SLEEP_SHIFT,USB0_ISTAT);
        break;
        //ERROR�ж�
        case USB_ERROR_INT:
            //������־
            FLAG_SET(USB_ISTAT_ERROR_SHIFT,USB0_ISTAT);
    }
}


//=========================================================================
//������: usb_get_isr
//��  ��: ��ȡUSB�жϵ�����
//��  ������
//��  ��: 0�������ж�
//      1����λ�ж�
//      2:SOF�ж�
//      3:STALL�ж�
//      4:SLEEP�ж�
//      5:ERROR�ж�
//=========================================================================
uint_8  usb_get_isr()
{
    // ��������жϣ� USB_ISTAT_TOKDNE��������ɺ���1��
    if(FLAG_CHK(USB_ISTAT_TOKDNE_SHIFT,USB0_ISTAT))
        return USB_TOKDNE_INT;
    //���USBģ���Ƿ��������Ч�ĸ�λ
    else if(FLAG_CHK(USB_ISTAT_USBRST_SHIFT,USB0_ISTAT))
        return USB_RST_INT;
    //USBģ���յ�SOF��
    else if(FLAG_CHK(USB_ISTAT_SOFTOK_SHIFT,USB0_ISTAT))
        return USB_SOF_INT;
    // ���STALL
    else if(FLAG_CHK(USB_ISTAT_STALL_SHIFT,USB0_ISTAT))
        return USB_STALL_INT;
    // SLEEP
    else if(FLAG_CHK(USB_ISTAT_SLEEP_SHIFT,USB0_ISTAT))
        return USB_SLEEP_INT;
    //ERROR�жϣ���⵽����
    else
        return USB_ERROR_INT;
}


//=========================================================================
//������:usb_stall_handler
//��  ��: ����stall�ж�
//��  ��: ��
//��  ��: ��
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
//������:usb_reset_handler
//��  ��: USB��λ�жϷ������̣��������������־λ���������ж˵�Ĵ�����ͬʱ��EP0��ʼ��Ϊ���ƶ˵�
//      ����EP0��������� ��ż���������г�ʼ��������USB�����жϡ�USB��һ֡�����жϡ�USB����
//      �ж�,USB��λ�жϡ�    ��USB��λ��ɺ�USBͨ�Ž�����.
//��  ��: ��
//��  ��: ��
//=========================================================================
 void usb_reset_handler(void)
{      
    //���־
    gu8USBClearFlags=0xFF;
    gu8USB_Toogle_flags=0;

    //��ֹ���ж˵�    EPRXEN �� EPTXEN ��Ϊ0 ����
    USB0_ENDPT1=0x00;
    USB0_ENDPT2=0x00;
    USB0_ENDPT3=0x00;
    USB0_ENDPT4=0x00;
    USB0_ENDPT5=0x00;
    USB0_ENDPT6=0x00;

    // EP0 BDT Setup
    // EP0 OUT BDT ����
    BDTtable[bEP0OUT_ODD].Cnt = EP0_SIZE;
    BDTtable[bEP0OUT_ODD].Addr =(uint_32)gu8EP0_OUT_ODD_Buffer;
    BDTtable[bEP0OUT_ODD].Stat._byte = kUDATA1;
    // EP0 OUT BDT ����
    BDTtable[bEP0OUT_EVEN].Cnt = EP0_SIZE;
    BDTtable[bEP0OUT_EVEN].Addr =(uint_32)gu8EP0_OUT_EVEN_Buffer;
    BDTtable[bEP0OUT_EVEN].Stat._byte = kUDATA1;
    // EP0 IN BDT ���� 
    BDTtable[bEP0IN_ODD].Cnt = EP0_SIZE;
    BDTtable[bEP0IN_ODD].Addr =(uint_32)gu8EP0_IN_ODD_Buffer;
    BDTtable[bEP0IN_ODD].Stat._byte = kUDATA0;
    // EP0 IN BDT ���� 
    BDTtable[bEP0IN_EVEN].Cnt = (EP0_SIZE);
    BDTtable[bEP0IN_EVEN].Addr =(uint_32)gu8EP0_IN_EVEN_Buffer;
    BDTtable[bEP0IN_EVEN].Stat._byte = kUDATA0;

    // ʹ�� EP0
    USB0_ENDPT0 = 0x0D;  //�˵�����TX RX�����ִ������

    // ������еĴ���
    USB0_ERRSTAT = 0xFF;
    
    //������е��жϱ�־
    USB0_ISTAT = 0xFF;

    // USB�豸��ַ
    USB0_ADDR = 0x00;

    // ʹ�����еĴ����ж�
    USB0_ERREN = 0xFF;

    // USBģ���ж�ʹ��
    FLAG_SET(USB_INTEN_TOKDNEEN_SHIFT,USB0_INTEN);  //ʹ�������ж�
    FLAG_SET(USB_INTEN_SOFTOKEN_SHIFT,USB0_INTEN);  //ʹ��֡�ж�
    FLAG_SET(USB_INTEN_ERROREN_SHIFT,USB0_INTEN);   //ʹ�ܴ����ж�
    FLAG_SET(USB_INTEN_USBRSTEN_SHIFT,USB0_INTEN);  //ʹ�ܸ�λ�ж�
}


 //=========================================================================
 //������:usb_ep_in_transfer
 //��  ��: USB����IN����������USB�豸�������ݰ�
 //��  ��: u8EP���˵�0
 //       pu8DataPointer���û��洢���Ĵ������ݻ������׵�ַ
 //       u8DataSize���������ݳ���
 //��  ��: ��
 //=========================================================================
 static void usb_ep_in_transfer(uint_8 u8EP,uint_8 *pu8DataPointer,
         uint_8 u8DataSize)
 {
     uint_8 *pu8EPBuffer;
     uint_8 u8EPSize;
     uint_16 u16Lenght=0;
     uint_8 u8EndPointFlag;

     //���ö˵�����Ӧ�Ķ˵�������
     u8EndPointFlag = u8EP;
     if(u8EP)    //ò���е���࣬�ú���ֻ���ep0
         u8EP=(uint_8)(u8EP<<2);
     u8EP+=2;    //in_odd

     //ָ��˵�Ļ�����
     pu8EPBuffer = BD_BufferPointer[u8EP];    //ָ��_IN_ODD_Buffer

     //����Ƿ���Է�������
     if(FLAG_CHK(fIN,gu8USBClearFlags))
     {
         //�����������
         pu8IN_DataPointer = pu8DataPointer;
         gu8IN_Counter = u8DataSize;
         //���ƴ�������ݽ׶��д������ݵĴ�С
         u16Lenght = (Setup_Pkt -> wLength_h<<8) + Setup_Pkt -> wLength_l ;
         //���Ҫ����in���Ķ˵��Ƕ˵�0�����Ҵ��������ݱ�Ҫ�������ݳ�
         //��ôȡ���ֽڵĴ����ֽڴ�С
         if((u16Lenght < u8DataSize) && (u8EP==2))
         {
             gu8IN_Counter = Setup_Pkt->wLength_l;
         }
     }

     //���������͵������Ƿ���ڶ˵����ܷ������ݵĳ��ȡ�
     if(gu8IN_Counter > cEP_Size[u8EP])     //cEP_Size[u8EP] == 32
     {
         u8EPSize = cEP_Size[u8EP];
         gu8IN_Counter -= cEP_Size[u8EP];   //ʣ��һЩ��������
         FLAG_CLR(fIN,gu8USBClearFlags);    //���־�����ܷ�������
     }
     else
     {
         u8EPSize = gu8IN_Counter;
         gu8IN_Counter=0;
         FLAG_SET(fIN,gu8USBClearFlags);
     }

     //�Ѵ������ݳ���д��BDT
     BDTtable[u8EP].Cnt = (u8EPSize);

     // �����ݿ�����BDT������   (���û����������������ݿ�����ָ���˵�Ļ�����)
     while(u8EPSize--)
          *pu8EPBuffer++=*pu8IN_DataPointer++;

     // gu8USB_Toogle_flags : ��Data0 ��Data1 ����USB �豸����ͬ���õġ�
     // DATA0/DATA1 ����
     //���gu8USB_Toogle_flags bit0�Ƿ�Ϊ1
     if(FLAG_CHK(u8EndPointFlag,gu8USB_Toogle_flags))
     {
         //gu8USB_Toogle_flags : ��ʾ��DATA0����DATA1
         //1:��ʾ����DATA0, 0: ��ʾ����DATA1.
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
 //������:usb_set_interface
 //��  ��: USB���ýӿں���
 //       ͨ�����ö˵���ƼĴ������˵�2����Ϊ���ݷ��͵㣬�˵�3����Ϊ���ݽ��յ�
 //       �����˵㻺������ַ  �Լ�   ������Ϣ �洢��BDT��
 //��  ��: ��
 //��  ��: ��
 //=========================================================================
 static void usb_set_interface(void)
 {
     // ʹ�ܶ˵�
     // �˵� Register ����
     USB0_ENDPT1= EP1_VALUE | USB_ENDPT_EPHSHK_MASK;       //����ʹ��
     USB0_ENDPT2= EP2_VALUE | USB_ENDPT_EPHSHK_MASK;       //����ʹ��
     USB0_ENDPT3= EP3_VALUE | USB_ENDPT_EPHSHK_MASK;       //����ʹ��
     USB0_ENDPT4= EP4_VALUE | USB_ENDPT_EPHSHK_MASK;
     USB0_ENDPT5= EP5_VALUE | USB_ENDPT_EPHSHK_MASK;
     USB0_ENDPT6= EP6_VALUE | USB_ENDPT_EPHSHK_MASK;

     // ���� 1 BDT ����
     BDTtable[bEP1IN_ODD].Stat._byte= kUDATA1;
     BDTtable[bEP1IN_ODD].Cnt = 0x00;
     BDTtable[bEP1IN_ODD].Addr =(uint_32)gu8EP1_IN_ODD_Buffer;

     // ���� 2 BDT ����
     BDTtable[bEP2IN_ODD].Stat._byte= kUDATA1;
     BDTtable[bEP2IN_ODD].Cnt = 0x00;
     BDTtable[bEP2IN_ODD].Addr =(uint_32)gu8EP2_IN_ODD_Buffer;

     // ���� 3 BDT ����
     BDTtable[bEP3OUT_ODD].Stat._byte= kUDATA0;
     BDTtable[bEP3OUT_ODD].Cnt = 0xFF;
     BDTtable[bEP3OUT_ODD].Addr =(uint_32)gu8EP3_OUT_ODD_Buffer;
 }


 //=========================================================================
 //������:usb_stdReq_handler
 //��  ��: USBģ���׼��������豸��bmRequestType == 0x00���жϷ������̺���
 //       �ú�������setup���ݰ��е��������ͣ�������Ӧ������Ӧ�����ֶ�bRequest
 //��  ��: ��
 //��  ��: ��
 //=========================================================================
 static void usb_stdReq_handler(void)
 {
     uint_16 gu8Status;

     switch(Setup_Pkt->bRequest)
     {
         case mSET_ADDRESS:
             usb_ep_in_transfer(EP0,0,0);    //�˵�0����ACK��
             gu8USB_State = uADDRESS;   //��USB�豸Ϊ �����õ�ַ״̬
             break;

         // PC ��оƬ��ȡ������
         case mGET_DESC:

             switch(Setup_Pkt->wValue_h)
             {
                 case mDEVICE:
                     // �����豸������
                     usb_ep_in_transfer(EP0,(uint_8*) Device_Descriptor,sizeof(Device_Descriptor));
                     break;

                 case mCONFIGURATION:
                     // ��������������
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

//                     // �����ַ���������
//                     usb_ep_in_transfer(EP0,(uint_8*)String_Table[Setup_Pkt->wValue_l],
//                             String_Table[Setup_Pkt->wValue_l][0]);
                     break;

                 default:
                     usb_ep0_stall();
                     break;
             }
             break;
         // �������� Set Configuration
         case mSET_CONFIG:
             //ѡ������ֵ
             gu8Dummy=Setup_Pkt->wValue_h+Setup_Pkt->wValue_l; //wValue_h������wValue_lΪ����ֵ��
                                                               //Ϊ0�������������е�����ֵ
             if(Setup_Pkt->wValue_h+Setup_Pkt->wValue_l) //�ж�setup������λwValue
                                                         //����0����usb_set_interface���нӿ�����
             {
                 //ʹ��1 ��2 ��3 �˵�
                 usb_set_interface();
                 usb_ep_in_transfer(EP0,0,0);   //�˵�0����ACK
                 gu8USB_State = uENUMERATED;    //��USB�豸Ϊ �ѱ�ö��״̬
             }
             break;
         // ��ȡ������Ϣ Get Configuration
         case mGET_CONFIG:
             //��ȡ������Ϣ
             usb_ep_in_transfer(EP0,(uint_8*)&gu8Dummy,1);    //��������ֵ
             break;
         // ��ȡ״̬ Get Status
         case mGET_STATUS:
             gu8Status = 0;
             usb_ep_in_transfer(EP0,(uint_8*)&gu8Status,2);
             gu8USB_State=uPOWER;    //��USB�豸Ϊ �ѹ���״̬
             break;

         default:
             usb_ep0_stall();
             break;
     }
 }

 //=========================================================================
 //������:usb_setup_handler
 //��  ��: USB setup�жϷ�������
 //      setup��ʾһ�ο��ƴ���Ŀ�ʼ��USBģ����յ�PC���͵�setup���ݰ���
 //      ��ʹ��setup�жϣ������ú���������setup���ݰ��е�bmRequestType������Ӧ����
 //��  ��: ��
 //��  ��: ��
 //˵  ��:
 //   (1)ֻ�н��յ�SETUP���ŵ��øú���
 //   (2)SETUP����8�ֽ�����
 //    bmRequestType:1
 //    bRequest:1
 //    wValue.H:1 :������������
 //    wValue.L:1 :������������
 //    wIndex:2
 //    wLength:2
 //=========================================================================
 static void usb_setup_handler(void)
 {
    // uint_8 u8State;

     // ��DATA0��ʼ����
     FLAG_CLR(0,gu8USB_Toogle_flags);
     switch(Setup_Pkt->bmRequestType & 0x1F)  //�������豸 ��׼��   bmRequestType������
     {

         case DEVICE_REQ:
             // �豸
             if((Setup_Pkt->bmRequestType & 0x1F)== STANDARD_REQ)
                 usb_stdReq_handler();   // USB �豸�ı�׼����
             // ��BDT �Ŀ���Ȩ����USB ģ��
             BDTtable[bEP0OUT_ODD].Stat._byte= kUDATA0;
             break;
         case INTERFACE_REQ:
         case ENDPOINT_REQ:
             // �˵�
             usb_endpoint_setup_handler();
             BDTtable[bEP0OUT_ODD].Stat._byte= kUDATA0;
             break;

         default:
             usb_ep0_stall();
             break;
     }

     //�ӻ�ʱ����λΪ0: SIE������������  �����յ�setup���ƺ�SIE�Ὣ��λ��1��
     FLAG_CLR(USB_CTL_TXSUSPENDTOKENBUSY_SHIFT,USB0_CTL);
 }



 //=========================================================================
 //������:usb_endpoint_setup_handler
 //��  ��: USB�˵�setup�жϷ������̣���Զ˵��bRequest��bmRequestType == 0x02��
 //��  ��: ��
 //��  ��: ��
 //=========================================================================
 static void usb_endpoint_setup_handler(void)
 {
     uint_16 u16Status;

     switch(Setup_Pkt->bRequest)
     {
         case GET_STATUS:  //��ö˵�״̬
             //�����һ���ӿڻ�˵�ʱ��wIndex�ֶξ��������ĸ��ӿڻ�˵�
             if(FLAG_CHK(Setup_Pkt->wIndex_h,gu8HALT_EP))
                 u16Status=0x0100;  //gu8HALT_EP�����ж϶˵��Ƿ���ֹͣ״̬������ͣ��״̬���˵�0����0x0100
             else
                 u16Status=0x0000;
             usb_ep_in_transfer(EP0,(uint_8*)&u16Status,2);
             break;

         case CLEAR_FEATURE:  //����˵�����
             FLAG_CLR(Setup_Pkt->wIndex_h,gu8HALT_EP);
             usb_ep_in_transfer(EP0,0,0);
             break;

         case SET_FEATURE:    //���ö˵�����
             FLAG_SET(Setup_Pkt->wIndex_h,gu8HALT_EP);
             usb_ep_in_transfer(EP0,0,0);
             break;

         default:
             break;
     }
 }


 //=========================================================================
 //������:usb_ep0_in_handler
 //��  ��: �˵�0���ͷ�����
 //      �����ж�gu8USB_State�Ƿ��ѱ� ���óɵ�ַ״̬ ,�����ǣ���gu8USB_State���óɾ���״̬
 //��  ��: ��
 //��  ��: ��
 //=========================================================================
 static void usb_ep0_in_handler(void)   //���õ�ַ�Ĵ������������ַ���������״̬�׶α���ɣ�
                                 //������������״̬�׶�֮ǰ���
 {
     if(gu8USB_State==uADDRESS)
     {
         USB0_ADDR = Setup_Pkt->wValue_l;   //����USB�豸��ַ  setupָ��ep0_out_odd
         gu8USB_State=uREADY;               //USB�豸��Ϊ����״̬
         FLAG_SET(fIN,gu8USBClearFlags);    //����������
     }
     usb_ep_in_transfer(0,0,0);   //�˵�0����ACK
 }

 //=========================================================================
 //������:usb_ep0_stall
 //��  ��: �˵�0 stallֹͣ������
 //       ���˵�0���ƼĴ�����Stallλ��λ������һ��STALL��
 //       �����˵�0�Ļ������������Ŀ�����Ϣ���ó�kUDATA0
 //��  ��: ��
 //��  ��: ��
 //=========================================================================
 static void usb_ep0_stall(void)
 {
     //����һ��STALL��
     FLAG_SET(USB_ENDPT_EPSTALL_SHIFT,USB0_ENDPT0); //����һ��STALL���ְ�
     //ENDPT0_EP_STALL = 1;
     BDTtable[bEP0OUT_ODD].Stat._byte = kUDATA0;
     BDTtable[bEP0OUT_ODD].Cnt = EP0_SIZE;
 }

 //=========================================================================
 //������:usb_ep0_out_handler
 //��  ��: �˵�0�����жϷ�������
 //��  ��: ��
 //��  ��: ��
 //=========================================================================
 static void usb_ep0_out_handler(void)
 {
     //tBDTtable[bEP0OUT_ODD].Cnt = EP0_SIZE;
     BDTtable[bEP0OUT_ODD].Stat._byte = kUDATA0;
     //tBDTtable[bEP0IN].Stat._byte = kUDATA1;

 }

