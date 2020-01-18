//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//======================================================================

#include "includes.h"   //������ͷ�ļ�


int main(void)
{
    //1. ����������ʹ�õı���
    uint_32  mRuncount;     //��ѭ��������
    uint_32  mLight_chang_num;     //��״̬�任����

    //2. �����ж�
    DISABLE_INTERRUPTS;

    //3. ��ʼ������ģ��
    light_init(LIGHT_BLUE, LIGHT_ON);  //���Ƴ�ʼ��
    uart_init(UART_0, 9600);    //��ʼ������0��������Ϊ9600
    uart_init(UART_1, 9600);    //��ʼ������1��������Ϊ9600
    uart_init(UART_2, 9600);    //��ʼ������2��������Ϊ9600
    //uart_init(UART_Debug, 9600);    //��ʼ��UART_Debug��������Ϊ9600
    //���ڷ��ͳ�ʼ����ʾ
    uart_send_string(UART_0, "ʹ��uart_send_string���ͣ�Hello Uart_0!\r\n");
    uart_send_string(UART_1, "ʹ��uart_send_string���ͣ�Hello Uart_1!\r\n");
    uart_send_string(UART_2, "ʹ��uart_send_string���ͣ�Hello Uart_2!\r\n");
    printf("ʹ��printf�������ͣ�Hello Uart_2!\r\n");
    //4. ���йر�������ֵ
    mRuncount=0;            //��ѭ��������
    mLight_chang_num=0;     //��״̬�任����
    //5. ʹ��ģ���ж�
    uart_enable_re_int(UART_0);   //ʹ�ܴ���0�����ж�
    uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
    uart_enable_re_int(UART_2);   //ʹ�ܴ���2�����ж�

    //6. �����ж�
    ENABLE_INTERRUPTS;   //�����ж�
    
	//������ѭ��
	//��ѭ����ʼ==================================================================
	for(;;)
	{
		//����ָʾ�ƣ�RUN_LIGHT����˸---------------------------------------------
		mRuncount++;					   //��ѭ������������+1
		if (mRuncount >= RUN_COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
		{
			mRuncount=0;				   //��ѭ����������������
			light_change(LIGHT_BLUE);  //��ɫ����ָʾ�ƣ�RUN_LIGHT_BLUE��״̬�仯
			mLight_chang_num++;     //��״̬�任����+1
			//printf("��״̬�任����mLight_chang_num=%d\n",mLight_chang_num);
			//uart_send_string(UART_0, "UART_0!\r\n");
		    //uart_send_string(UART_1, "UART_1!\r\n");
		    //uart_send_string(UART_2, "UART_2!\r\n");
		}
		//���¼����û�����--------------------------------------------------------
	}//��ѭ��end_for
	//��ѭ������==================================================================
}

