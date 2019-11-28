//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件

int main(void)
{
    //1.声明主函数使用的局部变量
    uint_8 i, g_temp[32]="The keyboard you just input is .";
    //2.关总中断
    DISABLE_INTERRUPTS;   //关总中断
    //3.初始化底层模块
    LEDInit();                            //LED初始化
    LCDInit();                            //LCD初始化
    KBInit();                             //键盘初始化
	uart_init(UART_2, 9600);    //初始化串口2，波特率为9600
    systick_init(CORE_CLOCK_DIV_16, 5);   // 初始化SysTick周期为5ms
    //4.变量赋值
    g_kb_value=0xFF;
    //LED缓冲区赋值
    g_LEDBuffer[0]=0;
    g_LEDBuffer[1]=2;
    g_LEDBuffer[2]=3;
    g_LEDBuffer[3]=5;
    //LCD缓冲区赋值
    for(i=0;i<32;i++){
        g_LCDBuffer[i]=g_temp[i];
    }
    //5.开中断
    gpio_enable_int(n1,FALLING_EDGE);//允许GPIO键盘中断,下降沿产生中断请求
    gpio_enable_int(n2,FALLING_EDGE);//允许GPIO键盘中断,下降沿产生中断请求
    gpio_enable_int(n3,FALLING_EDGE);//允许GPIO键盘中断,下降沿产生中断请求
    gpio_enable_int(n4,FALLING_EDGE);//允许GPIO键盘中断,下降沿产生中断请求
    ENABLE_INTERRUPTS; //开总中断
    //6.lcd显示初始字符
    LCDShow((uint_8 *)"Wait Receiving..Soochow 2016.04.");
    //======================================================================
    for(;;)
    {
    }
    //======================================================================
    return 0;
}
