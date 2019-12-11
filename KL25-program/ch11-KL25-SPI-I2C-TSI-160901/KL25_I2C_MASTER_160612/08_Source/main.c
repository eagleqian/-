//===========================================================================
//文件名称：main
//功能概要：i2c主程序
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-10-12   V1.0
//       2016-03-17   V2.1
//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//===========================================================================
#include "includes.h"
// 定义全局变量
int main(void)
{
    //1. 声明主函数使用的变量
    uint_8 data[12];                    //发向从机的数据；
    uint_8 Num_flag;                    //data位置指向标记
    uint_32 mRunCount1;                 //发送间隔计数器1
    uint_32 mRunCount2;                 //发送间隔计数器2
    //2. 关总中断
    DISABLE_INTERRUPTS;
    //3. 初始化外设模块
    light_init(RUN_LIGHT_BLUE,LIGHT_OFF);
    i2c_init(I2C0,1,MasterAddress,100);     //第四个参数为波特率，其单位为KB/S
    uart_init (UART_TEST, 9600);//串口1初始化, 总线时钟24000Khz,波特率9600
    uart_send_string(UART_TEST, "This is i2c Test!\r\n");
    //4. 给有关变量赋初值
    strcpy(data,"Version3.4\n");               //为data数组赋值
    Num_flag=0;
    //5. 使能模块中断
    uart_enable_re_int(UART_TEST);
    //6. 开总中断
    ENABLE_INTERRUPTS;
    //i2c_write1(0, 0x73, 0x02, data);           //向从机写 A，0X73为从机地址
    //进入主循环
    //主循环开始============================================================
    for(;;)
    {
        mRunCount1++;
        mRunCount2++;
        if(mRunCount1 > 2000000)
        {
            mRunCount1=0;
            light_change(RUN_LIGHT_BLUE);
        }

        //以下加入用户程序-----------------------------------------------------
        if(mRunCount2 > 2000000)
        {
            //依次向从机写 data中数据，0X73为从机地址
            i2c_write1(I2C0, 0x73, 0x02, data[Num_flag]);
            Num_flag++;
            if(Num_flag > 10 )
            Num_flag=0;
            mRunCount2=0;
        }
    }//主循环end_for
    //主循环结束============================================================
    return 0;
}
