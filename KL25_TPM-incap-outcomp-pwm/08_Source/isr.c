//=====================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//=====================================================================
#include "includes.h"

//========================�жϺ�����������===============================
//=====================================================================
//�������ƣ�TPM0_IRQHandler��TPM0�жϷ������̣�
//���ܸ�Ҫ��10ms�ж�һ�Σ�������ִ��һ�Σ���̬����cnt��1������100����1��ʱ�䣬
//         ����SecAdd1����ȫ�ֱ�������g_time��ֵ��ʱ���֡��룩
//=====================================================================

//��֡����ԭ������
uint8_t CreateFrame(uint_8 Data, uint_8 * buffer);

void TPM0_IRQHandler(void) {
	static uint_32 cnt;       //�жϴ���
	if (tpm_get_int(0) == 1)   //����TPM0������ж�
			{
		tpm_clear_int(0);     //��TPM0������жϱ�־
		cnt++;                //�жϴ���+1
		if (cnt >= 100)        //���ﵽ100�Σ���1�룩
				{

			//ʵ����ֵ�������ַ�ASCII��ֵ��ת��,���ʱ���ַ���
			uart_send1(UART_1, (g_time[0] / 10) + 48);
			uart_send1(UART_1, (g_time[0] % 10) + 48);
			uart_send1(UART_1, ':');

			uart_send1(UART_1, (g_time[1] / 10) + 48);
			uart_send1(UART_1, (g_time[1] % 10) + 48);
			uart_send1(UART_1, ':');

			uart_send1(UART_1, (g_time[2] / 10) + 48);
			uart_send1(UART_1, (g_time[2] % 10) + 48);

			cnt = 0;          //�жϴ�����0
			//���á���+1��ʱ�Ӻ���������ȫ�ֱ�������g_time��ֵ��ʱ���֡��룩
			SecAdd1(g_time);

		}
	}
}

//=====================================================================
//�������ƣ�TPM1_IRQHandler��TPM1�жϷ������̣�
//���ܸ�Ҫ��20ms�ж�һ�Σ�������ִ��һ�Σ���̬����duty��0.0����100.0��
//         ����100.0����0.0��Ȼ�����dutyֵ���ı�pwm��ռ�ձȵ�ֵ��
//         ��Ӧ��PWM������ſ��Բ����Ӧ��PWM����
//=====================================================================

void TPM1_IRQHandler(void) {
	static float duty = 0.0;     //��̬����duty��ռ�ձȣ�
	static uint_8 Up_Down = 1;   //ռ�ձ�������־

	if (tpm_get_int(1) == 1)   //����TPM1������ж�
			{
		tpm_clear_int(1);     //��TPM1������жϱ�־
		pwm_update(TPM1_CH0, duty);    //PWN����
		if (Up_Down == 1)              //ռ�ձ�������
				{
			duty = duty + 0.5;
			if (duty > 100.0)          //��ֹռ�ձ�Խ��
					{
				duty = 100.0;
				Up_Down = 0;
			}
		} else                       //ռ�ձ��𽥼�С
		{
			duty = duty - 0.5;
			if (duty < 0)             //��ֹռ�ձ�Խ��
					{
				duty = 0;
				Up_Down = 1;
			}
		}
	}
}
//=====================================================================
//�������ƣ�TPM2_IRQHandler��TPM2�жϷ������̣�
//���ܸ�Ҫ�������жϺ��ж���20ms��ʱ������жϣ�����ͨ�������ж�,����Ǽ��������
//         �ж����жϱ�־λ�󷵻أ������ͨ�������ж���ô��¼��ǰ����ֵ������¼
//         ��ʮ��ֵ�󣬽���10��ֵһ���Ӵ��ڴ��
//=====================================================================
void TPM2_IRQHandler(void) {
	static uint_32 Cap_Value[10];    //�����ͨ��ֵ
	static uint_32 cnt = 0;            //��׽����

//����TPM2������ж�,�����жϱ�־
	if (tpm_get_int(2) == 1)
		tpm_clear_int(2);
//��ͨ���жϲ���
	if (tpm_chl_get_int(2, 0) == 1)  //�ж��ж������Ƿ�Ϊͨ���ж�
			{
		tpm_clear_chl_int(2, 0);    //���ͨ���жϱ�־
		Cap_Value[cnt] = tpm_get_capvalue(TPM2_CH0);  //��ȡͨ������ֵ
		cnt++;    //��׽����+1
		if (cnt >= 10)        //������ȡ10�β���ֵ
				{
			while (cnt)    //��10������ֵͳһͨ�����ڴ��
			{
				cnt--;
				printf("TPM2ͨ��0�����벶׽ͨ��ֵ��%d\n", Cap_Value[cnt]);
			}
		}
	}
}

