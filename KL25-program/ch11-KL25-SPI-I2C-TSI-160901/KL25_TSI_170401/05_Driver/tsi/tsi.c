//===========================================================================
//�ļ����ƣ�tsi.c
//���ܸ�Ҫ��KL25 tsi�ײ����������ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2012-11-25  V1.0   ��ʼ�汾
//       2013-05-05 v2.1
//===========================================================================
#include "tsi.h"
//=====================================================================
//�������ƣ�tsi_init                                                  
//���ܸ�Ҫ����ʼ��TSIģ�� ,KL25ֻ��һ��TSIģ��                                                 
//����˵����chnlIDs:8λ�޷�������TSIģ����ʹ�õ�ͨ���ţ���ȡֵΪ0~15                                                                               
//�������أ� ��                                                               
//=====================================================================
void tsi_init(uint_8 chnlID)
{
	//����TSIʱ��
	BSET(SIM_SCGC5_TSI_SHIFT,SIM_SCGC5);
	BSET(SIM_SCGC5_PORTA_SHIFT,SIM_SCGC5);

	//ͨ���ţ�0=PTB0�ţ�1=PTA0�ţ�2=PTA1�ţ�3=PTA2�ţ�4=PTA3�ţ�5=PTA4�ţ�
	//      6=PTB1�ţ�7=PTB2�ţ�8=PTB3�ţ�9=PTB16�ţ�10=PTB17�ţ�11=PTB18�ţ�
	//      12=PTB19�ţ�13=PTC0�ţ�14=PTC1�ţ�15=PTC2��
	//����1��2��3��4��5�����������ŵ�Ĭ�Ϲ��ܼ�ΪTSIͨ��
    switch(chnlID)   //chnlID��ȡֵΪ0~15
	{
	case 1:
		PORTA_PCR0 = PORT_PCR_MUX(0); 	//ͨ��1ʹ��
	case 2:
		PORTA_PCR1 = PORT_PCR_MUX(0); 	//ͨ��2ʹ��
	case 3:
		PORTA_PCR2 = PORT_PCR_MUX(0); 	//ͨ��3ʹ��
	case 4:
		PORTA_PCR3 = PORT_PCR_MUX(0); 	//ͨ��4ʹ��
	case 5:
		PORTA_PCR4 = PORT_PCR_MUX(0); 	//ͨ��5ʹ��
	}

	BSET(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);//TSI�ж�ʹ��
	BSET(TSI_GENCS_STPE_SHIFT,TSI0_GENCS);//TSI�ڵ͹���ģʽ������
	//�Ĵ���TSI0_GENCS��REFCHRGλ��λ4�����ο�������ŵ����Ϊ8uA
	TSI0_GENCS |= (TSI_GENCS_REFCHRG(4)
		| TSI_GENCS_DVOLT(0)//�Ĵ���TSI0_GENCS��DVOLTλΪ00��ʾ��ֵ��ѹ
		            //Vp=1.33V����ֵ��ѹVm=0.30V ����ֵ��ֵ֮��Dv=1.03V
	        | TSI_GENCS_EXTCHRG(6)//�缫������ŵ����ֵ32uA
		| TSI_GENCS_PS(2)     //�缫����4��Ƶ
		| TSI_GENCS_NSCN(11)  //ÿ���缫ɨ��4��
	);
	BCLR(TSI_GENCS_ESOR_SHIFT,TSI0_GENCS);//���ó�����ֵ�����ж�
	BCLR(TSI_GENCS_STM_SHIFT,TSI0_GENCS); //�������ɨ��
	//��Խֵ��־λ��ɨ�����λ
    //������ֵ��λ��EOSFΪ1���ó�ɨ�����״̬
	BSET(TSI_GENCS_OUTRGF_SHIFT,TSI0_GENCS);
	BSET(TSI_GENCS_EOSF_SHIFT,TSI0_GENCS);
	//ѡ��ͨ��
	TSI0_DATA |= (TSI_DATA_TSICH(chnlID)); 
	//TSIģ��ʹ��
	BSET(TSI_GENCS_TSIEN_SHIFT,TSI0_GENCS);
}


