#include "znfat.h"
#include "template.h"
#include "gb2uni.h"
#include "usb_class.h"
#include "printf.h"

UINT8 tmpBuf[ZNFAT_BUF_SIZE];

UINT8 *znFAT_Buffer=tmpBuf; //znFAT的内部缓冲区，使用者不可私自使用
                            //先定义tmpBuf，再用znFAT_Buffer指向它，是因为在一些架构的CPU中
                            //受限于RAM的特殊结构，只能用指针来访问大数组，比如PIC

//--------------------------------------------------------------------------------------------------
struct znFAT_Init_Args *pInit_Args; //初始化参数结构体指针，用以指向某一存储设备的初始化参数集合
                                    //使用之前*必须*先指向结构化变量
extern struct znFAT_IO_Ctl ioctl; 

UINT8 Dev_No=0; //设备号，用于实现多设备

//--------------------------------------------------------------------------------------------------

struct FileInfo *just_file=(struct FileInfo *)0; //用于记录最近操作的文件

//----------------------------------------------------------

//------------------EXB相关变量定义-------------------------
UINT8 *pexb_buf=(UINT8 *)0;


//内部函数声明
UINT8 Memory_Set(UINT8 *pmem,UINT32 len,UINT8 value);
UINT8 Memory_Compare(UINT8 *psmem,UINT8 *pdmem,UINT32 len);
UINT8 * Memory_Copy(UINT8 *pdmem,UINT8 *psmem,UINT32 len);
INT8 * StringCopy(INT8 *dest_str,INT8 *src_str);
UINT32 StringLen(INT8 *pstr);
UINT32 WStringLen(UINT16 *str);
UINT8 PGM_BYTE_FUN(ROM_TYPE_UINT8 *ptr);
UINT16 PGM_WORD_FUN(ROM_TYPE_UINT16 *ptr);
UINT32 PGM_DWORD_FUN(ROM_TYPE_UINT32 *ptr);
UINT8 * PGM2RAM(UINT8 *pdmem,ROM_TYPE_UINT8 *psmem,UINT32 len);
UINT32 Bytes2Value(UINT8 *dat,UINT8 len);
UINT8 Find_FSINFO_Sec(UINT32 *fsinfosec);
UINT8 Search_Free_Cluster_From_Start(UINT32 *nFreeCluster);
UINT8 Update_FSINFO(void);
UINT32 Get_Next_Cluster(UINT32 cluster);
UINT8 znFAT_Seek(struct FileInfo *pfi,UINT32 offset);
UINT8 Check_Illegal_Char(INT8 *pfn);
UINT8 Check_SFN_Special_Char(INT8 *pfn);
UINT8 Check_SFN_Dot(INT8 *pfn);
UINT8 Check_SFN_Illegal_Lower(INT8 *pfn);
UINT8 Check_SFN_Illegal_Length(INT8 *pfn);
UINT8 To_File_Name(INT8 *name_in_fdi,INT8 *pfileName);
UINT8 Analyse_FDI(struct FileInfo *pfi,struct FDI *pFDI);
UINT8 Is_WildFileName(INT8 *pfn);
UINT8 FindSubStr(INT8 *str,INT8 *substr,UINT8 pos);
UINT8 SFN_Match(INT8 *t,INT8 *s);
UINT8 Modify_FAT(UINT32 cluster,UINT32 next_cluster);
UINT8 Clear_Cluster(UINT32 cluster);
UINT8 Update_Next_Free_Cluster(void);
UINT8 Is_LFN(INT8 *filename);
UINT8 Get_Part_Name(UINT16 *lfn_buf,struct LFN_FDI *plfndi,UINT8 n);
UINT8 OEM2UNI(UINT16 oem_code,UINT16 *uni_code);
UINT8 oemstr2unistr(INT8 *oemstr,UINT16 *unistr);
UINT8 LFN_Match(UINT16 *t,UINT16 *s);
UINT8 Get_Binding_SumChk(struct FDI *pdi);
UINT32 ELFHash(INT8 *str);
UINT8 Hex2Str_32b(UINT32 hex,INT8 *str);
UINT8 Make_Short_Name(char *pfn,char *psfn);
UINT8 Fill_LFN_FDI(UINT16 *unifn,struct LFN_FDI *plfni,UINT8 ChkSum,UINT8 n);
UINT8 Register_LFN_FDI(UINT32 cluster,struct FDI *pfdi,UINT16 *unifn,UINT32 *psec,UINT8 *pn);
UINT8 Get_Dir_Start_Cluster(INT8 *dir_name,UINT32 *pCluster);
UINT8 znFAT_Enter_Dir(INT8 *dirpath,UINT32 *pCluster,UINT32 *pos);
UINT8 Fill_FDI(struct FDI *pfdi,INT8 *pfn,struct DateTime *pdt,UINT8 is_file);
UINT8 Register_FDI(UINT32 cluster,struct FDI *pfdi,UINT32 *psec,UINT8 *pn);
UINT8 Create_Dir_In_Cluster(UINT32 *cluster,INT8 *pdn,struct DateTime *pdt);
UINT8 znFAT_Create_Dir(INT8 *pdp,struct DateTime *pdt);
UINT8 Destroy_FAT_Chain(UINT32 cluster);
UINT8 Destroy_FDI(struct FDI *pitem);
UINT8 Have_Any_SubDir_With_Del_ForeFile(UINT32 *cluster,UINT8 for_del_dir);
UINT8 Enter_Deep_Ahead_Dir(UINT32 *cluster);
UINT8 Get_Upper_Dir(UINT32 *cluster);
UINT8 Get_Recmd_szClu(UINT32 nsec);
UINT8 znFAT_Make_FS(UINT32 tt_sec,UINT16 clu_sz);
UINT8 Update_File_Size(struct FileInfo *pfi);
UINT8 Update_File_sClust(struct FileInfo *pfi,UINT32 clu);
UINT8 Create_Cluster_Chain(struct FileInfo *pfi,UINT32 cluster,UINT32 datalen);
UINT32 WriteData_From_nCluster(struct FileInfo *pfi,UINT32 len,UINT8 *pbuf);
UINT8 znFAT_Dump_Data(struct FileInfo *pfi,UINT32 offset);

//============================================================================
//函数名: znFAT_Init
//功  能: 文件系统初始化
//参  数: 无
//返  回: 0=成功；1=失败
//============================================================================
UINT8 znFAT_Init(void)
{
    struct DBR *pdbr;
    USB_Class_Read_Sector(MBR_SECTOR,znFAT_Buffer);
    if(znFAT_Buffer[0]!=DBR_MARK) //检测0扇区是否为DBR扇区
    {
        pInit_Args->BPB_Sector_No=Bytes2Value(((((struct MBR *)(znFAT_Buffer))->Part[0]).StartLBA),4);
    }
    else
    {
        pInit_Args->BPB_Sector_No=0;
    }
    USB_Class_Read_Sector((pInit_Args->BPB_Sector_No),znFAT_Buffer); //读取DBR扇区
    pdbr=(struct DBR *)znFAT_Buffer;
    if(!IS_FAT32_TYPE((pdbr->BS_FilSysType1))) return FSTYPE_NOT_FAT32; //FAT32文件系统类型检验
    pInit_Args->FATsectors      =Bytes2Value((pdbr->BPB_FATSz32)    ,4);//装入FAT表占用的扇区数到FATsectors中
    pInit_Args->BytesPerSector  =Bytes2Value((pdbr->BPB_BytesPerSec),2);//装入每扇区字节数到BytesPerSector中
    pInit_Args->SectorsPerClust =pdbr->BPB_SecPerClus;//装入每簇扇区数到SectorsPerClust 中
    pInit_Args->FirstFATSector  =Bytes2Value((pdbr->BPB_RsvdSecCnt) ,2)+pInit_Args->BPB_Sector_No;//装入第一个FAT表扇区号到FirstFATSector 中
    pInit_Args->FirstDirSector  =(pInit_Args->FirstFATSector)+(pdbr->BPB_NumFATs)*(pInit_Args->FATsectors); //装入第一个目录扇区到FirstDirSector中
    pInit_Args->Total_SizeKB    =Bytes2Value((pdbr->BPB_TotSec32),4)/2;  //磁盘的总容量，单位是KB
    if(Find_FSINFO_Sec(&(pInit_Args->FSINFO_Sec))) //查找FSINFO信息扇区
    {
        return ERR_FAIL;
    }
    USB_Class_Read_Sector((pInit_Args->FSINFO_Sec),znFAT_Buffer);
    pInit_Args->Free_nCluster=Bytes2Value(((struct FSInfo *)znFAT_Buffer)->Free_Cluster,4); //获取剩余簇数
    if(0XFFFFFFFF==pInit_Args->Free_nCluster) //如果一个磁盘格式化后没有卷标，则其存储空间就没有一点占用，此时FSINFO记录的剩余空簇数为0XFFFFFFFF
    {
        pInit_Args->Free_nCluster=(((pInit_Args->Total_SizeKB*2)-(pInit_Args->FirstDirSector))/(pInit_Args->SectorsPerClust))-1;
    }
    if(Search_Free_Cluster_From_Start(&(pInit_Args->Next_Free_Cluster)))//遍历整个FAT表，搜索可用的空闲簇
    {                                                                   //此操作可能会耗费较多时间，但没有办法
        return ERR_FAIL;                                                   //FSINFO中的空闲簇参考值并不保证正确
    }                                                                   //修正和维护它反而会更加麻烦
    return ERR_SUCC;
}

//============================================================================
//函数名: znFAT_Select_Device
//功  能: 多个设备连接时，用于选择其中一个设备
//参  数: 无
//返  回: 无
//============================================================================
void znFAT_Select_Device(UINT8 devno,struct znFAT_Init_Args *pinitargs)
{
    pInit_Args=pinitargs; //将znFAT的初始化参数集合指针指向设备的初始化参数集合
    Dev_No=devno; //设置设备号
}

//=================================================================================
//函数名: znFAT_Open_File
//功  能: USB开始传输事务
//参  数: pfi：文件信息结构体
//       filepath:文件所在路径
//       n:文件项目
//       is_file:是否是文件
//返  回: 0=成功；1=失败
//=================================================================================
UINT8 znFAT_Open_File(struct FileInfo *pfi,INT8 *filepath,UINT32 n,UINT8 is_file)
{
     UINT8 result=0,flag=0;
     UINT32 sec_temp=0,Cur_Cluster=0,fn_pos=0,item=0;
     UINT32 iSec=0,iFDI=0;
     #ifdef USE_LFN
     struct LFN_FDI *plfni;

     UINT8 cur_binding_sumchk=0;
     UINT8 is_wfn=0;
     UINT16 temp_lfn[MAX_LFN_LEN+1]; //用于装载长名UNICODE码的临时缓冲
     UINT8 is_lfn=0; //输入的文件名是否是长名
     UINT8 is_lfn_buf_err=0; //产生长名缓冲溢出错误，此标记为1则直接跳过长名比对
     #endif
     INT8 temp_filename[13];
     INT8 *filename;

     struct FDIesInSEC *pitems; //指向文件目录项扇区数据的指针
     struct FDI *pitem; //指向文件目录项数据的指针

     #ifdef USE_LFN
     pfi->have_lfn=BOOL_FALSE; //先设定文件无长名
     #endif
     just_file=pfi;
     #ifdef USE_EXCHANGE_BUFFER
     #ifdef USE_ALONE_EXB
     //Memory_Set(just_file->exb_buf,512,0);
     just_file->exb_cursec=0;
     #endif
     #endif
     result=znFAT_Enter_Dir(filepath,&Cur_Cluster,&fn_pos); //获取路径最后一级目录的开始簇
     if(result) return result;
     filename=filepath+fn_pos; //filename指向filepath中的文件名
                               //注：如果打开的是目录，则路径filepath不以/或\结束，如打开目录\a\b\c
                               //不要写成\a\b\c\，这样会造成打开失败
                               //znFAT认为你要打开c目录下的一个名字为空的目录
                               //打开目录与进入目录不同，进入目录仅获取目录首簇，而打开目录
                               //则对目录进行解析，将文件相关参数填入文件信息集合，如目录创建时间等

     if(Check_Illegal_Char(filename)) return ERR_ILL_CHAR; //检查文件名中是否有非法字符，无论长名还是短名，或是通配名
     //这里主要针对于LFN、SFN及通配名进行相关检测
     if(!Is_WildFileName(filename)) //如果不是通配文件名，即确定名，则需要进行文件名合法性检测
     {
        #ifdef USE_LFN
        if(!Is_LFN(filename)) //如果不是长名,即是短名
        {
            #endif
            //检查SFN合法性，若非法则直接返回，不再进行后面的处理(此处对SFN的合法性检查比较严格)
            //事先检查SFN的合法性，减少后面处理上的麻烦
            if(Check_SFN_Illegal_Length(filename)) return ERR_SFN_ILL_LEN; //检查SFN是否符合8.3长度
            if(Check_SFN_Dot(filename)) return ERR_SFN_DOT; //检查SFN中.是否合法
            if(Check_SFN_Special_Char(filename)) return ERR_SFN_SPEC_CHAR; //检查SFN中是否有特殊字符
            if(((UINT8)(-1))==Check_SFN_Illegal_Lower(filename)) return ERR_SFN_ILL_LOWER; //检查SFN中是否有非法的大小写
                #ifdef USE_LFN
        }
        else //如果是长名
        {
            is_lfn=1; //标记输入的文件名为长名
            result=oemstr2unistr(filename,temp_lfn);//把filename转为UNICODE码，存在temp_lfn里，以便后面进行文件名比对
            if(result) return result;
        }
        #endif
     }
     else //如果是通配名，即含有*或?
     {
         #ifdef USE_LFN
         is_wfn=1; //标志输入的文件名为通配名
         is_lfn=1; //在这种情况下，也认为是长名，通配名也要与LFN相比对
         result=oemstr2unistr(filename,temp_lfn); //转为带通配符的UNI串
         if(result) return result; //OEM字符集不完全，OEM->UNI转换中有字符找不到 或 LFN缓冲溢出
             #endif
     }
     do
     {
         sec_temp=SOC(Cur_Cluster); //当前簇首扇区
         for(iSec=0;iSec<(pInit_Args->SectorsPerClust);iSec++)
         {
             USB_Class_Read_Sector(sec_temp+(UINT32)iSec,znFAT_Buffer);
             pitems=(struct FDIesInSEC *)znFAT_Buffer;
             for(iFDI=0;iFDI<NFDI_PER_SEC;iFDI++) //访问扇区中各文件目录项
             {
                 pitem=&(pitems->FDIes[iFDI]); //指向一个文件目录项数据
                 if((is_file?CHK_ATTR_FILE(pitem->Attributes):CHK_ATTR_DIR(pitem->Attributes))
                    && (0XE5!=pitem->Name[0]) && ('.'!=pitem->Name[0])) //依is_file检查属性，且没有被删除
                                                            //不是.与..
                 {
                     To_File_Name((INT8 *)(pitem->Name),temp_filename); //将FDI中的文件名字段转为8.3文件名

                         #ifdef USE_LFN
                     if(!is_lfn || is_wfn) //如果输入的文件名不是长文件名，即为短文件名，或者是配通名，则要进行SFN比对
                         #endif                //主要是为了防止多余的操作，如果输入文件名为长文件名，则根本不用SFN比对，就
                           //算比对，结果也一定是不匹配的
                     {
                         if(!SFN_Match(filename,temp_filename)) //短文件名通配
                         {
                             if(n==item)
                             {
                                 Analyse_FDI(pfi,pitem); //解析匹配的文件目录项
                                 pfi->FDI_Sec=sec_temp+iSec; //文件目录项所在的扇区
                                 pfi->nFDI=(UINT8)iFDI; //文件目录项在扇区中的索引

                                 #ifdef USE_LFN
                                 if(!pfi->have_lfn) (pfi->longname)[0]=0;
                                 #endif
                                 return ERR_SUCC;
                             }
                             flag=1;
                         }
                     }

                         #ifdef USE_LFN
                     if(is_lfn && (pfi->have_lfn) && !is_lfn_buf_err) //如果输入的文件名为长名，而且也发现了长名
                     {
                         if(cur_binding_sumchk==Get_Binding_SumChk(pitem)) //如果LFN与SFN目录项绑定校验和相等，则认为
                         {                                                    //长名有效
                             if(!LFN_Match(temp_lfn,(pfi->longname))) //长文件名通配
                             {
                                 if(n==item)
                                 {
                                     Analyse_FDI(pfi,pitem); //解析匹配的文件目录项
                                     pfi->FDI_Sec=sec_temp+iSec; //文件目录项所在的扇区
                                     pfi->nFDI=(UINT8)iFDI; //文件目录项在扇区中的索引
                                     return ERR_SUCC;
                                 }
                                 flag=1;
                             }
                         }
                     }

                     if(is_lfn_buf_err) is_lfn_buf_err=0;
                        #endif
                         if(flag) {item++;flag=0;} //如果LFN（如果用了LFN的话）与SFN有一项比对成功，但item不匹配，则item++
                 }
                 #ifdef USE_LFN
                 if(CHK_ATTR_LFN(pitem->Attributes) && (0XE5!=pitem->Name[0]) && is_lfn) //是长名项，而且没有被删除，并且输入的文件名是长名
                 {                                                                       //因为如果我们输入的文件名本身就不是长名，那我们就没必要去关心长名项
                     pfi->have_lfn=1;
                     plfni=(struct LFN_FDI *)pitem;
                     cur_binding_sumchk=(plfni->ChkVal)[0]; //获取长名项的绑定校验和
                     result=Get_Part_Name(pfi->longname,plfni,(UINT8)((((plfni->AttrByte[0])&0XBF)-1)*13)); //将当前LFN项中的文件名UNICODE码拼入临时缓冲
                                                                      //此临时缓冲长度为MAX_LFN_LEN，如果越界，则
                                                                      //不再装入，最终造成LFN的截断。
                     if(result) is_lfn_buf_err=1; //发生LFN_BUF溢出错误
                 }
                 else
                 {
                     pfi->have_lfn=0;
                 }
                 #endif

             }
         }
         Cur_Cluster=Get_Next_Cluster(Cur_Cluster); //获取下一簇
     }while(!IS_END_CLU(Cur_Cluster)); //如果不是最后一个簇，则继续循环

     return ERR_NO_FILE;
}

//=====================================================================================
//函数名: znFAT_Close_File
//功  能: 关闭文件
//参  数: pfi：文件信息结构体
//返  回: 0=成功；1=失败
//=====================================================================================
UINT8 znFAT_Close_File(struct FileInfo *pfi)
{
    Update_File_Size(pfi); //更文件目录项中的文件大小字段
    just_file=pfi;
    pexb_buf=pfi->exb_buf;
    if(0!=pfi->exb_cursec) //如果要关闭文件的EXB被占用
    {
        USB_Class_Write_Sector(pfi->File_CurSec,pexb_buf); //EXB缓冲数据回写
    }
    pexb_buf=(UINT8 *)0;
    Memory_Set((UINT8 *)pfi,(UINT32)sizeof(struct FileInfo),0);
    just_file=(struct FileInfo *)0;
    return ERR_SUCC;
}


