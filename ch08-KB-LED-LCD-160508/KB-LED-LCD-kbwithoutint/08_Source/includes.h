//======================================================================
//文件名称：includes.h
//功能概要：应用工程总头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2012-11-12  V2.0
//======================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "gpio.h"
#include "light.h"
#include "led.h"
#include "kb.h"
#include "lcd.h"
#include "systick.h"

//声明全局变量
uint_8  g_kb_value;         //键盘变量
uint_8  g_LEDBuffer[4];     //LED显示缓冲区
uint_8  g_LCDBuffer[32];    //LCD显示缓冲区

//定义小灯闪烁频率
#define RUN_COUNTER_MAX   1500000ul 

//定义使用的调试号
#define UART_TEST  UART_1
#define UART_TEST_BAUDRATE  9600UL

#endif
