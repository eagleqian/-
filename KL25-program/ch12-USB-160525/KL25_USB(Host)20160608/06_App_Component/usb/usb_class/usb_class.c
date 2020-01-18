#include "mytype.h"
#include "config.h"
#include "usb_class.h"
#include "usb_host.h" 

struct znFAT_IO_Ctl ioctl; 
extern UINT8 Dev_No; //�豸��
extern UINT8 *znFAT_Buffer;

int scsi_write(uint_32 lba, uint_32 length, const uint_8 *buffer);
int usb_write_sector(uint_32 lba, const uint_8 *buffer);
int usb_read_sector(uint_32 lba, const uint_8 *buffer);



UINT8 znFAT_Device_Init(void) 
{
    UINT8 res=0,err=0;
    ioctl.just_dev=0;
    ioctl.just_sec=0;
    //����Ϊ���洢�豸�ĳ�ʼ���������ã�����Ϯ���¸�ʽ
    if(res) err|=0X01;
    return
        res; //���ش����룬���ĳһ�豸��ʼ��ʧ�ܣ���err��ӦλΪ1
}

//=====================================================================================
//������: USB_Class_Read_Sector
//��  ��: �豸�㺯�����ڶ�ȡU�̵�һ������
//��  ��: addr��Ҫ��ȡ��������
//       buffer:��Ŷ�ȡ���ݵĻ�����
//��  ��: 0=�ɹ���1=ʧ��
//��  ע������USB�豸�㺯��usb_read_sector��ȡ��Ӧ������
//=====================================================================================
UINT8 USB_Class_Read_Sector(UINT32 addr,UINT8 *buffer)
{
    if(buffer==znFAT_Buffer) //��������znFAT�ڲ��������Ĳ���
    {
         //�������Ҫ��ȡ���������ڲ���������Ӧ�������������һ�β�������������ͬһ����
        if(ioctl.just_dev==Dev_No
                && (ioctl.just_sec==addr && 0!=ioctl.just_sec)) //���ٽ��ж�ȡ��ֱ�ӷ���
        {
            return 0;
        }
        else //���򣬾ͽ����һ�β������������Ϊ��ǰ����
        {
            ioctl.just_dev=Dev_No;
            ioctl.just_sec=addr;
        }
    }
    switch(Dev_No) //�ж��ٸ��洢�豸�����ж��ٸ�case��֧
    {
        case 0:
            while(usb_read_sector(addr,buffer));
            break;
    }
    return 0;
}


//===================================================================================
//������: USB_Class_Read_nSector
//��  ��: ���������
//��  ��: nsec:�����ĸ���
//       addr����ǰ������
//       buffer:��Ŷ�ȡ�����ݵĻ�����
//��  ��: 0=�ɹ���1=ʧ��
//��  ע������USB�豸�㺯��usb_read_sector��ȡ��Ӧ������
//====================================================================================
UINT8 USB_Class_Read_nSector(UINT32 nsec,UINT32 addr,UINT8 *buffer)
{
    UINT32 i=0;
    if(0==nsec) return 0;
    switch(Dev_No)
    {
        case 0:
            for(i=0;i<nsec;i++) //�����ʹ��Ӳ��������������ȡ����ʹ�õ�������ȡ+ѭ���ķ�ʽ
            {
                while(usb_read_sector(addr+i,buffer));
                buffer+=512;
            }
            break;
    }
    return 0;
}

//=====================================================================================
//������: USB_Class_Write_Sector
//��  ��:��USB�豸(U��)��Ӧ����д����
//��  ��: addr����ǰ������
//       buffer:��Ŷ�ȡ�����ݵĻ�����
//��  ��: 0=�ɹ���1=ʧ��
//��  ע������USB�豸�㺯��usb_write_sector��ȡ��Ӧ������
//=====================================================================================
UINT8 USB_Class_Write_Sector(UINT32 addr,UINT8 *buffer)
{
    if(buffer==znFAT_Buffer) //������ݻ��������ڲ�����
    {
        ioctl.just_dev=Dev_No; //����Ϊ��ǰ�豸��
        ioctl.just_sec=addr; //����Ϊ��ǰ������������ַ
    }
    switch(Dev_No)
    {
        case 0:
            while(usb_write_sector(addr,buffer));
            break;
    }
    return 0;
}


//===================================================================================
//������: USB_Class_Write_nSector
//��  ��: ��USB�豸(U��)�Ķ������д����
//��  ��: nsec��Ҫд�����ݵ���������
//       addr����ǰ������
//       buffer:���Ҫд������ݵĻ�����
//��  ��: 0=�ɹ���1=ʧ��
//��  ע������USB�豸�㺯��usb_write_sector�����ݽ���д��
//====================================================================================
UINT8 USB_Class_Write_nSector(UINT32 nsec,UINT32 addr,UINT8 *buffer)
{
    UINT32 i=0;
    if(0==nsec) return 0;
    switch(Dev_No)
    {
        case 0:
            for(i=0;i<nsec;i++)
            {
                while(usb_write_sector(addr+i,buffer));
                buffer+=512;
            }
            break;
    }
    return 0;
}

//===================================================================================
//������: znFAT_Device_Clear_nSector
//��  ��: ��USB�豸(U��)�Ķ���������
//��  ��: nsec��Ҫ��յ���������
//       addr:��ǰ������
//��  ��: 0=�ɹ���1=ʧ��
//��  ע������USB�豸�㺯��usb_write_sector��0д�뵽��Ӧ�Ķ������
//====================================================================================
UINT8 znFAT_Device_Clear_nSector(UINT32 nsec,UINT32 addr)
{
   UINT32 i=0;
   for(i=0;i<512;i++) //����ڲ�����������������������0
   {
       znFAT_Buffer[i]=0;
   }
   switch(Dev_No)
   {
          case 0:
              for(i=0;i<nsec;i++)
              {
                  while(usb_write_sector(addr+i,znFAT_Buffer));
              }
          break;
   }
   ioctl.just_dev=Dev_No; //����Ϊ��ǰ�豸��
   ioctl.just_sec=(addr+nsec-1); //����Ϊ��ǰ������������ַ
   return 0;
}
