using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ZedGraph;
using System.Threading;

namespace Tempture
{
    public partial class FormSCI : Form
    {
        //委托，刷新
        delegate void RefreshHandle(Object zedGraphControl1);
        //委托,将从串口接收到的数据显示到接收框里面
        //委托,将从串口接收到的数据显示到接收框里面
        delegate void handleinterfaceupdatedelegate(Object textbox,
                                                    string text);
        //串口默认情况
        private string msg = "无校验,8位数据位,1位停止位(No parity,8 data " +
                            "bits,1 stop bit)";
        string[] str =new string[17];
        string str1 = "";
        Queue<double> dataqueue=new Queue<double>(1000);
        PointPairList list = new PointPairList();
        LineItem myCurve;
        SCI sci = new SCI();    //要调用SCI类中所定义的函数
        public FormSCI()
        {
            InitializeComponent();
        }

        private void FormSCI_Load(object sender, EventArgs e)
        {
            this.zedGraphControl1.GraphPane.Title.Text = "KL25芯片温度实时监控";
            this.zedGraphControl1.GraphPane.XAxis.Title.Text = "时间";
            this.zedGraphControl1.GraphPane.YAxis.Title.Text = "温度";
            //this.zedGraphControl1.GraphPane.XAxis.Type = ZedGraph.AxisType.DateAsOrdinal;
            this.zedGraphControl1.GraphPane.XAxis.Type = AxisType.Date;
            this.zedGraphControl1.GraphPane.XAxis.Scale.Format = "hh:mm:ss";
            GraphPane myPane = this.zedGraphControl1.GraphPane;
            //填充图表颜色
            myPane.Fill = new Fill(Color.White, Color.FromArgb(200, 200, 210), 45.0f);
            for (int j = 0; j <= 100; j++)
            {
                double x = (double)new XDate(DateTime.Now.AddSeconds((0)));
                double y = 0;
                list.Add(x, y);
            }
            myCurve = this.zedGraphControl1.GraphPane.AddCurve("温度",
            list, Color.DarkGreen, SymbolType.None);
            this.zedGraphControl1.AxisChange();
            this.zedGraphControl1.Refresh();
            //初始化时,按钮显示"打开串口(Open SCI)"

            this.BtnSCISwitch.Text = "打开串口(Open SCI)";
            this.CbSCIComNum.Enabled = true;　//[串口选择框]处于可用状态

            //自动搜索串口,并将其加入到[串口选择框]中
            int i;
            string[] SCIPorts;
            SCIPorts = System.IO.Ports.SerialPort.GetPortNames();
            this.CbSCIComNum.Items.Clear();//首先将现有的项清除掉
            for (i = 0; i < SCIPorts.Length; i++)
                //向[串口选择框]中添加搜索到的串口号
                this.CbSCIComNum.Items.Add(SCIPorts[i]);

            //设置各组合框的初始显示值
            if (SCIPorts.Length != 0)
            {
                this.BtnSCISwitch.Enabled = true;
                this.CbSCIComNum.SelectedIndex = 0;
                //this.CbSCISendType.SelectedIndex = 0;

                //设置初始的串口号与波特率
                PublicVar.g_SCIComNum = this.CbSCIComNum.Text;
                //显示当前串口信与状态信息
                this.LblSCI.Text = str1 + PublicVar.g_SCIComNum + "、" +
                                   PublicVar.g_SCIBaudRate + "\n" + msg;
                this.TSSLState.Text = "无操作,请先选择波特率与串口号,打开串口," +
                                 "然后发送数据";
            }
            else
            {
                this.TSSLState.Text = "没有可用的串口,请检查!";
                this.BtnSCISwitch.Enabled = false;
            }
        }


        private void CbSCIComNum_SelectedIndexChanged(object sender, EventArgs e)
        {
            PublicVar.g_SCIComNum = this.CbSCIComNum.Text;
            this.TSSLState.Text = "过程提示:选择串口号";
        }

