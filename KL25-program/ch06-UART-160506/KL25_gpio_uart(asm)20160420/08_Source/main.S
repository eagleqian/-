#============================================================================
#�ļ����ƣ�main.s
#���ܸ�Ҫ������̿���С����˸
#��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
#�汾���£�2016-04-20  V1.6
#============================================================================
.include "include.S"

#start ������������
  	.section	.text
    .global main                            @����ȫ�ֱ�����ʹ����оƬ��ʼ��֮����Ե���
     .align 2
    .type main, function                     @������������
    .align 2
#end  ������������

 main:
    .syntax divided
    cpsid i                                 @�ر����жϣ����г�ʼ��
#С�Ƴ�ʼ��
    ldr r0,=LIGHT_BLUE
    ldr r3,=LIGHT_ON
    bl light_init                           @����С�Ƴ�ʼ������

#UART1��ʼ��
    ldr r0,=UART1_BUSCLK
    ldr r1,=9600
    mov r2,#0
    mov r3,#0
    bl  uart_init

#��������������

#ʹ��uart_send_str��������
    ldr r0,=UART1
    ldr r1,=test
    bl uart_send_str

#ʹ��uart_send1��������
    ldr r0,=UART1
    mov r1,#10    @�س�
    bl uart_send1
    ldr r0,=UART1
    mov r1,#10    @�س�
    bl uart_send1

#ʹ��uart_sendN��������
    ldr r0,=UART1
    ldr r1,=test2
    mov r2,#31
    bl uart_sendN

#ʹ��uart_send1��������
    ldr r0,=UART1
    mov r1,#10    @�س�
    bl uart_send1
    ldr r0,=UART1
    mov r1,#10    @�س�
    bl uart_send1

#�򿪴����ж�
    ldr r0,=UART1
    bl uart_enable_re_int
	cpsie  i                                @�����ж�

#��ѭ����ͨ��RUN_COUNTER_MAX�ݼ����ӳ٣��趨С�Ƶ���˸���
main_repeat:
    ldr r4,=RUN_COUNTER_MAX                 @ȡ��ʱ����ֵRUN_COUNTER_MAX�Ĵ洢��ַ��r4
    ldr r4,[r4]
    .hidden main_loop

/*    ldrb r0,=UART1
    ldr r1,=test
    bl uart_send_str
*/
main_loop:                                       @ȡ��ʱ����ֵRUN_COUNTER_MAX��ֵ��r4
    sub r4,#1
    cmp r4,#1                               @�ж���ʱʱ���Ƿ��ѵ�
    bne main_loop

    ldr r0,=LIGHT_BLUE
    bl light_change                         @����ʱʱ���ѵ��������С������ת�亯��

    b main_repeat
    .align 2

.end


