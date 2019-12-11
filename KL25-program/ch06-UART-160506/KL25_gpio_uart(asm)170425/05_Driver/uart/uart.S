#===========================================================================
#文件名称：uart.s
#功能概要：KL25 UART底层驱动构件（汇编）程序文件
#===========================================================================

.include "uart.inc"     @包含相应头文件

#常量定义
.section .rodata
    table_irq_uart: .byte 12, 13, 14

#宏函数定义
uart_clk:   .macro       @解析串口号和时钟源
             mov r2,r0   @r2=r0=串口号|时钟源
             lsr r0,#16  @r0=串口号
             ldr r3,=0xFFFF
             and r2,r3   @r2=时钟源KHz
            .endm

.section .text

#===========================================================================
# 函数名称：uart_init   
# 函数返回：无                
# 参数说明：r0:((串口号)|(时钟源KHz)) 例:(UART1|BUSCLK)表示UART1、总线时钟
#           r1: 波特率：300、600、1200、2400、4800、9600、19200、115200...
# 功能概要：初始化uart模块。当选择UART0时,时钟源只能选择MCGIRCLK或MCGPLL（若选择MCGIRCLK时
#           波特率需小于19200）;当为UART1、2时，时钟源只能选择BUSCLK
#===========================================================================
uart_init:
    push {r4-r7,lr}             @保存现场,pc(lr)入栈
    uart_clk                    @解析串口号r0和时钟源r2
    cmp r0,#0                   @判断是否为串口0
    bne u12                     @非串口0，转u12处理
u0:                             @处理串口0
#使用MCGPLLCLK=48000Khz时钟源
    ldr r4,=SIM_MCGFLLCLK
    ldr r5,=SIM_SOPT2 
    ldr r6,[r5]
    orr r4,r6
    ldr r6,=0x10000
    orr r4,r6
    str r4,[r5] 
#使能UART0_TXD、UART0_RXD
    lsl r0,r0,#2           
    ldr r7,=UART_BASE_RXD
    ldr r7,[r7,r0]              @得到串口基地址
    ldr r6,=0x100                             
    str r6,[r7]                     
    ldr r7,=UART_BASE_TXD
    ldr r7,[r7,r0]                
    str r6,[r7]                 
#启动串口0时钟
    ldr r7,=SIM_SCGC4
    ldr r6,[r7]
    ldr r5,=0x400
    orr r6,r5
    str r6,[r7]
