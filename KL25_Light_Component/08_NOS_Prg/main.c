//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//======================================================================

#include "includes.h"   //包含总头文件

int main(void) {
	//（1） 声明主函数使用的变量
	uint_32 mRuncount;     //主循环计数器
	uint_8 mflag;

	uint_8 k1;
	uint_8 k2;//B0,B2
	uint_8 k3;
	uint_8 k4;

	//定义四个状态变量负责返回输入引脚接受的输入

	//（2） 关总中断
	DISABLE_INTERRUPTS;

	//（3） 给有关变量赋初值
	mRuncount = 0;            //主循环计数器
	mflag = 0;               //灯控制标志

	//（4） 初始化外设模块
	light_init(LIGHT_RED, LIGHT_OFF);      //红灯初始化
	light_init(LIGHT_BLUE, LIGHT_OFF);     //蓝灯初始化
	light_init(LIGHT_GREEN, LIGHT_OFF);    //绿灯初始化

	//初始化开关为输入引脚
	key_init(key1);
	key_init(key2);
	key_init(key3);
	key_init(key4);

	//（5） 使能模块中断

	//（6） 开总中断
	ENABLE_INTERRUPTS;

	//进入主循环
	//主循环开始==================================================================

	for (;;) {
		k1 = key_get(key1);
		k2 = key_get(key2);

		if ((k1 == 1) && (k2 == 0)) {
			for (;;) {

				mRuncount++;	//主循环次数计数器+1
				if (mRuncount >= RUN_COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
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
				mRuncount++;	//主循环次数计数器+1

				if (mRuncount >= RUN_COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
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
//以下加入用户程序--------------------------------------------------------
} //主循环end_for
//主循环结束==================================================================

