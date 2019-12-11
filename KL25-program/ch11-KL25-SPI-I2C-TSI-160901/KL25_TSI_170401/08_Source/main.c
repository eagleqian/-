//====================================================================
//�ļ����ƣ�main
//���ܸ�Ҫ��TSI������
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-10-12   V1.0
//       2013-05-04   V2.1
//       2016-05-08   v2.2
//˵���ĵ���Readme.txt
//=====================================================================
#include "includes.h"
// ȫ�ֱ�������
int main(void)
{
    //1. ����������ʹ�õı���
    uint_32  mRuncount;   //��ѭ��������
    uint_8 chnlID=5;      //TSIͨ������ѡ��ͨ��5


    //2. �����ж�
    DISABLE_INTERRUPTS;
    //3.��ʼ��ģ��
    light_init(RUN_LIGHT_BLUE,LIGHT_OFF);  //��ʼ������Ϊ��
    light_init(RUN_LIGHT_RED,LIGHT_OFF);  //��ʼ�����Ϊ��
    uart_init (UART_1, 9600);       //����1��2ʹ������ʱ��
    tsi_init(chnlID);                      // ��ʼ��TSI
    pit_init(CH_0, PIT_WORK_FREQ, 4000);//��ʼ��CH_0ʹ��ϵͳ����ʱ��Ƶ�ʣ�����Ϊ1s
    uart_send_string(UART_1, "This is TSI Test!\r\n");//���ڷ��Ͳ�������
    //�趨������ֵ
    tsi_set_threshold(TSI_TSHD_VALUE_LOW, TSI_TSHD_VALUE_HIGH);
    //4. ���йر�������ֵ
    //5. ʹ��ģ���ж�
    tsi_enable_re_int();     //��TSI�ж�
    uart_enable_re_int(UART_1);
    //6. �����ж�
    ENABLE_INTERRUPTS;

    //������ѭ��
    //��ѭ����ʼ============================================================
    for(;;)
    {
        mRuncount++;
    if (mRuncount > RUN_COUNTER_MAX)
    {
       mRuncount = 0;
       //��˸����
       light_change(RUN_LIGHT_BLUE);
       //�ر�TSI�жϲ��Ե�
       light_control(RUN_LIGHT_RED, LIGHT_OFF);
       //�����ѯ�жϲ���
       tsi_softsearch();
     } //end_if



     } //end_for
    //��ѭ������============================================================
    return 0;
}
