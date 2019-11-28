//======================================================================
// 文件名称：kb.c
// 功能概要：键盘构件源文件
//======================================================================
#include "kb.h"

//键盘键值与定义值对应表
const uint_8 KBtable[] =
{
    0xEE,'7',  0xED,'4',  0xEB,'1',  0xE7,'0',
    0xDE,'8',  0xDD,'5',  0xDB,'2',  0xD7,'A',
    0xBE,'9',  0xBD,'6',  0xBB,'3',  0xB7,'B',
    0x7E,'C',  0x7D,'D',  0x7B,'E',  0x77,'F',
    0x00
};

//说明：用一个字节表达键值，其位顺序是{m4,m3,m2,m1,n4,n3,n2,n1}
uint_16 kbm[4]={m1, m2, m3, m4};
uint_16 kbn[4]={n1, n2, n3, n4};

//内部函数声明
uint_8 KBScan1(void);

//=====================================================================
//函数名称：KBInit
//函数返回：无
//参数说明：无
//功能概要：初始化键盘模块。
//=====================================================================
void KBInit(void)
{
    uint_8 i; 
    //定义列线为输入，且上拉
    for(i = 0;i < 4;i++)
    {
        gpio_init(kbn[i],GPIO_IN,0);
        gpio_pull(kbn[i],1);
    }
    //定义行线为输出，且初始状态为低电平，低电平是为中断方式时产生下降沿做准备
    for(i = 0;i < 4;i++)
    {
        gpio_init(kbm[i], GPIO_OUTPUT, 0);
    }
}

//=====================================================================
//函数名称：KBScanN
//函数返回：键值,无键按下返回0xFF
//参数说明：重复扫描键盘的的次数（scan_cnt），建议1~20之间
//功能概要：多次扫描键盘,返回键值，scan_cznt小于等于1，直接返回扫描1次键值，否则再
//        继续扫描到（scan_cnt*0.5）次相同的键值,且键值不为0xFF时返回该键值，
//        否则返回最后一次扫描值
//======================================================================
uint_8 KBScanN(uint_8 scan_cnt)
{
    uint_8 i,KB_value,KB_value_last,same_count;
    same_count=0;             //键值相同次数变量=0
    KB_value_last=0xFF;
    if(scan_cnt<1 || scan_cnt>20) scan_cnt=1;
    //以下多次扫描消除抖动
    for (i=1; i<=scan_cnt; i++)
    {
        KB_value = KBScan1();   //扫描一次,获取一次键值
        if ((KB_value == KB_value_last) && (KB_value!=0xFF))  //相等情况
        {
            same_count++;   //键值相同次数变量+1
            if(same_count>=scan_cnt*0.5)  break;  //返回键值
        }
        else    //不相等情况
        {
            KB_value_last=KB_value;  //保存当前键值
            same_count=1;            //键值相同次数变量=1
        }
    }
    return  KB_value;   //返回键值
}

//=====================================================================
//函数名称：KBDef
//函数返回：无
//参数说明：键值value 
//功能概要：键值转为定义值函数。
//=====================================================================
uint_8 KBDef(uint_8 value)
{
    uint_8 KeyPress;                //键定义值
    uint_8 i;
    i = 0;
    KeyPress = 0xff;
    while (KBtable[i] != 0x00)      //在键盘定义表中搜索欲转换的键值,直至表尾
    {
        if(KBtable[i] == value)     //在表中找到相应的键值
        {
            KeyPress = KBtable[i+1];//取出对应的键定义值
            break;
        }
        i += 2;                     //指向下一个键值,继续判断
    }
    return KeyPress;
}

//----------------------以下为内部函数存放处-------------------
//======================================================================
//函数名称：KBScan1
//函数返回：扫描到的键值
//参数说明：无
//功能概要：扫描1次4*4键盘,返回扫描到的键值,若无按键,返回0xff 。
//======================================================================
uint_8 KBScan1(void)
{
    uint_8 keyvalue;  //声明键值临时变量
    uint_8 i,n,flag;  //声明临时变量

    keyvalue = 0xff;  //键值临时变量初值
    flag=0;

    KBInit();         //键盘初始化
    //进行行扫描
    for (i = 0; i <= 3; i++)
    {
        //令第i行=低，其余各行拉高
        for(n=0;n<4;n++)
        {
            gpio_set(kbm[n],1);
        }
        gpio_set(kbm[i],0);
        //延时
        asm("NOP");
        asm("NOP");
        //检查列线，看是否有由于按键被按下而被拉低的列
        for(n=0;n<4;n++)
        {
            if(0==(gpio_get(kbn[n])))   //找到具体列线
            {
                BCLR(i+4,keyvalue);     //计算键值（对应行线=0）
                BCLR(n,keyvalue);       //计算键值（对应列线=0）
                //至此，有按键，且键值在临时变量keyvalue中
                flag=1;  //有按键标志
                break;
            }
        }
    if (1==flag) break; //有按键
    }
    return(keyvalue);   //返回键值。（若无按键，该值为0xff）
}
//----------------------------内部函数结束-----------------

