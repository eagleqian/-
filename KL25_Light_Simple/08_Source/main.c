//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�

int main(void) {
	//1. ����������ʹ�õı���
	uint_32 mRuncount = 0;     //��ѭ��������
	//2. �����ж�
	DISABLE_INTERRUPTS;
	//3. ��ʼ������ģ��

	//GPIO������̲��裺

	//(1)�������PORTB9�����ſ��ƼĴ�����ַ
	//PORTB�˿ڵ����ſ��ƼĴ�������ַΪ0x4004A000u����׺u��ʾ�޷�������
	volatile uint_32 *portB_ptr = (uint_32*) 0x4004A000u;
	//PORTB9�����ſ��ƼĴ�����ַ=����ַ+ƫ����
	volatile uint_32 *portB_PCR_9 = portB_ptr + 18;

	volatile uint_32 *portA_ptr = (uint_32*) 0x40049000u;
	volatile uint_32 *portA_PCR_1 = portA_ptr + 1;	//�˿�A����1�ļĴ���
	volatile uint_32 *portA_PCR_2 = portA_ptr + 2;
	*portA_PCR_1 &= 0b11111111111111111111100011111111; //��MUXλ��
	*portA_PCR_1 |= 0b00000000000000000000000100000000;
	*portA_PCR_2 &= 0b11111111111111111111100011111111; //��MUXλ��
	*portA_PCR_2 |= 0b00000000000000000000000100000000;

	//(2)�������PORTB�����ݷ���Ĵ����������ת�Ĵ�����ַ
	//PORTA�Ļ���ַ
	volatile uint_32 *gpioA_ptr = (uint_32*) 0x400FF000u;
	volatile uint_32 *portA_PDIR = gpioA_ptr + 4;
	volatile uint_32 *portA_PDDR = gpioA_ptr + 5;

	*portA_PDDR &= ~(1 << 1);

	//PORTB�˿ڣ���ΪGPIO���ܣ��Ļ���ַΪ0x400FF040u
	volatile uint_32 *gpioB_ptr = (uint_32*) 0x400FF040u;
	//PORTB�����ݷ���Ĵ�����ַ=����ַ+ƫ����
	volatile uint_32 *portB_PDDR = gpioB_ptr + 5;
	//PORTB������Ĵ�����ַ=����ַ+ƫ����
	volatile uint_32 *portB_PDO = gpioB_ptr + 0;
	//PORTB�������ת�Ĵ�����ַ=����ַ+ƫ����
	volatile uint_32 *portB_PTOR = gpioB_ptr + 3;

	//(3)����PORTB9����ΪGPIO���ţ�������Ӧ���ſ��ƼĴ�����10-8λ
	//(MUX)�ֶ�Ϊ001
	*portB_PCR_9 &= 0b11111111111111111111100011111111; //��MUXλ��
	*portB_PCR_9 |= 0b00000000000000000000000100000000;

	//(4)ͨ��PORTB������Ĵ���(����ɫС�ƵļĴ���������ֵ1����֤����Ϊ���ʱΪ��
	*portB_PDO |= (1 << 18);

	//(5)ͨ��PORTB�ķ���Ĵ���������PORTB9�������
	*portB_PDDR |= (1 << 18);

	//(6)ͨ��PORTB������Ĵ�������ɫС�Ƹ���ֵ��0-����
	//�����¹��������Թ۲죩
	*portB_PDO &= ~(1 << 18);   //��
	*portB_PDO |= (1 << 18);    //��
	*portB_PDO &= ~(1 << 18);   //��
	*portB_PDO |= (1 << 18);    //��

	//4. ���йر�������ֵ
	mRuncount = 0;                         //��ѭ��������
	//5. ʹ��ģ���ж�
	//6. �����ж�
	ENABLE_INTERRUPTS;
	for (;;) {
		//����ָʾ�ƣ���ƣ���˸----------------------------------------------
		/*
		 mRuncount++;
		 if (mRuncount >= 10000000) //���������ã���ֱ�����У� �Ƚϵ���������һ����������556677
		 {
		 mRuncount = 0;
		 *portB_PTOR |= (1 << 18);       //PTB9�����ƣ�ȡ��

		 }
		 */
		//���¼����û�����-----------------------------------------------------
		/*
		 if((*portA_PDIR) & (1<<1)){
		 *portB_PDO &= ~(1<<18);
		 }else{
		 *portB_PDO |= (1<<18);

		 } //end_for
		 }
		 */
		//��ѭ������===================================================================
		return 0;
	}
}

