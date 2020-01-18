//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件


int main(void)
{
	//1. 声明主函数使用的变量
	uint_32  mRuncount;     //主循环计数器
	uint_16  VReference;
	uint_8 light_flag;
	//2. 关总中断
	DISABLE_INTERRUPTS;

	//3. 初始化外设模块
	light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
	uart_init(UART_1, 9600);    //使能串口1，波特率为9600
	uart_init(UART_2, 9600);    //使能串口2，波特率为9600
    uart_send_string(UART_1, "This is DAC Test!\r\n");    //串口发送初始化提示
	dac_init(DAC_VDDA);     //DAC初始化，选择参考电压VDDA=3.3V
	//4. 给有关变量赋初值
	mRuncount=0;            //主循环计数器
    VReference=2000;           //DAC参考数字量
    light_flag=1;
	//5. 使能模块中断
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
			//DAC数字量转换，输出VReference的值对应的电压值
			dac_convert(VReference);

			//根据标志位，设置小灯慢慢点亮或慢慢熄灭
			if(light_flag==1)  VReference += 1;
			else if(light_flag==0)  VReference -= 1;

			//VReference限幅，并反转灯点亮或熄灭的标志位
			if(VReference >= 2600)  light_flag=0;
			if(VReference <= 2200)  light_flag=1;
		}
		//以下加入用户程序--------------------------------------------------------
	}//主循环end_for
	//主循环结束==================================================================
}

