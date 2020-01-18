namespace USBTest
{
    partial class USBTest
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(USBTest));
            this.label1 = new System.Windows.Forms.Label();
            this.txtSend = new System.Windows.Forms.TextBox();
            this.txtRecv = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnSend = new System.Windows.Forms.Button();
            this.btnClearRecvText = new System.Windows.Forms.Button();
            this.sSUSBInfo = new System.Windows.Forms.StatusStrip();
            this.TSSLState = new System.Windows.Forms.ToolStripStatusLabel();
            this.txtEnumerationMsg = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnRecv = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.cboUSBDevices = new System.Windows.Forms.ComboBox();
            this.txtUSBInfo = new System.Windows.Forms.TreeView();
            this.sSUSBInfo.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(9, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 14);
            this.label1.TabIndex = 0;
            this.label1.Text = "发送框：";
            // 
            // txtSend
            // 
            this.txtSend.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtSend.Location = new System.Drawing.Point(6, 58);
            this.txtSend.MaxLength = 31;
            this.txtSend.Multiline = true;
            this.txtSend.Name = "txtSend";
            this.txtSend.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtSend.Size = new System.Drawing.Size(226, 130);
            this.txtSend.TabIndex = 0;
            // 
            // txtRecv
            // 
            this.txtRecv.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.txtRecv.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtRecv.Location = new System.Drawing.Point(12, 231);
            this.txtRecv.Multiline = true;
            this.txtRecv.Name = "txtRecv";
            this.txtRecv.ReadOnly = true;
            this.txtRecv.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtRecv.Size = new System.Drawing.Size(220, 130);
            this.txtRecv.TabIndex = 3;
            this.txtRecv.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(9, 201);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 14);
            this.label2.TabIndex = 2;
            this.label2.Text = "接收框：";
            // 
            // btnSend
            // 
            this.btnSend.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnSend.Location = new System.Drawing.Point(238, 104);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(50, 30);
            this.btnSend.TabIndex = 4;
            this.btnSend.Text = "发送";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // btnClearRecvText
            // 
            this.btnClearRecvText.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnClearRecvText.Location = new System.Drawing.Point(238, 312);
            this.btnClearRecvText.Name = "btnClearRecvText";
            this.btnClearRecvText.Size = new System.Drawing.Size(50, 30);
            this.btnClearRecvText.TabIndex = 5;
            this.btnClearRecvText.Text = "清空";
            this.btnClearRecvText.UseVisualStyleBackColor = true;
            this.btnClearRecvText.Click += new System.EventHandler(this.btnClearRecvText_Click);
            // 
            // sSUSBInfo
            // 
            this.sSUSBInfo.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.TSSLState});
            this.sSUSBInfo.Location = new System.Drawing.Point(0, 472);
            this.sSUSBInfo.Name = "sSUSBInfo";
            this.sSUSBInfo.Size = new System.Drawing.Size(716, 22);
            this.sSUSBInfo.TabIndex = 7;
            this.sSUSBInfo.Text = "statusStrip1";
            // 
            // TSSLState
            // 
            this.TSSLState.Name = "TSSLState";
            this.TSSLState.Size = new System.Drawing.Size(56, 17);
            this.TSSLState.Text = "没有操作";
            // 
            // txtEnumerationMsg
            // 
            this.txtEnumerationMsg.Cursor = System.Windows.Forms.Cursors.Default;
            this.txtEnumerationMsg.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtEnumerationMsg.Location = new System.Drawing.Point(25, 22);
            this.txtEnumerationMsg.Multiline = true;
            this.txtEnumerationMsg.Name = "txtEnumerationMsg";
            this.txtEnumerationMsg.ReadOnly = true;
            this.txtEnumerationMsg.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtEnumerationMsg.Size = new System.Drawing.Size(346, 136);
            this.txtEnumerationMsg.TabIndex = 8;
            this.txtEnumerationMsg.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.ForeColor = System.Drawing.Color.Red;
            this.label3.Location = new System.Drawing.Point(262, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(134, 21);
            this.label3.TabIndex = 9;
            this.label3.Text = "USB测试程序";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtEnumerationMsg);
            this.groupBox1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(12, 46);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(377, 167);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "系统USB设备信息";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnRecv);
            this.groupBox2.Controls.Add(this.txtSend);
            this.groupBox2.Controls.Add(this.txtRecv);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.btnSend);
            this.groupBox2.Controls.Add(this.btnClearRecvText);
            this.groupBox2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.Location = new System.Drawing.Point(405, 46);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(299, 407);
            this.groupBox2.TabIndex = 11;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "操作区";
            // 
            // btnRecv
            // 
            this.btnRecv.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnRecv.Location = new System.Drawing.Point(238, 260);
            this.btnRecv.Name = "btnRecv";
            this.btnRecv.Size = new System.Drawing.Size(50, 30);
            this.btnRecv.TabIndex = 6;
            this.btnRecv.Text = "接收";
            this.btnRecv.UseVisualStyleBackColor = true;
            this.btnRecv.Click += new System.EventHandler(this.btnRecv_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.cboUSBDevices);
            this.groupBox3.Controls.Add(this.txtUSBInfo);
            this.groupBox3.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox3.Location = new System.Drawing.Point(12, 219);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(377, 234);
            this.groupBox3.TabIndex = 12;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "USB设备选择";
            // 
            // cboUSBDevices
            // 
            this.cboUSBDevices.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboUSBDevices.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cboUSBDevices.FormattingEnabled = true;
            this.cboUSBDevices.Location = new System.Drawing.Point(6, 27);
            this.cboUSBDevices.Name = "cboUSBDevices";
            this.cboUSBDevices.Size = new System.Drawing.Size(365, 20);
            this.cboUSBDevices.TabIndex = 1;
            this.cboUSBDevices.SelectedIndexChanged += new System.EventHandler(this.cboUSBDevices_SelectedIndexChanged);
            // 
            // txtUSBInfo
            // 
            this.txtUSBInfo.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtUSBInfo.Location = new System.Drawing.Point(6, 65);
            this.txtUSBInfo.Name = "txtUSBInfo";
            this.txtUSBInfo.Size = new System.Drawing.Size(365, 162);
            this.txtUSBInfo.TabIndex = 0;
            // 
            // USBTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(716, 494);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.sSUSBInfo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "USBTest";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "USBTest V2.0(C#2016)  苏州大学恩智浦嵌入式中心 20160520";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.USBTest_FormClosed);
            this.Load += new System.EventHandler(this.USBTest_Load);
            this.sSUSBInfo.ResumeLayout(false);
            this.sSUSBInfo.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtSend;
        private System.Windows.Forms.TextBox txtRecv;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.Button btnClearRecvText;
        private System.Windows.Forms.StatusStrip sSUSBInfo;
        private System.Windows.Forms.ToolStripStatusLabel TSSLState;
        private System.Windows.Forms.TextBox txtEnumerationMsg;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox cboUSBDevices;
        private System.Windows.Forms.TreeView txtUSBInfo;
        private System.Windows.Forms.Button btnRecv;
    }
}