#暂时关闭串口0发送、接收功能
    ldr r7,=UART_BASE_PTR
    ldr r7,[r7,r0]
    ldrb r6,[r7,#3]             @uart_C2
    ldr r5,=0xFFFFFFF3
    and r6,r5
    str r6,[r7]
#配置串口工作模式:8位无校验模式
    ldr r4,=1000
    ldr r2,=MCGPLL
    mul r2,r4                  @r2=MCGPLL时钟48000000Hz
    lsl r1,r1,#4        
    mov r0,r2     
    bl __aeabi_uidiv
    uxth r1,r0    
    ldrb r6,[r7]
    uxth r6,r6        
    mov r5,#31   
    bic r6,r5
    ldr r3,=0x1F00
    and r3,r1    
    asr r3,#8                   @得到分频因子
    uxtb r2,r3
    orr r2,r6    
    strb r2,[r7]                @高位寄存器     
    strb r1,[r7,#1]             @低位寄存器
#初始化控制寄存器,清标志位
    mov r6,#0
    strb r6,[r7,#2] 
    strb r6,[r7,#6]
    mov r6,#0x0F
    strb r6,[r7,#10] 
    mov r6,#0
    strb r6,[r7,#8] 
    strb r6,[r7,#9]
    ldrb r5,[r7,#4]
    uxtb r5,r5
    mov r6,#0x1F
    orr r6,r5
    strb r6,[r7,#4] 
    ldrb r5,[r7,#5]
    uxtb r5,r5
    mov r6,#0xC0
    orr r6,r5
    strb r6,[r7,#5]
#启动发送接收
    ldrb r5,[r7,#3]
    uxtb r5,r5
    mov r6,#0xC
    orr r6,r5
    strb r6,[r7,#3]
    b  uart_init_end
u12:                     @开始处理串口1、2
#判断串口1还是2
    cmp r0,#1
    beq u1               @串口1，转u1设置处理
    cmp r0,#2
    beq u2               @串口2，转u2设置处理
    b uart_init_end      @非串口1、2，初始化结束
u1:                      @串口1设置
#使能UART1_TXD、UART1_RXD
    lsl r0,#2  
    ldr r7,=UART_BASE_TXD         
    ldr r7,[r7,r0]
    ldr r6,=0x300                             
    str r6,[r7]                    
    ldr r7,=UART_BASE_RXD 
    ldr r7,[r7,r0]                
    str r6,[r7]                
#启动串口1时钟
    ldr r7,=SIM_SCGC4
    ldr r6,[r7]
    ldr r5,=0x800
    orr r6,r5
    str r6,[r7]
    b set_u12
u2:                         @串口2设置
#使能UART2_TXD、UART2_RXD
    lsl r0,#2  
    ldr r7,=UART_BASE_TXD     
    ldr r7,[r7,r0]
    ldr r6,=0x400                             
    str r6,[r7]                     
    ldr r7,=UART_BASE_RXD 
    ldr r7,[r7,r0]                 
    str r6,[r7]               
#启动串口2时钟
    ldr r7,=SIM_SCGC4
    ldr r6,[r7]
    ldr r5,=0x1000
    orr r6,r5
    str r6,[r7]
set_u12:                   @串口1、2公共设置
#暂时关闭串口1、2发送与接收功能
    ldr r7,=UART_BASE_PTR
    ldr r7,[r7,r0]
    ldrb r4,[r7,#3]         
    uxtb r4,r4
    mov r5,#12
    bic r4,r5
    strb r4,[r7,#3]     
#配置串口工作模式:8位无校验模式
    mov r4,#0                    
    strb r4,[r7,#2]

    ldr r4,=1000
    ldr r0,=BUSCLK
    mul r0,r4             @r0=总线时钟24000000Hz

    lsl r1,r1,#4     
    bl __aeabi_uidiv
    uxth r1,r0    
    ldrb r6,[r7]    
    uxth r6,r6
    mov r5,#31
    bic r6,r5       
    ldr r3,=0x1F00
    and r3,r0
    asr r3,#8
    uxtb r2,r3
    orr r2,r6
    strb r2,[r7]
    strb r0,[r7,#1]
#初始化控制寄存器
    mov r6,#0
    strb r6,[r7,#2]
    strb r6,[r7,#6]
    strb r6,[r7,#5]
    mov  r6,#0x1F
    strb r6,[r7,#4]
#启动发送接收
    ldrb r5,[r7,#3]
    uxtb r5,r5
    mov r6,#0xC
    orr r6,r5
    strb r6,[r7,#3]    
uart_init_end:
    pop {r4-r7,pc}          @恢复现场,lr出栈到pc

    
#============================================================================
#函数名称：uart_send1
#参数说明：r0:串口号
#          r1:待发送的字节
#函数返回：r0:0=正常,1=异常
#功能概要：串行发送1个字节    
#============================================================================
uart_send1:
    push {r4-r7,lr}  @保存现场,pc(lr)入栈
    mov r5 ,#0       @r5=0
    lsl r0,#2        @r0=r0*4,基地址单元地址偏移量
uart_send1_loop:
    ldr r4,=0xFBBB   @r4=发送缓冲区是否为空轮询次数阈值
    cmp r5,r4        @判断循环变量值
    bcs uart_send1_exit  @达到轮询次数阈值转uart_send1_exit处理
    add r5,#1         @当前轮询次数加1
    
    ldr r7,=UART_BASE_PTR @r7=所有UART的基地址
    ldr r7,[r7,r0]    @r7=特定UART的基地址
    ldr r6,=UART_S1   @r6=S1寄存器偏移地址
    ldrb r4,[r7,r6]  @r4=S1寄存器内容
    uxth r4,r4       @扩展成32位无符号数
    ldr r6,=uart_s1_TDRE_mask @r6=S1寄存器的TDRE位掩码
    and r4,r6                 @取出S1中TDRE位的值
    cmp r4,#0         @判断发送缓冲区是否为空
    beq uart_send1_loop @非空则轮询状态，为空则继续
    ldr r6,=UART_D     @为空，r6=D寄存器偏移地址
    strb r1,[r7,r6]   @将待发送字节送D寄存器发送
uart_send1_exit:
    ldr r4,=0xFBBB    @r4=0xFBBB
    cmp r5,r4         @比较循环变量r5与0xFBBB的大小
    bcc uart_send1_suc@若r5<0xFBBB发送成功,转uart_send1_suc处理
    mov r0,#1         @发送失败,r0=1
    b uart_send1_end  @转uart_send1_end处理
uart_send1_suc:
    mov r0,#0         @发送成功,r0=0
uart_send1_end:    
    pop {r4-r7,pc}    @现场恢复,lr出栈到pc
    
#============================================================================
#函数名称：uart_sendN
#参数说明：r0:串口号
#         r1:待发送数据缓冲区的首地址
#         r2:发送长度
#函数返回： r0:0=正常,1=异常。
#功能概要：串行发送n个字节
#============================================================================
uart_sendN:
     push {r4-r7,lr}          @保存现场,pc(lr)入栈
     mov r5,r0                @r5=r0=串口号
     mov r7,r1                @r7=发送缓冲区首地址
     mov r4,r2                @r4=发送长度
     mov r6,#0                @设置计数初值
uart_sendN_loop:
     mov r0,r5                 @r0=串口号
     ldrb r1,[r7,r6]           @r1=待发送的字节
     bl uart_send1             @发送字节
     cmp r0,#0                 @判断发送是否成功
     bne uart_sendN_fail       @发送失败,转uart_sendN_fail,发送成功继续
     add r6,#1                 @计数值加1
     cmp r6,r4                 @判断循环次数是否等于发送长度
     bcc uart_sendN_loop       @若小于发送长度则继续循环
     b uart_sendN_suc          @若等于发送长度则转发送成功处
uart_sendN_fail:
     mov  r0,#1                @发送失败,r0=1
     b uart_sendN_end          @转uart_sendN_end处理
uart_sendN_suc:
     mov r0,#0                 @发送成功,r0=0
uart_sendN_end:
    pop {r4-r7,pc}             @现场恢复,lr出栈到pc
    
#============================================================================
#函数名称：uart_send_str
#参数说明：r0:串口号
#         r1:待发送字符串的首地址
#函数返回： r0:0=正常,1=异常
#功能概要：从指定串口发送一个以'\0'结束的字符串
#============================================================================
uart_send_str:
     push {r4-r7,lr}          @保存现场,pc(lr)入栈
     mov r4,r0                @r4=r0=串口号
     mov r7,r1                @r7=待发送字符串首地址
     mov r6,#0                @待发送字符所在单元偏移地址
uart_sendstr_loop:
     mov r0,r4                @r0=串口号
     ldrb r1,[r7,r6]          @r1=字符串中待发送的字符
     mov r5,#0
     cmp r1,r5                @判断是否是字符串结束符'\0'
     beq uart_sendstr_back    @是结束符'\0',则转uart_sendstr_back
     bl uart_send1            @发送单个字符
     add r6,#1                @下一个待发送字符所在单元偏移地址
     cmp r0,#0                @判断发送是否成功
     beq uart_sendstr_loop    @发送单个字符成功,则继续循环
uart_sendstr_back:
     mov r5,#0
     cmp r1,r5               @判断是否是字符串结束符'\0'
     beq uart_sendstr_suc    @是结束符'\0',发送成功，转uart_sendstr_suc处理
     mov  r0,#1              @发送失败,r0=1
     b uart_sendstr_end      @转uart_sendstr_end处理
uart_sendstr_suc:
     mov r0,#0               @发送成功,r0=0
uart_sendstr_end:    
    pop {r4-r7,pc}           @现场恢复,lr出栈到pc
     
     
#============================================================================
#函数名称：uart_re1
#参数说明：r0:串口号
#函数返回：r0:0=正常,1=异常
#          r1:接收返回字节
#功能概要：串行接收1个字节
#============================================================================
uart_re1:
     push {r4-r7,lr}     
     lsl r0,#2
     mov r5,#0
uart_re1_loop:
     ldr r6,=0xFBBB
     cmp r5,r6                  @判断循环次数
     bcs uart_re1_back
     add r5,#1
     ldr r7, =UART_BASE_PTR    
     ldr r7,[r7,r0]             @得到串口基地址
     ldr r6,=UART_S1
     ldr r4,[r7,r6]
     uxth r4,r4
     ldr r6,=uart_s1_RDRF_mask
     and r4,r6
     cmp r4,#0                  @判断接收缓冲区是否满
     beq uart_re1_loop
     ldr r6,=UART_D
     ldrb r1,[r7,r6]            @收到数据
uart_re1_back:
     ldr r6,=0xFBBB
     cmp r5,r6
     bcc uart_re1_suc
     mov  r0,#1
     b uart_re1_end
uart_re1_suc:
     mov r0,#0
uart_re1_end:    
    pop {r4-r7,pc} 
     
     
#============================================================================
#函数名称：uart_reN
#参数说明：r0:串口号
#         r1:接收缓冲区首地址
#         r2:接收长度
#函数返回：r0:0=正常,1=异常。
#功能概要：串行接收N个字节
#============================================================================
uart_reN:
     push {r4-r7,lr}  
     mov r5,r0                  @保存串口号
     mov r7,r1
     mov r6,#0                  @设置计数初值
uart_reN_loop:
     mov r0,r5   
     bl uart_re1
     cmp r0,#0                  @判断接收是否成功
     bne uart_reN_back
     strb r1,[r7,r6]            @存储到接收缓冲区中
     add r6,#1
     cmp r6,r4                  @判断循环次数
     bcc uart_reN_loop
uart_reN_back:
     cmp r6,r4
     bls uart_reN_suc
     mov  r0,#1
     b uart_reN_end
uart_reN_suc:
     mov r0,#0
uart_reN_end:    
    pop {r4-r7,pc}   


#============================================================================
#函数名称：uart_enable_re_int
#参数说明：r0:串口号
#函数返回：无
#功能概要：开串口接收中断
#============================================================================
uart_enable_re_int:
     push {r4-r7,lr}
     lsl r0,#2
     ldr r7,=UART_BASE_PTR
     ldr r7,[r7,r0]             @得到串口基地址
     ldr r6,=UART_C2
     ldrb r4,[r7,r6]
     uxth r4,r4
     ldr r5,=uart_c2_RIE_mask
     orr r4,r5
     strb r4,[r7,r6]            @开放UART中断
     lsr r0,#2
     ldr r7,=table_irq_uart
     ldrb r0,[r7,r0]            @读取IRQ号
     uxth r0,r0
     bl enable_irq              @开中断控制器IRQ中断
     pop {r4-r7,pc}

#============================================================================
#函数名称：uart_disable_re_int
#参数说明：r0:串口号
#函数返回：无
#功能概要：关串口接收中断
#============================================================================
uart_disable_re_int:
     push {r4-r7,lr}
     lsl r0,#2
     ldr r7,=UART_BASE_PTR
     ldr r7,[r7,r0]             @得到串口基地址
     ldr r6,=UART_C2
     ldrb r4,[r7,r6]
     uxth r4,r4
     ldr r5,=~uart_c2_RIE_mask
     and r4,r5
     strb r4,[r7,r6]            @关闭UART中断
     lsr r0,#2
     ldr r7,=table_irq_uart
     ldrb r0,[r7,r0]            @读取IRQ号
     uxth r0,r0
     bl disable_irq             @关中断控制器IRQ中断
     pop {r4-r7,pc}
