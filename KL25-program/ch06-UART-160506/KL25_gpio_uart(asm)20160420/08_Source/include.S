#[include.S]总头文件====================================
#本文件包含:                                             
#    (1)工程中用到的头文件                                                                                   
#========================================================
#ifndef INCLUDE_S
#define INCLUDE_S

.include "light.inc"
.include "uart.inc"
  
declaration:
 #start 参数定义区域
    .section  .rodata                       @开辟rodata段，定义常数
     RUN_COUNTER_MAX:    .word  0x0016e360
     test:   .asciz   "现在测试uart_send_str函数的功能..."
     test2:  .ascii   "现在测试uart_sendN函数的功能..."
    .align 2
             
    .section  .data                        @开辟data段，定义可读写的数据    

    .section  .bss                         @开辟bss段，定义不初始化的量

#end  参数定义区域
   
#endif  
