//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//=====================================================================

#include "includes.h"   //包含总头文件

extern void Delay_ms(uint16_t u16ms);

int main(void)
{
    //1. 声明主函数使用的变量
    uint_32  mRuncount;     //主循环计数器
    uint_16  ADCResult[21];   //存放AD结果
    uint_16  i;
    //2. 关总中断
    DISABLE_INTERRUPTS;

    //3. 初始化外设模块
    light_init(LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
    uart_init(UART_1, 9600);    //使能串口1，波特率为9600
    uart_init(UART_2, 9600);    //使能串口2，波特率为9600
    uart_send_string(UART_1, "This is ADC Test!\r\n");  //串口发送提示
    printf("Hello Uart2!\r\n");
    //4. 给有关变量赋初值
    mRuncount=0;            //主循环计数器
    //5. 使能模块中断
    uart_enable_re_int(UART_1);   //使能串口1接收中断
    uart_enable_re_int(UART_2);   //使能串口2接收中断
    //6. 开总中断
    ENABLE_INTERRUPTS;
    
    //进入主循环
    //主循环开始==================================================
    for(;;)
    {
        //运行指示灯（LIGHT）闪烁------------------------------------
        mRuncount++;                       //主循环次数计数器+1
        if (mRuncount >= COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
        {
            mRuncount=0;                   //主循环次数计数器清零
            light_change(LIGHT_BLUE);  //蓝色运行指示灯状态变化
        }
        //以下加入用户程序-----------------------------
        //A组初始化（通道组、单端输入，采样精度，硬件均值）
        adc_init(MUXSEL_A,0,16,SAMPLE32);
        //加头标志
        ADCResult[0] = 0x1122;
        //采集数据
        ADCResult[1] = adc_read(0);
        for (i=2;i<=8;i++)  ADCResult[i] = adc_read(i+1);
        for (i=9;i<=13;i++)  ADCResult[i] = adc_read(i+2);
        ADCResult[14] = adc_read(23);
        ADCResult[15] = adc_read(26);     //芯片温度采集通道
        //B组初始化（通道组、单端输入，采样精度，硬件均值）
        adc_init(MUXSEL_B,0,16,SAMPLE32);
        //采样
        for (i=16;i<=20;i++)  ADCResult[i] = adc_read(i-12);
        //加末尾标志
        ADCResult[20] = 0x8899;
        //将采集的A/D值通过串口发送到PC
        uart_sendN(UART_TEST,42,(uint_8*)ADCResult);
        Delay_ms(50);
    }//主循环end_for
    //主循环结束==================================================
}