        private void BtnSCISwitch_Click(object sender, EventArgs e)
        {
            bool Flag;//标记打开是否成功
            //根据按钮BtnSCISwitch显示内容执行打开或关闭串口操作
            if (this.BtnSCISwitch.Text.CompareTo("打开串口(Open SCI)") == 0)
            {
                //提示当前正在执行打开串口操作
                this.TSSLState.Text = "过程提示:正在打开串口...";
                //进行串口的初始化,并用Flag返回结果
                Flag = sci.SCIInit(SCIPort, PublicVar.g_SCIComNum,
                            9600);

                if (Flag == true)//串口打开成功
                {
                    //显示打开串口相关信息
                    this.LblSCI.Text = str1 + PublicVar.g_SCIComNum +
                        "、" + PublicVar.g_SCIBaudRate + "\n" + msg;

                    this.BtnSCISwitch.Text = "关闭串口(Close SCI)";
                    //[串口选择框]处于禁用状态
                    this.CbSCIComNum.Enabled = false;
                    //[波特率选择框]处于禁用状态
                    //状态上显示结果信息
                    this.TSSLState.Text = this.TSSLState.Text +
                                          "打开" + PublicVar.g_SCIComNum + "成功!" + "波特率选择：" + 9600;
                }
                else//串口打开失败
                {
                    this.TSSLState.Text = this.TSSLState.Text +
                                          "打开" + PublicVar.g_SCIComNum + "失败!";
                }
            }
            else if (this.BtnSCISwitch.Text == "关闭串口(Close SCI)")
            {
                //提示当前操作
                this.TSSLState.Text = "过程提示:正在关闭串口...";
                //执行关闭串口操作,并用Flag返回结果
                Flag = sci.SCIClose(this.SCIPort);
                if (Flag == true)
                {
                    this.LblSCI.Text = str1 + PublicVar.g_SCIComNum
                             + "、" + PublicVar.g_SCIBaudRate + "\n" + msg;
                    this.BtnSCISwitch.Text = "打开串口(Open SCI)";
                    //[串口选择框]处于可用状态
                    this.CbSCIComNum.Enabled = true;
                    this.TSSLState.Text += "关闭" + PublicVar.g_SCIComNum + "成功!";
                }
                else//串口关闭失败
                {
                    this.TSSLState.Text += "关闭" + PublicVar.g_SCIComNum + "失败!";
                }
            }
        }



        private void SCIPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte len = 0;  //标记接收的数据的长度
            Int32 i;
            //调用串口接收函数,并返回结果
            /*
            txtchannel0.Clear();
            txtchannel3.Clear();
            txtchannel4.Clear();
            txtchannel5.Clear();
            txtchannel6.Clear();
            txtchannel7.Clear();
            txtchannel8.Clear();
            txtchannel9.Clear();
            txtchannel11.Clear();
            txtchannel12.Clear();
            txtchannel13.Clear();
            txtchannel14.Clear();
            txtchannel15.Clear();
            txtchannel23.Clear();
            */

            Thread.Sleep(50);
            sci.SCIReceiveData(SCIPort, ref PublicVar.g_ReceiveByteArray,ref len);

