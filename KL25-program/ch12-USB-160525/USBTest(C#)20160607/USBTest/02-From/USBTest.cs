using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using USBComponent;
using Function;
using LibUsbDotNet;
using LibUsbDotNet.Info;
using LibUsbDotNet.Main;
using LibUsbDotNet.DeviceNotify;
using LibUsbDotNet.LibUsb;

namespace USBTest
{
    public partial class USBTest : Form
    {

        //设备序列号数组，如需在软件中识别该设备，序列号加入本数组即可
        string[] mySerialStringArray = { "HWW_USA","HWW_USB","" };
        
        int usbDeviceNumber;            //满足条件usb设备数量
        UsbRegistry[] usbRegDeviceArray;//系统中usb设备注册信息数组
        USB usb;

        ///-----------------------------------------------------------------
        ///函数名:USBTest
        ///功  能:类构造函数，创建类实例时调用
        ///参  数:无
        ///返  回:无需填写类型，会返回USBTest的一个实例
        ///-----------------------------------------------------------------
        public USBTest()
        {
            InitializeComponent();

            usbDeviceNumber = 0;
            usbRegDeviceArray = null;
            usb = null;
            USB.UsbDeviceNotifier.OnDeviceNotify += OnDeviceNotifyEvent;
        }

        ///-----------------------------------------------------------------
        ///函数名:USBTest_Load
        ///功  能:窗体USBTest加载时自动执行，用于刷新设备及下拉列表
        ///对  象:USBTest                                                
        ///事  件:Load                                           
        ///参  数:(1)sender：Object类型,触发事件的对象            
        ///       (2)e：EventArgs类型
        ///返  回:无  
        ///-----------------------------------------------------------------
        private void USBTest_Load(object sender, EventArgs e)
        {
            refreshUSBDevicesList();
        }

        ///-----------------------------------------------------------------
        ///函数名:btnSend_Click
        ///功  能:单击btnSend按钮时，发送接收数据指令
        ///对  象:btnSend                                                
        ///事  件:Click                                           
        ///参  数:(1)sender：Object类型,触发事件的对象            
        ///       (2)e：EventArgs类型
        ///返  回:无  
        ///-----------------------------------------------------------------
        private void btnSend_Click(object sender, EventArgs e)
        {
            bool flag;
            byte[] sendData=new byte[32];

            this.TSSLState.Text = "过程提示: 执行发送数据...";

            try
            {
                sendData[0] = (byte) PublicProperty.eCmd.cmdOUTTESTDATA;

                byte[] tempArray = System.Text.Encoding.Default.GetBytes(txtSend.Text);
                int tempArrayLen = tempArray.Length;
                for (int i = 0; i < tempArrayLen; i++)
                {
                    sendData[i + PublicProperty.FRAMEHEADLENGTH] = tempArray[i];
                }

                    //发送数据
                flag = usb.sendData(sendData, tempArrayLen + PublicProperty.FRAMEHEADLENGTH);
                //判断是否发送成功
                if (flag == true)
                    this.TSSLState.Text += "数据发送成功!";
                else
                    this.TSSLState.Text += "数据发送失败!";
            }
            catch (Exception ex)
            {
                this.TSSLState.Text += "数据发送异常!";
                Console.WriteLine(ex.ToString());
            }
        }

        ///-----------------------------------------------------------------
        ///函数名:btnRecv_Click
        ///功  能:单击btnRecv按钮时，发送接收数据指令
        ///对  象:btnRecv                                                
        ///事  件:Click                                           
        ///参  数:(1)sender：Object类型,触发事件的对象            
        ///       (2)e：EventArgs类型
        ///返  回:无  
        ///-----------------------------------------------------------------
        private void btnRecv_Click(object sender, EventArgs e)
        {
            bool flag;

            this.TSSLState.Text = "过程提示: 执行发送获取数据命令...";
            try
            {
                //发送数据
                flag = usb.sendData((byte)PublicProperty.eCmd.cmdINTESTDATA);
                txtRecv.Text = "";
                //flag = usb.sendData(0xAA);
                //判断是否发送成功
                if (flag == true)
                    this.TSSLState.Text = "获取数据命令发送成功!";
                else
                    this.TSSLState.Text = "获取数据命令发送失败!";
            }
            catch (Exception ex)
            {
                this.TSSLState.Text = "发送获取命令异常!";
                Console.WriteLine(ex.ToString());
            }
        }

        ///-----------------------------------------------------------------
        ///函数名:btnClearRecvText_Click
        ///功  能:单击btnClearRecvText按钮时，清空txtRecv文本框
        ///对  象:btnClearRecvText                                                
        ///事  件:Click                                           
        ///参  数:(1)sender：Object类型,触发事件的对象            
        ///       (2)e：EventArgs类型
        ///返  回:无                                            
        ///-----------------------------------------------------------------
        private void btnClearRecvText_Click(object sender, EventArgs e)
        {
            txtRecv.Clear();//清空接收框txtRecv数据
        }

        ///-----------------------------------------------------------------
        ///函数名:USBTest_FormClosed
        ///功  能:关闭窗体USBTest时触发
        ///对  象:USBTest
        ///事  件:FormClosed  
        ///参  数:(1)sender：Object类型,触发事件的对象            
        ///       (2)e：FormClosedEventArgs类型
        ///返  回:无                                            
        ///-----------------------------------------------------------------
        private void USBTest_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                usb.reader.DataReceived -= OnRxEndPointData;
                usb.reader.DataReceivedEnabled = false;
                usb.CloseUSB();//关闭USB设备
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        ///-----------------------------------------------------------------
        ///函数名:cboUSBDevices_SelectedIndexChanged
        ///功  能:当下拉列表cboUSBDevices的SelectedIndex值改变时调用此函数 
        ///对  象:cboUSBDevices
        ///事  件:SelectedIndexChanged    
        ///参  数:(1)sender：Object类型,触发事件的对象            
        ///       (2)e：EventArgs类型
        ///返  回:无                                            
        ///-----------------------------------------------------------------
        private void cboUSBDevices_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine("下拉列表选择事件发生");
            if (cboUSBDevices.SelectedIndex >= 0)
            {
                if (usb != null) 
                {
                    usb.CloseUSB();
                }

                //将usb初始化为选中对象
                usb = new USB(usbRegDeviceArray[cboUSBDevices.SelectedIndex]);
                //使能节点接收中断，并设置接收处理函数
                usb.reader.DataReceivedEnabled = true;
                usb.reader.DataReceived += this.OnRxEndPointData;

                txtUSBInfo.Nodes.Clear();
                showUSBDeviceInfo();
            }
        }
        ///-----------------------------------------------------------------
        ///函数名:OnDeviceNotifyEvent       
        ///功  能:判断是否是指定设备，USB设备插入移除时触发
        ///对  象：USB.UsbDeviceNotifier
        ///事  件：USB.UsbDeviceNotifier.OnDeviceNotify
        ///参  数:(1)sender：Object类型,触发事件的对象            
        ///       (2)e：DeviceNotifyEventArgs类型，包含设备信息                    
        ///返  回:无                                                       
        ///-----------------------------------------------------------------
        private void OnDeviceNotifyEvent(object sender, DeviceNotifyEventArgs e)
        {
            string msg = "";
            try
            {
                //判断是否插入设备
                if (e.EventType == EventType.DeviceArrival)
                {
                    Console.WriteLine("有新USB设备插入。");
                    //看看目前新连接的USB设备是不是目标设备
                    if (PublicProperty.myVID == e.Device.IdVendor && PublicProperty.myPID == e.Device.IdProduct) 
                    {
                        Console.WriteLine(e.Device.IdProduct + "  " + e.Device.IdVendor + "  " 
                            + e.Device.SerialNumber);
                        msg = "插入USB设备是目标设备，已加入下拉列表中。";
                        refreshUSBDevicesList();
                    }
                    else
                    {
                        msg = "插入USB设备不是目标设备";
                    }
                }
                else if (e.EventType == EventType.DeviceRemoveComplete)
                {
                    Console.WriteLine("有USB设备移除。");
                    //看看目前移除的USB设备是不是目标设备
                    if (PublicProperty.myVID == e.Device.IdVendor && PublicProperty.myPID == e.Device.IdProduct)
                    {
                        //删除usb注册事件
                        usb.reader.DataReceived -= OnRxEndPointData;
                        usb.reader.DataReceivedEnabled = false;
                        usb.CloseUSB();//关闭USB设备
                        usb = null;
                        msg = "移除的USB设备是目标设备,已从下拉列表中移除";
                        refreshUSBDevicesList();
                    }
                    else
                    {
                        msg = "移除的USB设备不是目标设备";
                    }
                }
                this.TSSLState.Text = msg;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        ///-----------------------------------------------------------------
        ///函数名:OnRxEndPointData       
        ///功  能:接收缓冲区数据,USB接收缓冲区有内容时触发
        ///对  象：usb.reader
        ///事  件：usb.reader.DataReceived
        ///参  数:(1)sender：Object类型，触发事件的对象            
        ///       (2)e：EndpointDataEventArgs类型，包含缓冲区数据                    
        ///返  回:无                                                       
        ///-----------------------------------------------------------------
        private void OnRxEndPointData(object sender, EndpointDataEventArgs e)
        {

            int recvBufferCount = e.Count;//获取数据长度
            byte[] frameData;//重定义数组
            byte frameHead;
            int frameDataLen;

            if (recvBufferCount < 1)//当长度小于1直接返回
                return;
            try
            {
                this.TSSLState.Text = "正在接收数据....";

                frameHead = e.Buffer[0];
                frameDataLen = recvBufferCount - PublicProperty.FRAMEHEADLENGTH;

                Console.WriteLine("接收中断发生！,帧头：" + frameHead);

                Console.WriteLine("帧数据长度：" + recvBufferCount);
                frameData = new byte[frameDataLen];

                for (int i = 0; i < frameDataLen; i++)
                {
                    frameData[i] = e.Buffer[i + PublicProperty.FRAMEHEADLENGTH];//接收数据到数组recDataBuff
                    Console.Write(frameData[i] + " - ");
                }
                Console.WriteLine("");

                switch (frameHead){
                    case (byte) PublicProperty.eCmd.cmdINTESTDATA:
                        setControl(this.txtRecv, 1, false, Encoding.Default.GetString(frameData));
                        break;
                    default:
                        break;
                }

                this.TSSLState.Text += "接收数据成功!";
                //注销reader.DataReceived事件处理过程，否则会不停触发中断，并调用处理函数
                //usb.reader.DataReceived -= OnRxEndPointData;
                //usb.reader.DataReceivedEnabled = false;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());

            }
        }

        ///-----------------------------------------------------------------
        /// 函数名:refreshUSBDevicesList    
        /// 功  能: 刷新下拉列表及设备数组内容
        /// 参  数:无                   
        /// 返  回:无                                                       
        ///-----------------------------------------------------------------
        private void refreshUSBDevicesList()
        {
            //注销下拉列表事件，避免出现程序异常
            cboUSBDevices.SelectedIndexChanged -= cboUSBDevices_SelectedIndexChanged;
            cboUSBDevices.SelectedIndex = -1;
            cboUSBDevices.Sorted = false;
            cboUSBDevices.Items.Clear();

            //获取目前系统中全部目标设备列表，然后进行判断
            UsbRegDeviceList usbRegDeviceList = USB.getUsbRegDeviceList();

            Console.WriteLine("符合VID和PID字段设备数量："+usbRegDeviceList.Count);
            
            usbRegDeviceArray = new UsbRegistry[usbRegDeviceList.Count];//用以保存符合条件的设备注册信息
            usbDeviceNumber = 0;

            foreach (UsbRegistry deviceRegistry in usbRegDeviceList)
            {
                string usbDevInfo = string.Format("Vid:0x{0:X4} Pid:0x{1:X4}",
                                            deviceRegistry.Vid,
                                            deviceRegistry.Pid) + " SerialString:" + 
                                            deviceRegistry.Device.Info.SerialString;

                Console.WriteLine(deviceRegistry.Device.Info.SerialString);

                if (Array.IndexOf(mySerialStringArray, deviceRegistry.Device.Info.SerialString) >= 0) 
                {
                    usbRegDeviceArray[usbDeviceNumber] = deviceRegistry;
                    usbDeviceNumber++;

                    cboUSBDevices.Items.Add(usbDevInfo);//将该设备加入下拉列表中
                    usbDevInfo = " ----------------------------------------------\n" + usbDevInfo;
                    usbDevInfo += " CurrentCultureLangID:" + deviceRegistry.Device.Info.CurrentCultureLangID + "\n";
                    usbDevInfo += " Descriptor:" + deviceRegistry.Device.Info.Descriptor + "\n";
                    usbDevInfo += " ManufacturerString:" + deviceRegistry.Device.Info.ManufacturerString + "\n";
                    usbDevInfo += " ProductString:" + deviceRegistry.Device.Info.ProductString + "\n";
                    usbDevInfo += " ----------------------------------------------\n";

                    setControl(this.txtEnumerationMsg, 1, true, usbDevInfo);
                }
            }

            setControl(this.txtEnumerationMsg, 1, true, "已连接的设备:" + usbDeviceNumber);
            //重新注册下拉列表事件
            cboUSBDevices.SelectedIndexChanged += cboUSBDevices_SelectedIndexChanged;

            if (usbDeviceNumber == 0)
            {
                txtUSBInfo.Nodes.Clear();
                txtUSBInfo.Nodes.Add("没有找到USB设备.");
            }
            else
            {
                this.cboUSBDevices.SelectedIndex = 0;
            }
        }

        ///-----------------------------------------------------------------
        /// 函数名:showUSBDeviceInfo     
        /// 功  能: 显示目前打开的USB设备信息 
        /// 参  数:无                  
        /// 返  回:无                                                       
        ///-----------------------------------------------------------------
        private void showUSBDeviceInfo()
        {
            TreeNode tvDevice = txtUSBInfo.Nodes.Add("设备描述符");
            string[] sDeviceAdd = usb.myUsbDevice.Info.ToString().Split(new char[] { '\r', '\n' },
                StringSplitOptions.RemoveEmptyEntries);
            foreach (string s in sDeviceAdd)
                tvDevice.Nodes.Add(s);

            foreach (UsbConfigInfo cfgInfo in usb.myUsbDevice.Configs)
            {
                TreeNode tvConfig = tvDevice.Nodes.Add("配置描述符 " + cfgInfo.Descriptor.ConfigID);
                string[] sCfgAdd = cfgInfo.ToString().Split(new char[] { '\r', '\n' }, 
                    StringSplitOptions.RemoveEmptyEntries);
                foreach (string s in sCfgAdd)
                    tvConfig.Nodes.Add(s);

                TreeNode tvInterfaces = tvConfig; //.Nodes.Add("Interfaces");
                foreach (UsbInterfaceInfo interfaceInfo in cfgInfo.InterfaceInfoList)
                {
                    TreeNode tvInterface =
                        tvInterfaces.Nodes.Add("接口描述符[" + interfaceInfo.Descriptor.InterfaceID + "," 
                        + interfaceInfo.Descriptor.AlternateID + "]");
                    string[] sInterfaceAdd = interfaceInfo.ToString().Split(new char[] { '\r', '\n' }, 
                        StringSplitOptions.RemoveEmptyEntries);
                    foreach (string s in sInterfaceAdd)
                        tvInterface.Nodes.Add(s);

                    TreeNode tvEndpoints = tvInterface; //.Nodes.Add("Endpoints");
                    foreach (UsbEndpointInfo endpointInfo in interfaceInfo.EndpointInfoList)
                    {
                        TreeNode tvEndpoint = tvEndpoints.Nodes.Add("端口0x" + 
                            (endpointInfo.Descriptor.EndpointID).ToString("X2"));
                        string[] sEndpointAdd = endpointInfo.ToString().Split(new char[] { '\r', '\n' }, 
                            StringSplitOptions.RemoveEmptyEntries);
                        foreach (string s in sEndpointAdd)
                            tvEndpoint.Nodes.Add(s);
                    }
                }
            }
            tvDevice.Expand();
        }

        //声明委托：用于跨越线程设置文本框等控件的内容
        public delegate void SetControlDelegate(Control control, int type, bool
            append, string text);

        ///-----------------------------------------------------------------
        /// 函数名:setControl 
        /// 功  能:设置控件内容
        /// 参  数：(1)control:控件名
        ///         (2)type：控件的类型0--Control，1--TextBox
        ///         (3)append：是追加还是赋值 true-表示追加，false-表示赋值
        ///         (4)text：字符串
        /// 返  回：无
        ///-----------------------------------------------------------------
        private void setControl(Control control, int type, bool append, string text)
        {
            //如果调用方位于创建该控件线程以外的线程时，需要获取是否要调用Invoke方法
            if (this.InvokeRequired)
            {
                SetControlDelegate setControlDelegateInstance = new SetControlDelegate
                    (setControl);
                this.Invoke(setControlDelegateInstance,
                    new object[] { control, type, append, text });
            }
            else //如果不是线程外的调用时：直接设置文本框的值
            {
                if (append == true)
                {
                    control.Text += text;
                }
                else
                {
                    control.Text = text;
                }
                if (type == 0)
                {
                    control.Text = text;
                }
                else if (type == 1)
                {
                    control.Text += "\r\n";
                    //设置滚动位置
                    ((TextBox)control).SelectionStart =
                        ((TextBox)control).TextLength;
                    ((TextBox)control).ScrollToCaret();//滚动到当前光标位置
                    ((TextBox)control).SelectionLength = 0;
                }
                control.Refresh();
            }
        }

    }
}