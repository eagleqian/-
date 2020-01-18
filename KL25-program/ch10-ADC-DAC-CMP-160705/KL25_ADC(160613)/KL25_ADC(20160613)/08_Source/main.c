//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//=====================================================================

#include "includes.h"   //������ͷ�ļ�

extern void Delay_ms(uint16_t u16ms);

int main(void)
{
    //1. ����������ʹ�õı���
    uint_32  mRuncount;     //��ѭ��������
    uint_16  ADCResult[21];   //���AD���
    uint_16  i;
    //2. �����ж�
    DISABLE_INTERRUPTS;

    //3. ��ʼ������ģ��
    light_init(LIGHT_BLUE, LIGHT_ON);  //���Ƴ�ʼ��
    uart_init(UART_1, 9600);    //ʹ�ܴ���1��������Ϊ9600
    uart_init(UART_2, 9600);    //ʹ�ܴ���2��������Ϊ9600
    uart_send_string(UART_1, "This is ADC Test!\r\n");  //���ڷ�����ʾ
    printf("Hello Uart2!\r\n");
    //4. ���йر�������ֵ
    mRuncount=0;            //��ѭ��������
    //5. ʹ��ģ���ж�
    uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
    uart_enable_re_int(UART_2);   //ʹ�ܴ���2�����ж�
    //6. �����ж�
    ENABLE_INTERRUPTS;
    
    //������ѭ��
    //��ѭ����ʼ==================================================
    for(;;)
    {
        //����ָʾ�ƣ�LIGHT����˸------------------------------------
        mRuncount++;                       //��ѭ������������+1
        if (mRuncount >= COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
        {
            mRuncount=0;                   //��ѭ����������������
            light_change(LIGHT_BLUE);  //��ɫ����ָʾ��״̬�仯
        }
        //���¼����û�����-----------------------------
        //A���ʼ����ͨ���顢�������룬�������ȣ�Ӳ����ֵ��
        adc_init(MUXSEL_A,0,16,SAMPLE32);
        //��ͷ��־
        ADCResult[0] = 0x1122;
        //�ɼ�����
        ADCResult[1] = adc_read(0);
        for (i=2;i<=8;i++)  ADCResult[i] = adc_read(i+1);
        for (i=9;i<=13;i++)  ADCResult[i] = adc_read(i+2);
        ADCResult[14] = adc_read(23);
        ADCResult[15] = adc_read(26);     //оƬ�¶Ȳɼ�ͨ��
        //B���ʼ����ͨ���顢�������룬�������ȣ�Ӳ����ֵ��
        adc_init(MUXSEL_B,0,16,SAMPLE32);
        //����
        for (i=16;i<=20;i++)  ADCResult[i] = adc_read(i-12);
        //��ĩβ��־
        ADCResult[20] = 0x8899;
        //���ɼ���A/Dֵͨ�����ڷ��͵�PC
        uart_sendN(UART_TEST,42,(uint_8*)ADCResult);
        Delay_ms(50);
    }//��ѭ��end_for
    //��ѭ������==================================================
}

