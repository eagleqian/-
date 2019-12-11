//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件


int main(void)
{
	//1. 声明主函数使用的变量
	uint_32  mRuncount;     //主循环计数器
	uint_8 McuRstFlag;
	if (BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0))        //上电复位
	    McuRstFlag = 0;
    else if (BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0))  //看门狗复位
	    McuRstFlag = 1;
	else
	    McuRstFlag = 2;

	//2. 关总中断
	DISABLE_INTERRUPTS;

	//3. 初始化外设模块
	WDOG_ENABLE();
	light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
	uart_init(UART_1, 9600);    //使能串口1，波特率为9600
	uart_init(UART_2, 9600);    //使能串口2，波特率为9600
    uart_send_string(UART_1, "Hello Uart_1!\r\n");    //串口发送初始化提示
	printf("Hello Uart2!\r\n");
	//4. 给有关变量赋初值
	mRuncount=0;            //主循环计数器
	//5. 使能模块中断
	uart_enable_re_int(UART_1);   //使能串口1接收中断
	uart_enable_re_int(UART_2);   //使能串口2接收中断
	//6. 开总中断
	ENABLE_INTERRUPTS;
    
    if(McuRstFlag == 0)
        printf("0: Power On Reset\r\n");
    else if(McuRstFlag == 1)
        printf("1: System Watch Dog Reset\r\n");
    else
        printf("2: Other Reset\r\n");

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
			printf("change light\r\n");
		}
		FEED_DOG();

		//以下加入用户程序--------------------------------------------------------
	}//主循环end_for
	//主循环结束==================================================================
}

