//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//======================================================================

#include "includes.h"   //包含总头文件


int main(void)
{
    //1. 声明主函数使用的变量
    uint_32  remember;      //记录上一刻的秒值
    //2. 关总中断
    DISABLE_INTERRUPTS;
    //3. 初始化外设模块
    light_init(RUN_LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化
    uart_init(UART_1, 9600);    //使能串口1，波特率为9600
    uart_init(UART_2, 9600);    //使能串口2，波特率为9600
    printf("\r\n苏州大学嵌入式实验室TPM-incap-outcomp构件测试用例!");
    //初始化tpm引脚配置和时钟
    tpm_timer_init(TPM_0,3000,10);        //初始化TPM0模块10ms定时溢出
    tpm_timer_init(TPM_1,3000,20);        //初始化TPM1模块20ms定时溢出
    tpm_timer_init(TPM_2,3000,20);        //初始化TPM2模块20ms定时溢出
    //初始化PWM信号输出
    pwm_init(TPM1_CH0,0.0,1,PWM_PLUS);      //通道连接在PTA4
    //初始化输入捕捉,采用2模块,0通道
    incap_init(TPM2_CH0,CAP_UP);            //通道连接在PTA1
    //初始化输出比较
    outcompare_init(TPM0_CH0,5,CMP_REV);    //通道连接在PTC1

    //4. 给有关变量赋初值
    g_time[0] = 0;                 //"时分秒"缓存初始化(00:00:00)
    g_time[1] = 0;
    g_time[2] = 0;
    remember  = g_time[2];
    //5. 使能模块中断
    uart_enable_re_int(UART_1);   //使能串口1接收中断
    uart_enable_re_int(UART_2);   //使能串口2接收中断
    tpm_enable_int(0);        //使能TPM0中断
    tpm_enable_int(1);        //使能TPM1中断
    tpm_enable_int(2);        //使能TPM2中断
    //6. 开总中断
    ENABLE_INTERRUPTS;

    //======主循环开始======================================================
    for(;;)
    {
        //------运行指示灯（RUN_LIGHT_BLUE）闪烁------
        if (g_time[2] != remember)      //判断秒钟是否发生变化
        {
            light_change(RUN_LIGHT_BLUE);  //蓝色运行指示灯状态变化
            printf("\r\n时间：%02d:%02d:%02d",g_time[0],g_time[1],g_time[2]);
            remember=g_time[2];
        }
     }  //主循环end_for
    //======主循环结束======================================================
}

