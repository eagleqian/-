//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2015-4-26  V1.0
//оƬ���ͣ�KL25
//===========================================================================

#include "includes.h"
#include "app_inc.h"
#define FrameHead    'A'         //֡ͷ
#define FrameTail    'D'         //֡β
//�ڲ���������
uint8_t CreateFrame(uint8_t Data, uint8_t * buffer);

////========================�жϺ�����������===============================

//===========================================================================
//�ж����̣�UART2_IRQHandler
//���ܸ�Ҫ������2�жϷ������̣�ÿ�յ�һ���ֽ�ִ��һ�α����򣬷��ͻ�ȥ������֡
//����˵����user_isr_ptr��δʹ�ã�
//��       ע��ʹ��ȫ�ֱ��� g_UART_ISR_buffer[]
//===========================================================================
void UART2_IRQHandler(pointer user_isr_ptr) {
	uint8_t Redata;                 //��Ž�����������
	uint_8 flag = 1;

	Redata = uart_re1(UART_2, &flag);                 //���յ�һ���ֽ�����
	if (flag == 0)
		return;
	else
		uart_send1(UART_2, Redata);                 //���յ���һ���ֽ����ݷ��ͻ�ȥ
	//��֡�ɹ�,�á�����2������������֡�¼�λ��
	if (CreateFrame(Redata, g_UART_ISR_buffer) != 0) {
		_lwevent_set(&lwevent_group1, Event_UART2_ReData);
	}
}

//�ڲ����ú���

//===========================================================================
//ISR���ƣ�Createbuffer
//���ܸ�Ҫ���齨����֡��������֡���ݼ��뵽����֡��
//����˵����Data:����֡����
//         buffer:����֡����
//�������أ���֡״̬    0-��֡δ�ɹ���1-��֡�ɹ�
//��       ע��ʮ����������֡��ʽ
//             ֡ͷ         +   ���ݳ���     + ��Ч����     +   ֡β
//          FrameHead  +     len     + ��Ч����      + FrameTail
//===========================================================================
uint8_t CreateFrame(uint8_t Data, uint8_t * buffer) {
	static uint8_t frameCount = 0;    //��֡������
	uint8_t frameFlag;              //��֡״̬
	frameFlag = 0;
	//���ݾ�̬����frameCount��֡
	switch (frameCount) {
		case 0:    //��һ������
		{
			if (Data == FrameHead)    //�յ�������֡ͷFrameHead
			{
				buffer[0] = Data;
				frameCount++;
				frameFlag = 0;        //��֡��ʼ
			}
			break;
		}
		case 1:    //�ڶ������ݣ��������������յ����ݸ���
		{
			buffer[1] = Data;
			frameCount++;
			break;
		}
		default:    //�������
		{
			//�ڶ�λ��������Ч���ݳ���,�������������µ�����ֱ��֡βǰһλ
			if (frameCount >= 2 && frameCount <= (buffer[1] + 1)) {
				buffer[frameCount] = Data;
				frameCount++;
				break;
			}

			//����ĩβ������ִ��
			if (frameCount >= (buffer[1] + 2)) {
				if (Data == FrameTail)    //����֡β
				{
					buffer[frameCount] = Data;     //��֡β0x44���뻺����
					frameFlag = 1;    //��֡�ɹ�
				}
				frameCount = 0;     //������0��׼��������֡
				break;
			}
		}
	}     //switch_END
	return frameFlag;                 //������֡״̬
}
