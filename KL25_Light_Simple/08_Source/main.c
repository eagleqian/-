//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件

int main(void) {
	//1. 声明主函数使用的变量
	uint_32 mRuncount = 0;     //主循环计数器
	//2. 关总中断
	DISABLE_INTERRUPTS;
	//3. 初始化外设模块

	//GPIO基本编程步骤：

	//(1)计算给出PORTB9的引脚控制寄存器地址
	//PORTB端口的引脚控制寄存器基地址为0x4004A000u（后缀u表示无符号数）
	volatile uint_32 *portB_ptr = (uint_32*) 0x4004A000u;
	//PORTB9的引脚控制寄存器地址=基地址+偏移量
	volatile uint_32 *portB_PCR_9 = portB_ptr + 18;

	volatile uint_32 *portA_ptr = (uint_32*) 0x40049000u;
	volatile uint_32 *portA_PCR_1 = portA_ptr + 1;	//端口A引脚1的寄存器
	volatile uint_32 *portA_PCR_2 = portA_ptr + 2;
	*portA_PCR_1 &= 0b11111111111111111111100011111111; //清MUX位段
	*portA_PCR_1 |= 0b00000000000000000000000100000000;
	*portA_PCR_2 &= 0b11111111111111111111100011111111; //清MUX位段
	*portA_PCR_2 |= 0b00000000000000000000000100000000;

	//(2)计算给出PORTB的数据方向寄存器、输出反转寄存器地址
	//PORTA的基地址
	volatile uint_32 *gpioA_ptr = (uint_32*) 0x400FF000u;
	volatile uint_32 *portA_PDIR = gpioA_ptr + 4;
	volatile uint_32 *portA_PDDR = gpioA_ptr + 5;

	*portA_PDDR &= ~(1 << 1);

	//PORTB端口（作为GPIO功能）的基地址为0x400FF040u
	volatile uint_32 *gpioB_ptr = (uint_32*) 0x400FF040u;
	//PORTB的数据方向寄存器地址=基地址+偏移量
	volatile uint_32 *portB_PDDR = gpioB_ptr + 5;
	//PORTB的输出寄存器地址=基地址+偏移量
	volatile uint_32 *portB_PDO = gpioB_ptr + 0;
	//PORTB的输出反转寄存器地址=基地址+偏移量
	volatile uint_32 *portB_PTOR = gpioB_ptr + 3;

	//(3)设置PORTB9引脚为GPIO引脚，即令相应引脚控制寄存器的10-8位
	//(MUX)字段为001
	*portB_PCR_9 &= 0b11111111111111111111100011111111; //清MUX位段
	*portB_PCR_9 |= 0b00000000000000000000000100000000;

	//(4)通过PORTB的输出寄存器(给蓝色小灯的寄存器）赋初值1，保证定义为输出时为暗
	*portB_PDO |= (1 << 18);

	//(5)通过PORTB的方向寄存器，定义PORTB9引脚输出
	*portB_PDDR |= (1 << 18);

	//(6)通过PORTB的输出寄存器给蓝色小灯赋初值（0-亮）
	//（以下供单步调试观察）
	*portB_PDO &= ~(1 << 18);   //亮
	*portB_PDO |= (1 << 18);    //暗
	*portB_PDO &= ~(1 << 18);   //亮
	*portB_PDO |= (1 << 18);    //暗

	//4. 给有关变量赋初值
	mRuncount = 0;                         //主循环计数器
	//5. 使能模块中断
	//6. 开总中断
	ENABLE_INTERRUPTS;
	for (;;) {
		//运行指示灯（红灯）闪烁----------------------------------------------
		/*
		 mRuncount++;
		 if (mRuncount >= 10000000) //单步调试用，若直接运行， 比较的数可以是一个大数，如556677
		 {
		 mRuncount = 0;
		 *portB_PTOR |= (1 << 18);       //PTB9（蓝灯）取反

		 }
		 */
		//以下加入用户程序-----------------------------------------------------
		/*
		 if((*portA_PDIR) & (1<<1)){
		 *portB_PDO &= ~(1<<18);
		 }else{
		 *portB_PDO |= (1<<18);

		 } //end_for
		 }
		 */
		//主循环结束===================================================================
		return 0;
	}
}

