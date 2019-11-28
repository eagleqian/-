//=======================================================================
//文件名称：includes.h
//功能概要：应用工程总头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2012-11-12  V2.0
//=======================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "printf.h"
#include "gpio.h"
#include "light.h"
#include "uart.h"
#include "flash.h"

//定义全局变量
//定义小灯闪烁频率
#define RUN_COUNTER_MAX   1500000ul 

//定义使用的调试号
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL

//定义全局变量
uint_8 watchGlobalVar;

//1.3 声明全局变量
uint_8 g_uart_recvBuf[72];    //串口接收数据全局数组
uint_8 g_uart_sentBuf[72];    //串口发送数据全局数组
uint_8 framestate;//帧状态，0：非握手命令帧，1：握手命令帧
#endif
