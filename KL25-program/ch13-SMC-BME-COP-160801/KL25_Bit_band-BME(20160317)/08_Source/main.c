//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�


int main(void)
{
		unsigned long int temp,U32temp;
		unsigned char flag ;

		//BME��������Ĵ���,������16λ
		//�����ַ��һ����
		temp=(*( volatile unsigned long int *)(unsigned long int)0x400FF000);
		//��һ��λ
		temp=temp&(0xFFFEFFFF);
		//�����ַдһ����
		(*( volatile unsigned long int *)(unsigned long int)0x400FF000)=temp;
		//BME���һλ
		U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4A0FF000);
		//BME��AND����
		(*( volatile unsigned long int *)(unsigned long int) 0x440FF000)=0xFFFEFFFF;

		flag=1;	//flag ����ѡ��һ�ֿ���PORTB19�ķ���
		switch (flag)
		{
			case 1:
				//*************1.ͨ������********************************
				//�����Ÿ���ΪGPIO����
				PORT_PCR_REG(PORTB_BASE_PTR, 19) |= PORT_PCR_MUX(1);
				//�����ݷ���Ĵ�����19λ��1������PORTB19����Ϊ���
				GPIOB_PDDR |=(1<<19);
				//������Ĵ�����19λ��0��ʹPORTB19��������͵�ƽ
				GPIOB_PDOR &= ~(1<<19);
				break;
			case 2:
				//*************2.BME�궨�巽��***************************
				//ע�⣺�궨���е�ַ��GPIOB_PDOR��GPIOB_PDDR������ʹ��
				//    ֻ��ʹ����ֵ��ַ���д��Ρ�������
				//4.BME��������Ĵ���
				//PORTB_BASE_PTR->PCR[19]��ַ0x4004A04C
				//GPIOB_PDOR��ַ0x400FF040
				//GPIOB_PDDR��ַ0x400FF054
				BME_OR_IO(0x4004A04C,0xFFFFF1FF);
				BME_OR_IO(0x400FF054,0x00080000);
				BME_AND_IO(0x400FF040,0xFFF7FFFF);
				break;
			case 3:
				//*************3.BMEֱ�ӵ�ַ����***************************
				//4.BME��������Ĵ���
				//ͨ��LAS1������PORTB->PCR[19]����ΪGPIO����
				U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4C84A04C);
				//ͨ��LAS1���������ݷ���Ĵ�����19λ��1������PORTB19����Ϊ���
				U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4E6FF054);
				//ͨ��LAC1����������Ĵ�����19λ��0��ʹPORTB19��������͵�ƽ
				U32temp=(*( volatile unsigned long int *)(unsigned long int) 0x4A6FF040);
				break;
			case 4:
				//*************4.BME��OR����***************************
				//5.BME��������Ĵ���
				//ͨ��OR������PORTB->PCR[19]����ΪGPIO����
				(*( volatile unsigned long int *)(unsigned long int) 0x4804A04C)=0x00000100;
				//ͨ��OR���������ݷ���Ĵ�����19λ��1������PORTB19����Ϊ���
				(*( volatile unsigned long int *)(unsigned long int) 0x480FF054)=0x00080000;
				//ͨ��AND����������Ĵ�����19λ��0��ʹPORTB19��������ߵ�ƽ
				(*( volatile unsigned long int *)(unsigned long int) 0x440FF040)=0xFFF7FFFF;
				break;
			default:
				break;
		}
		for(;;)
		{
		}
		return 0;
}

