 //˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�

int main(void) {
	//1. ����������ʹ�õı���
	uint_32 remember;      //��¼��һ�̵���ֵ
	//2. �����ж�
	DISABLE_INTERRUPTS;
	//3. ��ʼ������ģ��
	light_init(LIGHT_BLUE, LIGHT_OFF);  //���Ƴ�ʼ��
	light_init(LIGHT_RED, LIGHT_OFF);  //���Ƴ�ʼ��

	uart_init(UART_1, 9600);    //ʹ�ܴ���1��������Ϊ9600
	uart_init(UART_2, 9600);    //ʹ�ܴ���2��������Ϊ9600
	systick_init(CORE_CLOCK_DIV_16, 10);    // ��ʼ��SysTick����Ϊ10ms
	printf("\r\n���ݴ�ѧǶ��ʽʵ����SysTick������������!");
	//4. ���йر�������ֵ
	g_time[0] = 0;          //"ʱ����"�����ʼ��(00:00:00)
	g_time[1] = 0;
	g_time[2] = 0;
	remember = g_time[2];
	//5. ʹ��ģ���ж�
	uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
	uart_enable_re_int(UART_2);   //ʹ�ܴ���2�����ж�
	//6. �����ж�
	ENABLE_INTERRUPTS;
	//������ѭ��
	//��ѭ����ʼ==================================================================
	for (;;) {
		//����ָʾ�ƣ�RUN_LIGHT����˸---------------------------------------------
		if (g_time[2] != remember)      //�ж������Ƿ����仯
				{

			/*if (colorChange == 0) {
			 light_control(LIGHT_RED, LIGHT_OFF);
			 light_change(LIGHT_BLUE);  //��ɫ����ָʾ��״̬�仯
			 } else if (colorChange == 1) {
			 light_control(LIGHT_BLUE, LIGHT_OFF);
			 light_change(LIGHT_RED);  //��ɫ����ָʾ��״̬�仯
			 } else {
			 }*/
			light_change(LIGHT_BLUE);
			printf("\r\nMCU��¼�����ʱ�䣺%02d:%02d:%02d", g_time[0], g_time[1],
					g_time[2]);
			remember = g_time[2];
		}
		//���¼����û�����--------------------------------------------------------
	}  //��ѭ��end_for
	   //��ѭ������==================================================================
}

