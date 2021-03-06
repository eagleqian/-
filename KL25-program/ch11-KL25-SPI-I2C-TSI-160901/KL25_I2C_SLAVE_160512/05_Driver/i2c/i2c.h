//=====================================================================
//文件名称：i2c.h
//功能概要：i2c底层驱动构件头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2013-03-12   V1.2
//        2015-01-21   V3.0
//=====================================================================
#ifndef _I2C_H         //防止重复定义（ 开头)
#define _I2C_H
#include "common.h"   //包含公共要素头文件
//模块宏定义

//IIC号的宏定义
#define IIC_0        0    //I2C0
#define IIC_1        1    //I2C1

//根据串口实际硬件引脚，确定以下宏常量值。
//在此工程中，我们只使用IIC0组中的第4个，IIC1组中的第3个，
//因此我们在此只需要将IIC_0_GROUP宏定义为4,IIC_1_GROUP宏定义为3

//IIC_0：1=PTE24~25脚，2=PTB0~1脚，3=PTB2~3脚，4=PTC8~9脚
#define IIC_0_GROUP 4    //SD-FSL-KL25-EVB板上使用PTC8~9脚

//IIC_1: 1=PTE1~0脚，2=PTA3~4脚, 3=PTC1~2脚, 4=PTC10~11脚
#define IIC_1_GROUP 3    //SD-FSL-KL25-EVB板上使用PTC1~2脚


// 功能接口(i2c通信函数声明)
//============================================================================
//函数名称：i2c_init                                                        
//功能概要：初始化IICX模块。                                     
//参数说明：I2C_No:模块号,其取值为0,1
//       Mode 模式  1：主机     0：从机
//       address 本模块初始化地址    范围(1~255)
//       BaudRate为波特率，其单位为Kb/s，其取值为50,75,100,150,300
//函数返回：无                                                                  
//============================================================================
void i2c_init(uint_8 I2C_No,uint_8 Mode,uint_8 address,uint_8 BaudRate );
//============================================================================
//函数名称：i2c_read1                                                        
//功能概要：从从机读1个字节数据                                            
//参数说明： I2C_No:模块号，其取值为0，1
//       DeviceAddr:设备地址    范围(1~255)
//       DataLocation:数据在从机接收数组中的位置    范围(0~255)
//       Data:带回收到的一个字节数据  
//函数返回：为0,成功读一个字节;为1,读一个字节失败  
//函数说明: 内部调用 send_signal,wait  
//============================================================================
uint_8 i2c_read1(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation, uint_8 *Data);
//============================================================================
//函数名称：i2c_write1                                                        
//功能概要：向从机写1个字节数据                                           
//参数说明：  I2C_No:模块号 ，其取值为0，1
//       DeviceAddr:设备地址    范围(1~255)
//       DataLocation:数据在从机接收数组中的位置    范围(0~255)
//       Data:要发给从机的1个字节数据  
//函数返回：为0,成功写一个字节;为1,写一个字节失败 
//函数说明: 内部调用 send_signal,wait  
//============================================================================

uint_8 i2c_write1(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation, uint_8 Data);
//============================================================================
//函数名称： i2c_readn                                                        
//功能概要： 从从机读N个字节数据                                             
//参数说明：  I2C_No:模块号，其取值为0，1
//       DeviceAddr:设备地址    范围(1~255)
//       DataLocation:数据在从机接收数组中的位置    范围(0~255)
//       Data:读出数据的缓冲区
//       N:从从机读的字节个数 
//函数返回： 为0,成功读N个字节;为1,读N个字节失败  
//函数说明: 内部调用i2c_read1  
//============================================================================
uint_8 i2c_readn(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation, uint_8 Data[], uint_8 N);
//============================================================================
//函数名称： i2c_writen                                                        
//功能概要： 向从机写N个字节数据                                              
//参数说明：  I2C_No:模块号，其取值为0，1
//       DeviceAddr:设备地址    范围(1~255)
//       DataLocation:数据在从机接收数组中的位置    范围(0~255)
//       Data:要写入的数据 的首地址
//       N:从从机读的字节个数 
//函数返回： 为0,成功写N个字节;为1,写N个字节失败
//函数说明: 内部调用i2c_write1   
//============================================================================
uint_8 i2c_writen(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation,uint_8 Data[], uint_8 N);
//==============================================================================
//函数名称：i2c_re_enable_int.
//功能说明：打开i2c的IRQ中断。
//函数参数：i2cNO:i2c模块号，其取值为0，1
//函数返回：无。
//==============================================================================
void i2c_enable_re_int(uint_8 I2C_No);
//==============================================================================
//函数名称：i2c_re_disable_int.
//功能说明：关闭i2c的IRQ中断。
//函数参数：i2cNO:i2c模块号，其取值为0,1
//函数返回：无。
//==============================================================================
void i2c_disable_re_int(uint_8 I2C_No);
#endif  //防止重复定义（结尾）

//===========================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，不足之处，
//     欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏州大学飞思卡尔嵌入式中心（苏州华祥信息科技有限公司）
//技术咨询：0512-65214835  http://sumcu.suda.edu.cn
//业务咨询：0512-87661670,18915522016  http://www.hxtek.com.cn
