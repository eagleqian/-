using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;

using System.Management;

namespace SerialPort
{
    ///-----------------------------------------------------------------------------------
    ///FrmMain :KW01-A1工程的窗体                                                          
    ///目    的:
    ///日    期:                                             
    ///编 程 者:
    ///-----------------------------------------------------------------------------------
    public partial class FrmMain : Form
    {      
        //1. 窗体类的临时变量区
        private System.IO.Ports.SerialPort UARTport;   //声明系统工具-串口对象的变量声明
        private Uart uart1;                          //声明一个自定义的Uart类型（串口操作）的变量
        private PCNode pcNode1;                      //声明一个自定义的PCNode类型的变量
          
   
        //2. 构造函数（启动窗体最先执行程序）
        public FrmMain()
        {
            //系统生成的构造函数（初始化窗体的元素）
            InitializeComponent();        
            //禁止检测跨线程调用异常(
            CheckForIllegalCrossThreadCalls = false;  
            //初始化窗体类临时变量
            UARTport = null;          //初始化“系统工具-串口对象”
            uart1 = null;             //初始化“Uart类型（串口操作）对象”
            pcNode1 = new PCNode();   //
       }
        
        //3. 加载窗体事件程序（在构造函数之后执行的程序）
        private void FrmMain_Load(object sender, EventArgs e)
        {
            byte[] B1 = {(byte)'P',11,(byte)'C',
                                 (byte)'W',(byte)'h',(byte)'o',(byte)'a',(byte)'r',(byte)'e',
                                 (byte)'y',(byte)'o',(byte)'u',(byte)'?', 
                                 (byte)'C' 
                                 };

            string s1;
            this.tb_statue.Text = "运行状态：FrmMain_Load开始,调用KL25类内部函数，寻找KL25...";
            this.tb_statue.Refresh();

            if (uart1 != null && uart1.IsOpen) uart1.close();
            s1 = pcNode1.findPCNode();           //调用PCNode类内部函数，寻找PCNode
            uart1 = pcNode1.PCNode_Uart1;
            
            this.tb_statue.Text = "运行状态："+s1;
            this.tb_statue.Refresh();

            lbl_PC_Node_State.Text = s1;
                       
            //保留编程参考：绑定DataReceived事件(即串口接收中断处理函数）
            if (uart1 != null)
            {
                UARTport = uart1.port;
                UARTport.DataReceived += new System.IO.Ports. //添加串口对象变量的接收事件的响应函数
                         SerialDataReceivedEventHandler(this.UARTport_recvData);
            }
            uart1.setReceInt(2);           //设置触发DataRecieved事件的字节数（目的是关闭该事件）
            uart1.sendData(B1, B1.Length); //发送握手数据

            //
          

       
            rBtnTargetComm_CheckedChanged(sender, e);
            
        }

        //========================以下是本窗体的各个事件响应函数==========================
       
        //------------------------单击“检测PC节点”按钮----------------------------------
        private void btnCheckPcNode_Click(object sender, EventArgs e)
        {
     
            //if (_port1.IsOpen) 
            
            this.tb_statue.Text = "运行状态：" + "单击“检测KL25”按钮...";
            this.tb_statue.Refresh();

            FrmMain_Load(sender, e);

            this.tb_statue.Text = "运行状态：" + "单击“检测KL25”按钮...退出";
        }

        //--------------------------单击窗口关闭“X”按钮---------------------------------
        private void FrmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (uart1 == null) return;
            //如果串口未关闭，则关闭
            if (uart1.IsOpen) uart1.close(); 
        }
        
        
        //-------------------------------串口接收事件的响应函数---------------------------
        private void UARTport_recvData(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string s1 = string.Empty;

            Thread.Sleep(100);
            PublicVar.g_ReceiveByteArray = uart1.recvData();    //调用串口接收函数
            if (PublicVar.g_ReceiveByteArray.Length > 0)
            {
                this.Txt_recv2.Text = "Interrupt--- " + System.Text.Encoding.Default.GetString(PublicVar.g_ReceiveByteArray);
            }
        }