//=====================================================================================
//函数名: znFAT_ReadData
//功  能: 读USB设备指定文件的数据
//参  数: pfi：文件信息结构体
//       offset:文件位置
//       len:要读取的数据长度
//       ReadBuff:保存读取数据的缓冲区
//返  回: 0=成功；1=失败
//备  注：调用类(Class)层函数USB_Class_Read_Sector和USB_Class_Read_nSector执行
//       读文件操作
//=====================================================================================
UINT32 znFAT_ReadData(struct FileInfo *pfi,UINT32 offset,UINT32 len,UINT8 *ReadBuff)
{
     UINT32 Cluster_Size=0,iClu=0,next_clu=0,start_clu=0,end_clu=0;
     UINT32 temp=0,temp1=0,temp2=0,ncluster=0,have_read=0;
     just_file=pfi;
     znFAT_Seek(pfi,offset); //文件定位

     if(0==len) return 0; //如果要读取的数据长度为0，则直接返回
     Cluster_Size=(pInit_Args->SectorsPerClust*pInit_Args->BytesPerSector); //计算簇的总字节数据，以免后面重复计算
     if((pfi->File_CurOffset+len)>=(pfi->File_Size)) //如果从当前位置开始要读取的数据长度len不小于文件大小
     {
         len=(pfi->File_Size-pfi->File_CurOffset);  //对len进行修正，置为文件剩余可读数据量。
         pfi->File_IsEOF=BOOL_TRUE;    //这种情况下，文件必然会读到末尾。
     }
     if((pfi->File_CurOffset%Cluster_Size)!=0) //如果当前偏移量是簇大小整数倍，说明此位置即为整簇开始
     {   //不要再进行当前簇内数据处理，直接进入簇-扇区-字节阶段
         USB_Class_Read_Sector(pfi->File_CurSec,znFAT_Buffer); //将当前扇区读入内部缓冲区
         temp=pInit_Args->BytesPerSector-pfi->File_CurPos; //计算当前扇区中的剩余数据量
         if(len<=temp)
         {
             Memory_Copy(ReadBuff,znFAT_Buffer+(pfi->File_CurPos),len);//将内部缓冲区中要读的数据拷入应用缓冲区
             //更新当前位置参数
             if(temp==len) //如果正好读到当前扇区的末尾
             {
                 if(IS_END_SEC_OF_CLU(pfi->File_CurSec,pfi->File_CurClust))//如果当前扇区是当前簇的最后一个扇区
                 {
                     if(!pfi->File_IsEOF) //如果不是文件末尾
                     {
                         pfi->File_CurClust=Get_Next_Cluster(pfi->File_CurClust); //可能有“窘簇”
                     }
                     pfi->File_CurSec=SOC(pfi->File_CurClust);
                 }
                 else
                 {
                     pfi->File_CurSec++;
                 }
                 pfi->File_CurPos=0;
             }
             else
             {
                 pfi->File_CurPos+=(UINT16)len;
             }
             pfi->File_CurOffset+=len;
             return len;
         }
         else
         {
             temp=(pInit_Args->BytesPerSector-pfi->File_CurPos); //将当前扇区的剩余数据量赋给中间变量temp
             Memory_Copy(ReadBuff,znFAT_Buffer+(pfi->File_CurPos),temp); //将当前扇区剩余数据誊到应用缓冲区
             have_read+=temp;
             if(!(IS_END_SEC_OF_CLU(pfi->File_CurSec,pfi->File_CurClust))) //如果当前扇区不是当前簇的最后一个扇区
             {
                 pfi->File_CurSec++;
                 pfi->File_CurPos=0;

                 temp2=(len-have_read); //计算剩余数据量
                 temp1=((LAST_SEC_OF_CLU(pfi->File_CurClust)-(pfi->File_CurSec-1))*(pInit_Args->BytesPerSector)); //剩余所有扇区数据量
                 if(temp2<=temp1) //如果要读的剩余数据量小于等于当前簇剩余数据量
                 {
                     //这说明要读的数据在当前簇内，没有跨到下一簇

                     temp=temp2/(pInit_Args->BytesPerSector); //计算要读取的剩余数据足够几个整扇区
                     USB_Class_Read_nSector(temp,pfi->File_CurSec,ReadBuff+have_read);
                     have_read+=((pInit_Args->BytesPerSector)*temp);

                     if(temp2==temp1)
                     {
                         if(!pfi->File_IsEOF) //如果不是文件末尾
                         {
                             pfi->File_CurClust=Get_Next_Cluster(pfi->File_CurClust); //可能有“窘簇”
                         }
                         pfi->File_CurSec=SOC(pfi->File_CurClust);
                         pfi->File_CurPos=0;
                     }
                     else
                     {
                         pfi->File_CurSec+=temp;
                         temp=len-have_read;
                         USB_Class_Read_Sector(pfi->File_CurSec,znFAT_Buffer); //当前扇区中可能还有部分剩余数据要读
                         Memory_Copy(ReadBuff+have_read,znFAT_Buffer,temp); //将最后不足扇区的数据誊入应用缓冲区
                         //更新当前位置参数
                         pfi->File_CurPos=(UINT16)temp;
                     }
                     pfi->File_CurOffset+=len;
                     return len;
                 }
                 else //如果剩余数据的整扇区数不小于当前簇的剩余扇区数，即要读的数据不光在当前簇内，已经跨簇了
                 {
                     temp=(LAST_SEC_OF_CLU(pfi->File_CurClust))-(pfi->File_CurSec)+1; //计算当前簇还有几个整扇区
                     USB_Class_Read_nSector(temp,(pfi->File_CurSec),ReadBuff+have_read);
                     have_read+=((pInit_Args->BytesPerSector)*temp);
                 }
             }
             //更新当前位置参数，此时已经读完当前簇的所有剩余数据，跨到下一簇
             pfi->File_CurClust=Get_Next_Cluster(pfi->File_CurClust); //这里不会产生“窘簇”
             pfi->File_CurSec=SOC(pfi->File_CurClust);
             pfi->File_CurPos=0;
         }
     }
     temp1=len-have_read;
     ncluster=temp1/Cluster_Size; //计算剩余数据的整簇数
     if(ncluster>0) //剩余数据起码足够一个簇
     {
         //以下计算连续簇段，以尽量使用多扇区读取驱动
         start_clu=end_clu=pfi->File_CurClust;
         for(iClu=1;iClu<ncluster;iClu++)
         {
             next_clu=Get_Next_Cluster(end_clu);
             if((next_clu-1)==end_clu)
             {
                 end_clu=next_clu;
             }
             else
             {
                 USB_Class_Read_nSector(((end_clu-start_clu+1)*(pInit_Args->SectorsPerClust)),SOC(start_clu),ReadBuff+have_read);
                 have_read+=((end_clu-start_clu+1)*Cluster_Size);
                 start_clu=end_clu=next_clu;
             }
         }
         //以上是处理整簇数据
         temp=temp1%Cluster_Size; //计算整簇读完之后，是否还有数据要读
         if(temp>0) //整簇数据后面还有数据要读
         {
             temp=temp/(pInit_Args->BytesPerSector); //计算最终不足整簇的剩余数据的整扇区数
             next_clu=Get_Next_Cluster(end_clu);
             if((next_clu-1)==end_clu) //如果最后一个簇仍然与前面的连续簇段连续
             {
                 USB_Class_Read_nSector(((end_clu-start_clu+1)*(pInit_Args->SectorsPerClust)+temp),SOC(start_clu),ReadBuff+have_read);
                 have_read+=((pInit_Args->BytesPerSector)*((end_clu-start_clu+1)*(pInit_Args->SectorsPerClust)+temp));
             }
             else //如果最后一个簇与前面的连续簇段并不连续
             {
                 USB_Class_Read_nSector(((end_clu-start_clu+1)*(pInit_Args->SectorsPerClust)),SOC(start_clu),ReadBuff+have_read);
                 have_read+=(Cluster_Size*(end_clu-start_clu+1));
                 USB_Class_Read_nSector(temp,SOC(next_clu),ReadBuff+have_read);
                 have_read+=(temp*(pInit_Args->BytesPerSector));
             }
             pfi->File_CurClust=next_clu;
             pfi->File_CurSec=(SOC(next_clu)+temp);

             //----------------------------以上是处理整扇区数据----------------------------------------
             temp=len-have_read;
             if(temp>0)
             {
                 USB_Class_Read_Sector(pfi->File_CurSec,znFAT_Buffer); //将最后的可能包含一部分要读的数据的扇区读到内部缓冲区
                 Memory_Copy(ReadBuff+have_read,znFAT_Buffer,temp); //将最后不足扇区的数据余量誊入应用缓冲区

                 //更新当前位置参数，此时数据读取操作已经结束
                 pfi->File_CurPos=(UINT16)temp;
             }
             //----------------------------以上是处理最后扇区内的剩余字节----------------------------------------
         }
         else //整簇数据读完之后再无数据要读
         {
             USB_Class_Read_nSector(((end_clu-start_clu+1)*(pInit_Args->SectorsPerClust)),SOC(start_clu),ReadBuff+have_read);
             pfi->File_CurClust=end_clu;
             if(!pfi->File_IsEOF)
             {
                 pfi->File_CurClust=Get_Next_Cluster(end_clu);
             }
             pfi->File_CurSec=SOC(pfi->File_CurClust);
         }
     }
     else //剩余的数据不足一个簇
     {
         temp=temp1/(pInit_Args->BytesPerSector); //计算剩余的数据足够几个扇区
         USB_Class_Read_nSector(temp,SOC(pfi->File_CurClust),ReadBuff+have_read);
         have_read+=temp*(pInit_Args->BytesPerSector);
         pfi->File_CurSec+=temp;
         temp=temp1%(pInit_Args->BytesPerSector); //计算最终的不足一扇区的数据量
         if(temp>0) //如果最后还有数据
         {
             USB_Class_Read_Sector(pfi->File_CurSec,znFAT_Buffer);
             Memory_Copy(ReadBuff+have_read,znFAT_Buffer,temp);
             pfi->File_CurPos=(UINT16)temp;
         }
     }
     //----------------------------------------------------------------------------------------
     pfi->File_CurOffset+=len;
     return len;
}

//======================================================================================
//函数名: znFAT_WriteData
//功  能: 读USB设备的数据
//参  数: pfi：文件信息结构体
//       len:要写入的数据长度
//       WriteBuff:要写入的数据缓冲区
//返  回: 0=成功；1=失败
//备  注：调用USB类层函数USB_Class_Write_Sector和USB_Class_Write_nSector函数执行写文件
//======================================================================================
UINT32 znFAT_WriteData(struct FileInfo *pfi,UINT32 len,UINT8 *WriteBuff)
{
    UINT32 temp=0,temp1=0,len_temp=len;
    UINT32 Cluster_Size=((pInit_Args->BytesPerSector)*(pInit_Args->SectorsPerClust));
    pexb_buf=(pfi->exb_buf);
    just_file=pfi;
    if(0==len) return 0; //如果要写入的数据长度为0，则直接返回0

    if(len>(0XFFFFFFFF-pfi->File_Size)) return (UINT32)-2; //文件大小在写入数据后将发生溢出错误

    znFAT_Seek(pfi,pfi->File_Size); //文件数据定位到文件末尾，文件位置相关信息随即改变

    //检查磁盘剩余空间是否够用
    if((pfi->File_CurOffset%Cluster_Size)!=0)
    {
        temp=((pInit_Args->BytesPerSector)-(pfi->File_CurPos))+((LAST_SEC_OF_CLU(pfi->File_CurClust))-(pfi->File_CurSec))*(Cluster_Size);
        //当前簇剩余数据量
        if(len>temp) //如果要写入的数据量大于temp，则说明必然会超出当前簇，为其扩展空簇
        {
            temp1=(len-temp)/(Cluster_Size);
            if((len-temp)%(Cluster_Size)) temp1++; //计算需要多少个空簇
            if(temp1>(pInit_Args->Free_nCluster)) return ((UINT32)-1); //空间不足
        }

    }
    else
    {
        temp1=len/(Cluster_Size);
        if(len%(Cluster_Size)) temp1++; //计算需要多少个空簇
        if(temp1>(pInit_Args->Free_nCluster)) return ((UINT32)-1); //空间不足
    }
    temp=((pInit_Args->BytesPerSector)-(pfi->File_CurPos)); //计算赋给临时变量，以免后面重复计算
    if((pfi->File_CurOffset%Cluster_Size)!=0)
    {
        if(len<=temp) //要写入的数据小于等于当前扇区剩余数据量
        {
            if(len==temp) //如果要写入的数据正好占满当前扇区
            {
                if(0!=pfi->File_CurPos)
                {
                    if(0==(just_file->exb_cursec))
                    {
                        USB_Class_Read_Sector(pfi->File_CurSec,pexb_buf);
                    }
                    Memory_Copy(pexb_buf+pfi->File_CurPos,WriteBuff,len); //扇区数据拼接
                    USB_Class_Write_Sector(pfi->File_CurSec,pexb_buf); //回写扇区数据
                    (just_file->exb_cursec)=0; //文件的独立EXB未占用

                }
                else
                {
                    USB_Class_Write_Sector(pfi->File_CurSec,WriteBuff); //回写扇区数据
                }
                if(IS_END_SEC_OF_CLU(pfi->File_CurSec,pfi->File_CurClust)) //如果当前扇区是当前簇的最后一个扇区
                {
                    pfi->File_CurSec=SOC(pfi->File_CurClust); //更新当前扇区，其实无效，为了规整
                }
                else //当前扇区不是当前簇的最后扇区
                {
                    pfi->File_CurSec++;
                }
                pfi->File_CurPos=0;
                pfi->File_CurOffset+=len; //更新当前偏移量
                pfi->File_Size+=len; //更新文件大小
                return len;
            }
            else//len小于当前扇区剩余数据量
            {
                if((0==(just_file->exb_cursec)) && (0!=(pfi->File_CurPos))) //当前文件的独立EXB未被占用，且文件当前扇区内偏移不为0，如果为0则没必要读扇区
                {
                    USB_Class_Read_Sector(pfi->File_CurSec,pexb_buf);
                }
                Memory_Copy(pexb_buf+pfi->File_CurPos,WriteBuff,len); //扇区数据拼接
                (just_file->exb_cursec)=pfi->File_CurSec;
                pfi->File_CurPos+=(UINT16)len;
                pfi->File_CurOffset+=len; //更新当前偏移量
                pfi->File_Size+=len; //更新文件大小
                return len;
            }
        }
        else
        {
            if(0!=pfi->File_CurPos)
            {
                if(0==(just_file->exb_cursec))
                {
                    USB_Class_Read_Sector(pfi->File_CurSec,pexb_buf);
                }
                Memory_Copy(pexb_buf+pfi->File_CurPos,WriteBuff,temp); //扇区数据拼接
                USB_Class_Write_Sector(pfi->File_CurSec,pexb_buf); //回写扇区数据
                (just_file->exb_cursec)=0; //当前文件独立EXB未被占用
            }
            else //如果当前位置在0位置，则直接写扇区
            {
                USB_Class_Write_Sector(pfi->File_CurSec,WriteBuff); //回写扇区数据
            }
            len_temp-=temp;
            WriteBuff+=temp;
            if(!(IS_END_SEC_OF_CLU(pfi->File_CurSec,pfi->File_CurClust))) //如果当前扇区不是当前簇的最后一个扇区
            {
                pfi->File_CurSec++;
                pfi->File_CurPos=0;
                pfi->File_CurOffset+=temp;
                temp=(LAST_SEC_OF_CLU(pfi->File_CurClust)-(pfi->File_CurSec)+1)*(pInit_Args->BytesPerSector);//当前簇中的剩余整整扇区数据量
                if(len_temp<=temp) //如果要写入的数据量小于等于当前簇中的剩余整扇区数据量
                {
                    temp1=len_temp/(pInit_Args->BytesPerSector); //计算要写入的数据量够几个整扇区
                    USB_Class_Write_nSector(temp1,pfi->File_CurSec,WriteBuff);
                    WriteBuff+=((pInit_Args->BytesPerSector)*temp1);
                    if(len_temp==temp) //如果正好写满当前簇
                    {
                        pfi->File_CurSec=SOC(pfi->File_CurClust); //囧簇
                        pfi->File_CurPos=0;
                        pfi->File_CurOffset+=len_temp;
                        pfi->File_Size+=len;
                        return len;
                    }
                    else
                    {
                        pfi->File_CurSec+=temp1;
                        pfi->File_CurPos=(UINT16)(len_temp%(pInit_Args->BytesPerSector));
                        if(pfi->File_CurPos) //还有要写的数据,处理最后的字节数据
                        {
                            Memory_Copy(pexb_buf,WriteBuff,pfi->File_CurPos);
                            just_file->exb_cursec=pfi->File_CurSec;
                        }
                        pfi->File_CurOffset+=len_temp;
                        pfi->File_Size+=len;
                        return len;
                    }
                }
                else
                {
                    temp1=temp/(pInit_Args->BytesPerSector);
                    USB_Class_Write_nSector(temp1,pfi->File_CurSec,WriteBuff);
                    WriteBuff+=temp;
                    len_temp-=temp;
                    pfi->File_CurSec=SOC(pfi->File_CurClust);
                    pfi->File_CurPos=0;
                    pfi->File_CurOffset+=temp;
                }
            }
            else //当前扇区是当前簇最后一个扇区
            {
                pfi->File_CurSec=SOC(pfi->File_CurClust);
                pfi->File_CurPos=0;
                pfi->File_CurOffset+=temp;
            }
        }
    }
    //如果文件的当前偏移量是簇大小的整数倍，则
    //直接进入空文件开始位置或整簇位置写数据的阶段
    WriteData_From_nCluster(pfi,len_temp,WriteBuff);
    pfi->File_Size+=len;
    return len;
}

//=====================================================================================
//函数名: znFAT_Delete_File
//功  能: 删除文件
//参  数: filepath:要删除的文件的路径
//返  回: 0=成功；1=失败
//备  注：调用USB类层函数USB_Class_Read_Sector和USB_Class_Write_Sector函数将相应的
//       文件删除
//=====================================================================================
UINT8 znFAT_Delete_File(INT8 *filepath)
{
    UINT8 res=0;
    struct FDIesInSEC *pitems; //指向文件目录项扇区数据的指针
    struct FileInfo fi;
    struct FDI *pitem; //指向文件目录项数据的指针
    res=znFAT_Open_File(&fi,filepath,0,BOOL_TRUE);
    if(res) return res;
    while(!res) //打开文件成功
    {
        USB_Class_Read_Sector(fi.FDI_Sec,znFAT_Buffer); //读取文件的文件目录项所在扇区
        pitems=(struct FDIesInSEC *)znFAT_Buffer;
        pitem=(pitems->FDIes)+fi.nFDI;
        if(0!=fi.File_StartClust) Destroy_FAT_Chain(fi.File_StartClust); //销毁整条簇链
        USB_Class_Read_Sector(fi.FDI_Sec,znFAT_Buffer); //读取文件目录项所在的扇区
        pitem->Name[0]=0XE5; //给文件目录项打上"已删除"的标记
        pitem->HighClust[0]=pitem->HighClust[1]=0; //开始簇的高字清0
        USB_Class_Write_Sector(fi.FDI_Sec,znFAT_Buffer); //回写扇区
        res=znFAT_Open_File(&fi,filepath,0,BOOL_TRUE);
    }
    znFAT_Close_File(&fi);
    return ERR_SUCC;
}

