//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//======================================================================

#include "includes.h"   //包含总头文件

int main(void)
{
    //1.声明主函数使用的局部变量
    uint_8 i;
    uint_8 g_temp[32]="The keyboard you just input is .";
//      uint_8 g_temp[32]="                                ";

    //2.关总中断
    DISABLE_INTERRUPTS;   //关总中断
    //3. 初始化外设模块
    LEDInit();                            //LED初始化

    LCDInit();                            //LCD初始化
    KBInit();                             //键盘初始化
    systick_init(CORE_CLOCK_DIV_16, 5);   //初始化SysTick周期、开中断、启动计数
    //4.变量赋初值
    g_LEDBuffer[0]=8;    //LED缓冲区赋值
    g_LEDBuffer[1]=6;
    g_LEDBuffer[2]=9;
    g_LEDBuffer[3]=2;
    for(i=0;i<32;i++)  {g_LCDBuffer[i]=g_temp[i];}  //LCD缓冲区赋值
    LCDShow(g_LCDBuffer);  //LCD显示初始字符
    //5. 使能模块中断

    //6. 开总中断
    ENABLE_INTERRUPTS;   //开总中断
    //======================================================================
    while(1)
    {
    }
    //======================================================================
    return 0;
}
