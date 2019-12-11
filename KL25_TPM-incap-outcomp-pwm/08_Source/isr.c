//=====================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//=====================================================================
#include "includes.h"

//========================中断函数服务例程===============================
//=====================================================================
//函数名称：TPM0_IRQHandler（TPM0中断服务例程）
//功能概要：10ms中断一次，本程序执行一次，静态变量cnt加1，到达100，即1秒时间，
//         调用SecAdd1，给全局变量数组g_time赋值（时、分、秒）
//=====================================================================

//组帧函数原型声明
uint8_t CreateFrame(uint_8 Data, uint_8 * buffer);

void TPM0_IRQHandler(void) {
	static uint_32 cnt;       //中断次数
	if (tpm_get_int(0) == 1)   //若有TPM0的溢出中断
			{
		tpm_clear_int(0);     //清TPM0的溢出中断标志
		cnt++;                //中断次数+1
		if (cnt >= 100)        //若达到100次（即1秒）
				{

			//实现数值向数字字符ASCII码值的转换,组成时间字符串
			uart_send1(UART_1, (g_time[0] / 10) + 48);
			uart_send1(UART_1, (g_time[0] % 10) + 48);
			uart_send1(UART_1, ':');

			uart_send1(UART_1, (g_time[1] / 10) + 48);
			uart_send1(UART_1, (g_time[1] % 10) + 48);
			uart_send1(UART_1, ':');

			uart_send1(UART_1, (g_time[2] / 10) + 48);
			uart_send1(UART_1, (g_time[2] % 10) + 48);

			cnt = 0;          //中断次数清0
			//调用“秒+1计时子函数”，给全局变量数组g_time赋值（时、分、秒）
			SecAdd1(g_time);

		}
	}
}

//=====================================================================
//函数名称：TPM1_IRQHandler（TPM1中断服务例程）
//功能概要：20ms中断一次，本程序执行一次，静态变量duty由0.0增到100.0，
//         再由100.0减到0.0，然后根据duty值来改变pwm的占空比的值，
//         对应的PWM输出引脚可以测得相应的PWM波形
//=====================================================================

void TPM1_IRQHandler(void) {
	static float duty = 0.0;     //静态变量duty（占空比）
	static uint_8 Up_Down = 1;   //占空比增减标志

	if (tpm_get_int(1) == 1)   //若有TPM1的溢出中断
			{
		tpm_clear_int(1);     //清TPM1的溢出中断标志
		pwm_update(TPM1_CH0, duty);    //PWN更新
		if (Up_Down == 1)              //占空比逐渐增加
				{
			duty = duty + 0.5;
			if (duty > 100.0)          //防止占空比越界
					{
				duty = 100.0;
				Up_Down = 0;
			}
		} else                       //占空比逐渐减小
		{
			duty = duty - 0.5;
			if (duty < 0)             //防止占空比越界
					{
				duty = 0;
				Up_Down = 1;
			}
		}
	}
}
//=====================================================================
//函数名称：TPM2_IRQHandler（TPM2中断服务例程）
//功能概要：进入中断后判断是20ms定时器溢出中断，还是通道捕获中断,如果是计数器溢出
//         中断清中断标志位后返回，如果是通道捕获中断那么记录当前捕获值，当记录
//         满十个值后，将这10个值一并从串口打出
//=====================================================================
void TPM2_IRQHandler(void) {
	static uint_32 Cap_Value[10];    //捕获的通道值
	static uint_32 cnt = 0;            //扑捉次数

//若有TPM2的溢出中断,清其中断标志
	if (tpm_get_int(2) == 1)
		tpm_clear_int(2);
//有通道中断产生
	if (tpm_chl_get_int(2, 0) == 1)  //判断中断类型是否为通道中断
			{
		tpm_clear_chl_int(2, 0);    //清除通道中断标志
		Cap_Value[cnt] = tpm_get_capvalue(TPM2_CH0);  //获取通道捕获值
		cnt++;    //扑捉次数+1
		if (cnt >= 10)        //连续获取10次捕获值
				{
			while (cnt)    //将10个捕获值统一通过串口打出
			{
				cnt--;
				printf("TPM2通道0的输入捕捉通道值：%d\n", Cap_Value[cnt]);
			}
		}
	}
}

//=====================================================================
//函数名称：UART0_IRQHandler（串口0接收中断服务例程）
//功能概要：串口0接收一个数据，并将其打出
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
//函数名称：UART1_IRQHandler（串口1接收中断服务例程）
//功能概要：串口1接收一个数据，并将其打出
//=====================================================================
void UART1_IRQHandler(void) {
	uint_8 ch;
	uint_8 flag;
	static uint_8 buffer[64];

	DISABLE_INTERRUPTS;
	if (uart_get_re_int(UART_1)) {
		ch = uart_re1(UART_1, &flag);
		if (CreateFrame(ch, buffer) != 0) {
			if (buffer[1] == 8) { //C#输入的数字都是字符型，每个数字字符都对应一个ASCII（码）值

				//buffer缓存中的数字部分每位字节运算都是用对应的ASCII码值计算
				//但是发送给c#的时候，必须发送数字相应的字符ASCII码值；

				//计算hh:mm:ss
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
//函数名称：UART2_IRQHandler（串口2接收中断服务例程）
//功能概要：串口2接收一个数据，并将其打出
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

//------功能性子函数------
//=====================================================================
//函数名称：SecAdd1，秒+1计时子函数
//函数返回：无
//参数说明：*p:为指向一个时分秒数组p[3]
//功能概要：秒单元+1，并处理时分单元（00:00:00-23:59:59)
//=====================================================================
void SecAdd1(uint_8 *p) {
	*(p + 2) += 1;         //秒+1
	if (*(p + 2) >= 60)     //秒溢出
			{
		*(p + 2) = 0;       //清秒
		*(p + 1) += 1;      //分+1
		if (*(p + 1) >= 60)  //分溢出
				{
			*(p + 1) = 0;    //清分
			*p += 1;       //时+1
			if (*p >= 24)   //时溢出
					{
				*p = 0;      //清时
			}
		}
	}
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
		//这才是关键所在！对ASCII码值进行了转换！
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

