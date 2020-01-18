#define GLOBLE_VAR

#include "app_inc.h"     

//===========================================================================
//任务名称：task_main
//功能概要：MQX自启动任务，主要实现全局变量初始化、创建其他任务、安装用户ISR
//参数说明：未使用
//===========================================================================
void task_main(uint32_t initial_data)
{
    //1.全局变量初始化
    _lwevent_create(&lwevent_group1,0);  //创建轻量级事件组
    g_UART_FrameCount=0;                 //接收的帧数

    //2. 关总中断
    DISABLE_INTERRUPTS;

    //3.外设初始化
    light_init(RUN_LIGHT_RED,LIGHT_OFF);   //红灯初始化
    light_init(RUN_LIGHT_GREEN,LIGHT_OFF);   //绿灯初始化
    light_init(RUN_LIGHT_BLUE,LIGHT_OFF);   //蓝灯初始化

    uart_init(UART_Debug,9600);      //初始化调试串口

    //4.创建其他任务
    _task_create_at(0, TASK_A, 0, task_A_stack, TASK_A_STACK_SIZE);
    _task_create_at(0, TASK_B, 0, task_B_stack, TASK_B_STACK_SIZE);
    _task_create_at(0, TASK_C, 0, task_C_stack, TASK_C_STACK_SIZE);
    _task_create_at(0, TASK_D, 0, task_D_stack, TASK_D_STACK_SIZE);

    //5.安装用户ISR
    _int_install_isr(UART0_IRQn+UART_Debug+16,UART2_IRQHandler,NULL);  //注册调试串口的ISR
    
    //6.使能模块中断及总中断
    uart_enable_re_int(UART_Debug);      //使能调试串口接收中断

    //7.开总中断
    ENABLE_INTERRUPTS;
    
    //------------执行完毕，本任务进入阻塞态-----------------------------------
    _task_block();
}