//=====================================================================================
//函数名: znFAT_Create_File
//功  能: 创建文件
//参  数: pfi:要创建的文件信息结构体
//       pfn:文件名
//       pdt:文件创建的日期
//返  回: 0=成功；1=失败
//备  注：调用USB类层函数USB_Class_Read_Sector函数创建相应的文件
//=====================================================================================
UINT8 znFAT_Create_File(struct FileInfo *pfi,INT8 *pfn,struct DateTime *pdt)
{
    UINT32 Cur_Cluster=0,pos=0,sec=0;
    UINT8 res=0,n=0;
    struct FDI fdi;
    INT8 *filename;
    UINT8 is_lfn=0;
    INT8 temp_filename[13];
    just_file=pfi;
    just_file->exb_cursec=0;
    res=znFAT_Enter_Dir(pfn,&Cur_Cluster,&pos); //进入目录
    if(res)
    {
        return res;
    }
    filename=pfn+pos;
    if(Check_Illegal_Char(filename)) return ERR_ILL_CHAR; //检查文件名中是否有非法字符
    #ifdef USE_LFN
    if(!Is_LFN(filename))
    {
        //检查短文件名合法性，若非法则直接返回，不再进行后面的处理(此处对SFN的合法性检查非常严格)
        //事先检查SFN的合法性，减少后面处理上的麻烦
        if(Check_SFN_Illegal_Length(filename)) return ERR_SFN_ILL_LEN; //检查SFN是否符合8.3长度
        if(Check_SFN_Dot(filename)) return ERR_SFN_DOT; //检查SFN中.是否合法
        if(Check_SFN_Special_Char(filename)) return ERR_SFN_SPEC_CHAR; //检查SFN中是否有特殊字符
        if(((UINT8)(-1))==Check_SFN_Illegal_Lower(filename))
            return ERR_SFN_ILL_LOWER; //检查SFN中是否有非法的大小写
    }
    else
    {
        is_lfn=1;
        res=oemstr2unistr(filename,pfi->longname); //如果是长名，则将filename转为UNI串
        if(res)
            return res;
    }
    if(!is_lfn) //如果不是长名
    {
        #endif
        Fill_FDI(&fdi,filename,pdt,BOOL_TRUE); //构造文件目录项
        res=Register_FDI(Cur_Cluster,&fdi,&sec,&n);//在当前簇中进行文件目录项的"注册"
        #ifdef USE_LFN
    }
    else //如果是长名
    {
        Make_Short_Name(filename,temp_filename);
        Fill_FDI(&fdi,temp_filename,pdt,BOOL_TRUE); //构造文件目录项
        res=Register_LFN_FDI(Cur_Cluster,&fdi,(pfi->longname),&sec,&n); //在当前簇中进行长名项及相应短名项“注册”
    }
     #endif
    if(!res)
    {
        //将新建文件的信息装入文件信息集合
            #ifdef USE_LFN
        if(is_lfn)
        {
            StringCopy(pfi->File_Name,temp_filename);
            pfi->have_lfn=1;
        }
        else
            #endif
        {
            StringCopy(pfi->File_Name,filename);
        }
        pfi->File_Attr=0X20;
        (pfi->File_CTime).hour=(pdt->time).hour;
        (pfi->File_CTime).min=(pdt->time).min;
        (pfi->File_CTime).sec=(pdt->time).sec;
        (pfi->File_CDate).year=(pdt->date).year;
        (pfi->File_CDate).month=(pdt->date).month;
        (pfi->File_CDate).day=(pdt->date).day;
        pfi->File_StartClust=0;
        pfi->File_Size=0;
        pfi->File_CurClust=0;
        pfi->File_CurSec=0;
        pfi->File_CurPos=0;
        pfi->File_CurOffset=0;
        pfi->File_IsEOF=BOOL_TRUE;
        pfi->FDI_Sec=sec;
        pfi->nFDI=n;
        return ERR_SUCC;
    }
    else
    {
        if(res==ERR_FDI_ALREADY_EXISTING) //如果文件已经存在，则直接解析它
        {
            USB_Class_Read_Sector(sec,znFAT_Buffer); //如果重名文件目录项所在的扇区
            Analyse_FDI(pfi,(((struct FDIesInSEC *)znFAT_Buffer)->FDIes)+n); //解析匹配的文件目录项
            pfi->FDI_Sec=sec;
            pfi->nFDI=n;
            if(is_lfn)
            {
                pfi->have_lfn=1;
            }
            else
            {
                pfi->have_lfn=0;
            }
        }
        return res;
    }
}

//=================================================================================
//函数名: znFAT_Delete_Dir
//功  能: 删除指定文件夹
//参  数:dirpath：要删除的文件夹路径
//返  回: 0=成功；1=失败
//备  注：调用USB类层函数USB_Class_Read_Sector和USB_Class_Write_Sector函数删除指定的
//      文件夹
//==================================================================================
UINT8 znFAT_Delete_Dir(INT8 *dirpath)
{
    UINT32 top_dir_first_cluster=0,sub_dir_first_cluster=0;
    UINT8 res=0;
    struct FDIesInSEC *pitems; //指向文件目录项扇区数据的指针
    struct FileInfo fi;
    res=znFAT_Open_File(&fi,dirpath,0,BOOL_FALSE); //尝试打开目录
    if(res) return res; //如果打开目录失败，则直接返回错误码
    while(!res) //目录打开成功
    {
        top_dir_first_cluster=fi.File_StartClust; //顶层目录的首簇
        sub_dir_first_cluster=top_dir_first_cluster;
        //以下代码将顶级目录下所有内容(文件、子目录及子目录中的内容，含递归)销毁
        Enter_Deep_Ahead_Dir(&sub_dir_first_cluster); //获取最深最靠前的目录首簇
        while(sub_dir_first_cluster!=top_dir_first_cluster) //如果最深最靠前目录首簇就是要删除的顶级目录
        {                                                   //则说明顶级目录下的所有内容都已经清空
            Get_Upper_Dir(&sub_dir_first_cluster); //获取上一层目录首簇
            Have_Any_SubDir_With_Del_ForeFile(&sub_dir_first_cluster,BOOL_TRUE); //把已清空其内容的子目录销毁
            Enter_Deep_Ahead_Dir(&sub_dir_first_cluster); //获取最深最靠前的目录首簇
        }
        //销毁顶级目录对应的文件目录项及其簇链
        USB_Class_Read_Sector(fi.FDI_Sec,znFAT_Buffer); //读取文件目录项所在的扇区
        pitems=(struct FDIesInSEC *)znFAT_Buffer;
        Destroy_FDI((pitems->FDIes)+fi.nFDI); //销毁顶级目录
        USB_Class_Read_Sector(fi.FDI_Sec,znFAT_Buffer); //读取文件目录项所在的扇区
        (pitems->FDIes)[fi.nFDI].Name[0]=0XE5;
        (pitems->FDIes)[fi.nFDI].HighClust[0]=(pitems->FDIes)[fi.nFDI].HighClust[1]=0;
        USB_Class_Write_Sector(fi.FDI_Sec,znFAT_Buffer); //回写扇区
        res=znFAT_Open_File(&fi,dirpath,0,BOOL_FALSE); //尝试打开目录
    }
    znFAT_Close_File(&fi);
    return ERR_SUCC;
}


//=================================================================================
//函数名: znFAT_Create_Dir
//功  能: 创建指定文件夹
//参  数: pdp：要创建的文件夹路径
//       pdt:创建的文件夹日期
//返  回: 0=成功；1=失败
//==================================================================================
UINT8 znFAT_Create_Dir(INT8 *pdp,struct DateTime *pdt)
{
    UINT32 Cur_Cluster=0,i=0;
    UINT8 index=0,res=0;
    UINT8 dirname[MAX_LFN_LEN+1];
    if(znFAT_Enter_Dir(pdp,&Cur_Cluster,&i)) //进入目录，如果中途发生错误
    {                                        //比如某一级目录名不合法，或
        while('\0'!=pdp[i])                     //目录不存在，则将最近的一层
        {                                       //目录的首簇记录在Cur_Cluster里
            if('\\'==pdp[i] || '/'==pdp[i])     //而将失败的那一级目录名的第一
            {                                   //字符的位置记录在i中
                dirname[index]='\0';            //比如\a1\b2\c3\e4\f5\，目录c3不存在
                index=0;                        //则Cur_Cluster为目录b2的首簇，i记录的是'c'的位置即7
                res=Create_Dir_In_Cluster(&Cur_Cluster,(INT8 *)dirname,pdt); //在簇Cur_Cluster中创建目录
                if(res)
                {
                    return res;  //返回错误码
                }
            }
            else
            {
                dirname[index]=pdp[i];
                index++;
                if(index>MAX_LFN_LEN) //如果使用长名，则目录名以及文件名最长不能超过设定的长名最长长度
                {
                    return ERR_LFN_BUF_OUT; //目录名长于MAX_LFN_LEN，亦防止dirname溢出
                }
            }
            i++;
        }
        return ERR_SUCC; //成功
    }
    else
    {
        return ERR_DIR_ALREADY_EXISTING; //要创建的目录已经存在了
    }
}

//=====================================================================================
//函数名: znFAT_Flush_FS
//功  能: 刷新文件系统
//参  数: 无
//返  回: 0=成功；1=失败
//=====================================================================================
UINT8 znFAT_Flush_FS(void)
{
    if(Update_FSINFO()==0) //更新文件系统信息
        return 0;
    else
        return 1;
}


//===================================以下是内部函数=====================================
UINT8 Memory_Set(UINT8 *pmem,UINT32 len,UINT8 value)
{
 UINT32 i=0;
 for(i=0;i<len;i++)
 {
  pmem[i]=value;
 }

 return 0;
}

UINT8 Memory_Compare(UINT8 *psmem,UINT8 *pdmem,UINT32 len)
{
 UINT32 i=0;

 for(i=0;i<len;i++)
 {
  if(psmem[i]!=pdmem[i])
  {
   return 0;
  }
 }
 return 1;
}

UINT8 * Memory_Copy(UINT8 *pdmem,UINT8 *psmem,UINT32 len)
{
 UINT32 i=0;

 for(i=0;i<len;i++)
 {
  pdmem[i]=psmem[i];
 }

 return pdmem;
}

INT8 * StringCopy(INT8 *dest_str,INT8 *src_str)
{
 UINT8 i=0;

 while('\0'!=src_str[i])
 {
  dest_str[i]=src_str[i];
  i++;
 }

 dest_str[i]='\0';

 return dest_str;
}

UINT32 StringLen(INT8 *pstr)
{
 UINT32 len=0;
 while('\0'!=pstr[len])
 {
  len++;
 }
 return len;
}

UINT32 WStringLen(UINT16 *str)
{
 UINT32 i=0;
 while(0!=str[i])
 {
  i++;
 }

 return i;
}

//=============================FLASHROM 操作相关函数=====================

UINT8 PGM_BYTE_FUN(ROM_TYPE_UINT8 *ptr)
{
 return *(ptr);
}

UINT16 PGM_WORD_FUN(ROM_TYPE_UINT16 *ptr)
{
 return *(ptr);
}

UINT32 PGM_DWORD_FUN(ROM_TYPE_UINT32 *ptr)
{
 return *(ptr);
}

UINT8 * PGM2RAM(UINT8 *pdmem,ROM_TYPE_UINT8 *psmem,UINT32 len)
{
 UINT32 i=0;

 for(i=0;i<len;i++)
 {
  pdmem[i]=PGM_BYTE_FUN((psmem+i));
 }

 return pdmem;
}


UINT32 Bytes2Value(UINT8 *dat,UINT8 len)
{
 UINT32 temp=0;

 if(len>=1) temp|=((UINT32)(dat[0]))    ;
 if(len>=2) temp|=((UINT32)(dat[1]))<<8 ;
 if(len>=3) temp|=((UINT32)(dat[2]))<<16;
 if(len>=4) temp|=((UINT32)(dat[3]))<<24;

 return temp;
}


UINT8 Find_FSINFO_Sec(UINT32 *fsinfosec) //寻找FSINFO扇区，里面有剩余簇数与可用的空簇
{
 UINT32 iSec=0;
 struct FSInfo *pfsinfo;

 UINT8 head[4]={'R','R','a','A'};
 UINT8 sign[4]={'r','r','A','a'}; //FSINFO扇区的标志

 for(iSec=(pInit_Args->BPB_Sector_No+1);iSec<(pInit_Args->FirstFATSector);iSec++)
 {
  USB_Class_Read_Sector(iSec,znFAT_Buffer);
  pfsinfo=((struct FSInfo *)znFAT_Buffer);
  if(Memory_Compare(pfsinfo->Head,head,4) //判断扇区是否是FSINFO扇区
     && Memory_Compare(pfsinfo->Sign,sign,4))
  {
   *fsinfosec=iSec;
   return ERR_SUCC;
  }
 }

 return ERR_FAIL;
}

UINT8 Search_Free_Cluster_From_Start(UINT32 *nFreeCluster)
{
 UINT32 iSec=0;
 UINT8  iItem=0;

 struct FAT_Sec *pFAT_Sec;

 for(iSec=0;iSec<pInit_Args->FATsectors;iSec++)
 {
  USB_Class_Read_Sector(pInit_Args->FirstFATSector+iSec,znFAT_Buffer); //读取FAT扇区
  pFAT_Sec=(struct FAT_Sec *)znFAT_Buffer;

  for(iItem=0;iItem<NITEMSINFATSEC;iItem++) //遍历所有簇项，寻找空闲簇
  {
   if((0==(((pFAT_Sec->items[iItem]).Item)[0])) && (0==(((pFAT_Sec->items[iItem]).Item)[1])) &&
      (0==(((pFAT_Sec->items[iItem]).Item)[2])) && (0==(((pFAT_Sec->items[iItem]).Item)[3])))
   {
    *nFreeCluster=((iSec*NITEMSINFATSEC)+(UINT32)iItem);
    return ERR_SUCC;
   }
  }
 }

 return    ERR_FAIL;
}


#ifdef UPDATE_FSINFO
UINT8 Update_FSINFO(void) //更新FSINFO扇区
{
 struct FSInfo *pfsinfo;
 USB_Class_Read_Sector(pInit_Args->FSINFO_Sec,znFAT_Buffer);

 pfsinfo=((struct FSInfo *)znFAT_Buffer);

 //写入剩余空簇数
 pfsinfo->Free_Cluster[0]=(UINT8)( pInit_Args->Free_nCluster&0X000000FF)    ;
 pfsinfo->Free_Cluster[1]=(UINT8)((pInit_Args->Free_nCluster&0X0000FF00)>>8);
 pfsinfo->Free_Cluster[2]=(UINT8)((pInit_Args->Free_nCluster&0X00FF0000)>>16);
 pfsinfo->Free_Cluster[3]=(UINT8)((pInit_Args->Free_nCluster&0XFF000000)>>24);

 //写入下一空闲簇参考值，并无多大意义
 pfsinfo->Next_Free_Cluster[0]=(UINT8)( pInit_Args->Next_Free_Cluster&0X000000FF)    ;
 pfsinfo->Next_Free_Cluster[1]=(UINT8)((pInit_Args->Next_Free_Cluster&0X0000FF00)>>8);
 pfsinfo->Next_Free_Cluster[2]=(UINT8)((pInit_Args->Next_Free_Cluster&0X00FF0000)>>16);
 pfsinfo->Next_Free_Cluster[3]=(UINT8)((pInit_Args->Next_Free_Cluster&0XFF000000)>>24);

 USB_Class_Write_Sector(pInit_Args->FSINFO_Sec,znFAT_Buffer);

 return 0;
}
#endif

#ifdef GET_NEXT_CLUSTER
UINT32 Get_Next_Cluster(UINT32 cluster)
{
 UINT32 clu_sec=0;
 struct FAT_Sec *pFAT_Sec;
 struct FAT_Item *pFAT_Item;
 clu_sec=(cluster/NITEMSINFATSEC)+(pInit_Args->FirstFATSector); //指定簇的簇项所在的扇区为其FAT区内的偏移量加上
 USB_Class_Read_Sector(clu_sec,znFAT_Buffer); //将簇项所在的扇区数据读入缓冲区

 pFAT_Sec=(struct FAT_Sec *)znFAT_Buffer; //将数据缓冲区首地址强转为FAT_Sec结构体的指针类型

 pFAT_Item=&((pFAT_Sec->items)[cluster%NITEMSINFATSEC]); //获取指定簇的簇项在所在扇区中的地址

 return Bytes2Value((UINT8 *)pFAT_Item,NFATITEMBYTES); //返回簇项的值，即指定簇下一簇的簇号
}
#endif


