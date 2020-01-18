//====================================================================
//文件名称：main
//功能概要：TSI主程序
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-10-12   V1.0
//       2013-05-04   V2.1
//       2016-05-08   v2.2
//说明文档见Readme.txt
//=====================================================================
#include "includes.h"
// 全局变量定义
int main(void)
{
    //1. 声明主函数使用的变量
    uint_32  mRuncount;   //主循环计数器
    uint_8 chnlID=5;      //TSI通道测试选择通道5


    //2. 关总中断
    DISABLE_INTERRUPTS;
    //3.初始化模块
    light_init(RUN_LIGHT_BLUE,LIGHT_OFF);  //初始化蓝灯为暗
    light_init(RUN_LIGHT_RED,LIGHT_OFF);  //初始化红灯为暗
    uart_init (UART_1, 9600);       //串口1、2使用总线时钟
    tsi_init(chnlID);                      // 初始化TSI
    pit_init(CH_0, PIT_WORK_FREQ, 4000);//初始化CH_0使用系统总线时钟频率，周期为1s
    uart_send_string(UART_1, "This is TSI Test!\r\n");//串口发送测试数据
    //设定触发阈值
    tsi_set_threshold(TSI_TSHD_VALUE_LOW, TSI_TSHD_VALUE_HIGH);
    //4. 给有关变量赋初值
    //5. 使能模块中断
    tsi_enable_re_int();     //开TSI中断
    uart_enable_re_int(UART_1);
    //6. 开总中断
    ENABLE_INTERRUPTS;

    //进入主循环
    //主循环开始============================================================
    for(;;)
    {
        mRuncount++;
    if (mRuncount > RUN_COUNTER_MAX)
    {
       mRuncount = 0;
       //闪烁蓝灯
       light_change(RUN_LIGHT_BLUE);
       //关闭TSI中断测试灯
       light_control(RUN_LIGHT_RED, LIGHT_OFF);
       //软件查询中断测试
       tsi_softsearch();
     } //end_if



     } //end_for
    //主循环结束============================================================
    return 0;
}
