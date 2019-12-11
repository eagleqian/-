#include "usb_device.h"
#include "usb_host.h"

extern int scsi_cmd_request_sense();
extern int usb_clear_stall_rd(void);
extern int usb_clear_stall_wr(void);
extern int usb_mst_soft_reset_recovery(void);

//===============================================================================
//函数名: usb_read_sector
//功  能: 读取一个扇区
//参  数:sec：扇区号
//      buffer:读取数据的缓冲区
//返  回：0-成功；1-失败
//备  注：调用usb_device_transfer函数，该函数内部调用同时作为对外接口函数，由USB主机
//       驱动层相关函数调用，用于读写数据
//===============================================================================
int usb_read_sector(uint_32 sec, uint_8 *buffer)
{
    uint_8 cmd[10];
    uint_32 i;
    int err;
    cmd[0]=SCSI_CMD_READ_10;
    cmd[1]=0<<5;
    cmd[2] = (uint_8)((0xFF000000 & sec)>>24);
    cmd[3] = (uint_8)((0x00FF0000 & sec)>>16);
    cmd[4] = (uint_8)((0x0000FF00 & sec)>>8);
    cmd[5] = (uint_8)((0x000000FF & sec)>>0);
    cmd[6]=0;
    cmd[7] = (uint_8)((0xFF00 & 1)>>8);
    cmd[8] = (uint_8)((0x00FF & 1)>>0);
    cmd[9]=0;

    while(1)
    {
        err=usb_device_transfer(10, cmd, DIR_IN, 1 * lun.sector_size, buffer);
        if (err)
        {
            switch(err)
            {
                case ERR_IO_NONE:
                    break;
                case ERR_IO_CHECK:
                    scsi_cmd_request_sense();
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
    return(0);
}


//===============================================================================
//函数名: usb_write_sector
//功  能: 写一个扇区
//参  数:sec:扇区号
//      buffer:存放要写入的数据的缓冲区
//返  回：0-成功；1-失败
//备  注：调用usb_device_transfer函数，该函数内部调用同时作为对外接口函数，由USB主机
//       驱动层相关函数调用，用于读写数据
//===============================================================================
int usb_write_sector(uint_32 sec, const uint_8 *buffer)
{
    uint_8 cmd[10];
    uint_32 i;
    int err;

    cmd[0]=SCSI_CMD_WRITE_10;
    cmd[1]=0 <<5;

    cmd[2] = (uint_8)((0xFF000000 & sec)>>24);
    cmd[3] = (uint_8)((0x00FF0000 & sec)>>16);
    cmd[4] = (uint_8)((0x0000FF00 & sec)>>8);
    cmd[5] = (uint_8)((0x000000FF & sec)>>0);
    cmd[6]=0;

    cmd[7] = (uint_8)((0xFF00 & 1)>>8);
    cmd[8] = (uint_8)((0x00FF & 1)>>0);

    cmd[9]=0;

    while(1)
    {
        err=usb_device_transfer(10, cmd, DIR_OUT, 1 * lun.sector_size, buffer);
        if (err)
        {
            switch(err)
            {
                case ERR_IO_NONE:
                    break;
                case ERR_IO_CHECK:
                    scsi_cmd_request_sense();

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
    return(0);
}


//===============================================================================
//函数名: usb_device_transfer
//功  能: 执行USB数据读写
//参  数:cmd_length:发送给USB设备的命令长度
//      cmd:发送的命令
//      dir:方向,上行传输还是下行传输
//      buf_length:写或者读缓冲区的长度
//      buf：读/写缓冲区
//返  回：0-成功；1-失败
//备  注：该函数调用USB主机驱动构件函数USBReadData和USBWriteData用于读写操作
//===============================================================================
int usb_device_transfer(uint_8 cmd_length, void *cmd, uint_8 dir,
        uint_32 buf_length, const uint_8 *buf)
{
    uint_8 cbw[31] = {0};
    uint_8 csw[13] = {0};
    int retry,
    first_csw=1;
    uint_32 r;
    static uint_32 tag = 0x0;
    WR_BE32(cbw, 0x55534243);
    tag++;
    ((uint_32*)cbw)[1]=tag;
    WR_LE32(&cbw[8], buf_length);
    cbw[12]=(uint_8)(dir ? 0x80 : 0);
    cbw[13]=(uint_8)(((char *)cmd)[1] >> 5);
    cbw[14]=cmd_length;
    CMX_ASSERT(cmd_length < 17);
    for(r=0; r<cmd_length; r++)
    {
        (&cbw[15])[r]=((uint_8*)cmd)[r];
    }

    retry=USB_RERTY_COUNT;
    retry_cmd:
    r=USBWriteData(mst_info.out_ep, 31, (uint_8 *)cbw);
    if (r != 31)
    {
        if (--retry)
        {
            if (ERR_IO_REMOVED != usb_mst_soft_reset_recovery())
            {
                goto retry_cmd;
            }
        }
        return(ERR_IO_REMOVED);
    }

    if (buf_length > 0 && dir != DIR_NONE)
    {
        switch(dir)
        {
            case DIR_IN:
                r=USBReadData(mst_info.in_ep, buf_length, (uint_8 *)buf);
                if (r != buf_length)
                {
                    usb_clear_stall_rd();
                }
                break;
            case DIR_OUT:
                r=USBWriteData(mst_info.out_ep, buf_length,(uint_8*)buf);
                if (r != buf_length)
                {
                    usb_clear_stall_wr();
                }
                break;
        }
    }
    retry_csw:
    r=USBReadData(mst_info.in_ep, 13, (uint_8*)csw);
    if (r != 13)
    {
        if (first_csw)
        {
            first_csw=0;
            usb_clear_stall_rd();
            goto retry_csw;
        }
        if (ERR_IO_REMOVED != usb_mst_soft_reset_recovery())
        {
            if (--retry)
            {
                goto retry_cmd;
            }
        }

        return(ERR_IO_REMOVED);
    }


    if (0x55534253 != RD_BE32(csw) || tag != ((uint_32*)csw)[1])
    {
        if (ERR_IO_REMOVED != usb_mst_soft_reset_recovery())
        {
            if (--retry)
            {
                goto retry_cmd;
            }
        }
        return(ERR_IO_REMOVED);
    }

    if (!(((csw[12] == 0) || (csw[12] == 1)) && RD_LE32(&csw[8]) <= buf_length)
        || csw[12] > 2)
    {
        if (ERR_IO_REMOVED != usb_mst_soft_reset_recovery())
        {
            if (--retry)
            {
                goto retry_cmd;
            }
        }
        return(ERR_IO_REMOVED);
    }

    if (csw[12] == 2)
    {
        if (ERR_IO_REMOVED != usb_mst_soft_reset_recovery())
        {
            if (--retry)
            {
                goto retry_cmd;
            }
        }
        return(ERR_IO_REMOVED);
    }

    if (csw[12] == 0 && RD_LE32(&csw[8]) != 0)
    {
        buf=((uint_8*)buf)+buf_length-RD_LE32(&csw[8]);
        buf_length -= RD_LE32(&csw[8]);
        goto retry_cmd;
    }

    if (csw[12] == 1)
    {
        return(ERR_IO_CHECK);
    }
    return(ERR_IO_NONE);
}