#ifdef ZNFAT_SEEK
UINT8 znFAT_Seek(struct FileInfo *pfi,UINT32 offset)
{
 UINT32 Cluster_Size=((pInit_Args->SectorsPerClust)*(pInit_Args->BytesPerSector)); //计算簇的总字节数据，以免后面重复计算
 UINT32 temp=0,temp1=0,temp2=0,len=0,k=0,ncluster=0,have_read=0;

 just_file=pfi;

 if(offset<(pfi->File_Size)) //如果要定位到的偏移量小于文件大小，则必定不在文件末尾
 {
  pfi->File_IsEOF=BOOL_FALSE;
 }

 if(offset==(pfi->File_CurOffset)) return 0; //如果要定位的位置正好是当前偏移量，则直接返回

 if(offset<(pfi->File_CurOffset)) //如果要定位的位置在当前偏移量之前，则先回到文件起点，因为簇链是单向的
 {
  pfi->File_CurClust=pfi->File_StartClust;
  pfi->File_CurSec=SOC(pfi->File_CurClust);
  pfi->File_CurPos=0;
  pfi->File_CurOffset=0;
  pfi->File_IsEOF=BOOL_FALSE;
 }

 len=offset-(pfi->File_CurOffset); //计算目标偏移量到当前偏移量之间的数据长度

 if(offset>=(pfi->File_Size)) //如果从当前位置开始要读取的数据长度len不小于文件大小
 {
  len=(pfi->File_Size-pfi->File_CurOffset);    //对len进行修正，置为文件剩余可读数据量。
  pfi->File_IsEOF=BOOL_TRUE;    //这种情况下，文件必然会读到末尾。
 }

 //===================================================================
 if((pfi->File_CurOffset%Cluster_Size)!=0) //如果当前偏移量是簇大小整数倍，说明此位置即为整簇开始
 {                                         //不要再进行当前簇内数据处理，直接进入簇-扇区-字节阶段
  if(len<=(pInit_Args->BytesPerSector-pfi->File_CurPos))
  {
   //更新当前位置参数
   if((pInit_Args->BytesPerSector-pfi->File_CurPos)==len) //如果正好读到当前扇区的末尾
   {
    if(IS_END_SEC_OF_CLU(pfi->File_CurSec,pfi->File_CurClust))//如果当前扇区是当前簇的最后一个扇区
    {
     if(!pfi->File_IsEOF)
     {
      pfi->File_CurClust=Get_Next_Cluster(pfi->File_CurClust);
     }
     pfi->File_CurSec=SOC(pfi->File_CurClust);
    }
    else
    {
     pfi->File_CurSec++;
    }
    pfi->File_CurPos=0;
   }
   else
   {
    pfi->File_CurPos+=((UINT16)len);
   }
   pfi->File_CurOffset+=len;

   return NUL_RET;
  }
  //===================================================================
  else
  {
   temp=(pInit_Args->BytesPerSector-pfi->File_CurPos); //将当前扇区的剩余数据量赋给中间变量temp
   have_read+=temp;

   if(!(IS_END_SEC_OF_CLU(pfi->File_CurSec,pfi->File_CurClust))) //如果当前扇区不是当前簇的最后一个扇区
   {
    pfi->File_CurSec++;
    pfi->File_CurPos=0;

    temp2=(len-have_read); //计算剩余数据量
    temp1=((LAST_SEC_OF_CLU(pfi->File_CurClust)-(pfi->File_CurSec-1))*(pInit_Args->BytesPerSector)); //剩余所有扇区数据量
    if(temp2<=temp1) //如果剩余数据量xxx
    {
     //这说明要读的数据在当前簇内，没有跨到下一簇
     temp=temp2/(pInit_Args->BytesPerSector); //计算当前簇内整扇区读取的结束扇区
        have_read+=((pInit_Args->BytesPerSector)*temp);

     if(temp2==temp1)
     {
      if(!pfi->File_IsEOF)
      {
       pfi->File_CurClust=Get_Next_Cluster(pfi->File_CurClust);
      }
      pfi->File_CurSec=SOC(pfi->File_CurClust);
      pfi->File_CurPos=0;
     }
     else
     {
      pfi->File_CurSec+=temp;
      //更新当前位置参数
      pfi->File_CurPos=(UINT16)(len-have_read);
     }
     pfi->File_CurOffset+=len;

     return NUL_RET;
    }
    else //如果剩余数据的整扇区数不小于当前簇的剩余扇区数，即要读的数据不光在当前簇内，已经跨簇了
    {
        temp=LAST_SEC_OF_CLU(pfi->File_CurClust)-(pfi->File_CurSec)+1; //计算当前簇的剩余整扇区数
        have_read+=((pInit_Args->BytesPerSector)*temp);
    }
   }

   //更新当前位置参数，此时已经读完当前簇的所有剩余数据，跨到下一簇
   pfi->File_CurClust=Get_Next_Cluster(pfi->File_CurClust);
   pfi->File_CurSec=SOC(pfi->File_CurClust);
   pfi->File_CurPos=0;
  }
 }
 //----------------------------以上是处理当前簇内的数据-------------------------------------
 if(len-have_read>0)
 {
  ncluster=(len-have_read)/Cluster_Size; //计算剩余数据的整簇数

  //更新当前位置参数，此时已经读完所有的整簇数据

  for(k=0;k<ncluster;k++) //读取整簇数据
  {
   have_read+=(Cluster_Size);
   if(!((len-have_read)==0 && pfi->File_IsEOF))
   {
    pfi->File_CurClust=Get_Next_Cluster(pfi->File_CurClust);
   }
  }

  pfi->File_CurSec=SOC(pfi->File_CurClust);

  //----------------------------以上是处理整簇数据------------------------------------------
  if(len-have_read>0)
  {
   temp=(len-have_read)/(pInit_Args->BytesPerSector); //计算最终剩余数据的整扇区数
   have_read+=((pInit_Args->BytesPerSector)*temp);

   pfi->File_CurSec+=temp;
   //----------------------------以上是处理整扇区数据----------------------------------------
   if(len-have_read>0)
   {
    //更新当前位置参数，此时数据读取操作已经结束
    pfi->File_CurPos=(UINT16)(len-have_read);
   }
   //----------------------------以上是处理最后扇区内的剩余字节----------------------------------------
  }
 }

 pfi->File_CurOffset+=len;

 return 0;
}
#endif




#ifdef CHECK_ILLEGAL_CHAR
UINT8 Check_Illegal_Char(INT8 *pfn)
{
 UINT32 i=0;
 while(pfn[i])
 {
  if(('\\'==pfn[i]) || ('/'==pfn[i]) || (':'==pfn[i])
   || /*('*'==pfn[i]) || ('?'==pfn[i]) ||*/ ('"'==pfn[i])
   || ('<'==pfn[i]) || ('>'==pfn[i]) || ('|'==pfn[i]))
  return ERR_FAIL;
  i++;
 }
 return ERR_SUCC;
}
#endif

#ifdef CHECK_SFN_SPECIAL_CHAR
UINT8 Check_SFN_Special_Char(INT8 *pfn)
{
 UINT32 i=0;
 UINT32 pos=(StringLen(pfn)-1);

 while(' '==pfn[pos]) pos--;

 while(i<=pos)
 {
  if( ('+'==pfn[i]) || ('['==pfn[i])
   || (']'==pfn[i]) || (','==pfn[i])
   || (' '==pfn[i]) || (';'==pfn[i])
   || ('='==pfn[i]))
  return ERR_FAIL;
  i++;
 }

 return ERR_SUCC;
}
#endif


#ifdef CHECK_SFN_DOT
UINT8 Check_SFN_Dot(INT8 *pfn)
{
 UINT32 pos=(StringLen(pfn)-1);
 UINT32 dot_counter=0;

 if('.'==pfn[0]) return ERR_FAIL;

 while(pos>0)
 {
  if('.'==pfn[pos])
  {
   dot_counter++;
  }
  pos--;
 }

 if(dot_counter>1) return ERR_FAIL;
 else return ERR_SUCC;
}
#endif


#ifdef CHECK_SFN_ILLEGAL_LOWER
UINT8 Check_SFN_Illegal_Lower(INT8 *pfn)
{
 UINT32 i=(StringLen(pfn)-1);
 UINT8 flag1=2,flag2=2;

 while('.'!=pfn[i] && i>0)
 {
  if(pfn[i]>='a' && pfn[i]<='z')
  {
   if(0==flag1)
   {
    return (UINT8)-1;
   }
   flag1=1;
  }

  if(pfn[i]>='A' && pfn[i]<='Z')
  {
   if(1==flag1)
   {
    return (UINT8)-1;
   }
   flag1=0;
  }

  i--;
 }

 if(0==i) //如果没有.说明没有扩展名
 {
  if(pfn[0]>='a' && pfn[0]<='z')
  {
   if(0==flag1)
   {
    return (UINT8)-1;
   }
   flag1=1;
  }

  flag2=flag1;
  flag1=0;
 }

 if('.'==pfn[i])
 {
  i--;
 }

 while(i>0)
 {
  if(pfn[i]>='a' && pfn[i]<='z')
  {
   if(0==flag2)
   {
    return (UINT8)-1;
   }
   flag2=1;
  }

  if(pfn[i]>='A' && pfn[i]<='Z')
  {
   if(1==flag2)
   {
    return (UINT8)-1;
   }
   flag2=0;
  }

  i--;
 }

 if(2==flag2)
 {
  if(pfn[0]>='a' && pfn[0]<='z')
  {
   flag2=1;
  }
  if(pfn[0]>='A' && pfn[0]<='Z')
  {
   flag2=0;
  }
 }

 return (UINT8)((flag1<<4)|(flag2));
}
#endif

#ifdef CHECK_SFN_ILLEGAL_LENGTH
UINT8 Check_SFN_Illegal_Length(INT8 *pfn)
{
 UINT8 dot_pos=0,have_dot=0,i=0;
 UINT8 mainfn_len=0,extfn_len=0;
 UINT32 fn_len=StringLen(pfn);

 while(' '==pfn[fn_len-1]) fn_len--;

 if(fn_len>12) return ERR_FAIL; //fn is longer than 8.3

 for(i=(UINT8)(fn_len-1);i>0;i--) //反向寻找. 第一个.是主文件与扩展名的分界
 {
  if('.'==pfn[i])
  {
   dot_pos=i;
   have_dot=1;
   break;
  }
 }

 if(0==have_dot) //没有点
 {
  mainfn_len=(UINT8)fn_len;
  extfn_len=0;

  if((mainfn_len>0 && mainfn_len<=8))
  {
   return ERR_SUCC;
  }
  else
  {
   return ERR_FAIL;
  }
 }
 else //有点
 {
  mainfn_len=dot_pos;
  extfn_len=(UINT8)(((UINT8)fn_len)-(UINT8)(dot_pos+1));

  if(( mainfn_len>0  && mainfn_len<=8)
   && (/*extfn_len>=0  && */extfn_len <=3))
  {
   return ERR_SUCC;
  }
  else
  {
   return ERR_FAIL;
  }
 }
}
#endif

#ifdef TO_FILE_NAME
UINT8 To_File_Name(INT8 *name_in_fdi,INT8 *pfileName)
{
 UINT8 i=0,n=7,m=10;

 while(' '==name_in_fdi[n])
 {
  n--;
 }
 n++;

 while(' '==name_in_fdi[m] && m>=8)
 {
  m--;
 }
 m-=7;

 for(i=0;i<n;i++)
 {
  pfileName[i]=name_in_fdi[i];
 }
 pfileName[i]='.';

 for(i=0;i<m;i++)
 {
  pfileName[n+i+1]=name_in_fdi[8+i];
 }

 if('.'==pfileName[n+m]) pfileName[n+m]=0;
 else pfileName[n+m+1]=0;

 return 0;
}
#endif


#ifdef ANALYSE_FDI
UINT8 Analyse_FDI(struct FileInfo *pfi,struct FDI *pFDI)
{
 UINT32 temp=0,i=0;

 //==========================================================

 just_file=pfi;

 To_File_Name((INT8 *)pFDI,pfi->File_Name);

 temp=(StringLen(pfi->File_Name)-1);
 while('.'!=(pfi->File_Name)[temp] && temp>0)
 {
  if(((pFDI->LowerCase)&0x10)!=0)
  {
   (pfi->File_Name)[temp]=(INT8)Upper2Low((pfi->File_Name)[temp]);
  }
  temp--;
 }
 if(((pFDI->LowerCase)&0x08)!=0)
 {
  for(i=0;i<temp;i++)
  {
   (pfi->File_Name)[i]=(INT8)Upper2Low((pfi->File_Name)[i]);
  }
 }

 temp=(StringLen(pfi->File_Name)-1);
 if(CHK_ATTR_DIR(pFDI->Attributes)) //如果是目录则将最后的.去掉
 {
  (pfi->File_Name)[temp+1]='\0';
 }
 //==以上是按照LowerCase字节对主文件名与扩展文件名进行小写化

 pfi->File_Attr=pFDI->Attributes; //文件属性
 pfi->File_StartClust=Bytes2Value(pFDI->LowClust,2)+Bytes2Value(pFDI->HighClust,2)*65536;
 pfi->File_Size=Bytes2Value(pFDI->FileSize,4);

 //解析文件创建时间与日期
 temp=Bytes2Value(pFDI->CTime,2);
 pfi->File_CTime.sec=(UINT8)((temp&TIME_SEC_MARK)*2); temp>>=TIME_SEC_NBITS;  //创建时间的2秒位
 pfi->File_CTime.min=(UINT8)(temp&TIME_MIN_MARK);   temp>>=TIME_MIN_NBITS; //创建时间的分位
 pfi->File_CTime.hour=(UINT8)(temp&TIME_HOUR_MARK); //创建时间的时位
 pfi->File_CTime.sec+=(UINT8)((UINT16)(pFDI->CTime10ms)/100); //在秒上加上10毫秒位

 temp=Bytes2Value(pFDI->CDate,2);
 pfi->File_CDate.day=(UINT8)(temp&DATE_DAY_MARK);     temp>>=DATE_DAY_NBITS;   //创建日期的日位
 pfi->File_CDate.month=(UINT8)(temp&DATE_MONTH_MARK); temp>>=DATE_MONTH_NBITS; //创建日期的月位
 pfi->File_CDate.year=(UINT16)((temp&DATE_YEAR_MARK)+DATE_YEAR_BASE); //创建日期的年位（加上年份基数）

 pfi->File_CurClust=pfi->File_StartClust;
 pfi->File_CurSec=(pfi->File_CurClust)?SOC(pfi->File_CurClust):0;
 pfi->File_CurPos=0;
 pfi->File_CurOffset=0;
 pfi->File_IsEOF=(UINT8)((pfi->File_StartClust)?BOOL_FALSE:BOOL_TRUE);

 return 0;
}
#endif


#ifdef IS_WILDFILENAME
UINT8 Is_WildFileName(INT8 *pfn)
{
 UINT8 i=0;
 while('\0'!=pfn[i])
 {
  if('*'==pfn[i] || '?'==pfn[i])
  {
   return 1;
  }
  i++;
 }
 return 0;
}
#endif

#ifdef FINDSUBSTR
UINT8 FindSubStr(INT8 *str,INT8 *substr,UINT8 pos)
{
 UINT8 i=pos,j=0,lens=(UINT8)StringLen(str),lent=(UINT8)StringLen(substr);

 while(i<lens && j<lent)
 {
  if(str[i]==substr[j] || '?'==substr[j])
  {
   i++;
   j++;
  }
  else
  {
   i=(UINT8)(i-j+1);
   j=0;
  }
 }
 if(j==lent) return (UINT8)(i-lent);
 else return (UINT8)0XFF;
}
#endif


#ifdef SFN_MATCH
UINT8 SFN_Match(INT8 *t,INT8 *s)
{
 UINT8 i=0,j=0,lens=(UINT8)StringLen(s);
 UINT8 lent=(UINT8)StringLen(t);
 INT8 buf[20];
 UINT8 bufp=0;

 //======================================================

 while(j<lent && '*'!=t[j])
 {
  buf[bufp]=(INT8)Lower2Up(t[j]);
  bufp++;
  j++;
 }

 if('\0'==t[j] && (lent!=lens)) return ERR_FAIL;

 buf[bufp]='\0';

 if(FindSubStr(s,buf,0)!=0) return ERR_FAIL;
 i=bufp;

 while(1)
 {
  while(j<lent && '*'==t[j]) j++;
  if(j==lent) return ERR_SUCC;
  bufp=0;

  while(j<lent && '*'!=t[j])
  {
   buf[bufp]=(INT8)Lower2Up(t[j]);
   bufp++;
   j++;
  }
  buf[bufp]='\0';

  if(j==lent)
  {
   if(FindSubStr(s,buf,i)!=(lens-bufp)) return ERR_FAIL;
   return ERR_SUCC;
  }

  i=FindSubStr(s,buf,i);
  if(0XFF==i) return ERR_FAIL;
  i+=bufp;
 }
}
#endif

#ifdef MODIFY_FAT
UINT8 Modify_FAT(UINT32 cluster,UINT32 next_cluster) //构造FAT簇链
{
 UINT32 temp1=0,temp2=0;

 if(0==cluster || 1==cluster) return ERR_FAIL; //簇项0与1是不能更改的

 temp1=pInit_Args->FirstFATSector+(cluster*4/pInit_Args->BytesPerSector);
 temp2=((cluster*4)%pInit_Args->BytesPerSector);

 USB_Class_Read_Sector(temp1,znFAT_Buffer);
 znFAT_Buffer[temp2+0]=(UINT8)( next_cluster&0x000000ff)     ;
 znFAT_Buffer[temp2+1]=(UINT8)((next_cluster&0x0000ff00)>>8 );
 znFAT_Buffer[temp2+2]=(UINT8)((next_cluster&0x00ff0000)>>16);
 znFAT_Buffer[temp2+3]=(UINT8)((next_cluster&0xff000000)>>24);
 USB_Class_Write_Sector(temp1,znFAT_Buffer);

 USB_Class_Read_Sector(temp1+pInit_Args->FATsectors,znFAT_Buffer);
 znFAT_Buffer[temp2+0]=(UINT8)( next_cluster&0x000000ff)     ;
 znFAT_Buffer[temp2+1]=(UINT8)((next_cluster&0x0000ff00)>>8 );
 znFAT_Buffer[temp2+2]=(UINT8)((next_cluster&0x00ff0000)>>16);
 znFAT_Buffer[temp2+3]=(UINT8)((next_cluster&0xff000000)>>24);
 USB_Class_Write_Sector(temp1+pInit_Args->FATsectors,znFAT_Buffer);

 return ERR_SUCC;
}
#endif


#ifdef CLEAR_CLUSTER
UINT8 Clear_Cluster(UINT32 cluster)
{
 znFAT_Device_Clear_nSector((pInit_Args->SectorsPerClust),SOC(cluster));

 return 0;
}
#endif

#ifdef UPDATE_NEXT_FREE_CLUSTER
UINT8 Update_Next_Free_Cluster(void)
{
 UINT32 clu_sec,iItem,iSec;
 struct FAT_Sec *pFAT_Sec;

 if(0!=pInit_Args->Free_nCluster) //磁盘仍有空间
 {
  pInit_Args->Free_nCluster--; //空闲簇数减1

  clu_sec=(pInit_Args->Next_Free_Cluster/NITEMSINFATSEC); //指定簇的簇项所在的扇区为其FAT区内的偏移量                                                                                 //FAT的首扇区
  USB_Class_Read_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer); //将簇项所在的扇区数据读入缓冲区
  pFAT_Sec=(struct FAT_Sec *)znFAT_Buffer; //将数据缓冲区首地址强转为FAT_Sec结构体的指针类型

  for(iItem=((pInit_Args->Next_Free_Cluster)%NITEMSINFATSEC)+1;iItem<NITEMSINFATSEC;iItem++) //检测在当前FAT扇区内当前簇项之后是否有空簇
  {
   if(0==(((pFAT_Sec->items)[iItem]).Item)[0]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[1]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[2]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[3])
   {
    pInit_Args->Next_Free_Cluster=(clu_sec*NITEMSINFATSEC)+iItem;
    #ifdef RT_UPDATE_FSINFO
    Update_FSINFO();
    #endif
    return ERR_SUCC;
   }
  }

  for(iSec=(clu_sec+1);iSec<(pInit_Args->FATsectors);iSec++) //在后面的FAT扇区中继续查找
  {
   USB_Class_Read_Sector(iSec+(pInit_Args->FirstFATSector),znFAT_Buffer);
   pFAT_Sec=(struct FAT_Sec *)znFAT_Buffer;
   for(iItem=0;iItem<NITEMSINFATSEC;iItem++) //检测在当前FAT扇区内当前簇项之后是否有空簇
   {
    if(0==(((pFAT_Sec->items)[iItem]).Item)[0]
    && 0==(((pFAT_Sec->items)[iItem]).Item)[1]
    && 0==(((pFAT_Sec->items)[iItem]).Item)[2]
    && 0==(((pFAT_Sec->items)[iItem]).Item)[3])
    {
     pInit_Args->Next_Free_Cluster=(iSec*NITEMSINFATSEC)+iItem;
     #ifdef RT_UPDATE_FSINFO
     Update_FSINFO();
     #endif
     return ERR_SUCC;
    }
   }
  }
 }
 pInit_Args->Next_Free_Cluster=2; //如果已无空间，即nFreeCluster为0，则将下一空簇设为2
                                  //WINDOWS就是这样作的
 return ERR_NO_SPACE;
}
#endif

#ifdef IS_LFN
UINT8 Is_LFN(INT8 *filename)
{
 UINT8 is_lfn=BOOL_FALSE;

 if(Check_SFN_Illegal_Length(filename)) is_lfn=BOOL_TRUE;
 if(Check_SFN_Dot(filename))            is_lfn=BOOL_TRUE;
 if(Check_SFN_Special_Char(filename))   is_lfn=BOOL_TRUE;
 if(((UINT8)(-1))==Check_SFN_Illegal_Lower(filename)) is_lfn=BOOL_TRUE;

 return is_lfn;
}
#endif

