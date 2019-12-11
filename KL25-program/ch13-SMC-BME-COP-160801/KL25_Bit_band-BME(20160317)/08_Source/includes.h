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
#include "light.h"

//����ȫ�ֱ���
//����С����˸Ƶ��
#define RUN_COUNTER_MAX   1500000ul 

#define BME_AND_MASK	(1<<26)//addr[28:26]=001ָ����AND����
#define BME_OR_MASK	    (1<<27)//addr[28:26]=010ָ����OR����
#define BME_SRAM_U_MASK	(1<<29)//addr[30��29]=01ָ��SRAM_U
#define BME_IO_MASK	    (1<<30)//addr[30��29]=10ָ������λ
#define BME_SRAM_MASK	(1<<29)//addr[30��29]=01ָ������λ

//addr[28:26]=010��ʾ���������addr[25:21]�ǡ�BIT����Ӧ��λ��־��
#define BME_LAC1_MASK(BIT)	(1<<27) | (BIT<<21
//addr[28:26]=010��ʾ��λ������addr[25:21]�ǡ�BIT����Ӧ��λ��־��
#define BME_LAS1_MASK(BIT)	(3<<26) | (BIT<<21)

#define BME_AND_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_AND_MASK| BME_IO_MASK)=w)
#define BME_OR_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_OR_MASK| BME_IO_MASK)=w)

//����ʹ�õĵ��Ժ�
#define UART_TEST UART_1
#define TEST_UART_BAUDRATE   9600UL


#endif
