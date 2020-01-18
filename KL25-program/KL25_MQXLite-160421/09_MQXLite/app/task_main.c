#define GLOBLE_VAR

#include "app_inc.h"     

//===========================================================================
//�������ƣ�task_main
//���ܸ�Ҫ��MQX������������Ҫʵ��ȫ�ֱ�����ʼ���������������񡢰�װ�û�ISR
//����˵����δʹ��
//===========================================================================
void task_main(uint32_t initial_data)
{
    //1.ȫ�ֱ�����ʼ��
    _lwevent_create(&lwevent_group1,0);  //�����������¼���
    g_UART_FrameCount=0;                 //���յ�֡��

    //2. �����ж�
    DISABLE_INTERRUPTS;

    //3.�����ʼ��
    light_init(RUN_LIGHT_RED,LIGHT_OFF);   //��Ƴ�ʼ��
    light_init(RUN_LIGHT_GREEN,LIGHT_OFF);   //�̵Ƴ�ʼ��
    light_init(RUN_LIGHT_BLUE,LIGHT_OFF);   //���Ƴ�ʼ��

    uart_init(UART_Debug,9600);      //��ʼ�����Դ���

    //4.������������
    _task_create_at(0, TASK_A, 0, task_A_stack, TASK_A_STACK_SIZE);
    _task_create_at(0, TASK_B, 0, task_B_stack, TASK_B_STACK_SIZE);
    _task_create_at(0, TASK_C, 0, task_C_stack, TASK_C_STACK_SIZE);
    _task_create_at(0, TASK_D, 0, task_D_stack, TASK_D_STACK_SIZE);

    //5.��װ�û�ISR
    _int_install_isr(UART0_IRQn+UART_Debug+16,UART2_IRQHandler,NULL);  //ע����Դ��ڵ�ISR
    
    //6.ʹ��ģ���жϼ����ж�
    uart_enable_re_int(UART_Debug);      //ʹ�ܵ��Դ��ڽ����ж�

    //7.�����ж�
    ENABLE_INTERRUPTS;
    
    //------------ִ����ϣ��������������̬-----------------------------------
    _task_block();
}
