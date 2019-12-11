//============================================================================
//�ļ����ƣ�cmp.c
//���ܸ�Ҫ��KL25 �Ƚ����ײ����������ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2012-11-25  V1.0   ��ʼ�汾
//============================================================================
#include "cmp.h"

//===========================================================================
//�������ƣ�cmp_init
//�������� �� ��
//����˵��: reference:�ο���ѹѡ��  0=Vin1in  1=Vin2in
//         plusChannel: ���Ƚ�ͨ����
//         minusChannel�����Ƚ�ͨ����
//ͨ����0,1,2,3,4,5��Ӧ����PTC6,PTC7,PTC8,PTC9,PTC30,PTC29��
//ͨ��6 Bandgap;ͨ��7 DAC����
//���ܸ�Ҫ��CMPģ���ʼ��
//===========================================================================
void cmp_init(uint_8 reference,uint_8 plusChannel,uint_8 minusChannel)
{
	    //ͨ����ȡģ���ѡ��Ƚ�����ַ
		CMP_MemMapPtr cmpch = CMP0_BASE_PTR;		
		if(plusChannel>7)
			plusChannel = 7;
		if(plusChannel<0)
			plusChannel = 0;
		
		if(minusChannel>7)
			minusChannel = 7;
		if(minusChannel<0)
			minusChannel = 0;
		
		//ʹ�ܱȽ�ģ��ʱ��
		SIM_SCGC4 |=SIM_SCGC4_CMP_MASK;
				
		//��ʼ���Ĵ���
		CMP_CR0_REG(cmpch) = 0;
		CMP_CR1_REG(cmpch) = 0;
		CMP_FPR_REG(cmpch) = 0;
		//��������˱�־����жϱ�־
		CMP_SCR_REG(cmpch) = 0x06;  
		CMP_DACCR_REG(cmpch) = 0;
		CMP_MUXCR_REG(cmpch) = 0;
		
		//���üĴ���
		//���ˣ�������ʱ��ֹ
		CMP_CR0_REG(cmpch) = 0x00;  
		//����ģʽ�����ٱȽϣ��޹��������������Ž�ֹ
		CMP_CR1_REG(cmpch) = 0x16;  
		//���˽�ֹ
		CMP_FPR_REG(cmpch) = 0x00; 
		//ʹ�������غ��½����жϣ����־λ
		CMP_SCR_REG(cmpch) = 0x1E;  
				
		if(reference==0)//�ο���ѹѡ��VDD3.3V
		{		
			//6λ�ο�DACʹ�ܣ�ѡ��VDD��ΪDAC�ο���ѹ
			CMP_DACCR_REG(cmpch) |= 0xC0;
		}
		else
		{
			//6λ�ο�DACʹ�ܣ�ѡ��VREF��ΪDAC�ο���
			CMP_DACCR_REG(cmpch) |= 0x80;
		}
				
		CMP_MUXCR_REG(cmpch) = CMP_MUXCR_PSEL(plusChannel)//��ͨ��ѡ��
				               | CMP_MUXCR_MSEL(minusChannel);//��ͨ��ѡ��		
				
		//ѡ���������
		PORTC_PCR5=PORT_PCR_MUX(6);
        //CMPʹ��		
		CMP_CR1_REG(cmpch) |= CMP_CR1_EN_MASK;
}

//===========================================================================
//�������ƣ�dac_set_value
//�������أ���
//����˵����value: dac�����ת��ֵ
//���ܸ�Ҫ������DAC���ֵ
//===========================================================================
void dac_set_value(uint_8 value)
{
	 //ͨ����ȡģ���ѡ��Ƚ�����ַ
	 CMP_MemMapPtr cmpch = CMP0_BASE_PTR;
	 CMP_DACCR_REG(cmpch) |= CMP_DACCR_VOSEL(value);
}

//===========================================================================
//�������ƣ�cmp_enable_int
//�������أ���
//����˵������
//���ܸ�Ҫ�����Ƚ��ж�
//===========================================================================
void cmp_enable_int()
{
	//ͨ����ȡģ���ѡ��Ƚ�����ַ
	 CMP_MemMapPtr cmpch = CMP0_BASE_PTR;
	//����cmp�����ж�,�������½��ؾ�����
	 CMP_SCR_REG(cmpch)|=  CMP_SCR_IEF_MASK  | CMP_SCR_IER_MASK; 
	 enable_irq(16);  	
}

//===========================================================================
//�������ƣ�cmp_disable_int
//�������أ���
//����˵������
//���ܸ�Ҫ���رȽ��ж�
//===========================================================================
void cmp_disable_int()
{
	//ͨ����ȡģ���ѡ��Ƚ�����ַ
    CMP_MemMapPtr cmpch = CMP0_BASE_PTR;
	//�ر�cmp�����ж�,�������½��ؾ��ر�
	CMP_SCR_REG(cmpch)&=(~CMP_SCR_IEF_MASK) | (~CMP_SCR_IER_MASK );   
	//�ؽ������ŵ�IRQ�ж�
	disable_irq(16);
	
}

