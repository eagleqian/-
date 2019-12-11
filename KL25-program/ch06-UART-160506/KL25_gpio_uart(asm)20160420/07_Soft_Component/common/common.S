#===========================================================================
#文件名称：common.S
#功能概要：common（汇编）程序文件
#===========================================================================

.include "common.inc"     @包含相应头文件

#============================================================================
#函数名称：enable_irq
#参数说明：r0:irq号
#函数返回：无
#功能概要：使能irq中断
#============================================================================
enable_irq:
    push {r4-r7,lr}           @保存现场,pc(lr)入栈

    cmp r0,#32                @比较irq与32大小
	bcc enable_irq_start      @若irq不超过32，则转start_irq
    mov r0,#0                 @若irq超过32，则irq=0
enable_irq_start:
    ldr r4,=NVIC_BASE_PTR
    ldr r4,[r4,#0]            @得到ISER的地址
	ldr r5,[r4]               @读取ISER的内容
	mov r7,#1
    lsl r7,r0                 @r7=1<<irq
	orr r5,r7                 @r5=ISER|(1<<irq)
	str r5,[r4]               @设置ISER

    ldr r4,=NVIC_BASE_PTR
    ldr r4,[r4,#12]           @得到ICPR的地址
	ldr r5,[r4]               @读取ICPR的内容
	orr r5,r7                 @r5=ICPR|(1<<irq)
	str r5,[r4]               @设置ICPR

    pop {r4-r7,pc}            @恢复现场,lr出栈到pc


#============================================================================
#函数名称：disable_irq
#参数说明：r0:irq号
#函数返回：无
#功能概要：禁止irq中断
#============================================================================
disable_irq:
    push {r4-r7,lr}           @保存现场,pc(lr)入栈

	cmp r0,#32                @比较irq与32大小
	bcc disable_irq_start     @若irq不超过32，则转start_irq
	mov r0,#0                 @若irq超过32，则irq=0
disable_irq_start:
    ldr r4,=NVIC_BASE_PTR
    ldr r4,[r4,#4]            @得到ICER的地址
    ldr r5,[r4]               @读取ICER的内容
    mov r7,#1
	lsl r7,r0                 @r7=1<<irq
	orr r5,r7                 @r5=ICER|(1<<irq)
	str r5,[r4]               @设置ICER

	pop {r4-r7,pc}            @恢复现场,lr出栈到pc
