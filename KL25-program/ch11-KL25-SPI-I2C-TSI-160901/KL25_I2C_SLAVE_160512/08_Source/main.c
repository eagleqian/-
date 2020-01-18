//===========================================================================
//文件名称：main
//功能概要：i2c从机主程序
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-10-12   V1.0
//      2013-05-04   V2.1
//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//===========================================================================
#include "includes.h"
// 定义全局变量
uint_8 j;
uint_8 buf[20];
uint_8 visitaddr;
uint_8 flag=0;

int main(void)
{
	//1. 声明主函数使用的变量
	uint_8 Num_flag;
	uint_32 Num_wait;
	//2. 关总中断
	DISABLE_INTERRUPTS;
	//3. 初始化外设模块
    i2c_init(IIC_1,0,0x73,75);                //i2c1模块初始化
    uart_init (UART_TEST, 9600); //串口1初始化,波特率9600
    uart_send_string(UART_TEST, "This is iic Test!\r\n");
	//4. 给有关变量赋初值
	//5. 使能模块中断
    uart_enable_re_int(UART_TEST);
    i2c_enable_re_int(IIC_1);
	//6. 开总中断
	ENABLE_INTERRUPTS;
    //进入主循环
    //主循环开始============================================================
    for(;;)
    {
		//以下加入用户程序----------------------------------------------------
        if(flag)                      //该位置位，表明接收到主机发送过来的数据
        {
             Num_flag++;
             uart_send1(UART_TEST,buf[visitaddr]);//发送主机传送过来的数据
             flag=0;
        }
    }//主循环end_for
	//主循环结束============================================================
    return 0;
}
