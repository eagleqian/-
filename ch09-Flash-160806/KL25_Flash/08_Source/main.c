//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//========================================================================

#include "includes.h"   //������ͷ�ļ�


//�궨�壬����ʵ�����õĲ������ݣ������û��޸�

int main(void)
{
    //1. ����������ʹ�õı���
    uint_32  mRuncount;     //��ѭ��������
    uint_32  offset,count;  //ƫ�Ƶ�ַ����ȡ�ֽ���
    uint_8  bufRetErr[19]  = {'M',16,'C','F','l','a','s',
            'h','-','x','x','x','x','x','-','E','r','r','U'};

    //2. �����ж�
    DISABLE_INTERRUPTS;

    //3. ��ʼ������ģ��
    light_init(LIGHT_BLUE, LIGHT_ON);  //���Ƴ�ʼ��

    //uart_init(UART_1, 9600);      //ʹ�ܴ���1��������Ϊ9600
    uart_init(UART_Debug, 9600);    //ʹ�ܴ���2��������Ϊ9600

    flash_init();
    //uart_send_string(UART_1, "Hello Uart_1!\r\n");    //���ڷ��ͳ�ʼ����ʾ
    printf("Hello Uart2!\r\n");
    printf("SD-FSL Library Flash Test!\r\n\r\n");
    //4. ���йر�������ֵ
    mRuncount=0;         //��ѭ��������
    watchGlobalVar='g';  //�����ڲ��Ե�ȫ�ֱ�������ֵ�����Զ�ȡ,���ַ��../Debug/.lst�ļ���
    framestate=1;//֡״̬��0������������֡��1����������֡

    //5. ʹ��ģ���ж�
    //uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
    uart_enable_re_int(UART_Debug);   //ʹ�ܴ���2�����ж�
    //6. �����ж�
    ENABLE_INTERRUPTS;
    
    //������ѭ��
    //��ѭ����ʼ==============================================================
    for(;;)
    {
        //����ָʾ�ƣ�RUN_LIGHT����˸-------------------------------------------
        mRuncount++;                       //��ѭ������������+1
        if (mRuncount >= RUN_COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
        {
            mRuncount=0;                   //��ѭ����������������
            light_change(LIGHT_BLUE);  //��ɫ����ָʾ�ƣ�LIGHT_BLUE��״̬�仯
        }

        //���¼����û�����--------------------------------------------------------
        if(framestate==0)
        {
            //2����֡g_uart_recvBuf,g_uart_recvBuf[2]�������ֽ�
            if(g_uart_recvBuf[2]=='D'){
                //Flash��������

                //��ȡflashָ����������
                switch(g_uart_recvBuf[3]){
                case 'R':
                    offset = g_uart_recvBuf[5] *256+g_uart_recvBuf[6];
                    count  = g_uart_recvBuf[7];

                    g_uart_sentBuf[0]  =(uint_8)'M';           //֡ͷ
                    g_uart_sentBuf[1]  =count+1;               //������������count+C��
                    g_uart_sentBuf[2]  = (uint_8)'C';          //������ʼ֡
                    flash_read_logic(&g_uart_sentBuf[3],g_uart_recvBuf[4],offset,count);
                    g_uart_sentBuf[count+3]  = (uint_8)'U';    //֡β
                    uart_sendN(UART_2,count+4,&g_uart_sentBuf[0]);
                    break;
                case 'A':
                	offset = (g_uart_recvBuf[4]<<24)+(g_uart_recvBuf[5]<<16)+(g_uart_recvBuf[6]<<8)+g_uart_recvBuf[7];
					count  = g_uart_recvBuf[8];

					g_uart_sentBuf[0]  =(uint_8)'M';           //֡ͷ
					g_uart_sentBuf[1]  =count+1;               //������������count+C��
					g_uart_sentBuf[2]  = (uint_8)'C';          //������ʼ֡
					flash_read_physical(&g_uart_sentBuf[3],offset,count);
					g_uart_sentBuf[count+3]  = (uint_8)'U';    //֡β

					uart_sendN(UART_2,count+4,&g_uart_sentBuf[0]);
					break;
                case 'W':
                    //DISABLE_INTERRUPTS;//���ж�
                    offset =g_uart_recvBuf[5]*256+g_uart_recvBuf[6];
                    count = g_uart_recvBuf[7];
                    if(flash_write(g_uart_recvBuf[4], offset, count, &g_uart_recvBuf[8]) == 0 )
                    {
                        g_uart_sentBuf[0]=(uint_8)'M';        //֡ͷ
                        g_uart_sentBuf[1]=count+1;            //������������count+C��
                        g_uart_sentBuf[2]= (uint_8)'C';       //������ʼ֡
                        flash_read_logic(&g_uart_sentBuf[3],g_uart_recvBuf[4],offset,count);
                        g_uart_sentBuf[count+3]  = (uint_8)'U';  //֡β
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
                    //ENABLE_INTERRUPTS;//���ж�
                    break;
                case 'E':
                    //DISABLE_INTERRUPTS;//���ж�
                	 if(flash_erase(g_uart_recvBuf[4]) == 0 )
					{
						count=32;
						g_uart_sentBuf[0]=(uint_8)'M';         //֡ͷ
						g_uart_sentBuf[1]=count+1;             //������������count+C��
						g_uart_sentBuf[2]= (uint_8)'C';        //������ʼ֡
						flash_read_logic(&g_uart_sentBuf[3],g_uart_recvBuf[4], 0, count);
						g_uart_sentBuf[count+3]  = (uint_8)'U';//֡β
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
                    //ENABLE_INTERRUPTS;//���ж�
                    break;
                    //���ж�
                case 'P':
                    //DISABLE_INTERRUPTS;//���ж�
                    flash_protect(g_uart_recvBuf[4]);
                    count=10;
					g_uart_sentBuf[0]=(uint_8)'M';     //֡ͷ
					g_uart_sentBuf[1]=count+1;         //������������count+C��
					g_uart_sentBuf[2]= (uint_8)'C';    //������ʼ֡
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
					g_uart_sentBuf[13]  = (uint_8)'U';  //֡β
					uart_sendN(UART_2,count+4, &g_uart_sentBuf[0]);
                    //uart_sendN(UART_2,count,"Protected!");
                    //ENABLE_INTERRUPTS;//���ж�
                }

                }
            }
            framestate=2;
        }
}//��ѭ��end_for
//��ѭ������===============================================================
