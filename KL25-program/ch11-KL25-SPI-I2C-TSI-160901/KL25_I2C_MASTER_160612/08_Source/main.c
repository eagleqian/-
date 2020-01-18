//===========================================================================
//�ļ����ƣ�main
//���ܸ�Ҫ��i2c������
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-10-12   V1.0
//       2016-03-17   V2.1
//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//===========================================================================
#include "includes.h"
// ����ȫ�ֱ���
int main(void)
{
    //1. ����������ʹ�õı���
    uint_8 data[12];                    //����ӻ������ݣ�
    uint_8 Num_flag;                    //dataλ��ָ����
    uint_32 mRunCount1;                 //���ͼ��������1
    uint_32 mRunCount2;                 //���ͼ��������2
    //2. �����ж�
    DISABLE_INTERRUPTS;
    //3. ��ʼ������ģ��
    light_init(RUN_LIGHT_BLUE,LIGHT_OFF);
    i2c_init(I2C0,1,MasterAddress,100);     //���ĸ�����Ϊ�����ʣ��䵥λΪKB/S
    uart_init (UART_TEST, 9600);//����1��ʼ��, ����ʱ��24000Khz,������9600
    uart_send_string(UART_TEST, "This is i2c Test!\r\n");
    //4. ���йر�������ֵ
    strcpy(data,"Version3.4\n");               //Ϊdata���鸳ֵ
    Num_flag=0;
    //5. ʹ��ģ���ж�
    uart_enable_re_int(UART_TEST);
    //6. �����ж�
    ENABLE_INTERRUPTS;
    //i2c_write1(0, 0x73, 0x02, data);           //��ӻ�д A��0X73Ϊ�ӻ���ַ
    //������ѭ��
    //��ѭ����ʼ============================================================
    for(;;)
    {
        mRunCount1++;
        mRunCount2++;
        if(mRunCount1 > 2000000)
        {
            mRunCount1=0;
            light_change(RUN_LIGHT_BLUE);
        }

        //���¼����û�����-----------------------------------------------------
        if(mRunCount2 > 2000000)
        {
            //������ӻ�д data�����ݣ�0X73Ϊ�ӻ���ַ
            i2c_write1(I2C0, 0x73, 0x02, data[Num_flag]);
            Num_flag++;
            if(Num_flag > 10 )
            Num_flag=0;
            mRunCount2=0;
        }
    }//��ѭ��end_for
    //��ѭ������============================================================
    return 0;
}
