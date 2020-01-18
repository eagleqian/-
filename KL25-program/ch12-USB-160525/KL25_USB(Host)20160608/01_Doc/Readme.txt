
功能概要：构件化理解USB主机编程
版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
版本更新：2012-10-12  V1.0
       2013-11-12 V2.0（WYH）
       2014-08-11 V3.0 (转入KDS)
       2016-03-14 V4.0 (更新到CMSIS标准)
硬件说明：PORTB19=红灯；PORTB18= 绿灯；PORTB9= 蓝灯；


1. 工程概述
(1)本工程为KL25微控制器无操作系统应用工程，中断和UART样例程序
(2)使用串口与外界通信，使用串口1，波特率为9600，1位停止位，无校验
(3)启动串口接收中断，回发接收数据
(4)实现KL25作为USB主机的功能

2. 软件环境
(1)Kinetis Design Studio IDE v3.0.0.

3. 硬件环境
(1)KL25 SD13-01 EVB板
(2)蓝灯对应引脚为PTB9
(3)串口1发送引脚为PTE0，接收引脚为PTE1
    
4. 实验现象
(1)KL25 SD13-01 EVB板板上的蓝灯亮
(2)通过串口发送字符串
   "----------------------USB主机测试!----------------
    System started, Please insert your USB MSD!" 
(3)将U盘插入到KL25板上的USB口，KL25识别该U盘并读取U盘内的数据，串口发送字符串
   “Device connection detected.
   Mass-storage driver started.
   USB MSD information: Kingston DataTraveler 2.0 V1.00
   File system init ok!
   Read OK!
   Udisk Data:suda-usb-test
   Close OK!”     
(4)串口回发接收数据

5. 实验注意
(1)可以使用PC端的c#2010来实时接受数据
(2)先打开串口，后开启KL25 SD13-01 EVB板电源
(3)C#2010串口测试程序中包含十进制数据发送和十六进制数据发送
(4)当U盘插入到KL25的USB口，若出现文件系统初始化失败的现象，进行复位即可。

================================================================
声明：
（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，不足之处，
欢迎指正。
（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。

苏州大学飞思卡尔嵌入式中心（苏州华祥信息科技有限公司）
技术咨询：http://sumcu.suda.edu.cn;0512-65214835
业务咨询：http://www.hxtek.com.cn


