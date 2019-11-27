//==========================================================================
//文件名称：RTC.c
//功能概要：KL25 RTC底层驱动程序源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2016-3-20   V4.0
//==========================================================================
#include "rtc.h"
             
//===========================================================================
//函数名称：rtc_clockconfig
//函数参数：clock,CLKOUT引脚的时钟类型
//函数返回：无
//功能概要：rtc时钟配置。将clock类型的时钟输出到CLKOUT引脚。
//调用举例：rtc_clockconfig(CLKOUT_MCGIRCLK);CLKOUT引脚输出IRC。
//===========================================================================
void rtc_clockconfig(uint_8 clock)
{
    PORTC_PCR3 = PORT_PCR_MUX(0x5);
    SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(clock); //复用PTC3为CLKOUT，观测输出时钟波形
    MCG_C1 |= MCG_C1_IRCLKEN_MASK|MCG_C1_IREFSTEN_MASK;
    MCG_C2 &= ~MCG_C2_IRCS_MASK;
}

//==========================================================================
//函数名称：rtc_init
//函数参数：SecondTimes:定时器秒寄存器的初始值
//         AlarmTimes:定时器报警寄存器的时间间隔
//函数返回：无
//功能概要：RTC驱动初始化。时钟源配置为32.768kHz的内部慢速时钟，需要通过导线把
//CLKOUT的PTC3连到RTC_CLKIN的PTC1。
//调用举例：rtc_init(1,2);初始RTC的秒计数器为1，报警值为2。
//==========================================================================
void rtc_init(uint32_t SecondTimes,uint32_t AlarmTimes)
{
    rtc_clockconfig(CLKOUT_MCGIRCLK);

    PORTC_PCR1 = PORT_PCR_MUX(0x1);        //使能PTC1为 RTC_CLKIN

    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;//使能RTC时钟门控制

    RTC_CR  = RTC_CR_SWR_MASK;//软件复位RTC寄存器      //通过软件复位清除写保护
    RTC_CR  &= ~RTC_CR_SWR_MASK;//软件复位之后清SWR位
    //如果定时器无效
    if (RTC_SR & RTC_SR_TIF_MASK) RTC_TSR = 0x00;
    //配置定时器补偿寄存器的时间间隔与时钟周期数
    RTC_TCR = RTC_TCR_CIR(0) | RTC_TCR_TCR(0);

    SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x02);//选择RTC_CLKIN作为RTC时钟源

    RTC_TSR = SecondTimes;  //初始化定时器秒寄存器

    RTC_TAR = AlarmTimes;   //初始化定时器报警寄存器

    RTC_TPR = 0;            //复位RTC定时器预分频器寄存器

    //使能秒中断，复位后TAIE、TOIE、TIIE值为1
    RTC_IER |= RTC_IER_TSIE_MASK;

    rtc_stop();
}

//===========================================================================
//函数名称：rtc_start
//函数参数：无
//函数返回：无
//功能概要：启动RTC模块计时。
//调用举例：rtc_start();启动RTC模块计时。
//===========================================================================
void rtc_start(void)
{
    RTC_SR |= RTC_SR_TCE_MASK;//打开计数器
}

//===========================================================================
//函数名称：rtc_stop
//函数参数：无
//函数返回：无
//功能概要：停止RTC模块计时。
//调用举例：rtc_stop();关闭RTC模块计时。
//===========================================================================
void rtc_stop(void)
{
    RTC_SR &= ~RTC_SR_TCE_MASK;//关闭计数器
}

//===========================================================================
//函数名称：rtc_reset_alarm_time
//函数参数：AlarmTimes复位时赋给报警计时器的值。
//函数返回：无
//功能概要：复位报警计时器。
//调用举例：rtc_reset_alarm_time();写入RTC模块报警的新值。
//===========================================================================
void rtc_reset_alarm_time(uint32_t AlarmTimes)
{
    RTC_TAR = AlarmTimes;
}

//===========================================================================
//函数名称：rtc_reset_second_time
//函数参数：SecondTimes复位时赋给秒计时器的值
//函数返回：无
//功能概要：复位秒计时器。
//调用举例：rtc_reset_second_time();写入RTC模块计数器的新值。
//===========================================================================
void rtc_reset_second_time(uint32_t SecondTimes)
{
    RTC_TSR = SecondTimes;
}

//===========================================================================
//函数名称：rtc_enable_int
//函数参数：无
//函数返回：无
//功能概要：使能RTC模块中断。
//调用举例：rtc_enable_int();使能RTC模块中断。
//===========================================================================
void rtc_enable_int()
{
    //开rtc中断
    NVIC_EnableIRQ(RTC_IRQn);
    NVIC_EnableIRQ(RTC_Seconds_IRQn);
}

//===========================================================================
//函数名称：rtc_disable_int
//函数参数：无
//函数返回：无
//功能概要：禁止RTC模块中断。
//调用举例：rtc_disable_int();禁止RTC模块中断。
//===========================================================================
void rtc_disable_int()
{
    //关rtc中断
    NVIC_DisableIRQ(RTC_IRQn);
    NVIC_DisableIRQ(RTC_Seconds_IRQn);
}
