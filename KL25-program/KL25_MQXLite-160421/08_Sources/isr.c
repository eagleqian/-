//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2015-4-26  V1.0
//芯片类型：KL25
//===========================================================================

#include "includes.h"
#include "app_inc.h"
#define FrameHead    'A'         //帧头
#define FrameTail    'D'         //帧尾
//内部函数声明
uint8_t CreateFrame(uint8_t Data, uint8_t * buffer);

////========================中断函数服务例程===============================

//===========================================================================
//中断例程：UART2_IRQHandler
//功能概要：串口2中断服务例程，每收到一个字节执行一次本程序，发送回去，并组帧
//参数说明：user_isr_ptr（未使用）
//备       注：使用全局变量 g_UART_ISR_buffer[]
//===========================================================================
void UART2_IRQHandler(pointer user_isr_ptr) {
	uint8_t Redata;                 //存放接收来的数据
	uint_8 flag = 1;

	Redata = uart_re1(UART_2, &flag);                 //接收的一个字节数据
	if (flag == 0)
		return;
	else
		uart_send1(UART_2, Redata);                 //将收到的一个字节数据发送回去
	//组帧成功,置“串口2接收完整数据帧事件位”
	if (CreateFrame(Redata, g_UART_ISR_buffer) != 0) {
		_lwevent_set(&lwevent_group1, Event_UART2_ReData);
	}
}

//内部调用函数

//===========================================================================
//ISR名称：Createbuffer
//功能概要：组建数据帧，将待组帧数据加入到数据帧中
//参数说明：Data:待组帧数据
//         buffer:数据帧变量
//函数返回：组帧状态    0-组帧未成功，1-组帧成功
//备       注：十六进制数据帧格式
//             帧头         +   数据长度     + 有效数据     +   帧尾
//          FrameHead  +     len     + 有效数据      + FrameTail
//===========================================================================
uint8_t CreateFrame(uint8_t Data, uint8_t * buffer) {
	static uint8_t frameCount = 0;    //组帧计数器
	uint8_t frameFlag;              //组帧状态
	frameFlag = 0;
	//根据静态变量frameCount组帧
	switch (frameCount) {
		case 0:    //第一个数据
		{
			if (Data == FrameHead)    //收到数据是帧头FrameHead
			{
				buffer[0] = Data;
				frameCount++;
				frameFlag = 0;        //组帧开始
			}
			break;
		}
		case 1:    //第二个数据，该数据是随后接收的数据个数
		{
			buffer[1] = Data;
			frameCount++;
			break;
		}
		default:    //其他情况
		{
			//第二位数据是有效数据长度,根据它接收余下的数据直到帧尾前一位
			if (frameCount >= 2 && frameCount <= (buffer[1] + 1)) {
				buffer[frameCount] = Data;
				frameCount++;
				break;
			}

			//若是末尾数据则执行
			if (frameCount >= (buffer[1] + 2)) {
				if (Data == FrameTail)    //若是帧尾
				{
					buffer[frameCount] = Data;     //将帧尾0x44存入缓冲区
					frameFlag = 1;    //组帧成功
				}
				frameCount = 0;     //计数清0，准备重新组帧
				break;
			}
		}
	}     //switch_END
	return frameFlag;                 //返回组帧状态
}
