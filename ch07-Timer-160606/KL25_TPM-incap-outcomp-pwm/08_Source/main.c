//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//======================================================================

#include "includes.h"   //������ͷ�ļ�


int main(void)
{
    //1. ����������ʹ�õı���
    uint_32  remember;      //��¼��һ�̵���ֵ
    //2. �����ж�
    DISABLE_INTERRUPTS;
    //3. ��ʼ������ģ��
    light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //���Ƴ�ʼ��
    uart_init(UART_1, 9600);    //ʹ�ܴ���1��������Ϊ9600
    uart_init(UART_2, 9600);    //ʹ�ܴ���2��������Ϊ9600
    printf("\r\n���ݴ�ѧǶ��ʽʵ����TPM-incap-outcomp������������!");
    //��ʼ��tpm�������ú�ʱ��
    tpm_timer_init(TPM_0,3000,10);        //��ʼ��TPM0ģ��10ms��ʱ���
    tpm_timer_init(TPM_1,3000,20);        //��ʼ��TPM1ģ��20ms��ʱ���
    tpm_timer_init(TPM_2,3000,20);        //��ʼ��TPM2ģ��20ms��ʱ���
    //��ʼ��PWM�ź����
    pwm_init(TPM1_CH0,0.0,1,PWM_PLUS);      //ͨ��������PTA4
    //��ʼ�����벶׽,����2ģ��,0ͨ��
    incap_init(TPM2_CH0,CAP_UP);            //ͨ��������PTA1
    //��ʼ������Ƚ�
    outcompare_init(TPM0_CH0,5,CMP_REV);    //ͨ��������PTC1

    //4. ���йر�������ֵ
    g_time[0] = 0;                 //"ʱ����"�����ʼ��(00:00:00)
    g_time[1] = 0;
    g_time[2] = 0;
    remember  = g_time[2];
    //5. ʹ��ģ���ж�
    uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
    uart_enable_re_int(UART_2);   //ʹ�ܴ���2�����ж�
    tpm_enable_int(0);        //ʹ��TPM0�ж�
    tpm_enable_int(1);        //ʹ��TPM1�ж�
    tpm_enable_int(2);        //ʹ��TPM2�ж�
    //6. �����ж�
    ENABLE_INTERRUPTS;

    //======��ѭ����ʼ======================================================
    for(;;)
    {
        //------����ָʾ�ƣ�RUN_LIGHT_BLUE����˸------
        if (g_time[2] != remember)      //�ж������Ƿ����仯
        {
            light_change(RUN_LIGHT_BLUE);  //��ɫ����ָʾ��״̬�仯
            printf("\r\nʱ�䣺%02d:%02d:%02d",g_time[0],g_time[1],g_time[2]);
            remember=g_time[2];
        }
     }  //��ѭ��end_for
    //======��ѭ������======================================================
}

