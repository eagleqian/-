namespace Tempture
{
    /// --------------------------------------------------------------------
    /// <summary>                                                           
    /// �๦��:����ȫ�ֱ���                                                 
    /// </summary>                                                          
    /// <remarks></remarks>                                                 
    /// ------------------- ------------------------------------------------
    public partial class PublicVar
    {
        //���崮�ڵ�ȫ�ֱ���,���óɾ�̬��
        public static byte[] g_ReceiveByteArray = new byte[200];//ȫ�ֱ�������Ž��յ�����
        public static byte[] g_SendByteArray;   //ȫ�ֱ��������Ҫ���͵�����
        
        public static string g_SCIComNum;       //ȫ�ֱ��������ѡ��Ĵ��ں�
        public static int g_SCIBaudRate;        //ȫ�ֱ��������ѡ��Ĳ�����

        public static byte g_ReceiveByteArrayLen = 0;
    }
}                                                     