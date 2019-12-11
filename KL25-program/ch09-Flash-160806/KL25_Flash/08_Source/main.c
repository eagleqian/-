//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//========================================================================

#include "includes.h"   //包含总头文件


//宏定义，定义实验所用的测试数据，方便用户修改

int main(void)
{
    //1. 声明主函数使用的变量
    uint_32  mRuncount;     //主循环计数器
    uint_32  offset,count;  //偏移地址，存取字节数
    uint_8  bufRetErr[19]  = {'M',16,'C','F','l','a','s',
            'h','-','x','x','x','x','x','-','E','r','r','U'};

    //2. 关总中断
    DISABLE_INTERRUPTS;

    //3. 初始化外设模块
    light_init(LIGHT_BLUE, LIGHT_ON);  //蓝灯初始化

    //uart_init(UART_1, 9600);      //使能串口1，波特率为9600
    uart_init(UART_Debug, 9600);    //使能串口2，波特率为9600

    flash_init();
    //uart_send_string(UART_1, "Hello Uart_1!\r\n");    //串口发送初始化提示
    printf("Hello Uart2!\r\n");
    printf("SD-FSL Library Flash Test!\r\n\r\n");
    //4. 给有关变量赋初值
    mRuncount=0;         //主循环计数器
    watchGlobalVar='g';  //给用于测试的全局变量赋初值，用以读取,其地址见../Debug/.lst文件中
    framestate=1;//帧状态，0：非握手命令帧，1：握手命令帧

    //5. 使能模块中断
    //uart_enable_re_int(UART_1);   //使能串口1接收中断
    uart_enable_re_int(UART_Debug);   //使能串口2接收中断
    //6. 开总中断
    ENABLE_INTERRUPTS;
    
    //进入主循环
    //主循环开始==============================================================
    for(;;)
    {
        //运行指示灯（RUN_LIGHT）闪烁-------------------------------------------
        mRuncount++;                       //主循环次数计数器+1
        if (mRuncount >= RUN_COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
        {
            mRuncount=0;                   //主循环次数计数器清零
            light_change(LIGHT_BLUE);  //蓝色运行指示灯（LIGHT_BLUE）状态变化
        }

        //以下加入用户程序--------------------------------------------------------
        if(framestate==0)
        {
            //2）解帧g_uart_recvBuf,g_uart_recvBuf[2]是命令字节
            if(g_uart_recvBuf[2]=='D'){
                //Flash处理任务

                //读取flash指定扇区操作
                switch(g_uart_recvBuf[3]){
                case 'R':
                    offset = g_uart_recvBuf[5] *256+g_uart_recvBuf[6];
                    count  = g_uart_recvBuf[7];

                    g_uart_sentBuf[0]  =(uint_8)'M';           //帧头
                    g_uart_sentBuf[1]  =count+1;               //内容数（内容count+C）
                    g_uart_sentBuf[2]  = (uint_8)'C';          //内容起始帧
                    flash_read_logic(&g_uart_sentBuf[3],g_uart_recvBuf[4],offset,count);
                    g_uart_sentBuf[count+3]  = (uint_8)'U';    //帧尾
                    uart_sendN(UART_2,count+4,&g_uart_sentBuf[0]);
                    break;
                case 'A':
                	offset = (g_uart_recvBuf[4]<<24)+(g_uart_recvBuf[5]<<16)+(g_uart_recvBuf[6]<<8)+g_uart_recvBuf[7];
					count  = g_uart_recvBuf[8];

					g_uart_sentBuf[0]  =(uint_8)'M';           //帧头
					g_uart_sentBuf[1]  =count+1;               //内容数（内容count+C）
					g_uart_sentBuf[2]  = (uint_8)'C';          //内容起始帧
					flash_read_physical(&g_uart_sentBuf[3],offset,count);
					g_uart_sentBuf[count+3]  = (uint_8)'U';    //帧尾

					uart_sendN(UART_2,count+4,&g_uart_sentBuf[0]);
					break;
                case 'W':
                    //DISABLE_INTERRUPTS;//关中断
                    offset =g_uart_recvBuf[5]*256+g_uart_recvBuf[6];
                    count = g_uart_recvBuf[7];
                    if(flash_write(g_uart_recvBuf[4], offset, count, &g_uart_recvBuf[8]) == 0 )
                    {
                        g_uart_sentBuf[0]=(uint_8)'M';        //帧头
                        g_uart_sentBuf[1]=count+1;            //内容数（内容count+C）
                        g_uart_sentBuf[2]= (uint_8)'C';       //内容起始帧
                        flash_read_logic(&g_uart_sentBuf[3],g_uart_recvBuf[4],offset,count);
                        g_uart_sentBuf[count+3]  = (uint_8)'U';  //帧尾
                        uart_sendN(UART_2,count+4, &g_uart_sentBuf[0]);
                    }
                    else
                    {
                    	bufRetErr[9]='w';
						bufRetErr[10]='r';
						bufRetErr[11]='i';
						bufRetErr[12]='t';
						bufRetErr[13]='e';
						uart_sendN(UART_2,19,&bufRetErr[0]);
                    }
                    //ENABLE_INTERRUPTS;//开中断
                    break;
                case 'E':
                    //DISABLE_INTERRUPTS;//关中断
                	 if(flash_erase(g_uart_recvBuf[4]) == 0 )
					{
						count=32;
						g_uart_sentBuf[0]=(uint_8)'M';         //帧头
						g_uart_sentBuf[1]=count+1;             //内容数（内容count+C）
						g_uart_sentBuf[2]= (uint_8)'C';        //内容起始帧
						flash_read_logic(&g_uart_sentBuf[3],g_uart_recvBuf[4], 0, count);
						g_uart_sentBuf[count+3]  = (uint_8)'U';//帧尾
						uart_sendN(UART_2,count+4, &g_uart_sentBuf[0]);
					}
					else
					{
						bufRetErr[9]='e';
						bufRetErr[10]='r';
						bufRetErr[11]='a';
						bufRetErr[12]='s';
						bufRetErr[13]='e';
						uart_sendN(UART_2,19,&bufRetErr[0]);
					}
                    //ENABLE_INTERRUPTS;//开中断
                    break;
                    //开中断
                case 'P':
                    //DISABLE_INTERRUPTS;//关中断
                    flash_protect(g_uart_recvBuf[4]);
                    count=10;
					g_uart_sentBuf[0]=(uint_8)'M';     //帧头
					g_uart_sentBuf[1]=count+1;         //内容数（内容count+C）
					g_uart_sentBuf[2]= (uint_8)'C';    //内容起始帧
					g_uart_sentBuf[3]= (uint_8)'P';
					g_uart_sentBuf[4]= (uint_8)'r';
					g_uart_sentBuf[5]= (uint_8)'o';
					g_uart_sentBuf[6]= (uint_8)'t';
					g_uart_sentBuf[7]= (uint_8)'e';
					g_uart_sentBuf[8]= (uint_8)'c';
					g_uart_sentBuf[9]= (uint_8)'t';
					g_uart_sentBuf[10]= (uint_8)'e';
					g_uart_sentBuf[11]= (uint_8)'d';
					g_uart_sentBuf[12]= (uint_8)'!';
					g_uart_sentBuf[13]  = (uint_8)'U';  //帧尾
					uart_sendN(UART_2,count+4, &g_uart_sentBuf[0]);
                    //uart_sendN(UART_2,count,"Protected!");
                    //ENABLE_INTERRUPTS;//开中断
                }

                }
            }
            framestate=2;
        }
}//主循环end_for
//主循环结束===============================================================
