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
#include "usb_host.h"
#include "znfat.h"

//����ȫ�ֱ���
//����С����˸Ƶ��
#define RUN_COUNTER_MAX   1500000ul 

//����ʹ�õĵ��Ժ�
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL

#define FILE_NAME   "log.TXT"  /* LOG file name (Previously created)*/
#define AUTHER      "Vera"
#define VERSION     "V1.0"
#define FILE_BUFFER_SIZE_R (2048u)

#endif
