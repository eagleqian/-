//======================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//======================================================================
#include "includes.h"

//内部函数声明
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//========================中断函数服务例程===============================
//串口0接收中断服务例程
void UART0_IRQHandler(void)
{
    uint_8 flag;
    uint_8 i;
    
    DISABLE_INTERRUPTS;
    
    i = uart_re1(UART_0, &flag);
    if (0 == flag)
    {
        uart_send1(UART_0, i);
    }
    
    ENABLE_INTERRUPTS;
}


//串口1接收中断服务例程
void UART1_IRQHandler(void)
{

    uint_8 flag;
    uint_8 i;
    
    DISABLE_INTERRUPTS;
    
    i = uart_re1(UART_1, &flag);
    if (0 == flag)
    {
        uart_send1(UART_1, i);
    }
 
    ENABLE_INTERRUPTS;
}

//======================================================================
//函数名称：isr_uart2_re
//参数说明：user_isr_ptr：用户自定义参数，此处未用
//功能概要：UART_2（串口2）中断服务例程
//======================================================================
void UART2_IRQHandler(void)
{
    uint_8 i,flag;
    DISABLE_INTERRUPTS;                //关总中断
    //-----------------------------------------------------------------------

    i=uart_re1(UART_2, &flag);             //接收一个字节
    //调用内部函数CreateFrame进行组帧
    if(CreateFrame(i,g_uart_recvBuf)!=0)    //组帧成功
    {
        //g_uart_recvBuf[2]是命令字节
        if(g_uart_recvBuf[2] == 'C')    //握手命令
        {
            g_uart_sentBuf[0]=(uint_8)'M';     //
            g_uart_sentBuf[1]=5;               //
            g_uart_sentBuf[2]  = (uint_8)'C';  //
            g_uart_sentBuf[3]  = (uint_8)'K';  //"PCNode"
            g_uart_sentBuf[4]  = (uint_8)'L';
            g_uart_sentBuf[5]  = (uint_8)'2';
            g_uart_sentBuf[6]  = (uint_8)'5';
            g_uart_sentBuf[7]  = (uint_8)'U';  //
            uart_sendN(UART_2,8,&g_uart_sentBuf[0]);
            framestate=1;//握手命令帧
        }
        //
        else   //其他情况,置“串口0接收完整数据帧事件位(EVENT_UART0_RE)”,触发task_uart0_re任务处理
        {
            framestate=0;//非握手命令帧
        }
    }

    //-----------------------------------------------------------------------
    ENABLE_INTERRUPTS;                //开总中断
}


//内部调用函数

//======================================================================
//ISR名称：Createbuffer
//功能概要：组建数据帧，将待组帧数据加入到数据帧中
//参数说明：Data：                            待组帧数据
//          buffer:        数据帧变量
//函数返回：组帧状态    0-组帧未成功，1-组帧成功
//备注：十六进制数据帧格式
//               帧头        + 数据长度          + 有效数据    +  帧尾
//        FrameHead   +   len   + 有效数据    + FrameTail
//======================================================================

#define FrameHead    (0x50)         //帧头
#define FrameTail    (0x43)         //帧尾
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
    static uint8_t frameLen=0;    //组帧计数器
    uint8_t frameFlag;              //组帧状态
    frameFlag=0;            //组帧状态 初始化
    //根据静态变量frameCount组帧
    switch(frameLen)
    {
        case 0:    //第一个数据
        {
            if (Data==FrameHead)    //收到数据是帧头FrameHead
            {
                buffer[0]=Data;
                frameLen++;
                frameFlag=0;        //组帧开始
            }
            break;
        }
        case 1:    //第二个数据，该数据是随后接收的数据个数
        {
            buffer[1]=Data;
            frameLen++;
            break;
        }
        default:    //其他情况
        {
            //第二位数据是有效数据长度,根据它接收余下的数据直到帧尾前一位
            if(frameLen>=2 && frameLen<=(buffer[1] + 1))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //若是末尾数据则执行
            if(frameLen>=(buffer[1]+2))
            {
                if (Data==FrameTail)    //若是帧尾
                {
                    buffer[frameLen]=Data;     //将帧尾存入缓冲区
                    frameFlag=1;    //组帧成功
                }
                frameLen=0;     //计数清0，准备重新组帧
                break;
            }
        }
    }     //switch_END
    return frameFlag;                 //返回组帧状态
}

