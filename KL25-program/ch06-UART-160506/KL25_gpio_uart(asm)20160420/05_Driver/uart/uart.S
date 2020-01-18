#===========================================================================
#�ļ����ƣ�uart.s
#���ܸ�Ҫ��KL25 UART�ײ�������������ࣩ�����ļ�
#===========================================================================

.include "uart.inc"     @������Ӧͷ�ļ�

#��������
.section .rodata
    table_irq_uart: .byte 12, 13, 14

#�꺯������
uart_clk:   .macro       @�������ںź�ʱ��Դ
             mov r2,r0   @r2=r0=���ں�|ʱ��Դ
             lsr r0,#16  @r0=���ں�
             ldr r3,=0xFFFF
             and r2,r3   @r2=ʱ��ԴKHz
            .endm

.section .text

#===========================================================================
# �������ƣ�uart_init   
# �������أ���                
# ����˵����r0:((���ں�)|(ʱ��ԴKHz)) ��:(UART1|BUSCLK)��ʾUART1������ʱ��
#           r1: �����ʣ�300��600��1200��2400��4800��9600��19200��115200...
# ���ܸ�Ҫ����ʼ��uartģ�顣��ѡ��UART0ʱ,ʱ��Դֻ��ѡ��MCGIRCLK��MCGPLL����ѡ��MCGIRCLKʱ
#           ��������С��19200��;��ΪUART1��2ʱ��ʱ��Դֻ��ѡ��BUSCLK
#===========================================================================
uart_init:
    push {r4-r7,lr}             @�����ֳ�,pc(lr)��ջ
    uart_clk                    @�������ں�r0��ʱ��Դr2
    cmp r0,#0                   @�ж��Ƿ�Ϊ����0
    bne u12                     @�Ǵ���0��תu12����
u0:                             @��������0
#ʹ��MCGPLLCLK=48000Khzʱ��Դ
    ldr r4,=SIM_MCGFLLCLK
    ldr r5,=SIM_SOPT2 
    ldr r6,[r5]
    orr r4,r6
    ldr r6,=0x10000
    orr r4,r6
    str r4,[r5] 
#ʹ��UART0_TXD��UART0_RXD
    lsl r0,r0,#2           
    ldr r7,=UART_BASE_RXD
    ldr r7,[r7,r0]              @�õ����ڻ���ַ
    ldr r6,=0x100                             
    str r6,[r7]                     
    ldr r7,=UART_BASE_TXD
    ldr r7,[r7,r0]                
    str r6,[r7]                 
#��������0ʱ��
    ldr r7,=SIM_SCGC4
    ldr r6,[r7]
    ldr r5,=0x400
    orr r6,r5
    str r6,[r7]
