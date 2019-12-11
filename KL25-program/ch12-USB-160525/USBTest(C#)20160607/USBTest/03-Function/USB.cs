using System;
using System.Collections.Generic;
using System.Text;
using LibUsbDotNet;
using LibUsbDotNet.Info;
using LibUsbDotNet.Main;
using LibUsbDotNet.DeviceNotify;
using LibUsbDotNet.LibUsb;

namespace USBComponent
{
    class USB
    {
        public UsbDevice myUsbDevice;         //USB设备
        public UsbRegistry myUsbRegistry;     //USB注册信息

        List<byte> readEndpointList;
        List<byte> writeEndpointList;

        public UsbEndpointReader reader;      //读端点
        private UsbEndpointWriter writer;     //写端点

        public bool connectionStatus = false; //USB设备打开状态

        //USB设备插拔事件
        public static IDeviceNotifier UsbDeviceNotifier = DeviceNotifier.OpenDeviceNotifier();

        ///-----------------------------------------------------------------
        ///函数名:UsbRegDeviceList
        ///功  能:返回系统中全部LibUsb设备注册信息
        ///参  数:无
        ///返  回:UsbRegDeviceList数组，包含系统中全部LibUsb设备注册信息
        ///-----------------------------------------------------------------
        public static UsbRegDeviceList getUsbRegDeviceList()
        {
            return UsbDevice.AllDevices;
        }

        ///-----------------------------------------------------------------
        ///函数名:USB
        ///功  能:类构造函数，根据参数创建USB设备
        ///参  数:(1)usbRegistry:设备注册信息，创建USB的依据
        ///返  回:无需填写类型，会返回USB的一个实例
        ///-----------------------------------------------------------------
        public USB(UsbRegistry usbRegistry)
        {
            this.myUsbRegistry = usbRegistry;
            this.readEndpointList = new List<byte>();
            this.writeEndpointList = new List<byte>();
            if (InitializeUSB(usbRegistry))
            {
                connectionStatus = true;
            }
        }

        /// ----------------------------------------------------------------
        ///函数名:InitializeUSB
        ///功  能:初始化USB
        ///参  数:(1)usbRegistry:存放需要初始化设备注册信息
        ///返  回:布尔值,当USB成功打开后,返回true，当USB打开异常时,返回false                                                    
        /// ----------------------------------------------------------------
        public bool InitializeUSB(UsbRegistry usbRegistry)
        {
            try
            {
                usbRegistry.Open(out myUsbDevice);
                Console.WriteLine(myUsbDevice.Info.SerialString);
                if (myUsbDevice == null)
                {
                    throw new Exception("Device Not Found.");
                }
                //如果把USB设备(libusb-win32, linux libusb-1.0)作为一个整体，它提供一个IUsbDevice接口。
                IUsbDevice wholeUsbDevice = myUsbDevice as IUsbDevice;
                //如果变量"wholeUsbDevice"的值是null，它不需要支持配置和接口。
                if (!ReferenceEquals(wholeUsbDevice, null))
                {
                    //这是一个整设备，在使用它之前需要设置配置描述符和接口描述符。
                    // 选择配置描述符1
                    wholeUsbDevice.SetConfiguration(1);
                    // 申明接口描述符0
                    wholeUsbDevice.ClaimInterface(0);
                }

                //获取USB设备发送端点和接收端点编号
                foreach (UsbConfigInfo cfgInfo in myUsbDevice.Configs)
                {
                    foreach (UsbInterfaceInfo interfaceInfo in cfgInfo.InterfaceInfoList)
                    {
                        foreach (UsbEndpointInfo endpointInfo in interfaceInfo.EndpointInfoList)
                        {
                            byte endpointID=endpointInfo.Descriptor.EndpointID;
                            if (endpointID > 0x80)
                                readEndpointList.Add(endpointID);
                            else
                                writeEndpointList.Add(endpointID);
                        }
                    }
                }
                //Console.WriteLine("USB发送端点数量为" + readEndpointList.Count + "USB接收端点数量为" + writeEndpointList.Count);
                if (readEndpointList.Count<=0)
                    throw new Exception("USB发送端点数量为0");
                if(writeEndpointList.Count<=0)
                    throw new Exception("USB接收端点数量为0");
                
                //设置读端点
                //20160523增加缓冲区大小，且由于断点2发送数据量较小，因此设置断点类型为控制传输类型。
                //reader = myUsbDevice.OpenEndpointReader(ReadEndpointID.Ep02, 1000, EndpointType.Bulk);
                reader = myUsbDevice.OpenEndpointReader((ReadEndpointID)readEndpointList[0], 1000);
                
                //设置写端点
                //writer = myUsbDevice.OpenEndpointWriter(WriteEndpointID.Ep03, EndpointType.Bulk);
                writer = myUsbDevice.OpenEndpointWriter((WriteEndpointID)writeEndpointList[0]);
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                return false;
            }
        }

        /// ----------------------------------------------------------------
        ///函数名:sendData
        ///功  能:通过USB发送字符串
        ///参  数:(1)sendData:存放需要发送的字符串
        ///返  回:布尔值,当发送成功后,返回True，否则返回False                                                    
        /// ----------------------------------------------------------------
        public bool sendData(string sendData)
        {
            ErrorCode ec = ErrorCode.None;
            int bytesWritten;
            try
            {
                ec = writer.Write(Encoding.Default.GetBytes(sendData), 100, out bytesWritten);
                if (ec != ErrorCode.None)
                    throw new Exception(ec.ToString());
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error:" + ex.Message);
                return false;
            }

        }

        /// ----------------------------------------------------------------
        ///函数名:sendData
        ///功  能:通过USB发送一个字节
        ///参  数:(1)sendData:存放需要发送的一个字节
        ///返  回:布尔值,当发送成功后,返回True，否则返回False                                                    
        /// ----------------------------------------------------------------
        public bool sendData(byte sendData)
        {
            ErrorCode ec = ErrorCode.None;
            int bytesWritten;
            try
            {
                ec = writer.Write(sendData, 100, out bytesWritten);
                if (ec != ErrorCode.None)
                    throw new Exception(ec.ToString());
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error:" + ex.Message);
                return false;
            }
        }

        /// ----------------------------------------------------------------
        ///函数名:sendData
        ///功  能:通过USB发送一个字节数组
        ///参  数:(1)sendData:存放需要发送的字节数组
        ///       (2)count:需要发送的字节数量，从数组第0个元素算起
        ///返  回:布尔值,当发送成功后,返回True，否则返回False                                                    
        /// ----------------------------------------------------------------
        public bool sendData(byte[] sendData, int count)
        {
            ErrorCode ec = ErrorCode.None;
            int bytesWritten;
            try
            {
                ec = writer.Write(sendData, 0, count, 100, out bytesWritten);
                if (ec != ErrorCode.None)
                    throw new Exception(ec.ToString());
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error:" + ex.Message);
                return false;
            }

        }

        /// ----------------------------------------------------------------
        ///函数名:recvString
        ///功  能:通过USB接收一个字符换
        ///参  数:无
        ///返  回:从USB接收到的字符串                                                    
        /// ----------------------------------------------------------------
        public string recvString()
        {
            byte[] readBuffer = new byte[64];
            int bytesRead;
            reader.Read(readBuffer, 100, out bytesRead);
            return Encoding.Default.GetString(readBuffer, 0, bytesRead);
        }

        /// ----------------------------------------------------------------
        ///函数名:recvByte
        ///功  能:通过USB接收一个字节数组
        ///参  数:无
        ///返  回:从USB接收到的字节数组                                                   
        /// ----------------------------------------------------------------
        public byte[] recvByte()
        {
            byte[] readBuffer = new byte[64];
            int bytesRead;
            reader.Read(readBuffer, 100, out bytesRead);

            if (bytesRead > 0)
            {
                byte[] recvDataBuffer = new byte[bytesRead];
                Array.Copy(readBuffer, recvDataBuffer, bytesRead);
                return recvDataBuffer;
            }
            else
            {
                return null;
            }

        }

        /// ----------------------------------------------------------------
        ///函数名:CloseUSB
        ///功  能:关闭USB设备，释放相关资源
        ///参  数:无
        ///返  回:无                                                   
        /// ----------------------------------------------------------------
        public void CloseUSB()
        {
            try
            {
                if (!ReferenceEquals(reader, null))
                    reader.Dispose();
                if (!ReferenceEquals(writer, null))
                    writer.Dispose();
                if (!ReferenceEquals(myUsbDevice, null))
                    myUsbDevice.Close();

            }
            catch (Exception ex) {

                Console.WriteLine(ex.ToString());
            }

        }
    }
}
