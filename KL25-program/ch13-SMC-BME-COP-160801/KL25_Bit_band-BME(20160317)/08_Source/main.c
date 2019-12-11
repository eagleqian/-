//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件


int main(void)
{
		unsigned long int temp,U32temp;
		unsigned char flag ;

		//BME操作外设寄存器,操作第16位
		//外设地址读一个字
		temp=(*( volatile unsigned long int *)(unsigned long int)0x400FF000);
		//改一个位
		temp=temp&(0xFFFEFFFF);
		//外设地址写一个字
		(*( volatile unsigned long int *)(unsigned long int)0x400FF000)=temp;
		//BME清除一位
		U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4A0FF000);
		//BME的AND操作
		(*( volatile unsigned long int *)(unsigned long int) 0x440FF000)=0xFFFEFFFF;

		flag=1;	//flag 用于选择一种控制PORTB19的方法
		switch (flag)
		{
			case 1:
				//*************1.通常方法********************************
				//将引脚复用为GPIO引脚
				PORT_PCR_REG(PORTB_BASE_PTR, 19) |= PORT_PCR_MUX(1);
				//将数据方向寄存器的19位置1，定义PORTB19引脚为输出
				GPIOB_PDDR |=(1<<19);
				//将输出寄存器的19位清0，使PORTB19引脚输出低电平
				GPIOB_PDOR &= ~(1<<19);
				break;
			case 2:
				//*************2.BME宏定义方法***************************
				//注意：宏定义中地址的GPIOB_PDOR和GPIOB_PDDR不可以使用
				//    只能使用数值地址进行传参。！！！
				//4.BME操作外设寄存器
				//PORTB_BASE_PTR->PCR[19]地址0x4004A04C
				//GPIOB_PDOR地址0x400FF040
				//GPIOB_PDDR地址0x400FF054
				BME_OR_IO(0x4004A04C,0xFFFFF1FF);
				BME_OR_IO(0x400FF054,0x00080000);
				BME_AND_IO(0x400FF040,0xFFF7FFFF);
				break;
			case 3:
				//*************3.BME直接地址方法***************************
				//4.BME操作外设寄存器
				//通过LAS1操作将PORTB->PCR[19]复用为GPIO功能
				U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4C84A04C);
				//通过LAS1操作将数据方向寄存器的19位置1，定义PORTB19引脚为输出
				U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4E6FF054);
				//通过LAC1操作将输出寄存器的19位清0，使PORTB19引脚输出低电平
				U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4A6FF040);
				break;
			case 4:
				//*************4.BME的OR方法***************************
				//5.BME操作外设寄存器
				//通过OR操作将PORTB->PCR[19]复用为GPIO功能
				(*( volatile unsigned long int *)(unsigned long int) 0x4804A04C)=0x00000100;
				//通过OR操作将数据方向寄存器的19位置1，定义PORTB19引脚为输出
				(*( volatile unsigned long int *)(unsigned long int) 0x480FF054)=0x00080000;
				//通过AND操作将输出寄存器的19位清0，使PORTB19引脚输出高电平
				(*( volatile unsigned long int *)(unsigned long int) 0x440FF040)=0xFFF7FFFF;
				break;
			default:
				break;
		}
		for(;;)
		{
		}
		return 0;
}

