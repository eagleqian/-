//============================================================================
//�ļ����ƣ�includes.h
//���ܸ�Ҫ��Ӧ�ù�����ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2012-11-12  V2.0
//============================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "gpio.h"
#include "systick.h"
#include "uart.h"
#include "light.h"
#include "led.h"
#include "kb.h"
#include "lcd.h"

//����ȫ�ֱ���
uint_8 g_kb_value;         //���̱���
uint_8 g_LEDBuffer[4];     //LED��ʾ������
uint_8 g_LCDBuffer[32];    //LCD��ʾ������������.��ʾ���µ�����

//����С����˸Ƶ��
#define RUN_COUNTER_MAX   1500000ul 

//����ʹ�õĵ��Ժ�
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL


#endif
