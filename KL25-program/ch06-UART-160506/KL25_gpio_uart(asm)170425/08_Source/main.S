#============================================================================
#文件名称：main.s
#功能概要：汇编编程控制小灯闪烁
#版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
#版本更新：2016-04-20  V1.6
#============================================================================
.include "include.S"

#start 函数定义区域
  	.section	.text
    .global main                            @定义全局变量，使其在芯片初始化之后可以调用
     .align 2
    .type main, function                     @定义主函数类
    .align 2
#end  函数定义区域

 main:
    .syntax divided
    cpsid i                                 @关闭总中断，进行初始化
#小灯初始化
    ldr r0,=LIGHT_BLUE
    ldr r3,=LIGHT_ON
    bl light_init                           @调用小灯初始化函数

#UART1初始化
    ldr r0,=UART1_BUSCLK
    ldr r1,=9600
    mov r2,#0
    mov r3,#0
    bl  uart_init

#串口输出测试语句

#使用uart_send_str函数发送
    ldr r0,=UART1
    ldr r1,=test
    bl uart_send_str

#使用uart_send1函数发送
    ldr r0,=UART1
    mov r1,#10    @回车
    bl uart_send1
    ldr r0,=UART1
    mov r1,#10    @回车
    bl uart_send1

#使用uart_sendN函数发送
    ldr r0,=UART1
    ldr r1,=test2
    mov r2,#31
    bl uart_sendN

#使用uart_send1函数发送
    ldr r0,=UART1
    mov r1,#10    @回车
    bl uart_send1
    ldr r0,=UART1
    mov r1,#10    @回车
    bl uart_send1

#打开串口中断
    ldr r0,=UART1
    bl uart_enable_re_int
	cpsie  i                                @开总中断

#主循环，通过RUN_COUNTER_MAX递减来延迟，设定小灯的闪烁间隔
main_repeat:
    ldr r4,=RUN_COUNTER_MAX                 @取延时计数值RUN_COUNTER_MAX的存储地址到r4
    ldr r4,[r4]
    .hidden main_loop

/*    ldrb r0,=UART1
    ldr r1,=test
    bl uart_send_str
*/
main_loop:                                       @取延时计数值RUN_COUNTER_MAX的值到r4
    sub r4,#1
    cmp r4,#1                               @判断延时时间是否已到
    bne main_loop

    ldr r0,=LIGHT_BLUE
    bl light_change                         @如延时时间已到，则调用小灯亮暗转变函数

    b main_repeat
    .align 2

.end



