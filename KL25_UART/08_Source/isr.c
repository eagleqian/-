//=====================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//         2016-03-27 V2.0(XD)
//=====================================================================
#include "includes.h"
#include "string.h"
#include "includes.h"
//#include "01_app_include.h"

//========================中断函数服务例程===============================
//串口0接收中断服务例程
void UART0_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	DISABLE_INTERRUPTS;    //关总中断
	if (uart_get_re_int(UART_0)) {
		ch = uart_re1(UART_0, &flag);    //调用接收一个字节的函数，清接收中断位
		if (flag) {
			uart_send1(UART_0, ch);     //向原串口发回一个字节
		}
	}
	ENABLE_INTERRUPTS; //开总中断
}

uint8_t CreateFrame(uint_8 Data, uint_8 * buffer);

//串口1接收中断服务例程
void UART1_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	uint_8 buffer[64];
	DISABLE_INTERRUPTS;    //关总中断
	if (uart_get_re_int(UART_1)) {
		ch = uart_re1(UART_1, &flag);    //调用接收一个字节的函数，清接收中断位
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
			uart_send1(UART_1, ch);     //向原串口发回一个字节
		}
	}
	ENABLE_INTERRUPTS;
}

//串口2接收中断服务例程
void UART2_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	DISABLE_INTERRUPTS;    //关总中断
	if (uart_get_re_int(UART_2)) {
		ch = uart_re1(UART_2, &flag);    //调用接收一个字节的函数，清接收中断位
		if (flag) {
			uart_send1(UART_2, ch);

			switch (ch) {
			case 'b': {
				light_change(LIGHT_BLUE);
				light_control(LIGHT_RED, LIGHT_OFF);
				light_control(LIGHT_GREEN, LIGHT_OFF);
				uart_send_string(UART_2, "blue_UART_2!\r\n");

				break;    //向原串口发回一个字节
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
//文件名称：isr.c（ 中断底层驱动构件源文件）
//功能概要：中断服务例程存放处
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：根据实际情况更新
//
//===========================================================================

//内部函数声明

//===========================================================================
//ISR 名称：UART0_IRQHandler,UART_0（串口0）中断服务例程
//参数说明：user_isr_ptr：用户自定义参数，此处未用
//功能概要：每接收到一个字节，产生一次串口接收中断，执行本例程一次。
//          本例程对串口收到的数据，按照本文件中CreateFrame函数头给出的协议
//          组帧。组帧成功后，先把接收到的数据赋给g_uart_recvBuf_32，然后把它放在消息队列
//          uart_rev_queue中。
//===========================================================================

/*===========================================================================
 ISR 名称：PORTC_PORTD_IRQHandler,PTC、PTD端口中断服务例程
 参数说明：user_isr_ptr：用户自定义参数，此处未用
 功能概要：每接收到一帧64个字节的RF数据，产生一次本中断。
 本例程对收到的数据，按照RF_ReceiveFrame函数对数据进行接收
 组帧。接收成功后，先把接收到的数据赋给g_port_recvBuf_32，然后把它放在消息队列
 rf_rev_queue中。
 ===========================================================================
 void PORTC_PORTD_IRQHandler(pointer user_isr_ptr)
 {
 uint_32 g_port_recvBuf_32[64];
 uint_8 cc;
 DISABLE_INTERRUPTS;           //关总中断
 //-----------------------------------------------------------------------
 if(RFIRQ()) 	//判断是否是RF收发中断
 {
 //接收数据包成功，置事件位EVENT_RF_RECV，启动task_rf_recv()任务
 if(0 == RF_ReceiveFrame(g_rf_recvBuf,&g_rf_recvCount,g_rf_hdaddr))
 {
 for(cc=0;cc<64;cc++)
 {
 g_port_recvBuf_32[cc]=g_rf_recvBuf[cc];
 }
 //发送g_port_recvBuf_32至消息队列rf_rev_queue
 _lwmsgq_send((pointer)rf_rev_queue, g_port_recvBuf_32, 0);
 Delay_ms(5);
 // }
 PortClean(); 	//清标中断状态标志位
 }
 //-----------------------------------------------------------------------

 ENABLE_INTERRUPTS;                      //开总中断
 }*/

//内部调用函数
//===========================================================================
//函数名称：CreateFrame
//功能概要：组建数据帧，将待组帧数据加入到数据帧中
//参数说明：Data：                   待组帧数据
//          buffer:        数据帧变量
//函数返回：组帧状态    0-组帧未成功，1-组帧成功
//备注：十六进制数据帧格式
//               帧头        + 数据长度         + 有效数据    +  帧尾
//           FrameHead   +   len       + 有效数据    + FrameTail
//===========================================================================
#define FrameHead    (0x50)       //帧头     ASCII码对应P
#define FrameTail    (0x43)       //帧尾     ASCII码对应C

uint8_t CreateFrame(uint_8 Data, uint_8 * buffer) {
	static uint_8 frameLen = 0;    //帧的计数器
	uint_8 frameFlag;            //组帧状态

	frameFlag = 0;            //组帧状态初始化
	//根据静态变量frameCount组帧
	switch (frameLen) {
	case 0:    //第一个数据
	{
		if (Data == FrameHead)    //收到数据是帧头FrameHead
		{
			buffer[0] = Data;
			frameLen++;
			frameFlag = 0;        //组帧开始
		}
		break;
	}
	case 1:    //第二个数据，该数据是随后接收的数据个数
	{
		buffer[1] = Data - 0x30;
		frameLen++;
		break;
	}
	default:    //其他情况
	{
		//第二位数据是有效数据长度,根据它接收余下的数据直到帧尾前一位
		if (frameLen >= 2 && frameLen <= (buffer[1] + 1)) {
			buffer[frameLen] = Data;
			frameLen++;
			break;
		}

		//若是末尾数据则执行
		if (frameLen >= (buffer[1] + 2)) {
			if (Data == FrameTail)    //若是帧尾
			{
				buffer[frameLen] = Data;     //将帧尾存入缓冲区
				frameFlag = 1;    //组帧成功
			}
			frameLen = 0;     //计数清0，准备重新组帧
			break;
		}
	}
	}     //switch_END
	return frameFlag;                 //返回组帧状态
}
