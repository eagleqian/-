//============================================================================
//�ļ����ƣ�includes.h
//���ܸ�Ҫ��Ӧ�ù�����ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2012-11-12  V2.0
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

//����ȫ�ֱ���
//����С����˸Ƶ��
#define RUN_COUNTER_MAX   1500000ul

//����ʹ�õĵ��Ժ�
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL

 enum eAppCmd
{
    cmdNULL         =  0x00,
    cmdOUTTESTDATA  =  0X01,
    cmdINTESTDATA   =  0X02,
    cmdMAX
};

//USB���ȫ�ֱ�������
uint_8  g_USBRecv[100];   //USB�豸�������ݻ����������������32���ֽ�����
uint_8  g_USBRecvLength;  //USB�豸�������ݳ���
uint_8  g_USBSend[100];   //USB�豸���ͻ����������������32���ֽڵ�����
uint_8  g_USBSendLength;  //USB�������ݳ���
uint_8  g_USBSendFlag;    //USB�������ݱ�־


#endif
