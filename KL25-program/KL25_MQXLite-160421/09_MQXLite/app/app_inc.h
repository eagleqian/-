#ifndef __APP_INC_H_
#define __APP_INC_H_
//---------------------------------------------------------------------------

//1.包含头文件
#include "bsp.h"
#include "mqxlite.h"
#include "mqx_inc.h"
#include "light.h"
#include "lwevent.h"
#include "printf.h"

//2.声明全局变量
//防止全局变量重复声明的前缀处理方法
#ifdef GLOBLE_VAR             //GLOBLE_VAR在task_main.c文件中宏定义
#define G_VAR_PREFIX          //task_main.c文件中使用全局变量不加“extern”前缀
#else
#define G_VAR_PREFIX  extern  //其他文件中使用全局变量自动加“extern”前缀
#endif

//声明全局变量（全局变量类型前一律前缀G_VAR_PREFIX）
G_VAR_PREFIX uint8_t g_UART_ISR_buffer[100];      //存放UART2接收的数据帧
G_VAR_PREFIX uint8_t g_UART_FrameCount;           //UART2接收的数据帧的个数
G_VAR_PREFIX LWEVENT_STRUCT  lwevent_group1;      //轻量级事件组
#define  Event_UART2_ReData   ((1uL)<<(6))  //串口2接收完整数据帧事件位

#define DELAY_TIMES    200           // 每个tick对应5ms

//3.登记任务模板编号
#define TASK_MAIN                     1
#define TASK_A                        2
#define TASK_B                        3
#define TASK_C                        4
#define TASK_D                        5

//4.为任务创建任务栈
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


//5.声明任务函数
void task_main(uint32_t initial_data);
void task_A(uint32_t initial_data);
void task_B(uint32_t initial_data);
void task_C(uint32_t initial_data);
void task_D(uint32_t initial_data);

//6.声明中断服务例程ISR
void UART2_IRQHandler(pointer user_isr_ptr);

//---------------------------------------------------------------------------
#endif    //app_inc.h
