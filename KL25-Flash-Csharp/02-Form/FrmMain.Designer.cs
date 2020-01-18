namespace SerialPort
{
    partial class FrmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMain));
            this.btnCheckPcNode = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lbl_PC_Node_State = new System.Windows.Forms.Label();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.tbtail = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.tbfirst = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.tblen = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.tbhead = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.Txt_recv2 = new System.Windows.Forms.TextBox();
            this.Txt_recv1 = new System.Windows.Forms.TextBox();
            this.btnClear1 = new System.Windows.Forms.Button();
            this.tbSector3 = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.label38 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.tbCount2 = new System.Windows.Forms.TextBox();
            this.tbOffset2 = new System.Windows.Forms.TextBox();
            this.tbWriteData1 = new System.Windows.Forms.TextBox();
            this.tbSector2 = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.textBox15 = new System.Windows.Forms.TextBox();
            this.btnPnFlashWrite = new System.Windows.Forms.Button();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.btnPnFlashErase = new System.Windows.Forms.Button();
            this.textBox17 = new System.Windows.Forms.TextBox();
            this.btnPnFlashRead = new System.Windows.Forms.Button();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.label37 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.tbCount1 = new System.Windows.Forms.TextBox();
            this.tbOffset1 = new System.Windows.Forms.TextBox();
            this.tbSector1 = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.tbCountaddr = new System.Windows.Forms.TextBox();
            this.btnPnFlashReadAddr = new System.Windows.Forms.Button();
            this.tbAddr = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.tb_statue = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tbSectorprot = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnPnFlashProtect = new System.Windows.Forms.Button();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnCheckPcNode
            // 
            this.btnCheckPcNode.Location = new System.Drawing.Point(736, 17);
            this.btnCheckPcNode.Name = "btnCheckPcNode";
            this.btnCheckPcNode.Size = new System.Drawing.Size(135, 36);
            this.btnCheckPcNode.TabIndex = 0;
            this.btnCheckPcNode.Text = "检测KL25";
            this.btnCheckPcNode.UseVisualStyleBackColor = true;
            this.btnCheckPcNode.Click += new System.EventHandler(this.btnCheckPcNode_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.MenuBar;
            this.groupBox1.Controls.Add(this.lbl_PC_Node_State);
            this.groupBox1.Controls.Add(this.btnCheckPcNode);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.groupBox1.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(887, 59);
            this.groupBox1.TabIndex = 20;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "KL25节点状态";
            // 
            // lbl_PC_Node_State
            // 
            this.lbl_PC_Node_State.AutoSize = true;
            this.lbl_PC_Node_State.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_PC_Node_State.ForeColor = System.Drawing.Color.Blue;
            this.lbl_PC_Node_State.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.lbl_PC_Node_State.Location = new System.Drawing.Point(139, 26);
            this.lbl_PC_Node_State.Name = "lbl_PC_Node_State";
            this.lbl_PC_Node_State.Size = new System.Drawing.Size(163, 20);
            this.lbl_PC_Node_State.TabIndex = 1;
            this.lbl_PC_Node_State.Text = "lbl_KL25_State";
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.tbtail);
            this.groupBox7.Controls.Add(this.label11);
            this.groupBox7.Controls.Add(this.tbfirst);
            this.groupBox7.Controls.Add(this.label10);
            this.groupBox7.Controls.Add(this.tblen);
            this.groupBox7.Controls.Add(this.label8);
            this.groupBox7.Controls.Add(this.tbhead);
            this.groupBox7.Controls.Add(this.textBox2);
            this.groupBox7.Controls.Add(this.label4);
            this.groupBox7.Controls.Add(this.Txt_recv2);
            this.groupBox7.Controls.Add(this.Txt_recv1);
            this.groupBox7.Controls.Add(this.btnClear1);
            this.groupBox7.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox7.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox7.Location = new System.Drawing.Point(3, 474);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(874, 174);
            this.groupBox7.TabIndex = 27;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "串口接收信息";
            // 
            // tbtail
            // 
            this.tbtail.Location = new System.Drawing.Point(484, 95);
            this.tbtail.Name = "tbtail";
            this.tbtail.Size = new System.Drawing.Size(34, 26);
            this.tbtail.TabIndex = 36;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(438, 98);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(51, 19);
            this.label11.TabIndex = 35;
            this.label11.Text = "帧尾：";
            // 
            // tbfirst
            // 
            this.tbfirst.Location = new System.Drawing.Point(397, 95);
            this.tbfirst.Name = "tbfirst";
            this.tbfirst.Size = new System.Drawing.Size(34, 26);
            this.tbfirst.TabIndex = 34;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(308, 98);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(93, 19);
            this.label10.TabIndex = 33;
            this.label10.Text = "内容起始帧：";
            // 
            // tblen
            // 
            this.tblen.Location = new System.Drawing.Point(265, 95);
            this.tblen.Name = "tblen";
            this.tblen.Size = new System.Drawing.Size(34, 26);
            this.tblen.TabIndex = 32;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(218, 98);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(51, 19);
            this.label8.TabIndex = 31;
            this.label8.Text = "长度：";
            // 
            // tbhead
            // 
            this.tbhead.Location = new System.Drawing.Point(178, 95);
            this.tbhead.Name = "tbhead";
            this.tbhead.Size = new System.Drawing.Size(34, 26);
            this.tbhead.TabIndex = 30;
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox2.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox2.Location = new System.Drawing.Point(-7, 198);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox2.Size = new System.Drawing.Size(720, 26);
            this.textBox2.TabIndex = 25;
            this.textBox2.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 98);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(167, 19);
            this.label4.TabIndex = 29;
            this.label4.Text = "串口接收内容解析：帧头:";
            // 
            // Txt_recv2
            // 
            this.Txt_recv2.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.Txt_recv2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Txt_recv2.ForeColor = System.Drawing.Color.AliceBlue;
            this.Txt_recv2.Location = new System.Drawing.Point(5, 123);
            this.Txt_recv2.Multiline = true;
            this.Txt_recv2.Name = "Txt_recv2";
            this.Txt_recv2.ReadOnly = true;
            this.Txt_recv2.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.Txt_recv2.Size = new System.Drawing.Size(708, 48);
            this.Txt_recv2.TabIndex = 24;
            // 
            // Txt_recv1
            // 
            this.Txt_recv1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.Txt_recv1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Txt_recv1.ForeColor = System.Drawing.Color.AliceBlue;
            this.Txt_recv1.Location = new System.Drawing.Point(8, 25);
            this.Txt_recv1.Multiline = true;
            this.Txt_recv1.Name = "Txt_recv1";
            this.Txt_recv1.ReadOnly = true;
            this.Txt_recv1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.Txt_recv1.Size = new System.Drawing.Size(708, 55);
            this.Txt_recv1.TabIndex = 24;
            this.Txt_recv1.Text = "KL25-Csharp功能：\r\n接受PC机发送的指令，控制KL25 Flash的读、写、擦除、保护操作。";
            // 
            // btnClear1
            // 
            this.btnClear1.Location = new System.Drawing.Point(727, 123);
            this.btnClear1.Name = "btnClear1";
            this.btnClear1.Size = new System.Drawing.Size(141, 29);
            this.btnClear1.TabIndex = 21;
            this.btnClear1.Text = "清空显示框";
            this.btnClear1.UseVisualStyleBackColor = true;
            this.btnClear1.Click += new System.EventHandler(this.btnClear1_Click);
            // 
            // tbSector3
            // 
            this.tbSector3.Location = new System.Drawing.Point(83, 21);
            this.tbSector3.Name = "tbSector3";
            this.tbSector3.Size = new System.Drawing.Size(34, 23);
            this.tbSector3.TabIndex = 27;
            this.tbSector3.Text = "50";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(21, 27);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(56, 17);
            this.label12.TabIndex = 26;
            this.label12.Text = "扇区号：";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.label38);
            this.groupBox9.Controls.Add(this.label24);
            this.groupBox9.Controls.Add(this.label16);
            this.groupBox9.Controls.Add(this.tbCount2);
            this.groupBox9.Controls.Add(this.tbOffset2);
            this.groupBox9.Controls.Add(this.tbWriteData1);
            this.groupBox9.Controls.Add(this.tbSector2);
            this.groupBox9.Controls.Add(this.label18);
            this.groupBox9.Controls.Add(this.label19);
            this.groupBox9.Controls.Add(this.label21);
            this.groupBox9.Controls.Add(this.label22);
            this.groupBox9.Controls.Add(this.textBox15);
            this.groupBox9.Controls.Add(this.btnPnFlashWrite);
            this.groupBox9.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox9.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox9.Location = new System.Drawing.Point(8, 178);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(863, 101);
            this.groupBox9.TabIndex = 32;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Flash写测试";
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label38.ForeColor = System.Drawing.Color.Red;
            this.label38.Location = new System.Drawing.Point(355, 43);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(75, 19);
            this.label38.TabIndex = 31;
            this.label38.Text = "（1~56）";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label24.ForeColor = System.Drawing.Color.Red;
            this.label24.Location = new System.Drawing.Point(145, 43);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(200, 19);
            this.label24.TabIndex = 31;
            this.label24.Text = "（0~1023，须为4的整数倍）";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label16.ForeColor = System.Drawing.Color.Red;
            this.label16.Location = new System.Drawing.Point(17, 43);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(93, 19);
            this.label16.TabIndex = 28;
            this.label16.Text = "（30~127）";
            // 
            // tbCount2
            // 
            this.tbCount2.Location = new System.Drawing.Point(434, 20);
            this.tbCount2.Name = "tbCount2";
            this.tbCount2.Size = new System.Drawing.Size(39, 23);
            this.tbCount2.TabIndex = 24;
            this.tbCount2.Text = "30";
            // 
            // tbOffset2
            // 
            this.tbOffset2.Location = new System.Drawing.Point(213, 13);
            this.tbOffset2.Name = "tbOffset2";
            this.tbOffset2.Size = new System.Drawing.Size(46, 23);
            this.tbOffset2.TabIndex = 24;
            this.tbOffset2.Text = "0";
            // 
            // tbWriteData1
            // 
            this.tbWriteData1.Location = new System.Drawing.Point(85, 69);
            this.tbWriteData1.Name = "tbWriteData1";
            this.tbWriteData1.Size = new System.Drawing.Size(772, 23);
            this.tbWriteData1.TabIndex = 24;
            this.tbWriteData1.Text = "Welcome to Soochow University!";
            // 
            // tbSector2
            // 
            this.tbSector2.Location = new System.Drawing.Point(83, 17);
            this.tbSector2.Name = "tbSector2";
            this.tbSector2.Size = new System.Drawing.Size(34, 23);
            this.tbSector2.TabIndex = 24;
            this.tbSector2.Text = "50";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(360, 23);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(68, 17);
            this.label18.TabIndex = 23;
            this.label18.Text = "写字节数：";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(151, 19);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(56, 17);
            this.label19.TabIndex = 23;
            this.label19.Text = "偏移量：";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(13, 72);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(68, 17);
            this.label21.TabIndex = 23;
            this.label21.Text = "写入数据：";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(21, 19);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(56, 17);
            this.label22.TabIndex = 23;
            this.label22.Text = "扇区号：";
            // 
            // textBox15
            // 
            this.textBox15.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox15.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox15.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox15.Location = new System.Drawing.Point(6, 159);
            this.textBox15.Multiline = true;
            this.textBox15.Name = "textBox15";
            this.textBox15.ReadOnly = true;
            this.textBox15.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox15.Size = new System.Drawing.Size(648, 123);
            this.textBox15.TabIndex = 20;
            this.textBox15.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // btnPnFlashWrite
            // 
            this.btnPnFlashWrite.Location = new System.Drawing.Point(567, 14);
            this.btnPnFlashWrite.Name = "btnPnFlashWrite";
            this.btnPnFlashWrite.Size = new System.Drawing.Size(141, 29);
            this.btnPnFlashWrite.TabIndex = 22;
            this.btnPnFlashWrite.Text = "KL25 Flash写测试";
            this.btnPnFlashWrite.UseVisualStyleBackColor = true;
            this.btnPnFlashWrite.Click += new System.EventHandler(this.btnPnFlashWrite_Click);
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.label7);
            this.groupBox11.Controls.Add(this.tbSector3);
            this.groupBox11.Controls.Add(this.label12);
            this.groupBox11.Controls.Add(this.btnPnFlashErase);
            this.groupBox11.Controls.Add(this.textBox17);
            this.groupBox11.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox11.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox11.Location = new System.Drawing.Point(8, 280);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(863, 51);
            this.groupBox11.TabIndex = 33;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "Flash擦除测试";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.ForeColor = System.Drawing.Color.Red;
            this.label7.Location = new System.Drawing.Point(209, 25);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(93, 19);
            this.label7.TabIndex = 28;
            this.label7.Text = "（30~127）";
            // 
            // btnPnFlashErase
            // 
            this.btnPnFlashErase.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnPnFlashErase.Location = new System.Drawing.Point(567, 15);
            this.btnPnFlashErase.Name = "btnPnFlashErase";
            this.btnPnFlashErase.Size = new System.Drawing.Size(141, 29);
            this.btnPnFlashErase.TabIndex = 22;
            this.btnPnFlashErase.Text = "KL25 Flash擦除测试";
            this.btnPnFlashErase.UseVisualStyleBackColor = false;
            this.btnPnFlashErase.Click += new System.EventHandler(this.btnPnFlashErase_Click);
            // 
            // textBox17
            // 
            this.textBox17.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox17.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox17.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox17.Location = new System.Drawing.Point(6, 159);
            this.textBox17.Multiline = true;
            this.textBox17.Name = "textBox17";
            this.textBox17.ReadOnly = true;
            this.textBox17.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox17.Size = new System.Drawing.Size(648, 123);
            this.textBox17.TabIndex = 20;
            this.textBox17.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // btnPnFlashRead
            // 
            this.btnPnFlashRead.Location = new System.Drawing.Point(567, 22);
            this.btnPnFlashRead.Name = "btnPnFlashRead";
            this.btnPnFlashRead.Size = new System.Drawing.Size(141, 29);
            this.btnPnFlashRead.TabIndex = 22;
            this.btnPnFlashRead.Text = "读测试（逻辑地址）";
            this.btnPnFlashRead.UseVisualStyleBackColor = true;
            this.btnPnFlashRead.Click += new System.EventHandler(this.btnPnFlashRead_Click);
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.label37);
            this.groupBox8.Controls.Add(this.label23);
            this.groupBox8.Controls.Add(this.label20);
            this.groupBox8.Controls.Add(this.tbCount1);
            this.groupBox8.Controls.Add(this.tbOffset1);
            this.groupBox8.Controls.Add(this.btnPnFlashRead);
            this.groupBox8.Controls.Add(this.tbSector1);
            this.groupBox8.Controls.Add(this.label14);
            this.groupBox8.Controls.Add(this.label15);
            this.groupBox8.Controls.Add(this.label17);
            this.groupBox8.Controls.Add(this.textBox9);
            this.groupBox8.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox8.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox8.Location = new System.Drawing.Point(8, 21);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(863, 69);
            this.groupBox8.TabIndex = 31;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Flash读测试（逻辑地址）";
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label37.ForeColor = System.Drawing.Color.Red;
            this.label37.Location = new System.Drawing.Point(355, 43);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(75, 19);
            this.label37.TabIndex = 31;
            this.label37.Text = "（1~56）";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label23.ForeColor = System.Drawing.Color.Red;
            this.label23.Location = new System.Drawing.Point(145, 43);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(93, 19);
            this.label23.TabIndex = 31;
            this.label23.Text = "（0~1023）";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label20.ForeColor = System.Drawing.Color.Red;
            this.label20.Location = new System.Drawing.Point(17, 43);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(84, 19);
            this.label20.TabIndex = 28;
            this.label20.Text = "（0~127）";
            // 
            // tbCount1
            // 
            this.tbCount1.Location = new System.Drawing.Point(434, 14);
            this.tbCount1.Name = "tbCount1";
            this.tbCount1.Size = new System.Drawing.Size(39, 23);
            this.tbCount1.TabIndex = 24;
            this.tbCount1.Text = "30";
            // 
            // tbOffset1
            // 
            this.tbOffset1.Location = new System.Drawing.Point(213, 17);
            this.tbOffset1.Name = "tbOffset1";
            this.tbOffset1.Size = new System.Drawing.Size(46, 23);
            this.tbOffset1.TabIndex = 24;
            this.tbOffset1.Text = "0";
            // 
            // tbSector1
            // 
            this.tbSector1.Location = new System.Drawing.Point(83, 17);
            this.tbSector1.Name = "tbSector1";
            this.tbSector1.Size = new System.Drawing.Size(34, 23);
            this.tbSector1.TabIndex = 24;
            this.tbSector1.Text = "50";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(360, 17);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(68, 17);
            this.label14.TabIndex = 23;
            this.label14.Text = "读字节数：";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(151, 21);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(56, 17);
            this.label15.TabIndex = 23;
            this.label15.Text = "偏移量：";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(21, 20);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(56, 17);
            this.label17.TabIndex = 23;
            this.label17.Text = "扇区号：";
            // 
            // textBox9
            // 
            this.textBox9.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox9.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox9.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox9.Location = new System.Drawing.Point(6, 159);
            this.textBox9.Multiline = true;
            this.textBox9.Name = "textBox9";
            this.textBox9.ReadOnly = true;
            this.textBox9.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox9.Size = new System.Drawing.Size(648, 123);
            this.textBox9.TabIndex = 20;
            this.textBox9.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox4);
            this.groupBox3.Controls.Add(this.groupBox9);
            this.groupBox3.Controls.Add(this.groupBox11);
            this.groupBox3.Controls.Add(this.groupBox8);
            this.groupBox3.Font = new System.Drawing.Font("微软雅黑", 8F, System.Drawing.FontStyle.Bold);
            this.groupBox3.Location = new System.Drawing.Point(3, 60);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(874, 410);
            this.groupBox3.TabIndex = 35;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "测试类型选择";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.label5);
            this.groupBox4.Controls.Add(this.tbCountaddr);
            this.groupBox4.Controls.Add(this.btnPnFlashReadAddr);
            this.groupBox4.Controls.Add(this.tbAddr);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Controls.Add(this.textBox6);
            this.groupBox4.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox4.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox4.Location = new System.Drawing.Point(6, 100);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(863, 69);
            this.groupBox4.TabIndex = 34;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Flash读测试（物理地址）";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.ForeColor = System.Drawing.Color.Red;
            this.label3.Location = new System.Drawing.Point(355, 43);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 19);
            this.label3.TabIndex = 31;
            this.label3.Text = "（1~56）";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.ForeColor = System.Drawing.Color.Red;
            this.label5.Location = new System.Drawing.Point(17, 43);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(283, 19);
            this.label5.TabIndex = 28;
            this.label5.Text = "（RAM：0x1FFF_F000 - 0x2000_2FFF）";
            // 
            // tbCountaddr
            // 
            this.tbCountaddr.Location = new System.Drawing.Point(434, 14);
            this.tbCountaddr.Name = "tbCountaddr";
            this.tbCountaddr.Size = new System.Drawing.Size(39, 23);
            this.tbCountaddr.TabIndex = 24;
            this.tbCountaddr.Text = "1";
            // 
            // btnPnFlashReadAddr
            // 
            this.btnPnFlashReadAddr.Location = new System.Drawing.Point(567, 22);
            this.btnPnFlashReadAddr.Name = "btnPnFlashReadAddr";
            this.btnPnFlashReadAddr.Size = new System.Drawing.Size(141, 29);
            this.btnPnFlashReadAddr.TabIndex = 22;
            this.btnPnFlashReadAddr.Text = "读测试（物理地址）";
            this.btnPnFlashReadAddr.UseVisualStyleBackColor = true;
            this.btnPnFlashReadAddr.Click += new System.EventHandler(this.btnPnFlashReadAddr_Click);
            // 
            // tbAddr
            // 
            this.tbAddr.Location = new System.Drawing.Point(83, 17);
            this.tbAddr.Name = "tbAddr";
            this.tbAddr.Size = new System.Drawing.Size(126, 23);
            this.tbAddr.TabIndex = 24;
            this.tbAddr.Text = "0x1FFFF0A0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(360, 17);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(68, 17);
            this.label6.TabIndex = 23;
            this.label6.Text = "读字节数：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(21, 20);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(68, 17);
            this.label9.TabIndex = 23;
            this.label9.Text = "物理地址：";
            // 
            // textBox6
            // 
            this.textBox6.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox6.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox6.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox6.Location = new System.Drawing.Point(6, 159);
            this.textBox6.Multiline = true;
            this.textBox6.Name = "textBox6";
            this.textBox6.ReadOnly = true;
            this.textBox6.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox6.Size = new System.Drawing.Size(648, 123);
            this.textBox6.TabIndex = 20;
            this.textBox6.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // tb_statue
            // 
            this.tb_statue.Location = new System.Drawing.Point(3, 652);
            this.tb_statue.Name = "tb_statue";
            this.tb_statue.Size = new System.Drawing.Size(874, 21);
            this.tb_statue.TabIndex = 26;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.tbSectorprot);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.btnPnFlashProtect);
            this.groupBox2.Controls.Add(this.textBox3);
            this.groupBox2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.ForeColor = System.Drawing.SystemColors.Highlight;
            this.groupBox2.Location = new System.Drawing.Point(12, 399);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(863, 51);
            this.groupBox2.TabIndex = 36;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Flash保护测试";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(209, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(288, 19);
            this.label1.TabIndex = 28;
            this.label1.Text = "（0~31，实际保护扇区号为N*4~N*4+3）";
            // 
            // tbSectorprot
            // 
            this.tbSectorprot.Location = new System.Drawing.Point(83, 21);
            this.tbSectorprot.Name = "tbSectorprot";
            this.tbSectorprot.Size = new System.Drawing.Size(34, 23);
            this.tbSectorprot.TabIndex = 27;
            this.tbSectorprot.Text = "12";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(21, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 17);
            this.label2.TabIndex = 26;
            this.label2.Text = "区域号：";
            // 
            // btnPnFlashProtect
            // 
            this.btnPnFlashProtect.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnPnFlashProtect.Location = new System.Drawing.Point(567, 15);
            this.btnPnFlashProtect.Name = "btnPnFlashProtect";
            this.btnPnFlashProtect.Size = new System.Drawing.Size(141, 29);
            this.btnPnFlashProtect.TabIndex = 22;
            this.btnPnFlashProtect.Text = "KL25 Flash保护测试";
            this.btnPnFlashProtect.UseVisualStyleBackColor = false;
            this.btnPnFlashProtect.Click += new System.EventHandler(this.btnPnFlashProtect_Click);
            // 
            // textBox3
            // 
            this.textBox3.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.textBox3.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox3.ForeColor = System.Drawing.Color.AliceBlue;
            this.textBox3.Location = new System.Drawing.Point(6, 159);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox3.Size = new System.Drawing.Size(648, 123);
            this.textBox3.TabIndex = 20;
            this.textBox3.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(887, 685);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.tb_statue);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox3);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FrmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "KL25Flash测试软件(KL25-Csharp)-20160511(苏州大学嵌入式中心) ";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FrmMain_FormClosing);
            this.Load += new System.EventHandler(this.FrmMain_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCheckPcNode;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lbl_PC_Node_State;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox Txt_recv1;
        private System.Windows.Forms.Button btnClear1;
        private System.Windows.Forms.TextBox tbSector3;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Label label38;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox tbCount2;
        private System.Windows.Forms.TextBox tbOffset2;
        private System.Windows.Forms.TextBox tbWriteData1;
        private System.Windows.Forms.TextBox tbSector2;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.TextBox textBox15;
        private System.Windows.Forms.Button btnPnFlashWrite;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox17;
        private System.Windows.Forms.Button btnPnFlashRead;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox tbCount1;
        private System.Windows.Forms.TextBox tbOffset1;
        private System.Windows.Forms.TextBox tbSector1;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.Button btnPnFlashErase;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox Txt_recv2;
        private System.Windows.Forms.TextBox tb_statue;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbSectorprot;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnPnFlashProtect;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tbCountaddr;
        private System.Windows.Forms.Button btnPnFlashReadAddr;
        private System.Windows.Forms.TextBox tbAddr;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.TextBox tbtail;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox tbfirst;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox tblen;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox tbhead;
        private System.Windows.Forms.Label label4;

    }
}

