//============================================================================
//文件名称：includes.h
//功能概要：应用工程总头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2012-11-12  V2.0
//============================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "gpio.h"
#include "light.h"

//定义全局变量
//定义小灯闪烁频率
#define RUN_COUNTER_MAX   1500000ul 

#define BME_AND_MASK	(1<<26)//addr[28:26]=001指定了AND操作
#define BME_OR_MASK	    (1<<27)//addr[28:26]=010指定了OR操作
#define BME_SRAM_U_MASK	(1<<29)//addr[30：29]=01指定SRAM_U
#define BME_IO_MASK	    (1<<30)//addr[30：29]=10指定外设位
#define BME_SRAM_MASK	(1<<29)//addr[30：29]=01指定外设位

//addr[28:26]=010表示清除操作；addr[25:21]是“BIT”对应的位标志符
#define BME_LAC1_MASK(BIT)	(1<<27) | (BIT<<21
//addr[28:26]=010表示置位操作；addr[25:21]是“BIT”对应的位标志符
#define BME_LAS1_MASK(BIT)	(3<<26) | (BIT<<21)

#define BME_AND_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_AND_MASK| BME_IO_MASK)=w)
#define BME_OR_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_OR_MASK| BME_IO_MASK)=w)

//定义使用的调试号
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL


#endif
