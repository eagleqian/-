//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================中断函数服务例程===============================
//======================================================================
//函数名称：SysTick_Handler
//参数说明：无
//函数返回：无
//功能概要：SysTick定时器中断服务例程
//======================================================================

//全局变量用来改变时钟,tickCount作为选择模式取值为1~5
uint_8 tickCount = 1;

static uint_8 modeChange = 0; //模式切换标志，用于切换不同闪烁模式


//组帧函数原型声明
uint8_t CreateFrame(uint_8 Data, uint_8 * buffer);

void SysTick_Handler(void) //深入了解中断的内涵
//默认值为100,则表示1S闪一次
{
	static uint_8 SysTickcount = 0; //静态变量,负责控制每次亮灭间隔的时间
	static uint_8 twinkleCount = 0; //密集闪烁指示灯次数变量
	SysTickcount++;

	if (tickCount == 1) {
		if (SysTickcount >= 30)
				{
			SysTickcount = 0;
			//秒计时程序
			SecAdd1(g_time);      //g_time是时分秒全局变量数组
		}
	} else if (tickCount == 2 || tickCount == 3 || tickCount == 4
			|| tickCount == 5) {
		switch (modeChange) {
		case 1: {
			if (twinkleCount <= (tickCount * 2 - 2)) {
				if (SysTickcount >= 30){
					SysTickcount = 0;
					//秒计时程序
					SecAdd1(g_time);      //g_time是时分秒全局变量数组
					twinkleCount++;
				}
			} else {

				twinkleCount = 0;      //初始化密集闪烁次数
				modeChange = 0;      //更改闪烁指示标志

			}
		}
		case 0: {
			if (SysTickcount >= 150)   //设置等待时间，足够区分闪烁模式
					{
				SysTickcount = 0;   //1.5s以后，小灯延续了1.5s的暗状态才会切换为亮状态
				//秒计时程序
				SecAdd1(g_time);      //g_time是时分秒全局变量数组
				modeChange = 1;      //更改闪烁指示标志
			}
		}
		}
	}
	else{}

}

//串口0接收中断服务例程
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

//串口1接收中断服务例程
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

//串口2接收中断服务例程
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


//组帧函数，用来组成输入的帧
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
