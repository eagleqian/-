//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�


int main(void)
{
	//1. ����������ʹ�õı���
	uint_32  mRuncount;     //��ѭ��������
	uint_16  VReference;
	uint_8 light_flag;
	//2. �����ж�
	DISABLE_INTERRUPTS;

	//3. ��ʼ������ģ��
	light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //���Ƴ�ʼ��
	uart_init(UART_1, 9600);    //ʹ�ܴ���1��������Ϊ9600
	uart_init(UART_2, 9600);    //ʹ�ܴ���2��������Ϊ9600
    uart_send_string(UART_1, "This is DAC Test!\r\n");    //���ڷ��ͳ�ʼ����ʾ
	dac_init(DAC_VDDA);     //DAC��ʼ����ѡ��ο���ѹVDDA=3.3V
	//4. ���йر�������ֵ
	mRuncount=0;            //��ѭ��������
    VReference=2000;           //DAC�ο�������
    light_flag=1;
	//5. ʹ��ģ���ж�
	uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
	uart_enable_re_int(UART_2);   //ʹ�ܴ���2�����ж�
	//6. �����ж�
	ENABLE_INTERRUPTS;
    
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
			//DAC������ת�������VReference��ֵ��Ӧ�ĵ�ѹֵ
			dac_convert(VReference);

			//���ݱ�־λ������С����������������Ϩ��
			if(light_flag==1)  VReference += 1;
			else if(light_flag==0)  VReference -= 1;

			//VReference�޷�������ת�Ƶ�����Ϩ��ı�־λ
			if(VReference >= 2600)  light_flag=0;
			if(VReference <= 2200)  light_flag=1;
		}
		//���¼����û�����--------------------------------------------------------
	}//��ѭ��end_for
	//��ѭ������==================================================================
}

