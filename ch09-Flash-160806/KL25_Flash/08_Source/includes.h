//=======================================================================
//�ļ����ƣ�includes.h
//���ܸ�Ҫ��Ӧ�ù�����ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2012-11-12  V2.0
//=======================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "printf.h"
#include "gpio.h"
#include "light.h"
#include "uart.h"
#include "flash.h"

//����ȫ�ֱ���
//����С����˸Ƶ��
#define RUN_COUNTER_MAX   1500000ul 

//����ʹ�õĵ��Ժ�
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL

//����ȫ�ֱ���
uint_8 watchGlobalVar;

//1.3 ����ȫ�ֱ���
uint_8 g_uart_recvBuf[72];    //���ڽ�������ȫ������
uint_8 g_uart_sentBuf[72];    //���ڷ�������ȫ������
uint_8 framestate;//֡״̬��0������������֡��1����������֡
#endif
