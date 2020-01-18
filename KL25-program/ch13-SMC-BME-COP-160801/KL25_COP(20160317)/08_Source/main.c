//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�


int main(void)
{
	//1. ����������ʹ�õı���
	uint_32  mRuncount;     //��ѭ��������
	uint_8 McuRstFlag;
	if (BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0))        //�ϵ縴λ
	    McuRstFlag = 0;
    else if (BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0))  //���Ź���λ
	    McuRstFlag = 1;
	else
	    McuRstFlag = 2;

	//2. �����ж�
	DISABLE_INTERRUPTS;

	//3. ��ʼ������ģ��
	WDOG_ENABLE();
	light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //���Ƴ�ʼ��
	uart_init(UART_1, 9600);    //ʹ�ܴ���1��������Ϊ9600
	uart_init(UART_2, 9600);    //ʹ�ܴ���2��������Ϊ9600
    uart_send_string(UART_1, "Hello Uart_1!\r\n");    //���ڷ��ͳ�ʼ����ʾ
	printf("Hello Uart2!\r\n");
	//4. ���йر�������ֵ
	mRuncount=0;            //��ѭ��������
	//5. ʹ��ģ���ж�
	uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
	uart_enable_re_int(UART_2);   //ʹ�ܴ���2�����ж�
	//6. �����ж�
	ENABLE_INTERRUPTS;
    
    if(McuRstFlag == 0)
        printf("0: Power On Reset\r\n");
    else if(McuRstFlag == 1)
        printf("1: System Watch Dog Reset\r\n");
    else
        printf("2: Other Reset\r\n");

	//������ѭ��
	//��ѭ����ʼ==================================================================
	for(;;)
	{
		//����ָʾ�ƣ�RUN_LIGHT����˸---------------------------------------------
		mRuncount++;					   //��ѭ������������+1
		if (mRuncount >= RUN_COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
		{
			mRuncount=0;				   //��ѭ����������������
			light_change(RUN_LIGHT_BLUE);  //��ɫ����ָʾ�ƣ�RUN_LIGHT_BLUE��״̬�仯
			printf("change light\r\n");
		}
		FEED_DOG();

		//���¼����û�����--------------------------------------------------------
	}//��ѭ��end_for
	//��ѭ������==================================================================
}

