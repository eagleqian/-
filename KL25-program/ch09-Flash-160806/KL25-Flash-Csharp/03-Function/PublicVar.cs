namespace SerialPort
{
    /// --------------------------------------------------------------------*
    /// <summary>                                                           *
    /// �๦��:����ȫ�ֱ���                                                 *
    /// </summary>                                                          *
    /// <remarks></remarks>                                                 *
    /// ------------------- ------------------------------------------------*
    public partial class PublicVar
    {
        //���崮�ڵ�ȫ�ֱ���,���óɾ�̬��
        public static byte[] g_ReceiveByteArray = new byte[250];//��Ž��յ�����
        public static byte[] g_SendByteArray;                   //���Ҫ���͵�����
        public static string g_SCIComNum;                       //���ѡ��Ĵ��ں�
        public static int g_SCIBaudRate;                        //���ѡ��Ĳ�����
        public static byte g_ReceiveByteArrayLen = 0;           //���ջ������ֽ���
    }
}