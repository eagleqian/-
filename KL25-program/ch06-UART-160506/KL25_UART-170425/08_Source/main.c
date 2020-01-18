//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//======================================================================

#include "includes.h"   //包含总头文件


int main(void)
{
    //1. 声明主函数使用的变量
    uint_32  mRuncount;     //主循环计数器
    uint_32  mLight_chang_num;     //灯状态变换次数

    //2. 关总中断
    DISABLE_INTERRUPTS;

    //3. 初始化外设模块
    light_init(LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
    uart_init(UART_0, 9600);    //初始化串口0，波特率为9600
    uart_init(UART_1, 9600);    //初始化串口1，波特率为9600
    uart_init(UART_2, 9600);    //初始化串口2，波特率为9600
    //uart_init(UART_Debug, 9600);    //初始化UART_Debug，波特率为9600
    //串口发送初始化提示
    uart_send_string(UART_0, "使用uart_send_string发送：Hello Uart_0!\r\n");
    uart_send_string(UART_1, "使用uart_send_string发送：Hello Uart_1!\r\n");
    uart_send_string(UART_2, "使用uart_send_string发送：Hello Uart_2!\r\n");
    printf("使用printf函数发送：Hello Uart_2!\r\n");
    //4. 给有关变量赋初值
    mRuncount=0;            //主循环计数器
    mLight_chang_num=0;     //灯状态变换次数
    //5. 使能模块中断
    uart_enable_re_int(UART_0);   //使能串口0接收中断
    uart_enable_re_int(UART_1);   //使能串口1接收中断
    uart_enable_re_int(UART_2);   //使能串口2接收中断

    //6. 开总中断
    ENABLE_INTERRUPTS;   //开总中断
    
	//进入主循环
	//主循环开始==================================================================
	for(;;)
	{
		//运行指示灯（RUN_LIGHT）闪烁---------------------------------------------
		mRuncount++;					   //主循环次数计数器+1
		if (mRuncount >= RUN_COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
		{
			mRuncount=0;				   //主循环次数计数器清零
			light_change(LIGHT_BLUE);  //蓝色运行指示灯（RUN_LIGHT_BLUE）状态变化
			mLight_chang_num++;     //灯状态变换次数+1
			//printf("灯状态变换次数mLight_chang_num=%d\n",mLight_chang_num);
			//uart_send_string(UART_0, "UART_0!\r\n");
		    //uart_send_string(UART_1, "UART_1!\r\n");
		    //uart_send_string(UART_2, "UART_2!\r\n");
		}
		//以下加入用户程序--------------------------------------------------------
	}//主循环end_for
	//主循环结束==================================================================
}

