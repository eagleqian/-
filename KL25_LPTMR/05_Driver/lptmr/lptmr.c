//===========================================================================
//�ļ����ƣ�lptmr.c
//���ܸ�Ҫ��lptmr�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2016-3-20   V4.0
//===========================================================================
#include "lptmr.h"
    
//============================================================================
//�������ƣ�lptmr_init
//�������أ���
//����˵����clktype��ָ��ʱ��Դ��𣬲���lptmr.h��LPTMRʱ��Դ�ĺ궨�塣
//���ܸ�Ҫ��LPTMRģ���ʼ��������LPTMR������ʱ��Դ���ж�ʱ��Ϊ1�롣
//���þ�����lptmr_init(LPOCLK);����LPTMRģ��ʱ��ԴΪLPOCLKʱ�ӡ�
//============================================================================
void lptmr_init(uint_8 clktype)
{    
    uint_16 compare_value; 

    SIM_SCGC5|=SIM_SCGC5_LPTMR_MASK;//ʹ��LPTMRģ��ʱ��

    switch(clktype)
    {
        case LPOCLK:
            SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x01);//ѡ��LPOʱ��
            LPTMR0_PSR |= LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK;
            compare_value=1000;
            break;
        case IRC32KCLK:
            MCG_C1 |= MCG_C1_IRCLKEN_MASK;//ʹ���ڲ��ο�ʱ��
            MCG_C2 |= MCG_C2_IRCS(0);     //MCG_C2[IRCS]=0,ʹ��32kHz�ڲ��ο�ʱ��

            LPTMR0_PSR=LPTMR_PSR_PCS(0)|LPTMR_PSR_PBYP_MASK;
            compare_value=32768;
            break;
        case IRC4MCLK:
            MCG_C1 |= MCG_C1_IRCLKEN_MASK;//ʹ���ڲ��ο�ʱ��
            MCG_C2 |= MCG_C2_IRCS(1);     //MCG_C2[IRCS]=1,ʹ��4MHz�ڲ��ο�ʱ��

            LPTMR0_PSR = LPTMR_PSR_PCS(0)|LPTMR_PSR_PRESCALE(0x7);//256��Ƶ
            compare_value=15625;
            break;
        case OSCERCLK:  //ע�⣺ʵ����K64�����岢û�и��ⲿ����
        default:
            //���ⲿ�ο�ʱ��
            SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x00);//ѡ��ϵͳ����
            OSC0_CR |= OSC_CR_ERCLKEN_MASK;  //ѡ�� EXTAL to drive  XOSCxERCLK

            LPTMR0_PSR = LPTMR_PSR_PCS(3)|LPTMR_PSR_PRESCALE(0x7);//256��Ƶ
            compare_value=31250;
            break;
    }
    LPTMR0_CMR = LPTMR_CMR_COMPARE(compare_value);      //���ñȽϼĴ���ֵ
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; //����LPTMRģ������
}

//============================================================================
//�������ƣ�lptmr_enable_int
//�������أ���
//����˵������
//���ܸ�Ҫ��ʹ��LPTMRģ���жϡ�
//���þ�����lptmr_enable_int();ʹ��LPTMRģ���ж�
//============================================================================
void lptmr_enable_int()
{     
    LPTMR0_CSR|=LPTMR_CSR_TIE_MASK;        //����LPTMR��ʱ���ж�
    NVIC_EnableIRQ(LPTMR0_IRQn);           //�����ŵ�IRQ�ж�
}

//============================================================================
//�������ƣ�lptmr_disable_int
//�������أ���
//����˵������
//���ܸ�Ҫ����ֹLPTMRģ���ж�
//���þ�����lptmr_disable_int();��ֹLPTMRģ���ж�
//============================================================================
void lptmr_disable_int()
{      
    LPTMR0_CSR &=~LPTMR_CSR_TIE_MASK;      //��ֹLPTMR��ʱ���ж�
    NVIC_DisableIRQ(LPTMR0_IRQn);          //�����ŵ�IRQ�ж�
}


