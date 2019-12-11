//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================�жϺ�����������===============================
//======================================================================
//�������ƣ�SysTick_Handler
//����˵������
//�������أ���
//���ܸ�Ҫ��SysTick��ʱ���жϷ�������
//======================================================================

//ȫ�ֱ��������ı�ʱ��,tickCount��Ϊѡ��ģʽȡֵΪ1~5
uint_8 tickCount = 1;

static uint_8 modeChange = 0; //ģʽ�л���־�������л���ͬ��˸ģʽ


//��֡����ԭ������
uint8_t CreateFrame(uint_8 Data, uint_8 * buffer);

void SysTick_Handler(void) //�����˽��жϵ��ں�
//Ĭ��ֵΪ100,���ʾ1S��һ��
{
	static uint_8 SysTickcount = 0; //��̬����,�������ÿ����������ʱ��
	static uint_8 twinkleCount = 0; //�ܼ���˸ָʾ�ƴ�������
	SysTickcount++;

	if (tickCount == 1) {
		if (SysTickcount >= 30)
				{
			SysTickcount = 0;
			//���ʱ����
			SecAdd1(g_time);      //g_time��ʱ����ȫ�ֱ�������
		}
	} else if (tickCount == 2 || tickCount == 3 || tickCount == 4
			|| tickCount == 5) {
		switch (modeChange) {
		case 1: {
			if (twinkleCount <= (tickCount * 2 - 2)) {
				if (SysTickcount >= 30){
					SysTickcount = 0;
					//���ʱ����
					SecAdd1(g_time);      //g_time��ʱ����ȫ�ֱ�������
					twinkleCount++;
				}
			} else {

				twinkleCount = 0;      //��ʼ���ܼ���˸����
				modeChange = 0;      //������˸ָʾ��־

			}
		}
		case 0: {
			if (SysTickcount >= 150)   //���õȴ�ʱ�䣬�㹻������˸ģʽ
					{
				SysTickcount = 0;   //1.5s�Ժ�С��������1.5s�İ�״̬�Ż��л�Ϊ��״̬
				//���ʱ����
				SecAdd1(g_time);      //g_time��ʱ����ȫ�ֱ�������
				modeChange = 1;      //������˸ָʾ��־
			}
		}
		}
	}
	else{}

}

//����0�����жϷ�������
void UART0_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	DISABLE_INTERRUPTS;

	ch = uart_re1(UART_0, &flag);
	if (flag) {
		uart_send1(UART_0, ch);
	}

	ENABLE_INTERRUPTS;
}

//����1�����жϷ�������
void UART1_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	uint_8 buffer[64];

	DISABLE_INTERRUPTS;
	if (uart_get_re_int(UART_1)) {
		ch = uart_re1(UART_1, &flag);

		if (ch == '1') {
			tickCount = 1;
			modeChange=1;
			light_control(LIGHT_BLUE, LIGHT_ON);
		} else if (ch == '2') {
			tickCount = 2;
			modeChange=1;
			light_control(LIGHT_BLUE, LIGHT_ON);
		} else if (ch == '3') {
			tickCount = 3;
			modeChange=1;
			light_control(LIGHT_BLUE, LIGHT_ON);
		} else if (ch == '4') {
			tickCount = 4;
			modeChange=1;
			light_control(LIGHT_BLUE, LIGHT_ON);
		} else if (ch == '5') {
			tickCount = 5;
			modeChange=1;
			light_control(LIGHT_BLUE, LIGHT_ON);
		} else {
			tickCount = 1;
			modeChange=1;
			light_control(LIGHT_BLUE, LIGHT_ON);
		}

	}
	if (flag) {
		uart_send1(UART_1, ch);
	}
	ENABLE_INTERRUPTS;
}

//����2�����жϷ�������
void UART2_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;

	DISABLE_INTERRUPTS;

	ch = uart_re1(UART_2, &flag);
	if (flag) {
		uart_send1(UART_2, ch);
	}

	ENABLE_INTERRUPTS;
}


//��֡������������������֡
#define FrameHead    (0x50)       //֡ͷ     ASCII���ӦP
#define FrameTail    (0x43)       //֡β     ASCII���ӦC

uint8_t CreateFrame(uint_8 Data, uint_8 * buffer) {
	static uint_8 frameLen = 0;    //֡�ļ�����
	uint_8 frameFlag;            //��֡״̬

	frameFlag = 0;            //��֡״̬��ʼ��
//���ݾ�̬����frameCount��֡
	switch (frameLen) {
	case 0:    //��һ������
	{
		if (Data == FrameHead)    //�յ�������֡ͷFrameHead
		{
			buffer[0] = Data;
			frameLen++;
			frameFlag = 0;        //��֡��ʼ
		}
		break;
	}
	case 1:    //�ڶ������ݣ��������������յ����ݸ���
	{
		buffer[1] = Data - 0x30;
		frameLen++;
		break;
	}
	default:    //�������
	{
		//�ڶ�λ��������Ч���ݳ���,�������������µ�����ֱ��֡βǰһλ
		if (frameLen >= 2 && frameLen <= (buffer[1] + 1)) {
			buffer[frameLen] = Data;
			frameLen++;
			break;
		}

		//����ĩβ������ִ��
		if (frameLen >= (buffer[1] + 2)) {
			if (Data == FrameTail)    //����֡β
			{
				buffer[frameLen] = Data;     //��֡β���뻺����
				frameFlag = 1;    //��֡�ɹ�
			}
			frameLen = 0;     //������0��׼��������֡
			break;
		}
	}
	}     //switch_END
	return frameFlag;                 //������֡״̬
}
