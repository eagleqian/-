//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件


int main(void)
{
    //1. 声明主函数使用的变量
    uint_32  remember;      //记录上一刻的秒值
    //2. 关总中断
    DISABLE_INTERRUPTS;
    //3. 给有关变量赋初值
    g_time[0] = 0;          //"时分秒"缓存初始化(00:00:00)
    g_time[1] = 0;
    g_time[2] = 0;
    remember  = g_time[2];
    SecondTimes=0;
    AlarmTimes=0;

    //4. 初始化外设模块
    light_init(LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
    uart_init(UART_1, 9600);    //使能串口1，波特率为9600
    uart_init(UART_2, 9600);    //使能串口2，波特率为9600
    rtc_init(SecondTimes,AlarmTimes);       //RTC初始化
    printf("\r\n苏州大学嵌入式实验室RTC构件测试用例!");

    //5. 使能模块中断
    uart_enable_re_int(UART_1);   //使能串口1接收中断
    uart_enable_re_int(UART_2);   //使能串口2接收中断
    rtc_enable_int();             //使能RTC模块中断
    //6. 启动RTC计时
    rtc_start();
    //7. 开总中断
    ENABLE_INTERRUPTS;

    //进入主循环
    //主循环开始==================================================================
    for(;;)
    {
        //运行指示灯（LIGHT_BLUE）闪烁---------------------------------------------
        if (g_time[2] != remember)      //判断秒钟是否发生变化
        {
            light_change(LIGHT_BLUE);   //蓝色运行指示灯状态变化
            printf("\r\nMCU记录的相对时间：%02d:%02d:%02d",g_time[0],g_time[1],g_time[2]);
            remember=g_time[2];
        }
        //以下加入用户程序--------------------------------------------------------
    }//主循环end_for
    //主循环结束==================================================================
}

