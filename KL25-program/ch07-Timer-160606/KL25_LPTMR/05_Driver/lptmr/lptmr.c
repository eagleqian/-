//===========================================================================
//文件名称：lptmr.c
//功能概要：lptmr底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2016-3-20   V4.0
//===========================================================================
#include "lptmr.h"
    
//============================================================================
//函数名称：lptmr_init
//函数返回：无
//参数说明：clktype，指明时钟源类别，参照lptmr.h中LPTMR时钟源的宏定义。
//功能概要：LPTMR模块初始化，配置LPTMR工作的时钟源，中断时间为1秒。
//调用举例：lptmr_init(LPOCLK);配置LPTMR模块时钟源为LPOCLK时钟。
//============================================================================
void lptmr_init(uint_8 clktype)
{    
    uint_16 compare_value; 

    SIM_SCGC5|=SIM_SCGC5_LPTMR_MASK;//使能LPTMR模块时钟

    switch(clktype)
    {
        case LPOCLK:
            SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x01);//选择LPO时钟
            LPTMR0_PSR |= LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK;
            compare_value=1000;
            break;
        case IRC32KCLK:
            MCG_C1 |= MCG_C1_IRCLKEN_MASK;//使能内部参考时钟
            MCG_C2 |= MCG_C2_IRCS(0);     //MCG_C2[IRCS]=0,使能32kHz内部参考时钟

            LPTMR0_PSR=LPTMR_PSR_PCS(0)|LPTMR_PSR_PBYP_MASK;
            compare_value=32768;
            break;
        case IRC4MCLK:
            MCG_C1 |= MCG_C1_IRCLKEN_MASK;//使能内部参考时钟
            MCG_C2 |= MCG_C2_IRCS(1);     //MCG_C2[IRCS]=1,使能4MHz内部参考时钟

            LPTMR0_PSR = LPTMR_PSR_PCS(0)|LPTMR_PSR_PRESCALE(0x7);//256分频
            compare_value=15625;
            break;
        case OSCERCLK:  //注意：实验室K64评估板并没有该外部晶振
        default:
            //打开外部参考时钟
            SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x00);//选择系统振荡器
            OSC0_CR |= OSC_CR_ERCLKEN_MASK;  //选择 EXTAL to drive  XOSCxERCLK

            LPTMR0_PSR = LPTMR_PSR_PCS(3)|LPTMR_PSR_PRESCALE(0x7);//256分频
            compare_value=31250;
            break;
    }
    LPTMR0_CMR = LPTMR_CMR_COMPARE(compare_value);      //设置比较寄存器值
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; //开启LPTMR模块设置
}

//============================================================================
//函数名称：lptmr_enable_int
//函数返回：无
//参数说明：无
//功能概要：使能LPTMR模块中断。
//调用举例：lptmr_enable_int();使能LPTMR模块中断
//============================================================================
void lptmr_enable_int()
{     
    LPTMR0_CSR|=LPTMR_CSR_TIE_MASK;        //开启LPTMR定时器中断
    NVIC_EnableIRQ(LPTMR0_IRQn);           //开引脚的IRQ中断
}

//============================================================================
//函数名称：lptmr_disable_int
//函数返回：无
//参数说明：无
//功能概要：禁止LPTMR模块中断
//调用举例：lptmr_disable_int();禁止LPTMR模块中断
//============================================================================
void lptmr_disable_int()
{      
    LPTMR0_CSR &=~LPTMR_CSR_TIE_MASK;      //禁止LPTMR定时器中断
    NVIC_DisableIRQ(LPTMR0_IRQn);          //关引脚的IRQ中断
}


