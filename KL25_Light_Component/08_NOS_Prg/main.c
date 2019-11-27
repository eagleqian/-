//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//======================================================================

#include "includes.h"   //������ͷ�ļ�

int main(void) {
	//��1�� ����������ʹ�õı���
	uint_32 mRuncount;     //��ѭ��������
	uint_8 mflag;

	uint_8 k1;
	uint_8 k2;//B0,B2
	uint_8 k3;
	uint_8 k4;

	//�����ĸ�״̬�������𷵻��������Ž��ܵ�����

	//��2�� �����ж�
	DISABLE_INTERRUPTS;

	//��3�� ���йر�������ֵ
	mRuncount = 0;            //��ѭ��������
	mflag = 0;               //�ƿ��Ʊ�־

	//��4�� ��ʼ������ģ��
	light_init(LIGHT_RED, LIGHT_OFF);      //��Ƴ�ʼ��
	light_init(LIGHT_BLUE, LIGHT_OFF);     //���Ƴ�ʼ��
	light_init(LIGHT_GREEN, LIGHT_OFF);    //�̵Ƴ�ʼ��

	//��ʼ������Ϊ��������
	key_init(key1);
	key_init(key2);
	key_init(key3);
	key_init(key4);

	//��5�� ʹ��ģ���ж�

	//��6�� �����ж�
	ENABLE_INTERRUPTS;

	//������ѭ��
	//��ѭ����ʼ==================================================================

	for (;;) {
		k1 = key_get(key1);
		k2 = key_get(key2);

		if ((k1 == 1) && (k2 == 0)) {
			for (;;) {

				mRuncount++;	//��ѭ������������+1
				if (mRuncount >= RUN_COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
				{
					mRuncount = 0;
					k1 = key_get(key1);
					k2 = key_get(key2);
					if ((k1 == 0) && (k2 == 1))
						break;

					switch (mflag) {
					case 0: {
						light_change(LIGHT_RED);
						light_control(LIGHT_BLUE, LIGHT_OFF);
						light_control(LIGHT_GREEN, LIGHT_OFF);
						mflag = 1;
						break;
					}
					case 1: {
						light_change(LIGHT_BLUE);
						light_control(LIGHT_RED, LIGHT_OFF);
						light_control(LIGHT_GREEN, LIGHT_OFF);
						mflag = 0;
						break;
					}
					default: {

					}
					}
				}
			}
		} else if ((k1 == 0) && (k2 == 1)) {

			for (;;) {
				mRuncount++;	//��ѭ������������+1

				if (mRuncount >= RUN_COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
				{
					mRuncount = 0;
					k1 = key_get(key1);
					k2 = key_get(key2);
					if ((k1 == 1) && (k2 == 0))
						break;

					switch (mflag) {
					case 0: {
						light_change(LIGHT_GREEN);
						light_control(LIGHT_BLUE, LIGHT_OFF);
						light_control(LIGHT_RED, LIGHT_OFF);
						mflag = 1;
						break;
					}
					case 1: {
						light_change(LIGHT_BLUE);
						light_control(LIGHT_RED, LIGHT_OFF);
						light_control(LIGHT_GREEN, LIGHT_OFF);
						mflag = 0;
						break;
					}
					default: {

					}
					}
				}
			}
		} else {
		}

	}
//���¼����û�����--------------------------------------------------------
} //��ѭ��end_for
//��ѭ������==================================================================

