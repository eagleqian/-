//============================================================================
//文件名称：includes.h
//功能概要：应用工程总头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2012-11-12  V2.0
//============================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "printf.h"
#include "gpio.h"
#include "light.h"
#include "uart.h"
#include "usb.h"
#include "flash.h"

//定义全局变量
//定义小灯闪烁频率
#define RUN_COUNTER_MAX   1500000ul

//定义使用的调试号
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL

 enum eAppCmd
{
    cmdNULL         =  0x00,
    cmdOUTTESTDATA  =  0X01,
    cmdINTESTDATA   =  0X02,
    cmdMAX
};

//USB相关全局变量声明
uint_8  g_USBRecv[100];   //USB设备接收数据缓冲区，缓冲区最大32个字节数据
uint_8  g_USBRecvLength;  //USB设备接收数据长度
uint_8  g_USBSend[100];   //USB设备发送缓冲区，缓冲区最大32个字节的数据
uint_8  g_USBSendLength;  //USB发送数据长度
uint_8  g_USBSendFlag;    //USB发送数据标志


#endif