        //---------------------------单击“读测试（逻辑地址）”按钮----------------------------
        private void btnPnFlashRead_Click(object sender, EventArgs e)
        {
            // 1. 临时变量声明
            byte sector;           // 扇区号
            int offset;            // 偏移量
            byte count;            // 读取字节数

            byte[] SendByteArray = new byte[9];          // 定义发送缓冲区
            byte offset_high, offset_low;                // 定义偏移地址的高低字节

            // 2. 临时变量赋值
            sector = Convert.ToByte(tbSector1.Text);    // 将TextBox中的Text转换为Byte类型
            offset  = Convert.ToInt32(tbOffset1.Text);  // 将TextBox中的Text转换为Byte类型
            count = Convert.ToByte(tbCount1.Text);
            
            // 计算偏移地址高低位
            offset_low = (byte)(0xff & offset);
            offset_high = (byte)((0xff00 & offset) >> 8);

            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
            this.Txt_recv1.Refresh();
            this.Txt_recv2.Refresh();

            this.tb_statue.Text = "运行状态：" + "单击“KL25 Flash 按逻辑地址读测试”按钮...";
            this.tb_statue.Refresh();
            try
            {
                SendByteArray[0] = (byte)'P';      //帧头
                SendByteArray[1] = 0x06;           //帧长
                SendByteArray[2] = (byte)'D';      //FLASH操作命令
                SendByteArray[3] = (byte)'R';      //FLASH读操作
                SendByteArray[4] = sector;         //第几页
                SendByteArray[5] = offset_high;    //偏移量高字节
                SendByteArray[6] = offset_low;     //偏移量低字节
                SendByteArray[7] = count;          //读取字节数
                SendByteArray[8] = (byte)'C';      //帧尾

                //发送、接收、显示
                sendRecv(SendByteArray,2,100);
            }
            catch
            {
                this.Txt_recv1.Text = "KL25 Flash读取操作失败！";
            }
        }

        //---------------------------单击“读测试（物理地址）”按钮-----------------------
        private void btnPnFlashReadAddr_Click(object sender, EventArgs e)
        {
            // 1. 临时变量声明
            int addr;            // 偏移量
            byte count;            // 读取字节数

            byte[] SendByteArray = new byte[10];          // 定义发送缓冲区
            byte offset_3, offset_2, offset_1, offset_0;                // 定义偏移地址的高低字节

            // 2. 临时变量赋值
            //sector = Convert.ToByte(tbSector1.Text);    // 将TextBox中的Text转换为Byte类型
            addr = Convert.ToInt32(tbAddr.Text,16);  // 将TextBox中的Text转换为Byte类型
            count = Convert.ToByte(tbCountaddr.Text);

            // 计算偏移地址高低位
            offset_0 = (byte)(0xff & addr);
            offset_1 = (byte)((0xff00 & addr) >> 8);
            offset_2 = (byte)((0xff0000 & addr) >> 16);
            offset_3 = (byte)((0xff000000 & addr) >> 24);

            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
            this.Txt_recv1.Refresh();
            this.Txt_recv2.Refresh();

            this.tb_statue.Text = "运行状态：" + "单击“KL25 Flash 按物理地址读测试”按钮...";
            this.tb_statue.Refresh();
            try
            {
                SendByteArray[0] = (byte)'P';      //帧头
                SendByteArray[1] = 0x07;           //帧长
                SendByteArray[2] = (byte)'D';      //FLASH操作命令
                SendByteArray[3] = (byte)'A';      //FLASH读操作（物理地址）
                SendByteArray[4] = offset_3;       //地址高位
                SendByteArray[5] = offset_2;       //
                SendByteArray[6] = offset_1;       //
                SendByteArray[7] = offset_0;       //地址低位
                SendByteArray[8] = count;          //读取字节数
                SendByteArray[9] = (byte)'C';      //帧尾

                //发送、接收、显示
                sendRecv(SendByteArray, 2, 100);
            }
            catch
            {
                this.Txt_recv1.Text = "KL25 Flash读取操作失败！";
            }
        }


        //---------------------------Flash写入操作按钮点击事件----------------------------
        private void btnPnFlashWrite_Click(object sender, EventArgs e)
        {

            // 1. 临时变量声明
            byte sector;        //扇区号
            int offset;         //偏移量
            byte n;             //读取字节数
            int i;
            byte len;
         

            // 2. 临时变量赋值
 
            sector = Convert.ToByte(tbSector2.Text);  // 将TextBox中的Text转换为Byte类型
            offset = Convert.ToInt32(tbOffset2.Text);   // 将TextBox中的Text转换为Byte类型
            n = Convert.ToByte(tbCount2.Text);
            byte[] writeDataArray = System.Text.Encoding.Default.GetBytes(tbWriteData1.Text); //String转化为Byte[]

            len = (byte)(n + 6);

            byte[] SendByteArray = new byte[len +3];

            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
            this.Txt_recv1.Refresh();
            this.Txt_recv2.Refresh();

            this.tb_statue.Text = "运行状态：" + "单击“KL25 Flash 写测试”按钮...";
            this.tb_statue.Refresh();

            try
            {
 
                SendByteArray[0] = (byte)'P';      //帧头

                SendByteArray[1] = len;           //帧长
                
                SendByteArray[2] = (byte)'D';      //FLASH操作命令
                SendByteArray[3] = (byte)'W';      //FLASH读操作

                SendByteArray[4] = sector;         //扇区号

                SendByteArray[5] = (byte)(offset/256);    //偏移量高字节
                SendByteArray[6] = (byte)(offset%256);    //偏移量低字节

                SendByteArray[7] = n;              //字节数 

                for (i=8;i<= 7+n;i++)
                {
                   SendByteArray[i]=writeDataArray[i-8];
                 }

                SendByteArray[len + 2] = (byte)'C';       //帧尾

                //发送、接收、显示
                sendRecv(SendByteArray,2,100);
            }
            catch
            {
                this.Txt_recv1.Text = "KL25 Flash读取操作失败！";
            } 
        
        }
        //---------------------------Flash擦除操作按钮点击事件----------------------------
        private void btnPnFlashErase_Click(object sender, EventArgs e)
        {
            // 1. 临时变量声明
            byte sector;                         // 扇区号
            byte[] SendByteArray = new byte[6];  //定义发送缓冲区

            // 2. 临时变量赋值
            sector = Convert.ToByte(tbSector3.Text);  // 将TextBox中的Text转换为Byte类型

            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
            this.Txt_recv1.Refresh();
            this.Txt_recv2.Refresh();

            this.tb_statue.Text = "运行状态：" + "单击“KL25 Flash 擦除测试”按钮...";
            this.tb_statue.Refresh();

            try
            {
                SendByteArray[0] = (byte)'P';      //帧头
                SendByteArray[1] = 0x03;           //帧长
                SendByteArray[2] = (byte)'D';      //FLASH操作命令
                SendByteArray[3] = (byte)'E';      //FLASH擦除标记
                SendByteArray[4] = sector;         //第几页
                SendByteArray[5] = (byte)'C';      //帧尾

                //发送、接收、显示
                sendRecv(SendByteArray,2,100);                
            }
            catch
            {
                this.Txt_recv1.Text = "KL25 Flash擦除操作失败！";
            }
        }

