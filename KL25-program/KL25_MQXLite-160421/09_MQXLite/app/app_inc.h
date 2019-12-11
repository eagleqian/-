#ifndef __APP_INC_H_
#define __APP_INC_H_
//---------------------------------------------------------------------------

//1.����ͷ�ļ�
#include "bsp.h"
#include "mqxlite.h"
#include "mqx_inc.h"
#include "light.h"
#include "lwevent.h"
#include "printf.h"

//2.����ȫ�ֱ���
//��ֹȫ�ֱ����ظ�������ǰ׺������
#ifdef GLOBLE_VAR             //GLOBLE_VAR��task_main.c�ļ��к궨��
#define G_VAR_PREFIX          //task_main.c�ļ���ʹ��ȫ�ֱ������ӡ�extern��ǰ׺
#else
#define G_VAR_PREFIX  extern  //�����ļ���ʹ��ȫ�ֱ����Զ��ӡ�extern��ǰ׺
#endif

//����ȫ�ֱ�����ȫ�ֱ�������ǰһ��ǰ׺G_VAR_PREFIX��
G_VAR_PREFIX uint8_t g_UART_ISR_buffer[100];      //���UART2���յ�����֡
G_VAR_PREFIX uint8_t g_UART_FrameCount;           //UART2���յ�����֡�ĸ���
G_VAR_PREFIX LWEVENT_STRUCT  lwevent_group1;      //�������¼���
#define  Event_UART2_ReData   ((1uL)<<(6))  //����2������������֡�¼�λ

#define DELAY_TIMES    200           // ÿ��tick��Ӧ5ms

//3.�Ǽ�����ģ����
#define TASK_MAIN                     1
#define TASK_A                        2
#define TASK_B                        3
#define TASK_C                        4
#define TASK_D                        5

//4.Ϊ���񴴽�����ջ
#define TASK_MAIN_STACK_SIZE  (sizeof(TD_STRUCT) + 1024 + PSP_STACK_ALIGNMENT + 1)
#define TASK_A_STACK_SIZE     (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)
#define TASK_B_STACK_SIZE     (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)
#define TASK_C_STACK_SIZE     (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)
#define TASK_D_STACK_SIZE     (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)


G_VAR_PREFIX uint_8 task_main_stack[TASK_MAIN_STACK_SIZE];
G_VAR_PREFIX uint_8 task_A_stack[TASK_A_STACK_SIZE];
G_VAR_PREFIX uint_8 task_B_stack[TASK_B_STACK_SIZE];
G_VAR_PREFIX uint_8 task_C_stack[TASK_C_STACK_SIZE];
G_VAR_PREFIX uint_8 task_D_stack[TASK_D_STACK_SIZE];


//5.����������
void task_main(uint32_t initial_data);
void task_A(uint32_t initial_data);
void task_B(uint32_t initial_data);
void task_C(uint32_t initial_data);
void task_D(uint32_t initial_data);

//6.�����жϷ�������ISR
void UART2_IRQHandler(pointer user_isr_ptr);

//---------------------------------------------------------------------------
#endif    //app_inc.h
