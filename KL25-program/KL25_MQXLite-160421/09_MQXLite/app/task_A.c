#include "app_inc.h"    //Ӧ�����񹫹�ͷ�ļ�

//===========================================================================
//�������ƣ�task_A
//���ܸ�Ҫ��light redÿ4������һ��
//����˵����δʹ��
//===========================================================================
void task_A(uint_32 initial)
{    
    while (TRUE)
    {
        light_change(RUN_LIGHT_RED);           // �ı�������״̬
        printf("lingt red change\r\n");
        _time_delay_ticks(DELAY_TIMES*4);// ��ʱDELAY_TIMES(����CPU����Ȩ)
    }
}
