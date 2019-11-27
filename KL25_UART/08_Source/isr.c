//=====================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//         2016-03-27 V2.0(XD)
//=====================================================================
#include "includes.h"
#include "string.h"
#include "includes.h"
//#include "01_app_include.h"

//========================�жϺ�����������===============================
//����0�����жϷ�������
void UART0_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	DISABLE_INTERRUPTS;    //�����ж�
	if (uart_get_re_int(UART_0)) {
		ch = uart_re1(UART_0, &flag);    //���ý���һ���ֽڵĺ�����������ж�λ
		if (flag) {
			uart_send1(UART_0, ch);     //��ԭ���ڷ���һ���ֽ�
		}
	}
	ENABLE_INTERRUPTS; //�����ж�
}

uint8_t CreateFrame(uint_8 Data, uint_8 * buffer);

//����1�����жϷ�������
void UART1_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	uint_8 buffer[64];
	DISABLE_INTERRUPTS;    //�����ж�
	if (uart_get_re_int(UART_1)) {
		ch = uart_re1(UART_1, &flag);    //���ý���һ���ֽڵĺ�����������ж�λ
		if(CreateFrame(ch,buffer)!=0){
			if (buffer[2] == 'r' && buffer[3] == 'e' && buffer[4] == 'd') {
			    light_control(LIGHT_BLUE, LIGHT_OFF);
			    light_control(LIGHT_GREEN, LIGHT_OFF);
			    light_control(LIGHT_RED, LIGHT_ON);
			}
			else if (buffer[2] == 'b' && buffer[3] == 'l' && buffer[4] == 'u'
			        && buffer[5] == 'e') {
			    light_control(LIGHT_GREEN, LIGHT_OFF);
			    light_control(LIGHT_RED, LIGHT_OFF);
			    light_control(LIGHT_BLUE, LIGHT_ON);
			}
			else if (buffer[2] == 'g' && buffer[3] == 'r' && buffer[4] == 'e'
			        && buffer[5] == 'e' && buffer[6] == 'n') {
			    light_control(LIGHT_BLUE, LIGHT_OFF);
			    light_control(LIGHT_RED, LIGHT_OFF);
			    light_control(LIGHT_GREEN, LIGHT_ON);
			}

			else if (buffer[2] == 'c' && buffer[3] == 'l' && buffer[4] == 'o'
			        && buffer[5] == 's' && buffer[6] == 'e') {
			    light_control(LIGHT_BLUE, LIGHT_OFF);
			    light_control(LIGHT_RED, LIGHT_OFF);
			    light_control(LIGHT_GREEN, LIGHT_OFF);
			}
			else if (buffer[2] == 'v' && buffer[3] == 'i' && buffer[4] == 'o'
			        && buffer[5] == 'l' && buffer[6] == 'e'
			        && buffer[7] == 't') {
			    light_control(LIGHT_GREEN, LIGHT_OFF);
			    light_control(LIGHT_BLUE, LIGHT_ON);
			    light_control(LIGHT_RED, LIGHT_ON);
			}

			else if (buffer[2] == 'w' && buffer[3] == 'h' && buffer[4] == 'i'
			        && buffer[5] == 't' && buffer[6] == 'e') {
			    light_control(LIGHT_BLUE, LIGHT_ON);
			    light_control(LIGHT_RED, LIGHT_ON);
			    light_control(LIGHT_GREEN, LIGHT_ON);
			}
			else if (buffer[2] == 'c' && buffer[3] == 'y' && buffer[4] == 'a'
			        && buffer[5] == 'n') {
			    light_control(LIGHT_RED, LIGHT_OFF);
			    light_control(LIGHT_BLUE, LIGHT_ON);
			    light_control(LIGHT_GREEN, LIGHT_ON);
			}
			else if(buffer[2] == 'y' && buffer[3] == 'e' && buffer[4] == 'l'
			        && buffer[5] == 'l' && buffer[6] == 'o'
			        && buffer[7] == 'w') {
			    light_control(LIGHT_BLUE, LIGHT_OFF);
			    light_control(LIGHT_GREEN, LIGHT_ON);
			    light_control(LIGHT_RED, LIGHT_ON);
			}

			else {}

		}

		if (flag) {
			uart_send1(UART_1, ch);     //��ԭ���ڷ���һ���ֽ�
		}
	}
	ENABLE_INTERRUPTS;
}