#ifdef GET_PART_NAME
UINT8 Get_Part_Name(UINT16 *lfn_buf,struct LFN_FDI *plfndi,UINT8 n)
{
 UINT8 i=0;
 UINT16 temp=0;

 if((plfndi->AttrByte[0])&0X40) Memory_Set(((UINT8 *)lfn_buf),2*(MAX_LFN_LEN+1),0); //如果是最后一个长名项，则清空lfn_buf

 for(i=0;i<5;i++) //第一部分长名
 {
  if(n>=MAX_LFN_LEN) return ERR_LFN_BUF_OUT;
  temp=(((UINT16)(((plfndi->Name1)+i*2)[0]))&0X00FF)|((((UINT16)(((plfndi->Name1)+i*2)[1]))&0X00FF)<<8);
  if(0==temp)
  {
   lfn_buf[n]=0;
   return 0;
  }
  else
  {
   lfn_buf[n]=temp;n++;
  }
 }

 for(i=0;i<6;i++) //第二部分长名
 {
  if(n>=MAX_LFN_LEN) return ERR_LFN_BUF_OUT;
  temp=(((UINT16)(((plfndi->Name2)+i*2)[0]))&0X00FF)|((((UINT16)(((plfndi->Name2)+i*2)[1]))&0X00FF)<<8);
  if(0==temp)
  {
   lfn_buf[n]=0;
   return 0;
  }
  else
  {
   lfn_buf[n]=temp;n++;
  }
 }

 for(i=0;i<2;i++) //第三部分长名
 {
  if(n>=MAX_LFN_LEN) return ERR_LFN_BUF_OUT;
  temp=(((UINT16)(((plfndi->Name3)+i*2)[0]))&0X00FF)|((((UINT16)(((plfndi->Name3)+i*2)[1]))&0X00FF)<<8);
  if(0==temp)
  {
   lfn_buf[n]=0;
   return 0;
  }
  else
  {
   lfn_buf[n]=temp;n++;
  }
 }

 n--;
 if((plfndi->AttrByte[0])&0X40)
 {
  while(((UINT16)(0XFFFF))==lfn_buf[n]) n--;
  lfn_buf[n+1]=0;
 }

 return 0;
}
#endif


#ifdef OEMTOUNI
UINT8 OEM2UNI(UINT16 oem_code,UINT16 *uni_code) //通过二分法查表将OEM码转为UNI码
{
 UINT32 low=0,high=MAX_UNI_INDEX-1,mid;//置当前查找区间上下界的初值

 if(oem_code<GET_PGM_WORD(&(oem_uni[0][1]))) return ERR_FAIL;
 if(oem_code>GET_PGM_WORD(&(oem_uni[MAX_UNI_INDEX-1][1]))) return ERR_FAIL; //如果输入的oem_code不是表的范围内，则直接返回

 while(low<=high) //当前查找区间[low..high]非空
 {
  mid=low+(high-low)/2;

  if(oem_code==GET_PGM_WORD(&(oem_uni[mid][1])))
  {
   *uni_code=GET_PGM_WORD(&(oem_uni[mid][0]));

   return ERR_SUCC; //查找成功返回
  }

  if(GET_PGM_WORD(&(oem_uni[mid][1]))>oem_code)
  {
   high=mid-1;  //继续在[low..mid-1]中查找
  }
  else
  {
   low=mid+1; //继续在[mid+1..high]中查找
  }
 }

 return ERR_FAIL; //当low>high时表示查找区间为空，查找失败
}
#endif

#ifdef OEMSTRTOUNISTR
UINT8 oemstr2unistr(INT8 *oemstr,UINT16 *unistr)
{
 UINT32 len=StringLen(oemstr);
 UINT32 i=0,pos=0;
 UINT8 res=0;
 UINT16 temp=0;

 for(i=0;i<len;i++)
 {
  if(IS_ASC(oemstr[i])) //检查是否是ASCII码，ASCII码的数值范围为0X00~0X7F，OEM编码值不在此范围，以此区分是ASCII还是OEM
  {
   unistr[pos]=(UINT16)(((UINT16)oemstr[i])&0X00FF);
   pos++;
  }
  #ifdef USE_OEM_CHAR
  else //不是ASCII码，而是OEM编码
  {
   temp=((((UINT16)oemstr[i])<<8)&0xff00);
   temp|=(((UINT16)oemstr[i+1])&0x00ff);
   res=OEM2UNI(temp,unistr+pos);
   if(res)
   {
      unistr[0]=0;
      return ERR_OEM_CHAR_NOT_COMPLETE;
   }
   pos++;i++;
  }
  #endif

  if(pos>MAX_LFN_LEN)
  {
   unistr[0]=0;
   return ERR_LFN_BUF_OUT;
  }
 }

 unistr[pos]=0;

 return ERR_SUCC;
}
#endif

#ifdef WFINDSUBSTR
UINT32 WFindSubStr(UINT16 *str,UINT16 *substr,UINT32 pos)
{
 UINT32 i=pos,j=0,lens=WStringLen(str),lent=WStringLen(substr);

 while(i<lens && j<lent)
 {
  if(WLower2Up(str[i])==substr[j] || (UINT16)'?'==substr[j])
  {
   i++;
   j++;
  }
  else
  {
   i=i-j+1;
   j=0;
  }
 }

 if(j==lent) return i-lent;
 else return (UINT32)-1;
}
#endif

#ifdef LFN_MATCH
UINT8 LFN_Match(UINT16 *t,UINT16 *s)
{
 UINT32 i=0,j=0,lens=WStringLen(s),lent=WStringLen(t);
 UINT16 bufp=0;

 UINT16 buf[MAX_LFN_LEN+1];

 //======================================================

 while(j<lent && (UINT16)'*'!=t[j])
 {
  buf[bufp]=WLower2Up(t[j]);
  bufp++;
  j++;
 }

 if(0==t[j] && (lent!=lens)) return ERR_FAIL;

 buf[bufp]=0;

 if(WFindSubStr(s,buf,0)!=0) return ERR_FAIL;
 i=bufp;

 while(1)
 {
  while(j<lent && (UINT16)'*'==t[j]) j++;
  if(j==lent) return ERR_SUCC;
  bufp=0;

  while(j<lent && (UINT16)'*'!=t[j])
  {
   buf[bufp]=(UINT16)WLower2Up(t[j]);
   bufp++;
   j++;
  }
  buf[bufp]=0;

  if(j==lent)
  {
   if(WFindSubStr(s,buf,i)!=(lens-bufp)) return ERR_FAIL;
   return 0;
  }

  i=WFindSubStr(s,buf,i);
  if(((UINT32)(-1))==i) return ERR_FAIL;
  i+=bufp;
 }
}
#endif

#ifdef GET_BINDING_SUMCHK
UINT8 Get_Binding_SumChk(struct FDI *pdi)
{
 UINT8 i=0,c=0;

 for(i=0;i<11;i++)
 {
  c=(UINT8)(((c&0X01)?0X80:0)+(c>>1)+((pdi->Name)[i]));
 }

 return c;
}
#endif

#ifdef    ELFHASH
UINT32 ELFHash(INT8 *str)
{
 UINT32 hash=0;
 UINT32 x=0;

 while(*str)
 {
  hash=(hash<<4)+(*str++); //hash左移4位，当前字符ASCII存入hash低四位。
  x=hash&0xF0000000;
  if(0!=x)
  { //如果最高的四位不为0，则说明字符多余7个，如果不处理，再加第九个字符时，第一个字符会被移出，因此要有如下处理。
    //该处理，如果对于字符串(a-z 或者A-Z)就会仅仅影响5-8位，否则会影响5-31位，因为C语言使用的算数移位
   hash ^= (x >> 24);
   //清空28-31位。
   hash &= ~x;
  }
 }

 //返回一个符号位为0的数，即丢弃最高位，以免函数外产生影响。(我们可以考虑，如果只有字符，符号位不可能为负)
 return (hash&0X7FFFFFFF);
}
#endif

#ifdef HEX2STR_32B
UINT8 Hex2Str_32b(UINT32 hex,INT8 *str)
{
 UINT8 i=0,temp=0;
 for(i=0;i<8;i++)
 {
  temp=((unsigned char)((hex&(0X0000000F<<(i*4)))>>(i*4)));
  str[7-i]=(INT8)((temp>=10)?('A'+temp-10):(temp+0X30));
 }
 str[i]=0;

 return 0;
}
#endif


#ifdef MAKE_SHORT_NAME
UINT8 Make_Short_Name(char *pfn,char *psfn) //此函数用于生成长名对应的短名，使用了ELFHASH算法用于生成唯一的短名
{
 //psfn[0]=Lower2Up(pfn[0]);
 //psfn[1]='~';
 UINT32 temp=ELFHash(pfn);
 Hex2Str_32b(temp,psfn);
 //psfn[0]='*';
 psfn[8]='.';
 psfn[9]=psfn[10]=psfn[11]='A';
 psfn[12]=0;

 return 0;
}
#endif

#ifdef FILL_LFN_FDI
UINT8 Fill_LFN_FDI(UINT16 *unifn,struct LFN_FDI *plfni,UINT8 ChkSum,UINT8 n)
{
 UINT8 temp=(UINT8)(n*13),i=0,j=0;
 UINT16 len=(UINT16)WStringLen(unifn+temp);

 (plfni->AttrByte[0])=(UINT8)(n+1); //长名项的序号字节
 if(len<=13) (plfni->AttrByte[0])|=0X40; //如果发现从当前位置开始的UNI串长度小于等于13，则说明书这是最后一个长名项

 (plfni->ChkVal[0])=ChkSum; //写入与SFN的绑定校验值
 (plfni->LFNSign[0])=0X0F; //长名项的标志

 (plfni->Resv[0])=(plfni->StartClu[0])=(plfni->StartClu[1])=0;

 for(i=0;i<10;i++) (plfni->Name1)[i]=0XFF;
 for(i=0;i<12;i++) (plfni->Name2)[i]=0XFF;
 for(i=0;i<4;i++)  (plfni->Name3)[i]=0XFF; //先把长名UNI的字段用0XFF填充

 for(i=0;i<5;i++)
 {
  (plfni->Name1)[2*i]=(UINT8)(unifn[j+temp]&0X00FF);
  (plfni->Name1)[2*i+1]=(UINT8)((unifn[j+temp]&0XFF00)>>8);
  j++;
  if(j>=len)
  {
   if(4==i)
   {
    (plfni->Name2)[0]=(plfni->Name2)[1]=0;
   }
   else
   {
    i++;
    (plfni->Name1)[2*i]=(plfni->Name1)[2*i+1]=0;
   }
   return ERR_SUCC;
  }
 }

 for(i=0;i<6;i++)
 {
  (plfni->Name2)[2*i]=(UINT8)(unifn[j+temp]&0X00FF);
  (plfni->Name2)[2*i+1]=(UINT8)((unifn[j+temp]&0XFF00)>>8);
  j++;
  if(j>=len)
  {
   if(5==i)
   {
    (plfni->Name3)[0]=(plfni->Name3)[1]=0;
   }
   else
   {
    i++;
    (plfni->Name2)[2*i]=(plfni->Name2)[2*i+1]=0;
   }
   return ERR_SUCC;
  }
 }

 for(i=0;i<2;i++)
 {
  (plfni->Name3)[2*i]=(UINT8)(unifn[j+temp]&0X00FF);
  (plfni->Name3)[2*i+1]=(UINT8)((unifn[j+temp]&0XFF00)>>8);
  j++;
  if(j>=len)
  {
   if(1!=i)
   {
    i++;
    (plfni->Name3)[2*i]=(plfni->Name3)[2*i+1]=0;
   }
   return ERR_SUCC;
  }
 }

 return ERR_SUCC;
}
#endif

#ifdef REGISTER_LFN_FDI
UINT8 Register_LFN_FDI(UINT32 cluster,struct FDI *pfdi,UINT16 *unifn,UINT32 *psec,UINT8 *pn)
{
 UINT32 temp_sec=0,old_cluster=0;
 UINT8 iClu=0,iSec=0,iFDI=0,res=0;
 struct FDIesInSEC *pitems;
 struct FDI *pitem;

 struct LFN_FDI *plfni;

 UINT8 have_lfn=0; //在文件目录项扫描过程种，用于标记是否有长名
 UINT8 is_lfn_buf_err=0,cur_binding_sumchk=0,flag=0,chksum=Get_Binding_SumChk(pfdi);
 UINT16 lfn_buf[MAX_LFN_LEN+1]; //用于装载长名UNI码的缓冲
 struct LFN_FDI temp_lfni; //用于构造长名项的临时结构体变量

 UINT16 len=(UINT16)WStringLen(unifn); //计算UNI串长度
 UINT8 nclu=0,nsec=0,nlfni=(UINT8)(len/13);
 if(len%13) nlfni++; //计算UNI串会分为多少个长名项

 //===========================================================================================

 if(0==pInit_Args->Free_nCluster) return ERR_NO_SPACE; //如果没有空间，则直接返回

 //以下代码检查是否已经存在重复的文件或目录，以及查询空位并填入目录项
 do
 {
  temp_sec=SOC(cluster);
  for(iSec=0;iSec<(pInit_Args->SectorsPerClust);iSec++)
  {
   USB_Class_Read_Sector(temp_sec+(UINT32)iSec,znFAT_Buffer);
   pitems=((struct FDIesInSEC *)znFAT_Buffer);

   for(iFDI=0;iFDI<NFDI_PER_SEC;iFDI++)
   {
    pitem=&(pitems->FDIes[iFDI]); //指向一个文件目录项数据

    if((0X08!=pitem->Attributes) && (0X0F!=pitem->Attributes)  //不是卷标、不是长名项、没有删除、不是.与..
       && (0XE5!=pitem->Name[0]) && ('.'!=pitem->Name[0])) //即遇到一个合法的SFN项
    {
     if(have_lfn && !is_lfn_buf_err) //遇到SFN项后，它前面可能有长名项，如果有则与输入的UNI串比对，以确定是否有同名文件或目录
     {                               //而且没有发生lfn_buf的溢出错误
      if(cur_binding_sumchk==Get_Binding_SumChk(pitem)) //如果LFN与SFN目录项绑定校验和相等，则认为长名有效
      {
       if(Memory_Compare(((UINT8 *)unifn),((UINT8 *)lfn_buf),2*((UINT32)len))) //对UNI串进行比对
       {
            *psec=temp_sec+(UINT32)iSec;
            *pn=iFDI; //记录重名文件目录项的位置，以便对其进行解析
        return ERR_FDI_ALREADY_EXISTING; //已有同名文件或目录
       }
      }
     }
    }

    if(CHK_ATTR_LFN(pitem->Attributes) && (0XE5!=pitem->Name[0])) //是长名项，而且没有被删除
    {
     have_lfn=1;

     plfni=(struct LFN_FDI *)pitem;

     cur_binding_sumchk=(plfni->ChkVal)[0]; //获取长名项的绑定校验和

     res=Get_Part_Name(lfn_buf,plfni,(UINT8)((((plfni->AttrByte[0])&0XBF)-1)*13)); //将当前LFN项中的文件名UNICODE码拼入临时缓冲
                                                                      //此临时缓冲长度为MAX_LFN_LEN，如果越界，则
                                                                      //不再装入，最终造成LFN的截断。
     if(res) is_lfn_buf_err=1; //发生LFN_BUF溢出错误
    }
    else
    {
     have_lfn=0;
    }

    if(0==(pitem->Name)[0])
    {
     flag=1; //标记此扇区已经被修改

     if(nlfni>0)
     {
      Fill_LFN_FDI(unifn,&temp_lfni,chksum,(UINT8)(nlfni-1));
      Memory_Copy(((UINT8 *)pitem),((UINT8 *)(&temp_lfni)),FDI_NBYTES); //将合成的长名项拷贝到扇区数据中
      nlfni--;
     }
     else
     {
      *psec=temp_sec+(UINT32)iSec;
      *pn=iFDI; //记录空位的位置
      Memory_Copy(((UINT8 *)pitem),((UINT8 *)pfdi),FDI_NBYTES); //将短名项拷贝到扇区数据中
      USB_Class_Write_Sector(temp_sec+(UINT32)iSec,znFAT_Buffer);
      return ERR_SUCC;
     }
    }
   }

   if(flag)
   {
    USB_Class_Write_Sector(temp_sec+(UINT32)iSec,znFAT_Buffer);
    flag=0;
   }
  }
  old_cluster=cluster;
  cluster=Get_Next_Cluster(cluster);
 }while(!IS_END_CLU(cluster)); //如果不是最后一个簇，则继续循环
 //===========================================================
 //如果运行到这里，则说明当前簇中已无空位
 if(0!=pInit_Args->Free_nCluster) //如果剩余空簇数为0，则说明磁盘已无空间
 {
  nsec=(UINT8)((nlfni+1)/NFDI_PER_SEC); //剩余的长名项还需要多少个扇区,+1是因为最后还有一个短名项
  if((nlfni+1)%NFDI_PER_SEC) nsec++;

  nclu=(UINT8)(nsec/(pInit_Args->SectorsPerClust));
  if(nsec%(pInit_Args->SectorsPerClust)) nclu++;

  for(iClu=0;iClu<nclu;iClu++)
  {
   Modify_FAT(old_cluster,pInit_Args->Next_Free_Cluster);
   Modify_FAT(pInit_Args->Next_Free_Cluster,0X0FFFFFFF); //构造FAT簇链
   Clear_Cluster(pInit_Args->Next_Free_Cluster); //清空空闲簇

   temp_sec=SOC(pInit_Args->Next_Free_Cluster);

   old_cluster=pInit_Args->Next_Free_Cluster;
   Update_Next_Free_Cluster();

   for(iSec=0;iSec<(pInit_Args->SectorsPerClust);iSec++)
   {
    USB_Class_Read_Sector(temp_sec+(UINT32)iSec,znFAT_Buffer);
    pitems=((struct FDIesInSEC *)znFAT_Buffer);

    for(iFDI=0;iFDI<NFDI_PER_SEC;iFDI++)
    {
     pitem=&(pitems->FDIes[iFDI]); //指向一个文件目录项数据

     if(nlfni>0)
     {
      Fill_LFN_FDI(unifn,&temp_lfni,chksum,(UINT8)(nlfni-1));
      Memory_Copy(((UINT8 *)pitem),((UINT8 *)(&temp_lfni)),FDI_NBYTES); //将合成的长名项拷贝到扇区数据中
      nlfni--;
     }
     else
     {
      *psec=temp_sec+(UINT32)iSec;
      *pn=iFDI; //记录空位的位置
      Memory_Copy(((UINT8 *)pitem),((UINT8 *)pfdi),FDI_NBYTES); //将短名项拷贝到扇区数据中
      USB_Class_Write_Sector(temp_sec+(UINT32)iSec,znFAT_Buffer);
      return ERR_SUCC;
     }
    }
    USB_Class_Write_Sector(temp_sec+(UINT32)iSec,znFAT_Buffer);
   }
  }
  return ERR_SUCC;
 }
 else
 {
  return ERR_NO_SPACE;
 }
}
#endif