//=====================================================================
//�������ƣ�tsi_get_value16                                                  
//���ܸ�Ҫ����ȡTSIͨ���ļ���ֵ                                                  
//����˵������                               
//�������أ���ȡTSIͨ���ļ���ֵ                                                                
//=====================================================================
uint_16 tsi_get_value16()
{

	uint_16 value;      
	BCLR(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);          //��TSI�ж�  
	BSET(TSI_DATA_SWTS_SHIFT,TSI0_DATA);
	//TSI0_DATA |= TSI_DATA_SWTS_MASK;                  //ɨ��һ��ѡ����ͨ��  
	while(!(TSI0_GENCS & TSI_GENCS_EOSF_MASK));       //�ȴ�ɨ�����   
	BSET(TSI_GENCS_EOSF_SHIFT,TSI0_GENCS);            //д1��0ɨ�������־λ
	//TSI0_GENCS |= TSI_GENCS_EOSF_MASK;                //д1��0ɨ�������־λ
	value =  (TSI0_DATA & TSI_DATA_TSICNT_MASK);      //��ȡ�����Ĵ����е�ֵ
	BSET(TSI_GENCS_OUTRGF_SHIFT,TSI0_GENCS);		  //д1��0��ֵ��־λ
    //TSI0_GENCS |= TSI_GENCS_OUTRGF_MASK;              //д1��0��ֵ��־λ
    BSET(TSI_GENCS_EOSF_SHIFT,TSI0_GENCS);               //��ɨ�������־λ
    //TSI0_GENCS |= TSI_GENCS_EOSF_MASK;                //��ɨ�������־λ    
    BSET(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);          //��TSI�ж�   
    return value; 
}


//=====================================================================
//�������ƣ�tsi_set_threshold1                                                  
//���ܸ�Ҫ���趨ָ��ͨ������ֵ                                                  
//����˵����     low:   �趨��ֵ����   ��     ȡֵ��ΧΪ0~65535                                 
//        high:  �趨��ֵ����   ��    ȡֵ��ΧΪ0~65535                                                                              
//�������أ� ��                                                             
//=====================================================================
void tsi_set_threshold(uint_16 low, uint_16 high)
{
    uint_32 thresholdValue;
    //��16λΪ���ޣ���16λΪ����
    thresholdValue = high;
    thresholdValue = (thresholdValue<<16)|low;
    TSI0_TSHD = thresholdValue;
}


//=====================================================================
//�������ƣ�tsi_enable_re_int
//���ܸ�Ҫ����TSI�ж�,�ر��������ɨ��,���жϿ�����IRQ�ж�
//����˵������
//�������أ���
//=====================================================================
void tsi_enable_re_int()
{
	//��TSI�ж�,�ر��������ɨ��
	BSET(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);
	BSET(TSI_GENCS_STM_SHIFT,TSI0_GENCS);
    enable_irq(26); //���жϿ�����IRQ�ж�  
}

//=====================================================================
//�������ƣ�tsi_disable_re_int
//����˵������
//�������أ���
//���ܸ�Ҫ����TSI�ж�,���������ɨ��,���жϿ�����IRQ�ж�
//=====================================================================
void tsi_disable_re_int()
{
	//��TSI�ж�,���������ɨ��
	BCLR(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);
	BCLR(TSI_GENCS_STM_SHIFT,TSI0_GENCS);
	//��ֹ�жϿ�����IRQ�ж�
	disable_irq(26);          
}

//=====================================================================
//�������ƣ�tsi_softsearch
//���ܸ�Ҫ������һ�����ɨ��
//����˵������
//�������أ���
//=====================================================================
void tsi_softsearch()
{
	BCLR(TSI_GENCS_STM_SHIFT,TSI0_GENCS);
	//TSI0_GENCS &= ~TSI_GENCS_STM_MASK;    //�����������
	BSET(TSI_DATA_SWTS_SHIFT,TSI0_DATA);
	//TSI0_DATA |= TSI_DATA_SWTS_MASK;	 //��ʼһ�����ɨ��
}