//=====================================================================
//�������ƣ�UART0_IRQHandler������0�����жϷ������̣�
//���ܸ�Ҫ������0����һ�����ݣ���������
//=====================================================================
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

//=====================================================================
//�������ƣ�UART1_IRQHandler������1�����жϷ������̣�
//���ܸ�Ҫ������1����һ�����ݣ���������
//=====================================================================
void UART1_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	static uint_8 buffer[64];

	DISABLE_INTERRUPTS;
	if (uart_get_re_int(UART_1)) {
		ch = uart_re1(UART_1, &flag);
		if (CreateFrame(ch, buffer) != 0) {
			if (buffer[1] == 8) { //C#��������ֶ����ַ��ͣ�ÿ�������ַ�����Ӧһ��ASCII���룩ֵ

				//buffer�����е����ֲ���ÿλ�ֽ����㶼���ö�Ӧ��ASCII��ֵ����
				//���Ƿ��͸�c#��ʱ�򣬱��뷢��������Ӧ���ַ�ASCII��ֵ��

				//����hh:mm:ss
				uint_8 g_time0 = (buffer[2]);
				g_time0 -= 48;
				g_time0 *= 10;
				buffer[3] -= 48;
				g_time0 += (buffer[3]);

				uint_8 g_time1 = (buffer[5]);
				g_time1 -= 48;
				g_time1 *= 10;
				buffer[6] -= 48;
				g_time1 += (buffer[6]);

				uint_8 g_time2 = (buffer[8]);
				g_time2 -= 48;
				g_time2 *= 10;
				buffer[9] -= 48;
				g_time2 += (buffer[9]);

				g_time[0] = g_time0;
				g_time[1] = g_time1;
				g_time[2] = g_time2;

			}

		}
	}
	if (flag) {
		uart_send1(UART_1, ch);

	}

	ENABLE_INTERRUPTS;

}

//=====================================================================
//�������ƣ�UART2_IRQHandler������2�����жϷ������̣�
//���ܸ�Ҫ������2����һ�����ݣ���������
//=====================================================================
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

//------�������Ӻ���------
//=====================================================================
//�������ƣ�SecAdd1����+1��ʱ�Ӻ���
//�������أ���
//����˵����*p:Ϊָ��һ��ʱ��������p[3]
//���ܸ�Ҫ���뵥Ԫ+1��������ʱ�ֵ�Ԫ��00:00:00-23:59:59)
//=====================================================================
void SecAdd1(uint_8 *p) {
	*(p + 2) += 1;         //��+1
	if (*(p + 2) >= 60)     //�����
			{
		*(p + 2) = 0;       //����
		*(p + 1) += 1;      //��+1
		if (*(p + 1) >= 60)  //�����
				{
			*(p + 1) = 0;    //���
			*p += 1;       //ʱ+1
			if (*p >= 24)   //ʱ���
					{
				*p = 0;      //��ʱ
			}
		}
	}
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
		//����ǹؼ����ڣ���ASCII��ֵ������ת����
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