#ifdef GET_DIR_START_CLUSTER
UINT8 Get_Dir_Start_Cluster(INT8 *dir_name,UINT32 *pCluster) //获取目录下名为dir_name的子目录的开始簇
{                                                            //目录的首簇存入pCluster所指入的变量
 UINT32 sec_temp=0;
 UINT8 iSec=0,iFDI=0;
 UINT32 Cur_Clust=*pCluster;

 //===========for LFN=======
 #ifdef USE_LFN
 struct LFN_FDI *plfni;

 UINT8 cur_binding_sumchk=0,result=0;
 UINT16 temp_lfn[MAX_LFN_LEN+1]; //用于装载长名UNICODE码的临时缓冲
 UINT16 lfn_buf[MAX_LFN_LEN+1]; //从长名项中提取的UNI码装到这个缓冲中
 UINT8 is_lfn=0; //输入的文件名是否是长名
 UINT8 have_lfn=0; //在搜索目录项时发现了长名项
 UINT8 is_lfn_buf_err=0; //产生长名缓冲溢出错误，此标记为1则直接跳过长名比对
 #endif

 //===========for LFN=======

 INT8 temp_dirname[13];

 struct FDIesInSEC *pitems; //指向文件目录项扇区数据的指针
 struct FDI *pitem; //指向文件目录项数据的指针

 #ifndef RT_UPDATE_CLUSTER_CHAIN
 get_next_cluster_in_cccb=0;
 #endif

 if(Check_Illegal_Char(dir_name)) return ERR_ILL_CHAR; //检查文件名中是否有非法字符

 #ifdef USE_LFN
 if(!Is_LFN(dir_name)) //如果不是长名,即是短名
 {
 #endif
  //检查短文件名合法性，若非法则直接返回，不再进行后面的处理(此处对SFN的合法性检查非常严格)
  //事先检查SFN的合法性，减少后面处理上的麻烦
  if(Check_SFN_Illegal_Length(dir_name)) return ERR_SFN_ILL_LEN; //检查SFN是否符合8.3长度
  if(Check_SFN_Dot(dir_name)) return ERR_SFN_DOT; //检查SFN中.是否合法
  if(Check_SFN_Special_Char(dir_name)) return ERR_SFN_SPEC_CHAR; //检查SFN中是否有特殊字符
  if(((UINT8)(-1))==Check_SFN_Illegal_Lower(dir_name)) return ERR_SFN_ILL_LOWER; //检查SFN中是否有非法的大小写
 #ifdef USE_LFN
 }
 else //如果是长名
 {
  is_lfn=1; //标记输入的文件名为长名
  result=oemstr2unistr(dir_name,temp_lfn);//把filename转为UNICODE码，存在temp_lfn里，以便后面进行文件名比对
  if(result) return result;
 }
 #endif

 //================================================
 do
 {
  sec_temp=SOC(Cur_Clust); //当前簇首扇区
  for(iSec=0;iSec<(pInit_Args->SectorsPerClust);iSec++)
  {
   USB_Class_Read_Sector(sec_temp+(UINT32)iSec,znFAT_Buffer);
   pitems=(struct FDIesInSEC *)znFAT_Buffer;

   for(iFDI=0;iFDI<NFDI_PER_SEC;iFDI++) //访问扇区中各文件目录项
   {
    pitem=&(pitems->FDIes[iFDI]); //指向一个文件目录项数据

    if((CHK_ATTR_DIR(pitem->Attributes)) && (0XE5!=pitem->Name[0])) //文件属性为目录，且没有被删除
    {
     To_File_Name((INT8 *)(pitem->Name),temp_dirname); //将FDI中的目录名字段转为8.3文件名
     #ifdef USE_LFN
     if(!is_lfn)
     #endif
     {
      if(!SFN_Match(dir_name,temp_dirname)) //目录名匹配
      {
       //获取目录的开始簇
       *pCluster=(Bytes2Value(pitem->LowClust,2))|(Bytes2Value(pitem->HighClust,2)<<16);
       return ERR_SUCC;
      }
     }

     #ifdef USE_LFN
     if(is_lfn && have_lfn && !is_lfn_buf_err) //如果输入的文件名为长名，而且也发现了长名
     {                                         //同时又没有发生长名缓冲溢出错误
      if(cur_binding_sumchk==Get_Binding_SumChk(pitem)) //如果LFN与SFN目录项绑定校验和相等，则认为
      {                                                    //长名有效
       if(!LFN_Match(temp_lfn,lfn_buf)) //长文件名通配
       {
        //获取目录的开始簇
        *pCluster=(Bytes2Value(pitem->LowClust,2))|(Bytes2Value(pitem->HighClust,2)<<16);
        return ERR_SUCC;
       }
      }
     }
     #endif

    }

    #ifdef USE_LFN
    if(CHK_ATTR_LFN(pitem->Attributes) && (0XE5!=pitem->Name[0])) //是长名项，而且没有被删除
    {
     have_lfn=1;

     plfni=(struct LFN_FDI *)pitem;

     cur_binding_sumchk=(plfni->ChkVal)[0]; //获取长名项的绑定校验和

     result=Get_Part_Name(lfn_buf,plfni,(UINT8)((((plfni->AttrByte[0])&0XBF)-1)*13)); //将当前LFN项中的文件名UNICODE码拼入临时缓冲
                                                                      //此临时缓冲长度为MAX_LFN_LEN，如果越界，则
                                                                      //不再装入，最终造成LFN的截断。
     if(result) is_lfn_buf_err=1; //如果发生LFN_BUF溢出错误
    }
    #endif
   }
  }

  Cur_Clust=Get_Next_Cluster(Cur_Clust); //获取下一簇
 }while(!IS_END_CLU(Cur_Clust)); //如果不是最后一个簇，则继续循环

 return ERR_NO_DIR;
}
#endif

#ifdef ZNFAT_ENTER_DIR
UINT8 znFAT_Enter_Dir(INT8 *dirpath,UINT32 *pCluster,UINT32 *pos)
{
 UINT8 index=0,res=0;
 UINT32 i=1;

 #ifndef USE_LFN
 INT8 dirname[13];
 #else
 INT8 dirname[MAX_LFN_LEN+1];
 #endif

 *pos=1;
 *pCluster=2;

 if(('\\'==dirpath[0] || '/'==dirpath[0]) && '\0'==dirpath[1]) //如果是"\\"，则直接取首目录簇，即第2簇
 {
  return ERR_SUCC;
 }

 while('\0'!=dirpath[i])
 {
  if('\\'==dirpath[i] || '/'==dirpath[i])
  {
   dirname[index]='\0';
   index=0;

   res=Get_Dir_Start_Cluster(dirname,pCluster);
   if(res)
   {
    return res;  //返回错误码
   }
   *pos=i+1;
  }
  else
  {
   dirname[index]=dirpath[i];
   index++;
   #ifndef USE_LFN
   if(index>12) //如果不使用长名，则目录名以及文件名最长不能超过8+1+3
   {
    return ERR_SFN_ILL_LEN; //目录名长于8.3，亦防止dirname溢出
   }
   #else
   if(index>MAX_LFN_LEN) //如果使用长名，则目录名以及文件名最长不能超过设定的长名最长长度
   {
    return ERR_LFN_BUF_OUT; //目录名长于MAX_LFN_LEN，亦防止dirname溢出
   }
   #endif
  }
  i++;
 }

 return ERR_SUCC; //成功
}
#endif

#ifdef FILL_FDI
UINT8 Fill_FDI(struct FDI *pfdi,INT8 *pfn,struct DateTime *pdt,UINT8 is_file)
{
 UINT8 dot_pos=0,have_dot=0,lowcase=0;
 UINT8 i=0,j=0,fn_len=(UINT8)StringLen(pfn);
 UINT16 time=0,date=0;

 Memory_Set(((UINT8 *)pfdi),FDI_NBYTES,0); //对文件目录项清0

 for(i=(UINT8)(fn_len-1);i>0;i--) //反向寻找. 第一个.是主文件与扩展名的分界
 {
  if('.'==pfn[i])
  {
   dot_pos=i;
   have_dot=1;
   break;
  }
 }

 if(have_dot) //如果有点
 {
  //填入主文件名
  for(i=0;i<dot_pos;i++)
  {
   (pfdi->Name)[i]=(INT8)Lower2Up(pfn[i]); //转为大写
  }
  for(;i<8;i++)
  {
   (pfdi->Name)[i]=' '; //不足8字节部分填入空格
  }

  //填入扩展名
  for(i=(UINT8)(dot_pos+1);i<fn_len;i++)
  {
   (pfdi->Extension)[j]=(UINT8)Lower2Up(pfn[i]); //转为大写
   j++;
  }
  for(;j<3;j++)
  {
   (pfdi->Extension)[j]=' '; //不足8字节部分填入空格
  }
 }
 else //如果没有点
 {
  //填入主文件名
  for(i=0;i<fn_len;i++)
  {
   (pfdi->Name)[i]=(UINT8)Lower2Up(pfn[i]); //转为大写
  }
  for(;i<8;i++)
  {
   (pfdi->Name)[i]=' '; //不足8字节部分填入空格
  }

  //填入扩展名
  for(j=0;j<3;j++)
  {
   (pfdi->Extension)[j]=' '; //扩展名填入空格
  }
 }
 //=======================填入主文件名与扩展名========

 pfdi->Attributes=(UINT8)(is_file?0X20:0X30); //设置属性
 //=======================填入属性========

 lowcase=Check_SFN_Illegal_Lower(pfn); //获取主文件名与扩展名的大小写状态
 if((lowcase&0X0F)==0X01) //如果主文件名为小写
 {
  pfdi->LowerCase|=0X08;
 }
 if((lowcase&0XF0)==0X10) //如果扩展名为小写
 {
  pfdi->LowerCase|=0X10;
 }
 //=======================填入大小写控制字============

 pfdi->CTime10ms=(UINT8)((((pdt->time).sec)%2)?0X78:0X00);
 //=======================填入创建时间10MS位==========

 time=(UINT16)(MAKE_TIME((pdt->time).hour,(pdt->time).min,(pdt->time).sec));
 (pfdi->CTime)[0]=(UINT8)time;
 (pfdi->CTime)[1]=(UINT8)(time>>8);
 //=======================填入创建时间================

 date=(UINT16)(MAKE_DATE((pdt->date).year,(pdt->date).month,(pdt->date).day));
 (pfdi->CDate)[0]=(UINT8)date;
 (pfdi->CDate)[1]=(UINT8)(date>>8);
 //=======================填入创建日期================

 (pfdi->ADate)[0]=(UINT8)date;
 (pfdi->ADate)[1]=(UINT8)(date>>8);
 //=======================填入访问日期================

 (pfdi->MTime)[0]=(UINT8)time;
 (pfdi->MTime)[1]=(UINT8)(time>>8);
 //=======================填入修改时间================

 (pfdi->MDate)[0]=(UINT8)date;
 (pfdi->MDate)[1]=(UINT8)(date>>8);
 //=======================填入修改日期================

 //填充开始簇
 if(!is_file) //如果是目录，则在fdi中填充空簇
 {
  pfdi->HighClust[0]=(UINT8)(((pInit_Args->Next_Free_Cluster)>>16)&0X000000FF);//目录与文件不同，目录在创建之初
  pfdi->HighClust[1]=(UINT8)(((pInit_Args->Next_Free_Cluster)>>24)&0X000000FF);//就要为其分配空簇，为的是写入.与..
  pfdi->LowClust [0]=(UINT8)(((pInit_Args->Next_Free_Cluster)    )&0X000000FF);//这两个特殊的文件目录项
  pfdi->LowClust [1]=(UINT8)(((pInit_Args->Next_Free_Cluster)>>8 )&0X000000FF);
 }

 //文件大小字段暂置为0
 return 0;
}
#endif

#ifdef REGISTER_FDI
UINT8 Register_FDI(UINT32 cluster,struct FDI *pfdi,UINT32 *psec,UINT8 *pn)
{
 UINT32 temp_sec=0,old_cluster=0;
 UINT8 iSec=0,iFDI=0;
 struct FDIesInSEC *pfdis;

 if(0==pInit_Args->Free_nCluster) return ERR_NO_SPACE; //如果没有空间，则直接返回

 //以下代码检查是否已经存在重复的文件目录项，以及查询空位
 do
 {
  temp_sec=SOC(cluster);
  for(iSec=0;iSec<(pInit_Args->SectorsPerClust);iSec++)
  {
   USB_Class_Read_Sector(temp_sec+(UINT32)iSec,znFAT_Buffer);
   pfdis=((struct FDIesInSEC *)znFAT_Buffer);
   for(iFDI=0;iFDI<NFDI_PER_SEC;iFDI++)
   {
    if(Memory_Compare((UINT8*)((pfdis->FDIes)+iFDI),(UINT8*)pfdi,11))  //比较文件名
    {
     *psec=temp_sec+(UINT32)iSec;
     *pn=iFDI; //记录重名文件目录项的位置，以便对其进行解析
     return ERR_FDI_ALREADY_EXISTING;
    }
    else
    {
     if(0==((((pfdis->FDIes)[iFDI]).Name)[0]))
     {
      *psec=temp_sec+(UINT32)iSec;
      *pn=iFDI; //记录空位的位置

      USB_Class_Read_Sector(*psec,znFAT_Buffer);
      Memory_Copy((UINT8*)((((struct FDIesInSEC *)znFAT_Buffer)->FDIes)+*pn),(UINT8 *)pfdi,FDI_NBYTES);
      USB_Class_Write_Sector(*psec,znFAT_Buffer);

      return ERR_SUCC;
     }
    }
   }
  }
  old_cluster=cluster;
  cluster=Get_Next_Cluster(cluster);
 }while(!IS_END_CLU(cluster)); //如果不是最后一个簇，则继续循环
 //===========================================================
 //如果运行到这里，则说明当前簇中已无空位
 if(0!=pInit_Args->Free_nCluster) //如果剩余空簇数为0，则说明磁盘已无空间
 {
  Modify_FAT(old_cluster,pInit_Args->Next_Free_Cluster);
  Modify_FAT(pInit_Args->Next_Free_Cluster,0X0FFFFFFF); //构造FAT簇链
  Clear_Cluster(pInit_Args->Next_Free_Cluster); //清空空闲簇

  *psec=SOC(pInit_Args->Next_Free_Cluster);
  *pn=0; //记录空位的位置

  USB_Class_Read_Sector(*psec,znFAT_Buffer);
  Memory_Copy((UINT8*)((((struct FDIesInSEC *)znFAT_Buffer)->FDIes)),(UINT8 *)pfdi,FDI_NBYTES);
  USB_Class_Write_Sector(*psec,znFAT_Buffer);

  Update_Next_Free_Cluster();

  return ERR_SUCC;
 }
 else
 {
  return ERR_NO_SPACE;
 }
}
#endif


#ifdef CREATE_DIR_IN_CLUSTER
UINT8 Create_Dir_In_Cluster(UINT32 *cluster,INT8 *pdn,struct DateTime *pdt)
{
 UINT8 res=0,i=0;
 UINT32 dummy=0;
 struct FDI fdi;

 #ifdef USE_LFN
 UINT8 is_lfn=0; //标记输入的目录名是否长名
 UINT16 temp_lfn_buf[MAX_LFN_LEN+1]; //用于装载长名UNI串的临时缓冲
 INT8 temp_dirname[13];
 #endif

 #ifndef RT_UPDATE_CLUSTER_CHAIN
 get_next_cluster_in_cccb=0;
 #endif

 if(Check_Illegal_Char(pdn)) return ERR_ILL_CHAR; //检查目录名中是否有非法字符

 #ifdef USE_LFN
 if(!Is_LFN(pdn))
 {
 #endif
  //检查短文件名合法性，若非法则直接返回，不再进行后面的处理(此处对SFN的合法性检查非常严格)
  //事先检查SFN的合法性，减少后面处理上的麻烦
  if(Check_SFN_Illegal_Length(pdn)) return ERR_SFN_ILL_LEN; //检查SFN是否符合8.3长度
  if(Check_SFN_Dot(pdn)) return ERR_SFN_DOT; //检查SFN中.是否合法
  if(Check_SFN_Special_Char(pdn)) return ERR_SFN_SPEC_CHAR; //检查SFN中是否有特殊字符
  if(((UINT8)(-1))==Check_SFN_Illegal_Lower(pdn)) return ERR_SFN_ILL_LOWER; //检查SFN中是否有非法的大小写
 #ifdef USE_LFN
 }
 else
 {
  is_lfn=1;
  res=oemstr2unistr(pdn,temp_lfn_buf); //如果是长名，则将pdn转为UNI串
  if(res) return res;
 }

 if(!is_lfn) //如果不是长名
 {
 #endif
  Fill_FDI(&fdi,pdn,pdt,BOOL_FALSE); //构造目录项
  res=Register_FDI(*cluster,&fdi,&dummy,&i);//在当前簇中进行文件目录项的"注册"

 #ifdef USE_LFN
 }
 else //如果是长名
 {
  Make_Short_Name(pdn,temp_dirname);
  Fill_FDI(&fdi,temp_dirname,pdt,BOOL_FALSE); //构造文件目录项
  res=Register_LFN_FDI(*cluster,&fdi,temp_lfn_buf,&dummy,&i); //在当前簇中进行长名项及相应短名项“注册”
 }
 #endif

 if(res)
 {
  return res;
 }

 //====================================================================================

 //向目录簇中写入.与..
 Modify_FAT(pInit_Args->Next_Free_Cluster,0X0FFFFFFF); //构造FAT簇链
 Clear_Cluster(pInit_Args->Next_Free_Cluster); //清空空闲簇

 //把fdi中的名字替换为. 名为.的目录指向了相前簇
 fdi.Name[0]='.';
 for(i=1;i<11;i++)
 {
  fdi.Name[i]=' '; //.后面全部填充空格
 }

 Memory_Copy(znFAT_Buffer,((UINT8 *)(&fdi)),FDI_NBYTES); //将文件目录项.装入到内部缓冲区中

 //把fdi中的名字替换为.. 名为..的目录指向了上一簇(DOS中使用CD..可以回到上一级目录就是这个道理)
 fdi.Name[1]='.';

 //把fdi中的簇值改为上一级目录的首簇
 if(2!=(*cluster)) //如果上一级目录首簇不是"根目录"(首目录)
 {
  fdi.HighClust[0]=(UINT8)(((*cluster)>>16)&0X000000FF);
  fdi.HighClust[1]=(UINT8)(((*cluster)>>24)&0X000000FF);
  fdi.LowClust [0]=(UINT8)(((*cluster)    )&0X000000FF);
  fdi.LowClust [1]=(UINT8)(((*cluster)>>8 )&0X000000FF);
 }
 else
 {
  fdi.HighClust[0]=fdi.HighClust[1]=fdi.LowClust[0]=fdi.LowClust[1]=0;
 }

 Memory_Copy(znFAT_Buffer+FDI_NBYTES,((UINT8 *)(&fdi)),FDI_NBYTES); //将文件目录项..装入到内部缓冲区中

 USB_Class_Write_Sector(SOC(pInit_Args->Next_Free_Cluster),znFAT_Buffer);

 *cluster=(pInit_Args->Next_Free_Cluster); //返回新创建的目录首簇

 Update_Next_Free_Cluster();

 return ERR_SUCC;
}
#endif



