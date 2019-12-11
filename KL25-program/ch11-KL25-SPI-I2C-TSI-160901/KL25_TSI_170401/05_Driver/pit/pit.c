//==========================================================================
//�ļ����ƣ�pit.c
//���ܸ�Ҫ��KL25 pit�ײ����������ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2016-3-20   V4.0
//==========================================================================
#include "pit.h"             
//==========================================================================
//��������: pit_init                                                         
//��������: ��                                          
//����˵��: channel:PITģ���ͨ���ţ�0��1��
//         freq:ϵͳ����ʱ��Ƶ�ʣ���λKHz����:ϵͳ����ʱ��Ϊ24MHz����freq=24000��
//         int_ms:�ж����ڣ���msΪ��λ��ϵͳ����ʱ��Ϊ24MHz�����ֵΪ178956ms
//���ܸ�Ҫ: PITģ���ʼ����
//���þ�����pit_init(CH_0,PIT_WORK_FREQ,1000);����ʼ��PITģ���0ͨ��ʹ������
//ʱ��Ƶ�ʣ��ж�����Ϊ1�롣
//==========================================================================
void pit_init(uint_8 channel,uint_16 freq,uint_32 int_ms)
{
    if(channel>1)
    {
        channel = 0;
    }
    if((int_ms<1)||(int_ms>178956))
        int_ms = 4000;
    BSET(SIM_SCGC6_PIT_SHIFT,SIM_SCGC6);            //��PITʱ����
    BCLR(PIT_MCR_MDIS_SHIFT,PIT_MCR);               //ʹ��PITģ��
    BSET(PIT_MCR_FRZ_SHIFT,PIT_MCR);                //����ģʽ�½�ֹ
    PIT_LDVAL(channel) = int_ms*freq-1;
    PIT_TCTRL(channel) |= PIT_TCTRL_TEN_MASK;       //ʹ��pitͨ����ʱ��
    PIT_TCTRL(channel) |= (PIT_TCTRL_TIE_MASK);
}
    
//==========================================================================
//��������: pit_enable_int
//����˵��: channel:PITģ���ͨ���ţ�0��1��
//��������: ��
//���ܸ�Ҫ: ʹ��ĳһͨ����PIT�жϡ�
//���þ�����pit_enable_int(CH_0);ʹ��PITģ���ͨ��0�жϡ�
//==========================================================================
void pit_enable_int(uint_8 channel)
{
    if(channel>1)
    {
        channel = 0;
    }
    PIT_TCTRL(channel)|=(PIT_TCTRL_TIE_MASK);    //��PITͨ���ж�

    NVIC_EnableIRQ(PIT_IRQn);                      //��PIT��IRQ�ж�
}

//==========================================================================
//��������: pit_disable_int
//����˵��: channel:PITģ���ͨ���ţ�0��1��
//��������: ��
//���ܸ�Ҫ: ��ֹĳһͨ����PIT�жϡ�
//���þ�����pit_disable_int(CH_0);��ֹPITģ���ͨ��0�жϡ�
//==========================================================================
void pit_disable_int(uint_8 channel)
{
    if(channel>1)
    {
        channel = 0;
    }
    PIT_TCTRL(channel)&=~(PIT_TCTRL_TIE_MASK);   //��PITͨ���ж�

    NVIC_DisableIRQ(PIT_IRQn);                     //��PIT��IRQ�ж�
}