//����2�����жϷ�������
void UART2_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	DISABLE_INTERRUPTS;    //�����ж�
	if (uart_get_re_int(UART_2)) {
		ch = uart_re1(UART_2, &flag);    //���ý���һ���ֽڵĺ�����������ж�λ
		if (flag) {
			uart_send1(UART_2, ch);

			switch (ch) {
			case 'b': {
				light_change(LIGHT_BLUE);
				light_control(LIGHT_RED, LIGHT_OFF);
				light_control(LIGHT_GREEN, LIGHT_OFF);
				uart_send_string(UART_2, "blue_UART_2!\r\n");

				break;    //��ԭ���ڷ���һ���ֽ�
			}
			case 'r': {
				light_change(LIGHT_RED);
				light_control(LIGHT_BLUE, LIGHT_OFF);
				light_control(LIGHT_GREEN, LIGHT_OFF);
				uart_send_string(UART_2, "red_UART_2!\r\n");

				break;
			}
			case 'g': {
				light_change(LIGHT_GREEN);
				light_control(LIGHT_BLUE, LIGHT_OFF);
				light_control(LIGHT_RED, LIGHT_OFF);
				uart_send_string(UART_2, "green_UART_2!\r\n");
				break;
			}
			default: {
			}
			}
		}

	}
	ENABLE_INTERRUPTS;
}

//===========================================================================
//�ļ����ƣ�isr.c�� �жϵײ���������Դ�ļ���
//���ܸ�Ҫ���жϷ������̴�Ŵ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼������ʵ���������
//
//===========================================================================

//�ڲ���������

//===========================================================================
//ISR ���ƣ�UART0_IRQHandler,UART_0������0���жϷ�������
//����˵����user_isr_ptr���û��Զ���������˴�δ��
//���ܸ�Ҫ��ÿ���յ�һ���ֽڣ�����һ�δ��ڽ����жϣ�ִ�б�����һ�Ρ�
//          �����̶Դ����յ������ݣ����ձ��ļ���CreateFrame����ͷ������Э��
//          ��֡����֡�ɹ����Ȱѽ��յ������ݸ���g_uart_recvBuf_32��Ȼ�����������Ϣ����
//          uart_rev_queue�С�
//===========================================================================

/*===========================================================================
 ISR ���ƣ�PORTC_PORTD_IRQHandler,PTC��PTD�˿��жϷ�������
 ����˵����user_isr_ptr���û��Զ���������˴�δ��
 ���ܸ�Ҫ��ÿ���յ�һ֡64���ֽڵ�RF���ݣ�����һ�α��жϡ�
 �����̶��յ������ݣ�����RF_ReceiveFrame���������ݽ��н���
 ��֡�����ճɹ����Ȱѽ��յ������ݸ���g_port_recvBuf_32��Ȼ�����������Ϣ����
 rf_rev_queue�С�
 ===========================================================================
 void PORTC_PORTD_IRQHandler(pointer user_isr_ptr)
 {
 uint_32 g_port_recvBuf_32[64];
 uint_8 cc;
 DISABLE_INTERRUPTS;           //�����ж�
 //-----------------------------------------------------------------------
 if(RFIRQ()) 	//�ж��Ƿ���RF�շ��ж�
 {
 //�������ݰ��ɹ������¼�λEVENT_RF_RECV������task_rf_recv()����
 if(0 == RF_ReceiveFrame(g_rf_recvBuf,&g_rf_recvCount,g_rf_hdaddr))
 {
 for(cc=0;cc<64;cc++)
 {
 g_port_recvBuf_32[cc]=g_rf_recvBuf[cc];
 }
 //����g_port_recvBuf_32����Ϣ����rf_rev_queue
 _lwmsgq_send((pointer)rf_rev_queue, g_port_recvBuf_32, 0);
 Delay_ms(5);
 // }
 PortClean(); 	//����ж�״̬��־λ
 }
 //-----------------------------------------------------------------------

 ENABLE_INTERRUPTS;                      //�����ж�
 }*/

//�ڲ����ú���
//===========================================================================
//�������ƣ�CreateFrame
//���ܸ�Ҫ���齨����֡��������֡���ݼ��뵽����֡��
//����˵����Data��                   ����֡����
//          buffer:        ����֡����
//�������أ���֡״̬    0-��֡δ�ɹ���1-��֡�ɹ�
//��ע��ʮ����������֡��ʽ
//               ֡ͷ        + ���ݳ���         + ��Ч����    +  ֡β
//           FrameHead   +   len       + ��Ч����    + FrameTail
//===========================================================================
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