#��ʱ�رմ���0���͡����չ���
    ldr r7,=UART_BASE_PTR
    ldr r7,[r7,r0]
    ldrb r6,[r7,#3]             @uart_C2
    ldr r5,=0xFFFFFFF3
    and r6,r5
    str r6,[r7]
#���ô��ڹ���ģʽ:8λ��У��ģʽ
    ldr r4,=1000
    ldr r2,=MCGPLL
    mul r2,r4                  @r2=MCGPLLʱ��48000000Hz
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
    asr r3,#8                   @�õ���Ƶ����
    uxtb r2,r3
    orr r2,r6    
    strb r2,[r7]                @��λ�Ĵ���     
    strb r1,[r7,#1]             @��λ�Ĵ���
#��ʼ�����ƼĴ���,���־λ
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
#�������ͽ���
    ldrb r5,[r7,#3]
    uxtb r5,r5
    mov r6,#0xC
    orr r6,r5
    strb r6,[r7,#3]
    b  uart_init_end
u12:                     @��ʼ��������1��2
#�жϴ���1����2
    cmp r0,#1
    beq u1               @����1��תu1���ô���
    cmp r0,#2
    beq u2               @����2��תu2���ô���
    b uart_init_end      @�Ǵ���1��2����ʼ������
u1:                      @����1����
#ʹ��UART1_TXD��UART1_RXD
    lsl r0,#2  
    ldr r7,=UART_BASE_TXD         
    ldr r7,[r7,r0]
    ldr r6,=0x300                             
    str r6,[r7]                    
    ldr r7,=UART_BASE_RXD 
    ldr r7,[r7,r0]                
    str r6,[r7]                
#��������1ʱ��
    ldr r7,=SIM_SCGC4
    ldr r6,[r7]
    ldr r5,=0x800
    orr r6,r5
    str r6,[r7]
    b set_u12
u2:                         @����2����
#ʹ��UART2_TXD��UART2_RXD
    lsl r0,#2  
    ldr r7,=UART_BASE_TXD     
    ldr r7,[r7,r0]
    ldr r6,=0x400                             
    str r6,[r7]                     
    ldr r7,=UART_BASE_RXD 
    ldr r7,[r7,r0]                 
    str r6,[r7]               
#��������2ʱ��
    ldr r7,=SIM_SCGC4
    ldr r6,[r7]
    ldr r5,=0x1000
    orr r6,r5
    str r6,[r7]
set_u12:                   @����1��2��������
#��ʱ�رմ���1��2��������չ���
    ldr r7,=UART_BASE_PTR
    ldr r7,[r7,r0]
    ldrb r4,[r7,#3]         
    uxtb r4,r4
    mov r5,#12
    bic r4,r5
    strb r4,[r7,#3]     
#���ô��ڹ���ģʽ:8λ��У��ģʽ
    mov r4,#0                    
    strb r4,[r7,#2]

    ldr r4,=1000
    ldr r0,=BUSCLK
    mul r0,r4             @r0=����ʱ��24000000Hz

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
#��ʼ�����ƼĴ���
    mov r6,#0
    strb r6,[r7,#2]
    strb r6,[r7,#6]
    strb r6,[r7,#5]
    mov  r6,#0x1F
    strb r6,[r7,#4]
#�������ͽ���
    ldrb r5,[r7,#3]
    uxtb r5,r5
    mov r6,#0xC
    orr r6,r5
    strb r6,[r7,#3]    
uart_init_end:
    pop {r4-r7,pc}          @�ָ��ֳ�,lr��ջ��pc

    
#============================================================================
#�������ƣ�uart_send1
#����˵����r0:���ں�
#          r1:�����͵��ֽ�
#�������أ�r0:0=����,1=�쳣
#���ܸ�Ҫ�����з���1���ֽ�    
#============================================================================
uart_send1:
    push {r4-r7,lr}  @�����ֳ�,pc(lr)��ջ
    mov r5 ,#0       @r5=0
    lsl r0,#2        @r0=r0*4,����ַ��Ԫ��ַƫ����
uart_send1_loop:
    ldr r4,=0xFBBB   @r4=���ͻ������Ƿ�Ϊ����ѯ������ֵ
    cmp r5,r4        @�ж�ѭ������ֵ
    bcs uart_send1_exit  @�ﵽ��ѯ������ֵתuart_send1_exit����
    add r5,#1         @��ǰ��ѯ������1
    
    ldr r7,=UART_BASE_PTR @r7=����UART�Ļ���ַ
    ldr r7,[r7,r0]    @r7=�ض�UART�Ļ���ַ
    ldr r6,=UART_S1   @r6=S1�Ĵ���ƫ�Ƶ�ַ
    ldrb r4,[r7,r6]  @r4=S1�Ĵ�������
    uxth r4,r4       @��չ��32λ�޷�����
    ldr r6,=uart_s1_TDRE_mask @r6=S1�Ĵ�����TDREλ����
    and r4,r6                 @ȡ��S1��TDREλ��ֵ
    cmp r4,#0         @�жϷ��ͻ������Ƿ�Ϊ��
    beq uart_send1_loop @�ǿ�����ѯ״̬��Ϊ�������
    ldr r6,=UART_D     @Ϊ�գ�r6=D�Ĵ���ƫ�Ƶ�ַ
    strb r1,[r7,r6]   @���������ֽ���D�Ĵ�������
uart_send1_exit:
    ldr r4,=0xFBBB    @r4=0xFBBB
    cmp r5,r4         @�Ƚ�ѭ������r5��0xFBBB�Ĵ�С
    bcc uart_send1_suc@��r5<0xFBBB���ͳɹ�,תuart_send1_suc����
    mov r0,#1         @����ʧ��,r0=1
    b uart_send1_end  @תuart_send1_end����
uart_send1_suc:
    mov r0,#0         @���ͳɹ�,r0=0
uart_send1_end:    
    pop {r4-r7,pc}    @�ֳ��ָ�,lr��ջ��pc
    
#============================================================================
#�������ƣ�uart_sendN
#����˵����r0:���ں�
#         r1:���������ݻ��������׵�ַ
#         r2:���ͳ���
#�������أ� r0:0=����,1=�쳣��
#���ܸ�Ҫ�����з���n���ֽ�
#============================================================================
uart_sendN:
     push {r4-r7,lr}          @�����ֳ�,pc(lr)��ջ
     mov r5,r0                @r5=r0=���ں�
     mov r7,r1                @r7=���ͻ������׵�ַ
     mov r4,r2                @r4=���ͳ���
     mov r6,#0                @���ü�����ֵ
uart_sendN_loop:
     mov r0,r5                 @r0=���ں�
     ldrb r1,[r7,r6]           @r1=�����͵��ֽ�
     bl uart_send1             @�����ֽ�
     cmp r0,#0                 @�жϷ����Ƿ�ɹ�
     bne uart_sendN_fail       @����ʧ��,תuart_sendN_fail,���ͳɹ�����
     add r6,#1                 @����ֵ��1
     cmp r6,r4                 @�ж�ѭ�������Ƿ���ڷ��ͳ���
     bcc uart_sendN_loop       @��С�ڷ��ͳ��������ѭ��
     b uart_sendN_suc          @�����ڷ��ͳ�����ת���ͳɹ���
uart_sendN_fail:
     mov  r0,#1                @����ʧ��,r0=1
     b uart_sendN_end          @תuart_sendN_end����
uart_sendN_suc:
     mov r0,#0                 @���ͳɹ�,r0=0
uart_sendN_end:
    pop {r4-r7,pc}             @�ֳ��ָ�,lr��ջ��pc
    
#============================================================================
#�������ƣ�uart_send_str
#����˵����r0:���ں�
#         r1:�������ַ������׵�ַ
#�������أ� r0:0=����,1=�쳣
#���ܸ�Ҫ����ָ�����ڷ���һ����'\0'�������ַ���
#============================================================================
uart_send_str:
     push {r4-r7,lr}          @�����ֳ�,pc(lr)��ջ
     mov r4,r0                @r4=r0=���ں�
     mov r7,r1                @r7=�������ַ����׵�ַ
     mov r6,#0                @�������ַ����ڵ�Ԫƫ�Ƶ�ַ
uart_sendstr_loop:
     mov r0,r4                @r0=���ں�
     ldrb r1,[r7,r6]          @r1=�ַ����д����͵��ַ�
     mov r5,#0
     cmp r1,r5                @�ж��Ƿ����ַ���������'\0'
     beq uart_sendstr_back    @�ǽ�����'\0',��תuart_sendstr_back
     bl uart_send1            @���͵����ַ�
     add r6,#1                @��һ���������ַ����ڵ�Ԫƫ�Ƶ�ַ
     cmp r0,#0                @�жϷ����Ƿ�ɹ�
     beq uart_sendstr_loop    @���͵����ַ��ɹ�,�����ѭ��
uart_sendstr_back:
     mov r5,#0
     cmp r1,r5               @�ж��Ƿ����ַ���������'\0'
     beq uart_sendstr_suc    @�ǽ�����'\0',���ͳɹ���תuart_sendstr_suc����
     mov  r0,#1              @����ʧ��,r0=1
     b uart_sendstr_end      @תuart_sendstr_end����
uart_sendstr_suc:
     mov r0,#0               @���ͳɹ�,r0=0
uart_sendstr_end:    
    pop {r4-r7,pc}           @�ֳ��ָ�,lr��ջ��pc
     
     
#============================================================================
#�������ƣ�uart_re1
#����˵����r0:���ں�
#�������أ�r0:0=����,1=�쳣
#          r1:���շ����ֽ�
#���ܸ�Ҫ�����н���1���ֽ�
#============================================================================
uart_re1:
     push {r4-r7,lr}     
     lsl r0,#2
     mov r5,#0
uart_re1_loop:
     ldr r6,=0xFBBB
     cmp r5,r6                  @�ж�ѭ������
     bcs uart_re1_back
     add r5,#1
     ldr r7, =UART_BASE_PTR    
     ldr r7,[r7,r0]             @�õ����ڻ���ַ
     ldr r6,=UART_S1
     ldr r4,[r7,r6]
     uxth r4,r4
     ldr r6,=uart_s1_RDRF_mask
     and r4,r6
     cmp r4,#0                  @�жϽ��ջ������Ƿ���
     beq uart_re1_loop
     ldr r6,=UART_D
     ldrb r1,[r7,r6]            @�յ�����
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
#�������ƣ�uart_reN
#����˵����r0:���ں�
#         r1:���ջ������׵�ַ
#         r2:���ճ���
#�������أ�r0:0=����,1=�쳣��
#���ܸ�Ҫ�����н���N���ֽ�
#============================================================================
uart_reN:
     push {r4-r7,lr}  
     mov r5,r0                  @���洮�ں�
     mov r7,r1
     mov r6,#0                  @���ü�����ֵ
uart_reN_loop:
     mov r0,r5   
     bl uart_re1
     cmp r0,#0                  @�жϽ����Ƿ�ɹ�
     bne uart_reN_back
     strb r1,[r7,r6]            @�洢�����ջ�������
     add r6,#1
     cmp r6,r4                  @�ж�ѭ������
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
#�������ƣ�uart_enable_re_int
#����˵����r0:���ں�
#�������أ���
#���ܸ�Ҫ�������ڽ����ж�
#============================================================================
uart_enable_re_int:
     push {r4-r7,lr}
     lsl r0,#2
     ldr r7,=UART_BASE_PTR
     ldr r7,[r7,r0]             @�õ����ڻ���ַ
     ldr r6,=UART_C2
     ldrb r4,[r7,r6]
     uxth r4,r4
     ldr r5,=uart_c2_RIE_mask
     orr r4,r5
     strb r4,[r7,r6]            @����UART�ж�
     lsr r0,#2
     ldr r7,=table_irq_uart
     ldrb r0,[r7,r0]            @��ȡIRQ��
     uxth r0,r0
     bl enable_irq              @���жϿ�����IRQ�ж�
     pop {r4-r7,pc}

#============================================================================
#�������ƣ�uart_disable_re_int
#����˵����r0:���ں�
#�������أ���
#���ܸ�Ҫ���ش��ڽ����ж�
#============================================================================
uart_disable_re_int:
     push {r4-r7,lr}
     lsl r0,#2
     ldr r7,=UART_BASE_PTR
     ldr r7,[r7,r0]             @�õ����ڻ���ַ
     ldr r6,=UART_C2
     ldrb r4,[r7,r6]
     uxth r4,r4
     ldr r5,=~uart_c2_RIE_mask
     and r4,r5
     strb r4,[r7,r6]            @�ر�UART�ж�
     lsr r0,#2
     ldr r7,=table_irq_uart
     ldrb r0,[r7,r0]            @��ȡIRQ��
     uxth r0,r0
     bl disable_irq             @���жϿ�����IRQ�ж�
     pop {r4-r7,pc}