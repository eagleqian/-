#include "mytype.h"
#include "config.h"
#include "usb_class.h"
#include "usb_host.h" 

struct znFAT_IO_Ctl ioctl; 
extern UINT8 Dev_No; //设备号
extern UINT8 *znFAT_Buffer;

int scsi_write(uint_32 lba, uint_32 length, const uint_8 *buffer);
int usb_write_sector(uint_32 lba, const uint_8 *buffer);
int usb_read_sector(uint_32 lba, const uint_8 *buffer);



UINT8 znFAT_Device_Init(void) 
{
    UINT8 res=0,err=0;
    ioctl.just_dev=0;
    ioctl.just_sec=0;
    //以下为各存储设备的初始化函数调用，请沿袭以下格式
    if(res) err|=0X01;
    return
        res; //返回错误码，如果某一设备初始化失败，则err相应位为1
}

//=====================================================================================
//函数名: USB_Class_Read_Sector
//功  能: 设备层函数用于读取U盘的一个扇区
//参  数: addr：要读取的扇区号
//       buffer:存放读取数据的缓冲区
//返  回: 0=成功；1=失败
//备  注：调用USB设备层函数usb_read_sector读取相应的数据
//=====================================================================================
UINT8 USB_Class_Read_Sector(UINT32 addr,UINT8 *buffer)
{
    if(buffer==znFAT_Buffer) //如果是针对znFAT内部缓冲区的操作
    {
         //如果现在要读取的扇区与内部缓冲所对应的扇区（即最近一次操作的扇区）是同一扇区
        if(ioctl.just_dev==Dev_No
                && (ioctl.just_sec==addr && 0!=ioctl.just_sec)) //则不再进行读取，直接返回
        {
            return 0;
        }
        else //否则，就将最近一次操作的扇区标记为当前扇区
        {
            ioctl.just_dev=Dev_No;
            ioctl.just_sec=addr;
        }
    }
    switch(Dev_No) //有多少个存储设备，就有多少个case分支
    {
        case 0:
            while(usb_read_sector(addr,buffer));
            break;
    }
    return 0;
}


//===================================================================================
//函数名: USB_Class_Read_nSector
//功  能: 读多个扇区
//参  数: nsec:扇区的个数
//       addr：当前扇区号
//       buffer:存放读取的数据的缓冲区
//返  回: 0=成功；1=失败
//备  注：调用USB设备层函数usb_read_sector读取相应的数据
//====================================================================================
UINT8 USB_Class_Read_nSector(UINT32 nsec,UINT32 addr,UINT8 *buffer)
{
    UINT32 i=0;
    if(0==nsec) return 0;
    switch(Dev_No)
    {
        case 0:
            for(i=0;i<nsec;i++) //如果不使用硬件级连续扇区读取，则使用单扇区读取+循环的方式
            {
                while(usb_read_sector(addr+i,buffer));
                buffer+=512;
            }
            break;
    }
    return 0;
}

//=====================================================================================
//函数名: USB_Class_Write_Sector
//功  能:向USB设备(U盘)相应扇区写数据
//参  数: addr：当前扇区号
//       buffer:存放读取的数据的缓冲区
//返  回: 0=成功；1=失败
//备  注：调用USB设备层函数usb_write_sector读取相应的数据
//=====================================================================================
UINT8 USB_Class_Write_Sector(UINT32 addr,UINT8 *buffer)
{
    if(buffer==znFAT_Buffer) //如果数据缓冲区是内部缓冲
    {
        ioctl.just_dev=Dev_No; //更新为当前设备号
        ioctl.just_sec=addr; //更新为当前操作的扇区地址
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
//函数名: USB_Class_Write_nSector
//功  能: 向USB设备(U盘)的多个扇区写数据
//参  数: nsec：要写入数据的扇区个数
//       addr：当前扇区号
//       buffer:存放要写入的数据的缓冲区
//返  回: 0=成功；1=失败
//备  注：调用USB设备层函数usb_write_sector将数据进行写入
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
//函数名: znFAT_Device_Clear_nSector
//功  能: 将USB设备(U盘)的多个扇区清空
//参  数: nsec：要清空的扇区个数
//       addr:当前扇区号
//返  回: 0=成功；1=失败
//备  注：调用USB设备层函数usb_write_sector将0写入到相应的多个扇区
//====================================================================================
UINT8 znFAT_Device_Clear_nSector(UINT32 nsec,UINT32 addr)
{
   UINT32 i=0;
   for(i=0;i<512;i++) //清空内部缓冲区，用于连续扇区清0
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
   ioctl.just_dev=Dev_No; //更新为当前设备号
   ioctl.just_sec=(addr+nsec-1); //更新为当前操作的扇区地址
   return 0;
}