#ifdef DESTROY_FAT_CHAIN
UINT8 Destroy_FAT_Chain(UINT32 cluster)
{
 UINT32 clu_sec=0,temp1=0,temp2=0,old_clu=0,nclu=1;

 struct FAT_Sec *pFAT_Sec;

 if(cluster<(pInit_Args->Next_Free_Cluster)) //如果要销毁的簇链头簇比下一空簇值小，则将下一空簇值置为它
 {
  pInit_Args->Next_Free_Cluster=cluster;
 }

 old_clu=cluster;

 USB_Class_Read_Sector((old_clu/NITEMSINFATSEC)+(pInit_Args->FirstFATSector),znFAT_Buffer);

 pFAT_Sec=(struct FAT_Sec *)znFAT_Buffer;

 cluster=Bytes2Value(((pFAT_Sec->items)[cluster%NITEMSINFATSEC]).Item,4);

 while(!IS_END_CLU(cluster))
 {
  nclu++;

  clu_sec=cluster/NITEMSINFATSEC;

  temp1=old_clu%NITEMSINFATSEC;
  temp2=old_clu/NITEMSINFATSEC;

  ((pFAT_Sec->items)[temp1]).Item[0]=0;
  ((pFAT_Sec->items)[temp1]).Item[1]=0;
  ((pFAT_Sec->items)[temp1]).Item[2]=0;
  ((pFAT_Sec->items)[temp1]).Item[3]=0;

  if(temp2!=clu_sec)
  {
   USB_Class_Write_Sector(temp2+(pInit_Args->FirstFATSector),znFAT_Buffer);
   USB_Class_Write_Sector(temp2+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);

   USB_Class_Read_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);
  }

  old_clu=cluster;
  cluster=Bytes2Value(((pFAT_Sec->items)[cluster%NITEMSINFATSEC]).Item,4);
 }

 temp1=old_clu%NITEMSINFATSEC;
 temp2=old_clu/NITEMSINFATSEC;

 ((pFAT_Sec->items)[temp1]).Item[0]=0;
 ((pFAT_Sec->items)[temp1]).Item[1]=0;
 ((pFAT_Sec->items)[temp1]).Item[2]=0;
 ((pFAT_Sec->items)[temp1]).Item[3]=0;

 USB_Class_Write_Sector(temp2+(pInit_Args->FirstFATSector),znFAT_Buffer);
 USB_Class_Write_Sector(temp2+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);

 pInit_Args->Free_nCluster+=nclu; //更新剩余空簇数

 return ERR_SUCC;
}
#endif

#ifdef DESTROY_FDI
UINT8 Destroy_FDI(struct FDI *pitem)
{
 UINT32 start_cluster=Bytes2Value(pitem->LowClust,2)+Bytes2Value(pitem->HighClust,2)*65536;

 if(0==start_cluster) return ERR_SUCC;

 Destroy_FAT_Chain(start_cluster); //销毁簇链

 return ERR_SUCC;
}
#endif


#ifdef HAVE_ANY_SUBDIR_WITH_DEL_FOREFILE
UINT8 Have_Any_SubDir_With_Del_ForeFile(UINT32 *cluster,UINT8 for_del_dir)
{
 UINT8 iSec=0,iFDI=0;
 UINT32 sec_temp=0;
 UINT32 temp=*cluster;

 struct FDIesInSEC *pitems; //指向文件目录项扇区数据的指针
 struct FDI *pitem; //指向文件目录项数据的指针

 #ifndef RT_UPDATE_CLUSTER_CHAIN
 get_next_cluster_in_cccb=0;
 #endif

 do
 {
  sec_temp=SOC(temp); //当前簇首扇区
  for(iSec=0;iSec<(pInit_Args->SectorsPerClust);iSec++)
  {
   USB_Class_Read_Sector(sec_temp+(UINT32)iSec,znFAT_Buffer);
   pitems=(struct FDIesInSEC *)znFAT_Buffer;

   for(iFDI=0;iFDI<NFDI_PER_SEC;iFDI++) //访问扇区中各文件目录项
   {
    pitem=&(pitems->FDIes[iFDI]); //指向一个文件目录项数据

    if((CHK_ATTR_FILE(pitem->Attributes)) && (0XE5!=pitem->Name[0])) //文件属性为文件，且没有被删除
    {
     Destroy_FDI(pitem); //销毁文件目录项及其对应的簇链 注：内部缓冲区数据被变更
     USB_Class_Read_Sector(sec_temp+(UINT32)iSec,znFAT_Buffer); //重新读取扇区数据，恢复内部缓冲区的数据

     pitem->Name[0]=0XE5; //给文件目录项打上"已删除"的标记
     pitem->HighClust[0]=pitem->HighClust[1]=0; //开始簇的高字清0

     USB_Class_Write_Sector(sec_temp+(UINT32)iSec,znFAT_Buffer); //如果有销毁操作，则回写扇区
    }

    if((CHK_ATTR_DIR(pitem->Attributes)) && (0XE5!=pitem->Name[0]) //文件属性为目录，且没有被删除
       && ('.'!=pitem->Name[0]))                          //不是.与..
    {
     if(!for_del_dir) //不是为了把子目录本身删除，而是为了获取其首簇，进而进入更深子目录
     {
      *cluster=Bytes2Value(pitem->LowClust,2)+Bytes2Value(pitem->HighClust,2)*65536;
     }
     else
     {
      Destroy_FDI(pitem); //销毁文件目录项及其对应的簇链 注：内部缓冲区数据被变更
      USB_Class_Read_Sector(sec_temp+(UINT32)iSec,znFAT_Buffer); //重新读取扇区数据，恢复内部缓冲区的数据

      pitem->Name[0]=0XE5; //给文件目录项打上"已删除"的标记
      pitem->HighClust[0]=pitem->HighClust[1]=0; //开始簇的高字清0

      USB_Class_Write_Sector(sec_temp+(UINT32)iSec,znFAT_Buffer); //如果有销毁操作，则回写扇区
     }
     return BOOL_TRUE;
    }
   }
  }

  temp=Get_Next_Cluster(temp); //获取下一簇
 }while(!IS_END_CLU(temp)); //如果不是最后一个簇，则继续循环

 return BOOL_FALSE;
}
#endif

#ifdef ENTER_DEEP_AHEAD_DIR
UINT8 Enter_Deep_Ahead_Dir(UINT32 *cluster)
{
 UINT32 dir_cluster=*cluster;

 while(Have_Any_SubDir_With_Del_ForeFile(&dir_cluster,BOOL_FALSE));

 *cluster=dir_cluster;

 return ERR_SUCC;
}
#endif

#ifdef GET_UPPER_DIR
UINT8 Get_Upper_Dir(UINT32 *cluster)
{
 struct FDIesInSEC *pitems; //指向文件目录项扇区数据的指针
 struct FDI *pitem; //指向文件目录项数据的指针

 USB_Class_Read_Sector(SOC(*cluster),znFAT_Buffer);
 pitems=(struct FDIesInSEC *)znFAT_Buffer;

 pitem=&(pitems->FDIes[1]); //指向..文件目录项，用以获取上一级目录的首簇

 if('.'==pitem->Name[0] && '.'==pitem->Name[1])
  *cluster=Bytes2Value(pitem->LowClust,2)+Bytes2Value(pitem->HighClust,2)*65536;
 else
  return ERR_FS_DIR; //如果在目录的最头上不是.与..，则说明文件系统已被损坏
 
 if(0==(*cluster)) (*cluster)=2; //如果上一级目录为根目录(首目录)，将簇值置为2

 return ERR_SUCC;
}
#endif



#ifdef GET_RECMD_SZCLU
UINT8 Get_Recmd_szClu(UINT32 nsec)
{
 if(nsec<(14336)) return 0;

 if((nsec>=(14336)) && (nsec<=(32767))) return 0;
 if((nsec>=(32768)) && (nsec<=(65535))) return 1;
 if((nsec>=(65536)) && (nsec<=(131071))) return 1;
 if((nsec>=(131072)) && (nsec<=(262143))) return 2;
 if((nsec>=(262144)) && (nsec<=(524287))) return 4;
 if((nsec>=(524288)) && (nsec<=(16777215))) return 8;
 if((nsec>=(16777216)) && (nsec<=(33554431))) return 16;
 if((nsec>=(33554432)) && (nsec<=(67108863))) return 32;
 if((nsec>=(67108864)) && (nsec<=(4294967295UL))) return 64;

 return 0;
}
#endif


#ifdef ZNFAT_MAKE_FS
UINT8 znFAT_Make_FS(UINT32 tt_sec,UINT16 clu_sz) //格式化 tt_sec 总扇区数 clu_sz 指定的簇大小
{                                          //若为0则按磁盘大小选定默认值 格式化策略采用比较简单的SFD策略
                                           //无MBR，不支持分区，直接从DBR开始
 struct DBR      *pdbr;
 struct FSInfo   *pfsinfo;

 UINT32 temp=0,temp1=0,temp2=0;

 tt_sec/=(UINT32)(NSECPERCYLINDER);
 tt_sec*=(UINT32)(NSECPERCYLINDER);//舍去“剩余扇区”，剩余扇区是指不足一个柱面的扇区数


 PGM2RAM(znFAT_Buffer,_dbr,512); //从模版数组中把数据搬到内部缓冲区
 pdbr=(struct DBR *)znFAT_Buffer;

 pdbr->BPB_SecPerClus=(UINT8)(clu_sz/512); //每簇扇区数
 if(0==pdbr->BPB_SecPerClus) pdbr->BPB_SecPerClus=Get_Recmd_szClu(tt_sec);
 if(0==pdbr->BPB_SecPerClus) return ERR_FMT_TOO_LOW_VOLUME; //容量太小，不能用FAT32进行格式化

 temp1=pdbr->BPB_SecPerClus;

 pdbr->BPB_TotSec32[0]=(UINT8)((tt_sec)    &0X000000FF);
 pdbr->BPB_TotSec32[1]=(UINT8)((tt_sec>>8) &0X000000FF);
 pdbr->BPB_TotSec32[2]=(UINT8)((tt_sec>>16)&0X000000FF);
 pdbr->BPB_TotSec32[3]=(UINT8)((tt_sec>>24)&0X000000FF); //该分区的总扇区数

 temp=(tt_sec-32)/(((UINT32)NITEMSINFATSEC)*((UINT32)(pdbr->BPB_SecPerClus)));
 if((tt_sec-32)%((UINT32)NITEMSINFATSEC)*((UINT32)pdbr->BPB_SecPerClus)) temp++; //((tt_sec-32)-2*FATsz)/(SecPerClus*128)=FATsz 解这个等式
 temp2=temp;

 pdbr->BPB_FATSz32[0]=(UINT8)((temp)    &0X000000FF);
 pdbr->BPB_FATSz32[1]=(UINT8)((temp>>8) &0X000000FF);
 pdbr->BPB_FATSz32[2]=(UINT8)((temp>>16)&0X000000FF);
 pdbr->BPB_FATSz32[3]=(UINT8)((temp>>24)&0X000000FF); //FAT表的扇区数

 USB_Class_Write_Sector(0,znFAT_Buffer); //将合成好的DBR数据写入到0扇区中去



 Memory_Set(znFAT_Buffer,ZNFAT_BUF_SIZE,0); //将内部缓冲区清0
 PGM2RAM(znFAT_Buffer,_fsinfo_1,4); //将FSINFO模板数据的第一部分搬过来
 PGM2RAM(znFAT_Buffer+484,_fsinfo_2,28); //将FSINFO模板数据的第二部分搬过来
                                             //注：FSINFO模板数据分为两部分，主要是因为其中有绝大
                                             //部分是0，为了节省固化数据量，减少FLASHROM空间的使用量
 pfsinfo=(struct FSInfo *)znFAT_Buffer;

 temp=(tt_sec-32-2*temp)/((UINT32)(temp1))-1; //总簇数-1，因为第2簇为首目录，已经被卷标占用
 pfsinfo->Free_Cluster[0]=(UINT8)((temp)    &0X000000FF);
 pfsinfo->Free_Cluster[1]=(UINT8)((temp>>8) &0X000000FF);
 pfsinfo->Free_Cluster[2]=(UINT8)((temp>>16)&0X000000FF);
 pfsinfo->Free_Cluster[3]=(UINT8)((temp>>24)&0X000000FF); //剩余空簇数

 USB_Class_Write_Sector(1,znFAT_Buffer); //将合成好的DBR数据写入到64扇区中去，即DBR扇区的后一个扇区



 znFAT_Device_Clear_nSector(temp1,32+2*temp2);
 znFAT_Device_Clear_nSector(temp2-1,33);
 znFAT_Device_Clear_nSector(temp2-1,33+temp2);

 PGM2RAM(znFAT_Buffer,_fatsec,12); //将FAT表模版数据搬到内部缓冲区
 USB_Class_Write_Sector(32,znFAT_Buffer); //向FAT表1中写入0
 USB_Class_Write_Sector(32+temp2,znFAT_Buffer); //向FAT表2中写入0



 PGM2RAM(znFAT_Buffer,_1stsec,26);
 USB_Class_Write_Sector(32+2*temp2,znFAT_Buffer); //向数据区第一个扇区写入数据

 //=====================================以上.....==============================================
 return ERR_SUCC;
}
#endif

#ifdef UPDATE_FILE_SIZE
UINT8 Update_File_Size(struct FileInfo *pfi) //更新文件大小
{
 struct FDI *pfdi;

 just_file=pfi;

 USB_Class_Read_Sector(pfi->FDI_Sec,znFAT_Buffer);

 pfdi=(((struct FDIesInSEC *)znFAT_Buffer)->FDIes)+(pfi->nFDI); //文件的文件目录项

 (pfdi->FileSize)[0]=(UINT8)((pfi->File_Size)&0X000000FF)      ;
 (pfdi->FileSize)[1]=(UINT8)(((pfi->File_Size)&0X0000FF00)>>8) ;
 (pfdi->FileSize)[2]=(UINT8)(((pfi->File_Size)&0X00FF0000)>>16);
 (pfdi->FileSize)[3]=(UINT8)(((pfi->File_Size)&0XFF000000)>>24);

 USB_Class_Write_Sector(pfi->FDI_Sec,znFAT_Buffer);

 return 0;
}
#endif


#ifdef UPDATE_FILE_SCLUST
UINT8 Update_File_sClust(struct FileInfo *pfi,UINT32 clu) //更新文件开始簇
{
 struct FDI *pfdi;

 just_file=pfi;

 USB_Class_Read_Sector(pfi->FDI_Sec,znFAT_Buffer);

 pfdi=(((struct FDIesInSEC *)znFAT_Buffer)->FDIes)+(pfi->nFDI); //文件的文件目录项

 pfi->File_StartClust=clu;

 (pfdi->HighClust)[0]=(UINT8)((clu&0X00FF0000)>>16);
 (pfdi->HighClust)[1]=(UINT8)((clu&0XFF000000)>>24);
 (pfdi->LowClust )[0]=(UINT8)((clu&0X000000FF))    ;
 (pfdi->LowClust )[1]=(UINT8)((clu&0X0000FF00)>>8) ;

 USB_Class_Write_Sector(pfi->FDI_Sec,znFAT_Buffer);

 return 0;
}
#endif


