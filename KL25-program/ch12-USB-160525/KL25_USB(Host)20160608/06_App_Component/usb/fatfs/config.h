#ifndef _CONFIG_H_
#define _CONFIG_H_


#define ZNFAT_MAKE_FS   //�ļ�ϵͳ��ʽ��  �˹����漰ROM�������͵Ķ�д������ʵ��ROM���ݵĶ�д������֤���ȶ���ȷ
#define ZNFAT_FLUSH_FS  //ˢ���ļ�ϵͳ  ���û��ʹ��RT_UPDATE_FSINFO���������е��ļ��������֮����Ҫ���ô˺���

#define ZNFAT_OPEN_FILE  //���ļ�
#define ZNFAT_CLOSE_FILE //�ر��ļ� ����ʹ��RT_UPDATE_FILESIZE��������ļ�����д��ɾ���Ȳ���֮������ô˺��������򲻵���Ҳû��ϵ
#define ZNFAT_READDATA   //�ļ����ݶ�ȡ 

#define ZNFAT_CREATE_FILE //�����ļ�
#define ZNFAT_DELETE_FILE //ɾ���ļ�
#define ZNFAT_WRITEDATA //д�����ݣ�д�����ݾ��Ǵ��ļ���ĩβ׷������

#define ZNFAT_CREATE_DIR //����Ŀ¼������һ���Դ����༶���Ŀ¼
#define ZNFAT_DELETE_DIR //ɾ��Ŀ¼��Ŀ¼������Ŀ¼���ļ����Լ���״��Ŀ¼�ṹ��Ҳ��һ��ȫ��ɾ��

#define ZNFAT_DUMP_DATA //�ļ����ݽضϣ����ļ���ĳ��λ��֮�������ȫ��ɾ��

#define ZNFAT_LARGE_MODE //����znFAT�Ĵ�ģʽ���ܣ�������������ݴ洢������  ����"���ʽ���ļ�д��"

#define ZNFAT_SEEK       //�ļ����ݶ�λ��ʹ����һ���ò�����znFAT�Ѿ�������װ�����ܺ�����

#define USE_LFN //����znFAT�ĳ��ļ������ܣ��ڳ��ļ�������Ҫʹ�õ��϶��RAM��Դ����֧�ֵ���ļ������ȿ���MAX_LFN_LEN������
#define USE_OEM_CHAR //�Ƿ��ʹ��OEM�ַ������Ƿ���ڳ����г��������ַ�
#define MAX_LFN_LEN (200) //���һ���ļ��г����������Ӧ���ļ���Ϣ�����е�have_lfn=1��longname�м�¼����
                        //������unicode�루�����ֽڱ�ʾһ���ַ��������ﶨ��������������unicode�볤
                        //MAX_LFN_LEN��ֵ�����ʵ��Ŀ��ϵͳ��RAM��Դ�����壬��ֹRAM��� 

#define RT_UPDATE_CLUSTER_CHAIN //�Ƿ�ʵʱ����FAT��������ʵʱ���£���ʹ��CCCB�������壬���Լӿ�����д���ٶ�

#define USE_ALONE_CCCB //ѡ���Ƿ�ʹ�ö����������壬��RAM��Դ�Ƚϳ�ԣ������£����ֹ�����ʽ�½���ÿ���ļ����ٳ�һ�������Ĵ�������
                       //��֮��Ե��ǹ���������壨shared CCCB��������ļ�ͬʱ����һ���������壬���漰�����������������Ч�ʽ�alone CCCB�͡�
                       //��Ƶ������Զ���ļ�����С������д��ʱ������������彫�𲻵�ʲô����
#define CCCB_LEN (8)   //��������ĳ��ȣ�����Ϊż�����Ҳ�С��4

#define USE_EXCHANGE_BUFFER
#define USE_ALONE_EXB //ÿ���ļ������������Ľ���������������ʹ�ù�����������

#endif
