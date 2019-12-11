//============================================================================
//文件名称：main
//功能概要：SPI主程序
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-10-12   V1.0
//       2013-05-04   V2.1
//       2016-03-17   v3.0
//============================================================================
#include "includes.h"
//============================================================================
//函数名称：Delay_ms
//函数返回：无
//参数说明：无
//功能概要：延时 - 毫秒级
//============================================================================
void Delay_ms(uint16_t u16ms)
{
	  uint32_t u32ctr;
	  for(u32ctr = 0; u32ctr < ((48000 / 10)*u16ms); u32ctr++)
	  {
	    asm ("NOP");
	  }
}

int main(void)
{
    //1. 声明主函数使用的变量
    uint_32 mRuncount1;
    uint_32 mRuncount2;
    uint_8  TransferTemp;
    uint_8 i;
    //2. 关总中断
    DISABLE_INTERRUPTS;

    //3. 初始化外设模块
    light_init(RUN_LIGHT_BLUE,LIGHT_OFF);//初始化蓝灯
    uart_init (UART_1, 9600);     //串口1初始化,波特率9600
    uart_init (UART_2, 9600);     //串口2初始化,波特率9600
    uart_send_string(UART_1, "This is a SPI Test!\r\n");
    uart_send_string(UART_2, "This is a SPI Test!\r\n");
    //把SPI0初始化为主机,波特率6000，时钟极性0，时钟相位0
    SPI_init(SPI_0,1,6000,0,0);
    //把SPI1初始化为从机,波特率6000，时钟极性0，时钟相位0
    SPI_init(SPI_1,0,6000,0,0);
    //4. 给有关变量赋初值
    mRuncount1=0;
    mRuncount2=0;
    TransferTemp='A';
    i=0;
    //5. 使能模块中断
    uart_enable_re_int(UART_1);     //uart接收中断
    uart_enable_re_int(UART_2);     //uart接收中断
    SPI_enable_re_int(SPI_1);       //从机SPI_1的接收中断

     //6. 开总中断
     ENABLE_INTERRUPTS;

    //进入主循环
    //主循环开始============================================================
    for(;;)
    {
        mRuncount1++;                       //辅助循环次数计数器+1
        mRuncount2++;                       //用户程序循环次数计数器+1
        if (mRuncount1 >= RUN_COUNTER_MAX2)  //辅助循环次数计数器计数
        {
               mRuncount1=0;    //主循环次数计数器清零
               light_change(RUN_LIGHT_BLUE);    //蓝灯变化
        }
       //以下加入用户程序------------------------------------------------
        if (mRuncount2 >= RUN_COUNTER_MAX2)  //用户程序循环次数计数器计数
           {
               mRuncount2=0;    //主循环次数计数器清零
               SPI_send1(SPI_0,TransferTemp++);
//-------------------以下程序段可尝试封装------------------------------
               while(i<5 && !SPI_S_REG(SPI_baseadd(SPI_0))&SPI_S_SPRF_MASK)
               {							//通信原理可参考01_Doc文本中的硬件说明
            	   SPI_send1(SPI_0,'0');	//为从机向主机发送数据提供时钟信号；此时主机发送的内容应被从机自动过滤。
            	   i++;						//i：计数器，做限时用，一定时间后跳出while，默认从机未向主机发送数据
               }
               if(SPI_S_REG(SPI_baseadd(SPI_0))&SPI_S_SPRF_MASK)	//若主机接收缓冲区满，则返回接收到的数据
            	   uart_send1(UART_1,SPI_D_REG(SPI_baseadd(SPI_0)));
//-----------------------------------------------------------------------
               if(TransferTemp>='Z')
            	   TransferTemp='A'-1;
           }
    }  //主循环end_for
    //主循环结束============================================================
    return 0;
}
