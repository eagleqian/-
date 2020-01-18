using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Tempture
{ 
    ///---------------------------------------------------------------------
    /// <summary>                                                           
    /// ��          :SCI:���ڹ���ʵ����                                     
    /// ��   ��   ��:�򿪴��ڡ��رմ��ڼ����ڵĽ��պͷ��͹���               
    /// ���к�������:                                                       
    ///             (1)SCIInit:���ڳ�ʼ��                                   
    ///             (2)SCISendData:��������                                 
    ///             (3)SCIReceiveData:��������                              
    ///             (4)SCIClose:�رմ���                                    
    ///             (5)SetInterrupt: ���ô��ڽ����ж�����                   
    /// ˵        ��:��ģ�������Ĵ�������޹�                             
    /// </summary>                                                          
    /// <remarks></remarks>                                                 
    /// --------------------------------------------------------------------
    public partial class SCI
    {
        /// ----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:��ʼ������,���򿪴���                                  
        /// �ڲ�����:��                                                     
        /// </summary>                                                     
        /// <param name="Port">���ڿؼ�,��������</param>                    
        /// <param name="ComNum">���ں�,�ַ�������</param>                  
        /// <param name="Baud">������,����</param>                          
        /// <returns>����һ������ֵ,�����ڳɹ��򿪺�,����true               
        ///          �����ڴ��쳣ʱ,����false </returns>                  
        /// ----------------------------------------------------------------
        public bool SCIInit(System.IO.Ports.SerialPort Port, 
                            string ComNum, Int32 Baud)
        {
            try
            {
                Port.Close();               //��֤��ʼ��֮ǰ�ǹرյ�
                Port.PortName = ComNum;     //���ô��ں�
                Port.BaudRate = Baud;       //���ò�����
                Port.Parity = System.IO.Ports.Parity.None;//��������żУ��
                Port.DataBits = 8;          //����8��������λ
                Port.StopBits = System.IO.Ports.StopBits.One;//����1λֹͣλ
                Port.ReadBufferSize = 4096; //���ջ�������С(�ֽ�) 
                Port.Open();                //�򿪴���
            }
            catch
            {
                //��������,����false
                return false;
            }
            return true;
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:���ڷ�������                                           
        /// �ڲ�����:��                                                     
        /// </summary>                                                     
        /// <param name="Port">���ڿؼ�,��������</param>                    
        /// <param name="SendArray">���Ҫ���͵�����,�ֽ�����</param>       
        /// <returns>����һ������ֵ,�����ͳɹ���,����True;                  
        ///          ���򷵻�False</returns>                                
        ///-----------------------------------------------------------------
        public bool SCISendData(System.IO.Ports.SerialPort Port, 
                                       ref byte[] SendArray)
        {
            try
            {
                Port.Write(SendArray, 0, SendArray.Length);//ͨ�����ڷ��ͳ�ȥ
            }
            catch 
            {
                //��������,����false
                return false;
            }
            return true;
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:��������                                               
        /// ��������:��                                                     
        /// </summary>                                                      
        /// <param name="Port">���ڿؼ�,��������</param>                    
        /// <param name="ReceiveArray">��Ž�����������,�ֽ�����</param>    
        /// <returns>����һ������ֵ,�����ճɹ���,����true                   
        ///          ����,����false</returns>                               
        ///-----------------------------------------------------------------
        //public bool SCIReceiveData(System.IO.Ports.SerialPort Port,
        //                            ref byte[] ReceiveArray)
        //{
        //    int len;
        //    len = Port.BytesToRead;//��ý��ջ������е��ֽ���
        //    try
        //    {
        //        ReceiveArray = new byte[len];
        //      //�����뻺�����ж�ȡlen���ֽ�
        //      //���������ReceiveArray��,�����������
        //        Port.Read(ReceiveArray, 0, len);
        //    }
        //     catch
        //     {
        //        //��������,����false
        //        return false;
        //     }
        //    return true;
        //}
        public void SCIReceiveData(System.IO.Ports.SerialPort Port,
                           ref byte[] ReceiveArray,
                           ref byte ReceiveArrayLen)
        {
            try
            {
                while (Port.BytesToRead > 0)
                    ReceiveArray[ReceiveArrayLen++] = (byte)Port.ReadByte();
            }
            catch
            {
                //��������,����false��0��
            }
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:�رմ���                                               
        /// �ڲ�����:��                                                     
        /// </summary>                                                      
        /// <param name="Port">���ڿؼ�,��������</param>                    
        /// <returns>����һ������ֵ,�����ڳɹ��رպ�,����true               
        ///          ���򷵻�false</returns>                                
        ///-----------------------------------------------------------------
        public bool SCIClose(System.IO.Ports.SerialPort Port)
        {
            try
            {
               Port.DiscardInBuffer(); //�������ջ�����������
               Port.DiscardOutBuffer();//�������ͻ�����������
               Port.Dispose();         //�ͷŴ���ͨ�ŵ�������Դ
               Port.Close();           //�رմ���
            }
            catch
            {
                //��������,����false
                return false;
            }
            return true;
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:�����ж�����                                           
        /// ��������:��                                                     
        /// </summary>                                                     
        /// <param name="Port">���ڿؼ�,��������</param>                    
        /// <param name="a">���������жϵ�����,����</param>                 
        ///-----------------------------------------------------------------
        public void SetInterrupt(System.IO.Ports.SerialPort Port,int a)
        {
            //���ô��ڽ����ж�����
            Port.ReceivedBytesThreshold = a;
        }
        
    }
}