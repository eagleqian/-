#include "app_inc.h"

//===========================================================================
//�������ƣ�task_B
//���ܸ�Ҫ��light greenÿ4������һ�Σ��״�����ǰ��ʱ1��
//����˵����δʹ��
//===========================================================================
void task_B(uint_32 initial_data)
{
    _time_delay_ticks(DELAY_TIMES);
    while (TRUE) 
    {
        light_change(RUN_LIGHT_GREEN);            // �ı��̵�����״̬
        printf("light green change\r\n");
        _time_delay_ticks(DELAY_TIMES*4); // ��ʱDELAY_TIMES(����CPU����Ȩ)
    }
}
