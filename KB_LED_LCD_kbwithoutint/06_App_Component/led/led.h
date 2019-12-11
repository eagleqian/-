//=====================================================================
// �ļ����ƣ�led.h                                                         
// ���ܸ�Ҫ��led����ͷ�ļ�
// ��Ȩ����: ���ݴ�ѧǶ��ʽ����(sumcu.suda.edu.cn)
// �汾����: 2011-03-17  V1.0�� 2016-05-02  V6.0��WYH��
//=====================================================================

#ifndef _LED_H           //��ֹ�ظ����壨��ͷ)
#define _LED_H

#include "common.h"    //��������Ҫ��ͷ�ļ�
#include "gpio.h"      //����gpioͷ�ļ�

//LED��Ӳ������
#define LED_D1   (PTB_NUM|11)    //LED���ݿ�
#define LED_D2   (PTB_NUM|10)
#define LED_D3   (PTB_NUM|9)
#define LED_D4   (PTB_NUM|8)
#define LED_D5   (PTB_NUM|3)
#define LED_D6   (PTB_NUM|2)
#define LED_D7   (PTB_NUM|1)
#define LED_D8   (PTB_NUM|0)
#define LED_CS0  (PTB_NUM|19)   //LEDλѡ��
#define LED_CS1  (PTB_NUM|18)
#define LED_CS2  (PTB_NUM|17)
#define LED_CS3  (PTB_NUM|16)

//��ʾ�������led.c�ļ���--0~9֮��������Ҫ�ο��˱�

//=====================================================================
//�������ƣ�LEDInit
//�������أ���
//����˵������  
//���ܸ�Ҫ��LED��ʼ��������MCU�Ƕȣ������������������������ʼֵһ��Ϊ0��ȫ����
//=====================================================================
void LEDInit();

//=====================================================================
//�������ƣ�LEDshow
//�������أ���
//����˵����data[4]����ʾ�����ݡ�����ʾ������0~9,0.~9.,E,F,ȫ����ȫ��������ʾ�����
//���ܸ�Ҫ��������data������ʾ��LED�ϡ�����������һ�λ���ʾ�����е�һ���ַ���
//        �������ʱ10ms���ҵ���һ�α��������ܽ���������ȫ����ʾ��LED��
//=====================================================================
void LEDshow(uint_8 data[4]);

#endif    //��ֹ�ظ����壨��β��
//=====================================================================
//������
//��1�����ǿ�����Դ���룬�ڱ������ṩ��Ӳ��ϵͳ����ͨ������Ϸ��׸���ᣬ����֮����
//     ��ӭָ����
//��2������ʹ�÷Ǳ�����Ӳ��ϵͳ���û�����ֲ����ʱ������ϸ�����Լ���Ӳ��ƥ�䡣
//
//���ݴ�ѧǶ��ʽ����   512-65214835  http://sumcu.suda.edu.cn
