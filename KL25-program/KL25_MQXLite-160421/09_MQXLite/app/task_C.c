#include "app_inc.h"

//===========================================================================
//�������ƣ�task_C
//���ܸ�Ҫ��light blueÿ4������һ�Σ��״�����ǰ��ʱ2��
//����˵����δʹ��
//===========================================================================
void task_C(uint_32 initial_data)
{            
    _time_delay_ticks(DELAY_TIMES*2);
    while (TRUE) 
    {
        light_change(RUN_LIGHT_BLUE);            // �ı���������״̬
        printf("light blue change\r\n");
        _time_delay_ticks(DELAY_TIMES*4); // ��ʱDELAY_TIMES(����CPU����Ȩ)
    }
}