        //---------------------------Flash保护操作按钮点击事件----------------------------
        private void btnPnFlashProtect_Click(object sender, EventArgs e)
        {
            // 1. 临时变量声明
            byte regionNO;                         // 区域号
            byte[] SendByteArray = new byte[6];  //定义发送缓冲区

            // 2. 临时变量赋值
            regionNO = Convert.ToByte(tbSectorprot.Text);  // 将TextBox中的Text转换为Byte类型

            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
            this.Txt_recv1.Refresh();
            this.Txt_recv2.Refresh();

            this.tb_statue.Text = "运行状态：" + "单击“KL25 Flash 保护测试”按钮...";
            this.tb_statue.Refresh();

            try
            {
                SendByteArray[0] = (byte)'P';      //帧头
                SendByteArray[1] = 0x03;           //帧长
                SendByteArray[2] = (byte)'D';      //FLASH操作命令
                SendByteArray[3] = (byte)'P';      //FLASH保护标记
                SendByteArray[4] = regionNO;         //保护区域号
                SendByteArray[5] = (byte)'C';      //帧尾

                //发送、接收、显示
                sendRecv(SendByteArray, 2, 100);

            }
            catch
            {
                this.Txt_recv1.Text = "KL25 Flash保护操作失败！";
            }
        }   

        //------------------------------发送 接收并解析--------------------------------------
        private void sendRecv(byte[] SendByteArray,int cnt,int time)

        {
            byte[] recvData;
            int i;
            this.tb_statue.Text += "正在发送...";
            this.tb_statue.Refresh();
            recvData = pcNode1.PCNodeSendReturn(SendByteArray, cnt, time);

            if (recvData.Length <= 0)
            {
                this.tb_statue.Text += "无数据返回";
                this.tb_statue.Refresh();
            }
            else
            {
                this.tb_statue.Text += "有数据返回";
                this.tb_statue.Refresh();
                this.Txt_recv1.Text = string.Empty;                
                
                for (i = 0; i < recvData.Length; i++)
                    this.Txt_recv1.Text += recvData[i].ToString("X2").ToUpper() + " ";

                this.tbhead.Text = ""+(char)recvData[0];//帧头
                this.tblen.Text = "" + ((char)recvData[1]-1);//长度-1（内容起始帧C）
                this.tbfirst.Text = "" + (char)recvData[2];//内容起始帧C
                //this.Txt_recv2.Text = "帧头：" + (char)recvData[0] + " 接收长度：" + (recvData[1]-1) + " 接收起始字符帧：" + (char)recvData[2] + " 接收内容：";
                for (i = 3; i < recvData.Length - 1; i++)
                {   
                    //可显示字符予以显示，不可显示的ASCII码显示为空
                    if (recvData[i] > 31 && recvData[i] < 127)
                    {
                        this.Txt_recv2.Text += (char)recvData[i];
                    }
                    else {
                        this.Txt_recv2.Text += " ";
                    }

                }
                this.tbtail.Text = "" + (char)recvData[i];//帧尾

            }
        }



        

        //---------------------------单击“清空显示框”按钮-------------------------------
        private void btnClear1_Click(object sender, EventArgs e)
        {
            this.tb_statue.Text = "运行状态：" + "单击“清空显示框”按钮。";
            this.tb_statue.Refresh();
           
            this.Txt_recv1.Text = "";
            this.Txt_recv2.Text = "";
        }

        private void rBtnTargetComm_CheckedChanged(object sender, EventArgs e)
        {
           

            this.tb_statue.Text = "运行状态：" + "KL25 Flash测试";
            this.tb_statue.Refresh();

         
        }


       



       
    }
}
