//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//======================================================================

#include "includes.h"   //������ͷ�ļ�

int main(void)
{
    //1.����������ʹ�õľֲ�����
    uint_8 i;
    uint_8 g_temp[32]="The keyboard you just input is .";
//      uint_8 g_temp[32]="                                ";

    //2.�����ж�
    DISABLE_INTERRUPTS;   //�����ж�
    //3. ��ʼ������ģ��
    LEDInit();                            //LED��ʼ��

    LCDInit();                            //LCD��ʼ��
    KBInit();                             //���̳�ʼ��
    systick_init(CORE_CLOCK_DIV_16, 5);   //��ʼ��SysTick���ڡ����жϡ���������
    //4.��������ֵ
    g_LEDBuffer[0]=8;    //LED��������ֵ
    g_LEDBuffer[1]=6;
    g_LEDBuffer[2]=9;
    g_LEDBuffer[3]=2;
    for(i=0;i<32;i++)  {g_LCDBuffer[i]=g_temp[i];}  //LCD��������ֵ
    LCDShow(g_LCDBuffer);  //LCD��ʾ��ʼ�ַ�
    //5. ʹ��ģ���ж�

    //6. �����ж�
    ENABLE_INTERRUPTS;   //�����ж�
    //======================================================================
    while(1)
    {
    }
    //======================================================================
    return 0;
}
