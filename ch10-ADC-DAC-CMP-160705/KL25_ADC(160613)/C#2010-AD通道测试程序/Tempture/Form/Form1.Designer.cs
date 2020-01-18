namespace Tempture
{
    partial class FormSCI
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.SetSerialPort = new System.Windows.Forms.GroupBox();
            this.BtnSCISwitch = new System.Windows.Forms.Button();
            this.CbSCIComNum = new System.Windows.Forms.ComboBox();
            this.lbPortName = new System.Windows.Forms.Label();
            this.sSSerialPortInfo = new System.Windows.Forms.StatusStrip();
            this.TSSLState = new System.Windows.Forms.ToolStripStatusLabel();
            this.SCIPort = new System.IO.Ports.SerialPort(this.components);
            this.LblSCI = new System.Windows.Forms.Label();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.txtchannel0 = new System.Windows.Forms.TextBox();
            this.txtchannel3 = new System.Windows.Forms.TextBox();
            this.txtchannel4 = new System.Windows.Forms.TextBox();
            this.txtchannel5 = new System.Windows.Forms.TextBox();
            this.txtchannel6 = new System.Windows.Forms.TextBox();
            this.txtchannel7 = new System.Windows.Forms.TextBox();
            this.txtchannel8 = new System.Windows.Forms.TextBox();
            this.txtchannel9 = new System.Windows.Forms.TextBox();
            this.txtchannel11 = new System.Windows.Forms.TextBox();
            this.txtchannel12 = new System.Windows.Forms.TextBox();
            this.txtchannel13 = new System.Windows.Forms.TextBox();
            this.txtchannel14 = new System.Windows.Forms.TextBox();
            this.txtchannel15 = new System.Windows.Forms.TextBox();
            this.txtchannel23 = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.MUXSEL_A = new System.Windows.Forms.GroupBox();
            this.MUXSEL_B = new System.Windows.Forms.GroupBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.txtchannel7b = new System.Windows.Forms.TextBox();
            this.txtchannel5b = new System.Windows.Forms.TextBox();
            this.txtchannel6b = new System.Windows.Forms.TextBox();
            this.txtchannel4b = new System.Windows.Forms.TextBox();
            this.temptureShow = new System.Windows.Forms.GroupBox();
            this.SetSerialPort.SuspendLayout();
            this.sSSerialPortInfo.SuspendLayout();
            this.MUXSEL_A.SuspendLayout();
            this.MUXSEL_B.SuspendLayout();
            this.temptureShow.SuspendLayout();
            this.SuspendLayout();
            // 
            // SetSerialPort
            // 
            this.SetSerialPort.Controls.Add(this.BtnSCISwitch);
            this.SetSerialPort.Controls.Add(this.CbSCIComNum);
            this.SetSerialPort.Controls.Add(this.lbPortName);
            this.SetSerialPort.ForeColor = System.Drawing.Color.Red;
            this.SetSerialPort.Location = new System.Drawing.Point(12, 13);
            this.SetSerialPort.Name = "SetSerialPort";
            this.SetSerialPort.Size = new System.Drawing.Size(848, 73);
            this.SetSerialPort.TabIndex = 0;
            this.SetSerialPort.TabStop = false;
            this.SetSerialPort.Text = "串口设置(Setting Serial Port)";
            // 
            // BtnSCISwitch
            // 
            this.BtnSCISwitch.ForeColor = System.Drawing.Color.Black;
            this.BtnSCISwitch.Location = new System.Drawing.Point(465, 20);
            this.BtnSCISwitch.Name = "BtnSCISwitch";
            this.BtnSCISwitch.Size = new System.Drawing.Size(134, 40);
            this.BtnSCISwitch.TabIndex = 4;
            this.BtnSCISwitch.Text = "打开串口(Open SCI)";
            this.BtnSCISwitch.UseVisualStyleBackColor = true;
            this.BtnSCISwitch.Click += new System.EventHandler(this.BtnSCISwitch_Click);
            // 
            // CbSCIComNum
            // 
            this.CbSCIComNum.FormattingEnabled = true;
            this.CbSCIComNum.Location = new System.Drawing.Point(239, 31);
            this.CbSCIComNum.Name = "CbSCIComNum";
            this.CbSCIComNum.Size = new System.Drawing.Size(121, 20);
            this.CbSCIComNum.TabIndex = 1;
            this.CbSCIComNum.SelectedIndexChanged += new System.EventHandler(this.CbSCIComNum_SelectedIndexChanged);
            // 
            // lbPortName
            // 
            this.lbPortName.AutoSize = true;
            this.lbPortName.Location = new System.Drawing.Point(60, 34);
            this.lbPortName.Name = "lbPortName";
            this.lbPortName.Size = new System.Drawing.Size(173, 12);
            this.lbPortName.TabIndex = 0;
            this.lbPortName.Text = "串口选择(Select Serial Port)";
            // 
            // sSSerialPortInfo
            // 
            this.sSSerialPortInfo.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.TSSLState});
            this.sSSerialPortInfo.Location = new System.Drawing.Point(0, 528);
            this.sSSerialPortInfo.Name = "sSSerialPortInfo";
            this.sSSerialPortInfo.Size = new System.Drawing.Size(872, 22);
            this.sSSerialPortInfo.TabIndex = 1;
            this.sSSerialPortInfo.Text = "statusStrip1";
            // 
            // TSSLState
            // 
            this.TSSLState.Name = "TSSLState";
            this.TSSLState.Size = new System.Drawing.Size(60, 17);
            this.TSSLState.Text = "没有操作!";
            // 
            // SCIPort
            // 
            this.SCIPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SCIPort_DataReceived);
            // 
            // LblSCI
            // 
            this.LblSCI.AutoSize = true;
            this.LblSCI.Location = new System.Drawing.Point(369, 523);
            this.LblSCI.Name = "LblSCI";
            this.LblSCI.Size = new System.Drawing.Size(0, 12);
            this.LblSCI.TabIndex = 3;
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.Location = new System.Drawing.Point(4, 53);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(443, 292);
            this.zedGraphControl1.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "通道0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(220, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "通道3";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 66);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 8;
            this.label3.Text = "通道4";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(220, 69);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 12);
            this.label4.TabIndex = 9;
            this.label4.Text = "通道5";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(11, 103);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 12);
            this.label5.TabIndex = 10;
            this.label5.Text = "通道6";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(220, 103);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 12);
            this.label6.TabIndex = 11;
            this.label6.Text = "通道7";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(11, 142);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 12);
            this.label7.TabIndex = 12;
            this.label7.Text = "通道8";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(220, 142);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 12);
            this.label8.TabIndex = 13;
            this.label8.Text = "通道9";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(11, 175);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 12);
            this.label9.TabIndex = 14;
            this.label9.Text = "通道11";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(220, 178);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 12);
            this.label10.TabIndex = 15;
            this.label10.Text = "通道12";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(11, 212);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 12);
            this.label11.TabIndex = 16;
            this.label11.Text = "通道13";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(220, 212);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(41, 12);
            this.label12.TabIndex = 17;
            this.label12.Text = "通道14";
            // 
            // txtchannel0
            // 
            this.txtchannel0.Location = new System.Drawing.Point(63, 29);
            this.txtchannel0.Name = "txtchannel0";
            this.txtchannel0.Size = new System.Drawing.Size(100, 21);
            this.txtchannel0.TabIndex = 18;
            // 
            // txtchannel3
            // 
            this.txtchannel3.Location = new System.Drawing.Point(276, 29);
            this.txtchannel3.Name = "txtchannel3";
            this.txtchannel3.Size = new System.Drawing.Size(100, 21);
            this.txtchannel3.TabIndex = 19;
            // 
            // txtchannel4
            // 
            this.txtchannel4.Location = new System.Drawing.Point(63, 66);
            this.txtchannel4.Name = "txtchannel4";
            this.txtchannel4.Size = new System.Drawing.Size(100, 21);
            this.txtchannel4.TabIndex = 20;
            // 
            // txtchannel5
            // 
            this.txtchannel5.Location = new System.Drawing.Point(276, 63);
            this.txtchannel5.Name = "txtchannel5";
            this.txtchannel5.Size = new System.Drawing.Size(100, 21);
            this.txtchannel5.TabIndex = 21;
            // 
            // txtchannel6
            // 
            this.txtchannel6.Location = new System.Drawing.Point(63, 103);
            this.txtchannel6.Name = "txtchannel6";
            this.txtchannel6.Size = new System.Drawing.Size(100, 21);
            this.txtchannel6.TabIndex = 22;
            // 
            // txtchannel7
            // 
            this.txtchannel7.Location = new System.Drawing.Point(276, 100);
            this.txtchannel7.Name = "txtchannel7";
            this.txtchannel7.Size = new System.Drawing.Size(100, 21);
            this.txtchannel7.TabIndex = 23;
            // 
            // txtchannel8
            // 
            this.txtchannel8.Location = new System.Drawing.Point(63, 142);
            this.txtchannel8.Name = "txtchannel8";
            this.txtchannel8.Size = new System.Drawing.Size(100, 21);
            this.txtchannel8.TabIndex = 24;
            // 
            // txtchannel9
            // 
            this.txtchannel9.Location = new System.Drawing.Point(276, 139);
            this.txtchannel9.Name = "txtchannel9";
            this.txtchannel9.Size = new System.Drawing.Size(100, 21);
            this.txtchannel9.TabIndex = 25;
            // 
            // txtchannel11
            // 
            this.txtchannel11.Location = new System.Drawing.Point(63, 178);
            this.txtchannel11.Name = "txtchannel11";
            this.txtchannel11.Size = new System.Drawing.Size(100, 21);
            this.txtchannel11.TabIndex = 26;
            // 
            // txtchannel12
            // 
            this.txtchannel12.Location = new System.Drawing.Point(276, 175);
            this.txtchannel12.Name = "txtchannel12";
            this.txtchannel12.Size = new System.Drawing.Size(100, 21);
            this.txtchannel12.TabIndex = 27;
            // 
            // txtchannel13
            // 
            this.txtchannel13.Location = new System.Drawing.Point(63, 212);
            this.txtchannel13.Name = "txtchannel13";
            this.txtchannel13.Size = new System.Drawing.Size(100, 21);
            this.txtchannel13.TabIndex = 28;
            // 
            // txtchannel14
            // 
            this.txtchannel14.Location = new System.Drawing.Point(276, 209);
            this.txtchannel14.Name = "txtchannel14";
            this.txtchannel14.Size = new System.Drawing.Size(100, 21);
            this.txtchannel14.TabIndex = 29;
            // 
            // txtchannel15
            // 
            this.txtchannel15.Location = new System.Drawing.Point(63, 248);
            this.txtchannel15.Name = "txtchannel15";
            this.txtchannel15.Size = new System.Drawing.Size(100, 21);
            this.txtchannel15.TabIndex = 30;
            // 
            // txtchannel23
            // 
            this.txtchannel23.Location = new System.Drawing.Point(276, 248);
            this.txtchannel23.Name = "txtchannel23";
            this.txtchannel23.Size = new System.Drawing.Size(100, 21);
            this.txtchannel23.TabIndex = 31;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(11, 251);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(41, 12);
            this.label15.TabIndex = 37;
            this.label15.Text = "通道15";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(220, 251);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(41, 12);
            this.label16.TabIndex = 38;
            this.label16.Text = "通道23";
            // 
            // MUXSEL_A
            // 
            this.MUXSEL_A.Controls.Add(this.label16);
            this.MUXSEL_A.Controls.Add(this.label15);
            this.MUXSEL_A.Controls.Add(this.txtchannel23);
            this.MUXSEL_A.Controls.Add(this.txtchannel15);
            this.MUXSEL_A.Controls.Add(this.txtchannel14);
            this.MUXSEL_A.Controls.Add(this.txtchannel13);
            this.MUXSEL_A.Controls.Add(this.txtchannel12);
            this.MUXSEL_A.Controls.Add(this.txtchannel11);
            this.MUXSEL_A.Controls.Add(this.txtchannel9);
            this.MUXSEL_A.Controls.Add(this.txtchannel8);
            this.MUXSEL_A.Controls.Add(this.txtchannel7);
            this.MUXSEL_A.Controls.Add(this.txtchannel6);
            this.MUXSEL_A.Controls.Add(this.txtchannel5);
            this.MUXSEL_A.Controls.Add(this.txtchannel4);
            this.MUXSEL_A.Controls.Add(this.txtchannel3);
            this.MUXSEL_A.Controls.Add(this.txtchannel0);
            this.MUXSEL_A.Controls.Add(this.label12);
            this.MUXSEL_A.Controls.Add(this.label11);
            this.MUXSEL_A.Controls.Add(this.label10);
            this.MUXSEL_A.Controls.Add(this.label9);
            this.MUXSEL_A.Controls.Add(this.label8);
            this.MUXSEL_A.Controls.Add(this.label7);
            this.MUXSEL_A.Controls.Add(this.label6);
            this.MUXSEL_A.Controls.Add(this.label5);
            this.MUXSEL_A.Controls.Add(this.label4);
            this.MUXSEL_A.Controls.Add(this.label3);
            this.MUXSEL_A.Controls.Add(this.label2);
            this.MUXSEL_A.Controls.Add(this.label1);
            this.MUXSEL_A.ForeColor = System.Drawing.SystemColors.ControlText;
            this.MUXSEL_A.Location = new System.Drawing.Point(477, 100);
            this.MUXSEL_A.Name = "MUXSEL_A";
            this.MUXSEL_A.Size = new System.Drawing.Size(383, 287);
            this.MUXSEL_A.TabIndex = 39;
            this.MUXSEL_A.TabStop = false;
            this.MUXSEL_A.Text = "通道组A";
            // 
            // MUXSEL_B
            // 
            this.MUXSEL_B.Controls.Add(this.label18);
            this.MUXSEL_B.Controls.Add(this.label17);
            this.MUXSEL_B.Controls.Add(this.label14);
            this.MUXSEL_B.Controls.Add(this.label13);
            this.MUXSEL_B.Controls.Add(this.txtchannel7b);
            this.MUXSEL_B.Controls.Add(this.txtchannel5b);
            this.MUXSEL_B.Controls.Add(this.txtchannel6b);
            this.MUXSEL_B.Controls.Add(this.txtchannel4b);
            this.MUXSEL_B.Location = new System.Drawing.Point(477, 402);
            this.MUXSEL_B.Name = "MUXSEL_B";
            this.MUXSEL_B.Size = new System.Drawing.Size(383, 110);
            this.MUXSEL_B.TabIndex = 40;
            this.MUXSEL_B.TabStop = false;
            this.MUXSEL_B.Text = "通道组B";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(218, 63);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(35, 12);
            this.label18.TabIndex = 7;
            this.label18.Text = "通道7";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(7, 65);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(35, 12);
            this.label17.TabIndex = 6;
            this.label17.Text = "通道6";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(216, 29);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(35, 12);
            this.label14.TabIndex = 5;
            this.label14.Text = "通道5";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(7, 29);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(35, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "通道4";
            // 
            // txtchannel7b
            // 
            this.txtchannel7b.Location = new System.Drawing.Point(272, 62);
            this.txtchannel7b.Name = "txtchannel7b";
            this.txtchannel7b.Size = new System.Drawing.Size(100, 21);
            this.txtchannel7b.TabIndex = 3;
            // 
            // txtchannel5b
            // 
            this.txtchannel5b.Location = new System.Drawing.Point(272, 20);
            this.txtchannel5b.Name = "txtchannel5b";
            this.txtchannel5b.Size = new System.Drawing.Size(100, 21);
            this.txtchannel5b.TabIndex = 2;
            // 
            // txtchannel6b
            // 
            this.txtchannel6b.Location = new System.Drawing.Point(59, 62);
            this.txtchannel6b.Name = "txtchannel6b";
            this.txtchannel6b.Size = new System.Drawing.Size(100, 21);
            this.txtchannel6b.TabIndex = 1;
            // 
            // txtchannel4b
            // 
            this.txtchannel4b.Location = new System.Drawing.Point(59, 21);
            this.txtchannel4b.Name = "txtchannel4b";
            this.txtchannel4b.Size = new System.Drawing.Size(100, 21);
            this.txtchannel4b.TabIndex = 0;
            // 
            // temptureShow
            // 
            this.temptureShow.Controls.Add(this.zedGraphControl1);
            this.temptureShow.Location = new System.Drawing.Point(8, 100);
            this.temptureShow.Name = "temptureShow";
            this.temptureShow.Size = new System.Drawing.Size(461, 412);
            this.temptureShow.TabIndex = 41;
            this.temptureShow.TabStop = false;
            this.temptureShow.Text = "芯片温度";
            // 
            // FormSCI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(872, 550);
            this.Controls.Add(this.temptureShow);
            this.Controls.Add(this.MUXSEL_B);
            this.Controls.Add(this.MUXSEL_A);
            this.Controls.Add(this.LblSCI);
            this.Controls.Add(this.sSSerialPortInfo);
            this.Controls.Add(this.SetSerialPort);
            this.Name = "FormSCI";
            this.Text = "串口测试工程(苏州大学飞思卡尔嵌入式系统研究中心)";
            this.Load += new System.EventHandler(this.FormSCI_Load);
            this.SetSerialPort.ResumeLayout(false);
            this.SetSerialPort.PerformLayout();
            this.sSSerialPortInfo.ResumeLayout(false);
            this.sSSerialPortInfo.PerformLayout();
            this.MUXSEL_A.ResumeLayout(false);
            this.MUXSEL_A.PerformLayout();
            this.MUXSEL_B.ResumeLayout(false);
            this.MUXSEL_B.PerformLayout();
            this.temptureShow.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox SetSerialPort;
        private System.Windows.Forms.Button BtnSCISwitch;
        private System.Windows.Forms.ComboBox CbSCIComNum;
        private System.Windows.Forms.Label lbPortName;
        private System.Windows.Forms.StatusStrip sSSerialPortInfo;
        private System.Windows.Forms.ToolStripStatusLabel TSSLState;
        private System.IO.Ports.SerialPort SCIPort;
        private System.Windows.Forms.Label LblSCI;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox txtchannel0;
        private System.Windows.Forms.TextBox txtchannel3;
        private System.Windows.Forms.TextBox txtchannel4;
        private System.Windows.Forms.TextBox txtchannel5;
        private System.Windows.Forms.TextBox txtchannel6;
        private System.Windows.Forms.TextBox txtchannel7;
        private System.Windows.Forms.TextBox txtchannel8;
        private System.Windows.Forms.TextBox txtchannel9;
        private System.Windows.Forms.TextBox txtchannel11;
        private System.Windows.Forms.TextBox txtchannel12;
        private System.Windows.Forms.TextBox txtchannel13;
        private System.Windows.Forms.TextBox txtchannel14;
        private System.Windows.Forms.TextBox txtchannel15;
        private System.Windows.Forms.TextBox txtchannel23;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.GroupBox MUXSEL_A;
        private System.Windows.Forms.GroupBox MUXSEL_B;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox txtchannel7b;
        private System.Windows.Forms.TextBox txtchannel5b;
        private System.Windows.Forms.TextBox txtchannel6b;
        private System.Windows.Forms.TextBox txtchannel4b;
        private System.Windows.Forms.GroupBox temptureShow;

    }
}

