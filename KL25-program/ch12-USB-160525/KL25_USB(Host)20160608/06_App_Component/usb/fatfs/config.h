#ifndef _CONFIG_H_
#define _CONFIG_H_


#define ZNFAT_MAKE_FS   //文件系统格式化  此功能涉及ROM数据类型的读写，请先实现ROM数据的读写，并保证其稳定正确
#define ZNFAT_FLUSH_FS  //刷新文件系统  如果没有使用RT_UPDATE_FSINFO，则在所有的文件操作完成之后，需要调用此函数

#define ZNFAT_OPEN_FILE  //打开文件
#define ZNFAT_CLOSE_FILE //关闭文件 若无使用RT_UPDATE_FILESIZE，则进行文件数据写入删除等操作之后，需调用此函数，否则不调用也没关系
#define ZNFAT_READDATA   //文件数据读取 

#define ZNFAT_CREATE_FILE //创建文件
#define ZNFAT_DELETE_FILE //删除文件
#define ZNFAT_WRITEDATA //写入数据，写入数据均是从文件的末尾追加数据

#define ZNFAT_CREATE_DIR //创建目录，可以一次性创建多级深层目录
#define ZNFAT_DELETE_DIR //删除目录，目录下有子目录和文件，以及树状子目录结构，也可一并全部删除

#define ZNFAT_DUMP_DATA //文件数据截断，从文件的某个位置之后的数据全部删除

#define ZNFAT_LARGE_MODE //开启znFAT的大模式功能，以满足高速数据存储的需求  或是"框架式的文件写入"

#define ZNFAT_SEEK       //文件数据定位，使用者一般用不到，znFAT已经把它封装到功能函数里

#define USE_LFN //开启znFAT的长文件名功能，在长文件名下需要使用到较多的RAM资源，可支持的最长文件名长度可由MAX_LFN_LEN来定义
#define USE_OEM_CHAR //是否会使用OEM字符，即是否会在长名中出现中文字符
#define MAX_LFN_LEN (200) //如果一个文件有长名，则其对应的文件信息集合中的have_lfn=1，longname中记录的是
                        //长名的unicode码（两个字节表示一个字符），这里定义的最大长名长度是unicode码长
                        //MAX_LFN_LEN的值请根据实际目标系统的RAM资源来定义，防止RAM溢出 

#define RT_UPDATE_CLUSTER_CHAIN //是否实时更新FAT簇链，不实时更新，则使用CCCB簇链缓冲，可以加快数据写入速度

#define USE_ALONE_CCCB //选择是否使用独立簇链缓冲，在RAM资源比较充裕的情况下，这种工作方式下将给每个文件开辟出一个独立的簇链缓冲
                       //与之相对的是共享簇链缓冲（shared CCCB），多个文件同时共享一个簇链缓冲，会涉及到簇链缓冲的争抢，效率较alone CCCB低。
                       //在频繁交替对多个文件进行小数据量写入时，共享簇链缓冲将起不到什么作用
#define CCCB_LEN (8)   //簇链缓冲的长度，必须为偶数，且不小于4

#define USE_EXCHANGE_BUFFER
#define USE_ALONE_EXB //每个文件都有它单独的交换缓冲区，否则使用共享交换缓冲区

#endif
