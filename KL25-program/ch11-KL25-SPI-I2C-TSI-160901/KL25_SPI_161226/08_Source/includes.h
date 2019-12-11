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
#include "spi.h"

//����ȫ�ֱ���
uint_8 receive0;
//����С����˸Ƶ��
#define RUN_COUNTER_MAX1   150000ul
#define RUN_COUNTER_MAX2   1500000ul

//����ʹ�õĵ��Ժ�
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL


#endif