            if ((len == 42) && (PublicVar.g_ReceiveByteArray[0]==0x22) && (PublicVar.g_ReceiveByteArray[41]==0x88)) 
            {
                //将串口的数据显示到文本
                //通道A
                i = PublicVar.g_ReceiveByteArray[3] * 256 + PublicVar.g_ReceiveByteArray[2];
                SCIUpdateRevtxtbox(txtchannel0, Convert.ToString(i,16));

                i = PublicVar.g_ReceiveByteArray[5] * 256 + PublicVar.g_ReceiveByteArray[4];
                SCIUpdateRevtxtbox(txtchannel3, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[7] * 256 + PublicVar.g_ReceiveByteArray[6];
                SCIUpdateRevtxtbox(txtchannel4, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[9] * 256 + PublicVar.g_ReceiveByteArray[8];
                SCIUpdateRevtxtbox(txtchannel5, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[11] * 256 + PublicVar.g_ReceiveByteArray[10];
                SCIUpdateRevtxtbox(txtchannel6, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[13] * 256 + PublicVar.g_ReceiveByteArray[12];
                SCIUpdateRevtxtbox(txtchannel7, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[15] * 256 + PublicVar.g_ReceiveByteArray[14];
                SCIUpdateRevtxtbox(txtchannel8, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[17] * 256 + PublicVar.g_ReceiveByteArray[16];
                SCIUpdateRevtxtbox(txtchannel9, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[19] * 256 + PublicVar.g_ReceiveByteArray[18];
                SCIUpdateRevtxtbox(txtchannel11, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[21] * 256 + PublicVar.g_ReceiveByteArray[20];
                SCIUpdateRevtxtbox(txtchannel12, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[23] * 256 + PublicVar.g_ReceiveByteArray[22];
                SCIUpdateRevtxtbox(txtchannel13, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[25] * 256 + PublicVar.g_ReceiveByteArray[24];
                SCIUpdateRevtxtbox(txtchannel14, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[27] * 256 + PublicVar.g_ReceiveByteArray[26];
                SCIUpdateRevtxtbox(txtchannel15, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[29] * 256 + PublicVar.g_ReceiveByteArray[28];
                SCIUpdateRevtxtbox(txtchannel23, Convert.ToString(i, 16));
                
                //通道B
                i = PublicVar.g_ReceiveByteArray[33] * 256 + PublicVar.g_ReceiveByteArray[32];
                SCIUpdateRevtxtbox(txtchannel4b, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[35] * 256 + PublicVar.g_ReceiveByteArray[34];
                SCIUpdateRevtxtbox(txtchannel5b, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[37] * 256 + PublicVar.g_ReceiveByteArray[36];
                SCIUpdateRevtxtbox(txtchannel6b, Convert.ToString(i, 16));

                i = PublicVar.g_ReceiveByteArray[39] * 256 + PublicVar.g_ReceiveByteArray[38];
                SCIUpdateRevtxtbox(txtchannel7b, Convert.ToString(i, 16));
                
                //温度（26通道）数据处理
                i = PublicVar.g_ReceiveByteArray[31] * 256 + PublicVar.g_ReceiveByteArray[30];
                //string temp = Convert.ToString((PublicVar.g_ReceiveByteArray[30]), 16);

                double VTemp = Convert.ToInt32(i * 3300) / 65535.0;
                //将电压值转换为温度值
                //719为25度时的标准电压采样值，1.715为温度传感器的电压/温度曲线（近似线性关系）的斜率
                double t = 25 - (VTemp - 719) / 1.715;
                //绘制坐标
                double x = (double)new XDate(DateTime.Now);
                double y = t;
                list.Add(x, y);
                Refresh(zedGraphControl1); 
                this.TSSLState.Text = "过程提示:数据接收!";
            }
            //接收数据失败
            else
            {
                //sci.SCIReceInt(SCIPort, 1);//设置产生接收中断的字节数 
                this.TSSLState.Text = "过程提示:数据接收!";
            }
            //timer1.Enabled = true;
        }
        private void Refresh(Object zedGraphControl1)
        {
            //不在同一个线程中
            if (((ZedGraphControl)zedGraphControl1).InvokeRequired)
            {
                RefreshHandle InterFaceRefresh = new
                    RefreshHandle(Refresh);
                this.Invoke(InterFaceRefresh, new object[] { zedGraphControl1 });
            }
            else
            {
                this.zedGraphControl1.AxisChange();
                this.zedGraphControl1.Refresh();
            }
        }
        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 函数名:SCIUpdateRevtxtbox                                       
        /// 参  数:(1)textbox,Object类型,接收数据要放入的文本框             
        ///        (2)text,string类型,要放入文本框的数据                    
        /// 功  能:若串行接收与Object不在同一线程中运行，那么通过invoke     
        ///        跨线程用串口接收到的数据来更新接收文本框中的数据         
        /// 返  回:无                                                       
        /// </summary>                                                      
        /// <param name="textbox"></param>                                  
        /// <param name="str"></param>                                      
        ///-----------------------------------------------------------------
        private void SCIUpdateRevtxtbox(Object textbox, string text)
        {
            //textbox显示文本与串口执行不在同一个线程中
            if (((TextBox)textbox).InvokeRequired)
            {
                handleinterfaceupdatedelegate InterFaceUpdate = new
                    handleinterfaceupdatedelegate(SCIUpdateRevtxtbox);
                this.Invoke(InterFaceUpdate, new object[] { textbox, text });
            }
            else
            {
                ((TextBox)textbox).Text = text;
                //把光标放在最后一行
                ((TextBox)textbox).SelectionStart =
                                           ((TextBox)textbox).Text.Length;
                //将文本框中的内容调整到当前插入符号位置
                ((TextBox)textbox).ScrollToCaret();
            }
        }

    }
}