#ifdef CREATE_CLUSTER_CHAIN
UINT8 Create_Cluster_Chain(struct FileInfo *pfi,UINT32 cluster,UINT32 datalen)
{
 UINT32 iSec=0,clu_sec=0,old_clu=cluster,ncluster=0,temp_ncluster=0;
 UINT8 iItem=0,temp=0;
 struct FAT_Sec *pFAT_Sec=(struct FAT_Sec *)znFAT_Buffer; //将数据缓冲区首地址强转为FAT_Sec结构体的指针类型

 UINT32 Clu_Size=(pInit_Args->SectorsPerClust*pInit_Args->BytesPerSector); //簇大小，以免后面重复计算

 just_file=pfi;

 #ifndef RT_UPDATE_CLUSTER_CHAIN
 #ifdef USE_ALONE_CCCB
 CCCB_To_Alone();
 #endif
 #endif

 ncluster=datalen/Clu_Size;
 if(0!=datalen%Clu_Size) ncluster++; //如果有数据余量（整扇区），簇数加1

 temp_ncluster=ncluster; //记录下簇链的簇数

 if((pInit_Args->Free_nCluster)<ncluster) return ERR_NO_SPACE; //无足够的存储空间

 #ifndef RT_UPDATE_CLUSTER_CHAIN
 #ifndef USE_ALONE_CCCB
 if(pfi!=pcccb_cur_oc) //如果当前占用CCCB的不是现在要操作的文件
 {
  CCCB_Update_FAT();
  pcccb_cur_oc=pfi;
  (*pcccb_curdev)=Dev_No;
  pcccb_cur_initargs=pInit_Args;
 }
 #endif
 (*pcccb_curval)=cluster;
 #endif

 //===================================这里可能产生返链==========================================

 cluster=(pInit_Args->Next_Free_Cluster);

 pfi->File_CurClust=pInit_Args->Next_Free_Cluster; //当前簇为下一空簇
 pfi->File_CurSec=SOC(pfi->File_CurClust); //当前簇的首扇区

 ncluster--;
 //============================

 if(0!=old_clu)
 {
  clu_sec=(old_clu/NITEMSINFATSEC); //计算前一簇的簇项所在的FAT扇区
  USB_Class_Read_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);

  #ifdef RT_UPDATE_CLUSTER_CHAIN
  temp=(UINT8)(old_clu%NITEMSINFATSEC);
  (((pFAT_Sec->items)[temp]).Item)[0]=(UINT8)(cluster&0X000000FF)      ;  //将其链在前面的簇项上
  (((pFAT_Sec->items)[temp]).Item)[1]=(UINT8)((cluster&0X0000FF00)>>8) ;
  (((pFAT_Sec->items)[temp]).Item)[2]=(UINT8)((cluster&0X00FF0000)>>16);
  (((pFAT_Sec->items)[temp]).Item)[3]=(UINT8)((cluster&0XFF000000)>>24);
  #else
  //---------------------------------CCCB的处理--------------------------------------
  if(0==(*pcccb_counter))
  {
   pcccb_buf[(*pcccb_counter)]=(*pcccb_curval);
   (*pcccb_counter)++;
  }

  if(cluster==((*pcccb_curval)+1))
  {
   (*pcccb_curval)++;
  }
  else
  {
   if(((*pcccb_counter)+1)!=CCCB_LEN) //CCCB没有溢出
   {
    pcccb_buf[(*pcccb_counter)]=(*pcccb_curval);

    (*pcccb_counter)++;
    pcccb_buf[(*pcccb_counter)]=cluster;
    (*pcccb_curval)=cluster;
    (*pcccb_counter)++;
   }
   else //CCCB溢出，此时需要将CCCB更新到FAT
   {
    CCCB_Update_FAT();
    #ifndef USE_ALONE_CCCB
    pcccb_cur_oc=pfi;
    (*pcccb_curdev)=Dev_No;
    pcccb_cur_initargs=pInit_Args;
    #endif

    (*pcccb_counter)=0;
    pcccb_buf[(*pcccb_counter)]=pcccb_buf[(*pcccb_counter)+1]=(*pcccb_curval);
    pcccb_buf[(*pcccb_counter)+2]=cluster;
    (*pcccb_curval)=cluster;
    (*pcccb_counter)+=3;
   }
  }
  //---------------------------------CCCB的处理--------------------------------------
  #endif
 }
 else
 {
  clu_sec=(cluster/NITEMSINFATSEC); //计算前一簇的簇项所在的FAT扇区
  USB_Class_Read_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);

  #ifndef RT_UPDATE_CLUSTER_CHAIN
  //---------------------------------CCCB的处理--------------------------------------
  (*pcccb_counter)=0;
  pcccb_buf[(*pcccb_counter)]=cluster;
  (*pcccb_curval)=cluster;
  (*pcccb_counter)++;
  //---------------------------------CCCB的处理--------------------------------------
  #endif
 }

 #ifdef RT_UPDATE_CLUSTER_CHAIN
 if(clu_sec==(cluster/NITEMSINFATSEC)) //如果目标簇项与前一簇项在同一扇区
 {
  if(0==ncluster)
  {
   temp=(UINT8)(cluster%NITEMSINFATSEC);
   (((pFAT_Sec->items)[temp]).Item)[0]=0XFF;  //簇链封口
   (((pFAT_Sec->items)[temp]).Item)[1]=0XFF;
   (((pFAT_Sec->items)[temp]).Item)[2]=0XFF;
   (((pFAT_Sec->items)[temp]).Item)[3]=0X0F;

   USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);
   USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);
  }
 }
 else //如果目标簇项与前一簇项不在同一扇区
 {
  USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);
  USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);

  clu_sec=(cluster/NITEMSINFATSEC); //计算前一簇的簇项所在的FAT扇区
  USB_Class_Read_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);

  if(0==ncluster)
  {
   temp=(UINT8)(cluster%NITEMSINFATSEC);

   (((pFAT_Sec->items)[temp]).Item)[0]=0XFF;  //簇链封口
   (((pFAT_Sec->items)[temp]).Item)[1]=0XFF;
   (((pFAT_Sec->items)[temp]).Item)[2]=0XFF;
   (((pFAT_Sec->items)[temp]).Item)[3]=0X0F;

   USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);
   USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);
  }
 }
 #endif

 if(0==ncluster) //如果簇链构造完成
 {
  pInit_Args->Free_nCluster-=temp_ncluster; //更新剩余空簇数

  Update_Next_Free_Cluster();

  #ifdef RT_UPDATE_FSINFO
  Update_FSINFO();
  #endif

  return ERR_SUCC;
 }

 old_clu=cluster;

 //=============================================================================================

 clu_sec=(old_clu/NITEMSINFATSEC);

 if(((UINT8)((cluster%NITEMSINFATSEC)+1))!=((UINT8)NITEMSINFATSEC)) //如果当前的簇项不是其所在FAT扇区中的最后一个簇项
 {
  USB_Class_Read_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);

  for(iItem=(UINT8)((cluster%NITEMSINFATSEC)+1);iItem<NITEMSINFATSEC;iItem++) //检测在当前FAT扇区内当前簇项之后是否有空簇
  {
   cluster++; //簇号自增

   if(0==(((pFAT_Sec->items)[iItem]).Item)[0]  //如果发现空簇
   && 0==(((pFAT_Sec->items)[iItem]).Item)[1]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[2]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[3])
   {
    #ifdef RT_UPDATE_CLUSTER_CHAIN
    temp=(UINT8)(old_clu%NITEMSINFATSEC);

    (((pFAT_Sec->items)[temp]).Item)[0]=(UINT8)(cluster&0X000000FF)      ;  //将其链在前面的簇项上
    (((pFAT_Sec->items)[temp]).Item)[1]=(UINT8)((cluster&0X0000FF00)>>8) ;
    (((pFAT_Sec->items)[temp]).Item)[2]=(UINT8)((cluster&0X00FF0000)>>16);
    (((pFAT_Sec->items)[temp]).Item)[3]=(UINT8)((cluster&0XFF000000)>>24);
    #else
    //---------------------------------CCCB的处理--------------------------------------
    if(cluster==((*pcccb_curval)+1))
    {
     (*pcccb_curval)++;
    }
    else
    {
     if(((*pcccb_counter)+1)!=CCCB_LEN) //CCCB没有溢出
     {
      pcccb_buf[(*pcccb_counter)]=(*pcccb_curval);

      (*pcccb_counter)++;
      pcccb_buf[(*pcccb_counter)]=cluster;
      (*pcccb_curval)=cluster;
      (*pcccb_counter)++;
     }
     else //CCCB溢出，此时需要将CCCB更新到FAT，并清空CCCB，以便再次利用
     {
      CCCB_Update_FAT();
      #ifndef USE_ALONE_CCCB
      pcccb_cur_oc=pfi;
      (*pcccb_curdev)=Dev_No;
      pcccb_cur_initargs=pInit_Args;
      #endif

      (*pcccb_counter)=0;
      pcccb_buf[(*pcccb_counter)]=pcccb_buf[(*pcccb_counter)+1]=(*pcccb_curval);
      pcccb_buf[(*pcccb_counter)+2]=cluster;
      (*pcccb_curval)=cluster;
      (*pcccb_counter)+=3;
     }
    }
    //---------------------------------CCCB的处理--------------------------------------
    #endif
    ncluster--;
    old_clu=cluster;
   }

   if(0==ncluster)
   {
    #ifdef RT_UPDATE_CLUSTER_CHAIN
    (((pFAT_Sec->items)[iItem]).Item)[0]=0XFF;
    (((pFAT_Sec->items)[iItem]).Item)[1]=0XFF;
    (((pFAT_Sec->items)[iItem]).Item)[2]=0XFF;
    (((pFAT_Sec->items)[iItem]).Item)[3]=0X0F; //FAT链封口

    USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);
    USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);
    #endif
    pInit_Args->Free_nCluster-=temp_ncluster; //更新剩余空簇数
    pInit_Args->Next_Free_Cluster=cluster;

    Update_Next_Free_Cluster();

    #ifdef RT_UPDATE_FSINFO
    Update_FSINFO();
    #endif

    return ERR_SUCC;
   }
  }
 }
 #ifdef RT_UPDATE_CLUSTER_CHAIN
 USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);
 USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);
 #endif
 //=============================================================================================

 for(iSec=(clu_sec+1);iSec<(pInit_Args->FATsectors);iSec++) //在后面的FAT扇区中继续查找
 {
  USB_Class_Read_Sector(iSec+(pInit_Args->FirstFATSector),znFAT_Buffer);

  for(iItem=0;iItem<NITEMSINFATSEC;iItem++) //检测在当前FAT扇区内当前簇项之后是否有空簇
  {
   cluster++;

   if(0==(((pFAT_Sec->items)[iItem]).Item)[0]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[1]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[2]
   && 0==(((pFAT_Sec->items)[iItem]).Item)[3])
   {
    #ifdef RT_UPDATE_CLUSTER_CHAIN
    clu_sec=(old_clu/NITEMSINFATSEC);
    temp=(UINT8)(old_clu%NITEMSINFATSEC);

    if(iSec!=clu_sec) //如果要更新的簇项所在的扇区与当前扇区不是同一扇区
    {                 //则需要在更新簇项后，恢复内部级冲的数据为当前扇区
     Modify_FAT(old_clu,cluster);

     USB_Class_Read_Sector(iSec+(pInit_Args->FirstFATSector),znFAT_Buffer);
    }
    else //而如果要更新的簇项所在扇区与当前扇区为同一扇区，则只需要在内部缓冲中进行更新
    {    //而无需向扇区中回写，这是提供簇链创建速度的核心思想
     (((pFAT_Sec->items)[temp]).Item)[0]=(UINT8)(cluster&0X000000FF)      ;  //将其链在前面的簇项上
     (((pFAT_Sec->items)[temp]).Item)[1]=(UINT8)((cluster&0X0000FF00)>>8) ;
     (((pFAT_Sec->items)[temp]).Item)[2]=(UINT8)((cluster&0X00FF0000)>>16);
     (((pFAT_Sec->items)[temp]).Item)[3]=(UINT8)((cluster&0XFF000000)>>24);
    }
    #else
    //---------------------------------CCCB的处理--------------------------------------
    if(cluster==((*pcccb_curval)+1))
    {
     (*pcccb_curval)++;
    }
    else
    {
     if(((*pcccb_counter)+1)!=CCCB_LEN) //CCCB没有溢出
     {
      pcccb_buf[(*pcccb_counter)]=(*pcccb_curval);

      (*pcccb_counter)++;
      pcccb_buf[(*pcccb_counter)]=cluster;
      (*pcccb_curval)=cluster;
      (*pcccb_counter)++;
     }
     else //CCCB没有溢出，此时需要将CCCB更新到FAT
     {
      CCCB_Update_FAT();
      #ifndef USE_ALONE_CCCB
      pcccb_cur_oc=pfi;
      (*pcccb_curdev)=Dev_No;
      pcccb_cur_initargs=pInit_Args;
      #endif

      (*pcccb_counter)=0;
      pcccb_buf[(*pcccb_counter)]=pcccb_buf[(*pcccb_counter)+1]=(*pcccb_curval);
      pcccb_buf[(*pcccb_counter)+2]=cluster;
      (*pcccb_curval)=cluster;
      (*pcccb_counter)+=3;
     }
    }
    //---------------------------------CCCB的处理--------------------------------------
    #endif
    ncluster--;
    old_clu=cluster;
   }

   if(0==ncluster)
   {
    #ifdef RT_UPDATE_CLUSTER_CHAIN
    clu_sec=(old_clu/NITEMSINFATSEC);

    (((pFAT_Sec->items)[iItem]).Item)[0]=0XFF;
    (((pFAT_Sec->items)[iItem]).Item)[1]=0XFF;
    (((pFAT_Sec->items)[iItem]).Item)[2]=0XFF;
    (((pFAT_Sec->items)[iItem]).Item)[3]=0X0F; //FAT链封口

    USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector),znFAT_Buffer);
    USB_Class_Write_Sector(clu_sec+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);
    #endif
    pInit_Args->Free_nCluster-=temp_ncluster; //更新剩余空簇数
    pInit_Args->Next_Free_Cluster=cluster;

    Update_Next_Free_Cluster();

    #ifdef RT_UPDATE_FSINFO
    Update_FSINFO();
    #endif

    return ERR_SUCC;
   }
  }
  #ifdef RT_UPDATE_CLUSTER_CHAIN
  USB_Class_Write_Sector(iSec+(pInit_Args->FirstFATSector),znFAT_Buffer);
  USB_Class_Write_Sector(iSec+(pInit_Args->FirstFATSector+pInit_Args->FATsectors),znFAT_Buffer);
  #endif
 }

 return ERR_FAIL;
}
#endif

#ifdef WRITEDATA_FROM_NCLUSTER
UINT32 WriteData_From_nCluster(struct FileInfo *pfi,UINT32 len,UINT8 *pbuf)
{
 UINT32 CluSize=((pInit_Args->BytesPerSector)*(pInit_Args->SectorsPerClust)); //计算簇大小，以免后面重复计算
 UINT32 temp=len/CluSize;//计算要写入的数据量够几个整簇
 UINT32 iClu=0,start_clu=0,end_clu=0,next_clu=0;
 UINT32 temp1=0,temp2=0;
 UINT8 res=0;

 #ifdef USE_EXCHANGE_BUFFER
 #ifndef USE_ALONE_EXB
 UINT8 old_devno=Dev_No;
 #else
 pexb_buf=(pfi->exb_buf);
 #endif
 #endif

 just_file=pfi;

 #ifndef RT_UPDATE_CLUSTER_CHAIN
 get_next_cluster_in_cccb=1;
 #ifdef USE_ALONE_CCCB
 CCCB_To_Alone();
 #endif
 #endif

 if(0==len) return 0; //如果要写入的数据长度为0，则直接返回

 if(0==pfi->File_CurClust) //如果是空文件，则当前簇为0，即尚未为其分配簇
 {
  pfi->File_StartClust=pInit_Args->Next_Free_Cluster;
  Update_File_sClust(pfi,pInit_Args->Next_Free_Cluster);
 }

 res=Create_Cluster_Chain(pfi,pfi->File_CurClust,len); //为整簇数据预建簇链
 if(res) return res;

 if(0==temp) //如果要写入的数据少于一个簇
 {
  temp=len/(pInit_Args->BytesPerSector); //要写入的数据够几个整扇区
  USB_Class_Write_nSector(temp,SOC(pfi->File_CurClust),pbuf);
  pfi->File_CurSec+=temp;
  pbuf+=(temp*(pInit_Args->BytesPerSector));

  temp=len%(pInit_Args->BytesPerSector);
  if(0!=temp) //还有数据要写入，不足扇区的最后一点数据
  {
   #ifndef USE_EXCHANGE_BUFFER
   Memory_Copy(znFAT_Buffer,pbuf,temp); //把不足一扇区的数据先放入内部缓冲区中
   USB_Class_Write_Sector(pfi->File_CurSec,znFAT_Buffer); //将内部缓冲区中的数据写入扇区中
                                                         //如果直接使用pbuf作数据源来写入，因不足一个扇区
                                                         //从而会造成内存溢出,程序崩溃
   #else
   #ifndef USE_ALONE_EXB
   if(Dev_No!=sexb_cur_dev) //如果现在操作的设备不是当前占用EXB的设备
   {
    if(0!=sexb_cur_sec) //如果EXB正被占用
    {
     Dev_No=sexb_cur_dev;
     USB_Class_Write_Sector(sexb_cur_sec,pexb_buf); //如果EXB中还有数据，则先将这些数据回写到其相应扇区中

     Dev_No=old_devno;
    }
   }
   else //如果现在操作的设备正是当前占用EXB的设备
   {
    if(sexb_cur_sec!=(pfi->File_CurSec)) //占用EXB的扇区不是当前要操作的扇区
    {
     if(0!=sexb_cur_sec) //如果EXB正被占用
     {
      USB_Class_Write_Sector(sexb_cur_sec,pexb_buf); //如果EXB中还有数据，则先将这些数据回写到其相应扇区中
     }
    }
   }
   #endif

   Memory_Copy(pexb_buf,pbuf,temp);

   #ifndef USE_ALONE_EXB
   sexb_cur_sec=pfi->File_CurSec;   //记录当前交换缓冲中所反映的扇区地址
   sexb_cur_dev=Dev_No; //记录当前交换缓冲中数据所在的设备号
   psexb_cur_oc=pfi; //记录EXB中缓冲的数据属于哪个文件
   #else
   just_file->exb_cursec=pfi->File_CurSec;
   #endif
   #endif

   pfi->File_CurPos=(UINT16)temp;
  }
 }
 else
 {
  //计算各连续簇段，以尽可能的使用多扇区写驱动，以提高数据写入速度
  //start_clu与end_clu用于记录连续簇段的始末
  start_clu=end_clu=pfi->File_CurClust;

  for(iClu=1;iClu<temp;iClu++)
  {
   next_clu=Get_Next_Cluster(end_clu);

   if((next_clu-1)==end_clu) //如果两个簇相临，即连续
   {
    end_clu=next_clu;
   }
   else //如果两个簇不相临，即遇到簇链断点
   {
    USB_Class_Write_nSector(((end_clu-start_clu+1)*(pInit_Args->SectorsPerClust)),SOC(start_clu),pbuf);
    start_clu=next_clu;
    end_clu=next_clu;
   }
  }

  temp1=(len%CluSize)/(pInit_Args->BytesPerSector); //剩余数据够几个整扇区
  temp2=Get_Next_Cluster(end_clu);
  temp=(end_clu-start_clu+1)*(pInit_Args->SectorsPerClust);

  if(!IS_END_CLU(temp2)) //如果下一簇不是结束簇，即后面还有数据要写入
  {
   if((temp2-1)==end_clu) //如果最后一个簇中的剩余扇区与前面的最后的连续簇段是连续的
   {
    USB_Class_Write_nSector((temp+temp1),SOC(start_clu),pbuf);
    pbuf+=((temp+temp1)*(pInit_Args->BytesPerSector));
   }
   else
   {
    USB_Class_Write_nSector(((end_clu-start_clu+1)*(pInit_Args->SectorsPerClust)),SOC(start_clu),pbuf);
    pbuf+=(temp*(pInit_Args->BytesPerSector));
    USB_Class_Write_nSector(temp1,SOC(temp2),pbuf);
    pbuf+=(temp1*(pInit_Args->BytesPerSector));
   }

   pfi->File_CurClust=temp2;
   pfi->File_CurSec=(SOC(temp2)+temp1);
   //=======================================================================================
   temp=len%(pInit_Args->BytesPerSector);
   if(0!=temp) //还有数据要写入
   {
    #ifndef USE_EXCHANGE_BUFFER
    Memory_Copy(znFAT_Buffer,pbuf,temp); //把不足一扇区的数据先放入内部缓冲区中
    USB_Class_Write_Sector(pfi->File_CurSec,znFAT_Buffer); //将内部缓冲区中的数据写入扇区中
                                                         //如果直接使用pbuf作数据源来写入，因不足一个扇区
                                                         //从而会造成内存溢出,程序崩溃
    #else
    #ifndef USE_ALONE_EXB
    if(Dev_No!=sexb_cur_dev) //如果现在操作的设备不是当前占用EXB的设备
    {
     if(0!=sexb_cur_sec) //如果EXB正被占用
     {
      Dev_No=sexb_cur_dev;
      USB_Class_Write_Sector(sexb_cur_sec,pexb_buf); //如果EXB中还有数据，则先将这些数据回写到其相应扇区中

      Dev_No=old_devno;
     }
    }
    else //如果现在操作的设备正是当前占用EXB的设备
    {
     if(sexb_cur_sec!=(pfi->File_CurSec)) //占用EXB的扇区不是当前要操作的扇区
     {
      if(0!=sexb_cur_sec) //如果EXB正被占用
      {
       USB_Class_Write_Sector(sexb_cur_sec,pexb_buf); //如果EXB中还有数据，则先将这些数据回写到其相应扇区中
      }
     }
    }
    #endif

    Memory_Copy(pexb_buf,pbuf,temp);

    #ifndef USE_ALONE_EXB
    sexb_cur_sec=pfi->File_CurSec;
    sexb_cur_dev=Dev_No; //记录当前交换缓冲中数据所在的设备号
    psexb_cur_oc=pfi; //记录EXB中缓冲的数据属于哪个文件
    #else
    just_file->exb_cursec=pfi->File_CurSec;
    #endif
    #endif

    pfi->File_CurPos=(UINT16)temp;
   }
  }
  else //如果下一簇已为结束簇，即后面已无数据再要写入
  {
   USB_Class_Write_nSector(temp,SOC(start_clu),pbuf);
   pbuf+=((temp+temp1)*(pInit_Args->BytesPerSector));

   pfi->File_CurClust=end_clu;
   pfi->File_CurSec=SOC(end_clu);
  }
 }

 #ifdef RT_UPDATE_FSINFO
 Update_FSINFO();
 #endif

 pfi->File_CurOffset+=len;

 return len;
}
#endif


#ifdef ZNFAT_DUMP_DATA
UINT8 znFAT_Dump_Data(struct FileInfo *pfi,UINT32 offset)
{
 just_file=pfi;

 #ifndef RT_UPDATE_CLUSTER_CHAIN
 #ifdef USE_ALONE_CCCB
 CCCB_To_Alone();
 #endif
 #endif

 if(offset>=(pfi->File_Size)) //要截断的位置超出文件范围
 {
  return ERR_FAIL;
 }

 znFAT_Seek(pfi,offset); //定位到要截断的位置

 #ifndef RT_UPDATE_CLUSTER_CHAIN //销毁之前，先把CCCB中的簇链段更新到FAT
 #ifndef USE_ALONE_CCCB
 if(pfi==pcccb_cur_oc) 
 #endif
 {
  CCCB_Update_FAT();
 }
 #endif

 Destroy_FAT_Chain(pfi->File_CurClust); //销毁簇链

 if(offset>0)
 {
  Modify_FAT(pfi->File_CurClust,0X0FFFFFFF); //簇链封口
 }

 pfi->File_Size=offset; //更新文件大小

 #ifdef RT_UPDATE_FILESIZE
 Update_File_Size(pfi); //更文件目录项中的文件大小字段
 #endif

 if(0==pfi->File_Size) Update_File_sClust(pfi,0); //如果文件大小为0，更新文件开始簇为0

 #ifdef RT_UPDATE_FSINFO
 Update_FSINFO();
 #endif

 return ERR_SUCC;
}
#endif


