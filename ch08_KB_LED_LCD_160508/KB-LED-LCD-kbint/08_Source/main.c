//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�

int main(void)
{
    //1.����������ʹ�õľֲ�����
    uint_8 i, g_temp[32]="The keyboard you just input is .";
    //2.�����ж�
    DISABLE_INTERRUPTS;   //�����ж�
    //3.��ʼ���ײ�ģ��
    LEDInit();                            //LED��ʼ��
    LCDInit();                            //LCD��ʼ��
    KBInit();                             //���̳�ʼ��
	uart_init(UART_2, 9600);    //��ʼ������2��������Ϊ9600
    systick_init(CORE_CLOCK_DIV_16, 5);   // ��ʼ��SysTick����Ϊ5ms
    //4.������ֵ
    g_kb_value=0xFF;
    //LED��������ֵ
    g_LEDBuffer[0]=0;
    g_LEDBuffer[1]=2;
    g_LEDBuffer[2]=3;
    g_LEDBuffer[3]=5;
    //LCD��������ֵ
    for(i=0;i<32;i++){
        g_LCDBuffer[i]=g_temp[i];
    }
    //5.���ж�
    gpio_enable_int(n1,FALLING_EDGE);//����GPIO�����ж�,�½��ز����ж�����
    gpio_enable_int(n2,FALLING_EDGE);//����GPIO�����ж�,�½��ز����ж�����
    gpio_enable_int(n3,FALLING_EDGE);//����GPIO�����ж�,�½��ز����ж�����
    gpio_enable_int(n4,FALLING_EDGE);//����GPIO�����ж�,�½��ز����ж�����
    ENABLE_INTERRUPTS; //�����ж�
    //6.lcd��ʾ��ʼ�ַ�
    LCDShow((uint_8 *)"Wait Receiving..Soochow 2016.04.");
    //======================================================================
    for(;;)
    {
    }
    //======================================================================
    return 0;
}
