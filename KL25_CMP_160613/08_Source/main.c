//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件

int main(void)
{
	//1. 声明主函数使用的变量
	uint_32  mRuncount;     //主循环计数器
    uint_8 dac_value;
	//2. 关总中断
	DISABLE_INTERRUPTS;

	//3. 初始化外设模块
	light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
    gpio_init(PORT_D|1, 1, 0);     //初始化PTD1
	uart_init(UART_1, 9600);    //使能串口1，波特率为9600
	uart_init(UART_2, 9600);    //使能串口2，波特率为9600
    uart_send_string(UART_1, "This is CMP Test!\r\n");    //串口发送初始化提示
	cmp_init(0,1,7); 	    //初始化CMP0模块，DAC参考电压Vin1in，正向通道0，负向通道7
	//4. 给有关变量赋初值
	mRuncount=0;            //主循环计数器
    dac_value=0;
	//5. 使能模块中断
    cmp_enable_int();	          //使能CMP0中断和串口1作为通信
	uart_enable_re_int(UART_1);   //使能串口1接收中断
	uart_enable_re_int(UART_2);   //使能串口2接收中断
	//6. 开总中断
	ENABLE_INTERRUPTS;
    
	//进入主循环
	//主循环开始==================================================================
	for(;;)
	{
		//运行指示灯（RUN_LIGHT）闪烁---------------------------------------------
		mRuncount++;					   //主循环次数计数器+1
		if (mRuncount >= RUN_COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
		{
			mRuncount=0;				   //主循环次数计数器清零
			light_change(RUN_LIGHT_BLUE);  //蓝色运行指示灯（RUN_LIGHT_BLUE）状态变化
			gpio_reverse(PORT_D|1);        //反转D口1号引脚输出，制造CMP读取变化
			dac_value += 10;              //DAC输出值增加
			dac_set_value(dac_value); 	  //6位DAC设置输出
			//6位DAC输出值清零，值最大为63，这里因为上面DAC值累加幅度为10，所以这里设置60
			if(dac_value>60)  dac_value=0;
		}
		//以下加入用户程序--------------------------------------------------------
	}//主循环end_for
	//主循环结束==================================================================
}

