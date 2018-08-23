#ifndef communicate_h
#define communicate_h

/*
 *文件头信息的管理及操作的结构
 */
typedef struct file_head{
    char head_test[18];//数据文件头部的验证信息
    unsigned long long data_num;//数据文件中的标准数据结构的数目
}F_HEAD;

/*
 *数据文件的管理及操作的结构
 */
typedef struct data_file{
    FILE *fp;//数据文件
    F_HEAD *pf_head;//数据文件头
    List *pf_stdlst;//数据文件的标志数据结构的储存链表
}D_FILE;

/*
 *标准数据结构的管理及操作的结构
 */
typedef struct standard_data_blocks{
    unsigned int type;//数据块的类型
    unsigned long long location;//数据块在数据文件中的定位
    char *sid;//数据块的ID
    _Bool if_data;//数据块是否赋值
    unsigned int blocks_num;//数据块字节大小
    char *buff;//指向数据块储存值内存空间的指针
}STD_BLOCKS;

/*
 *标准数据结构中数据块的连接关系的管理及操作的结构
 */
typedef struct standard_data_connection{
    unsigned long long location;//数据块链接关系结构在文件中的定位
    char *f_sid;//前一个数据块的ID
    char *s_sid;//后一个数据块的ID
}STD_CTN;

/*
 *标准数据结构头的管理及操作的结构
 */
typedef struct standard_data_head{
    unsigned long long data_blk_num;//数据块的数目
    unsigned long long data_ctn_num;//数据块链接关系结构的数目
}STD_HEAD;

/*
 *标准数据结构的管理及操作的结构
 */
typedef struct standard_data{
    SID *s_id;//标准数据结构的ID
    int read_data;//标准数据结构是否已经读取完整
    unsigned int type;//标准数据结构所对应的类型
    unsigned long long size;//标准数据结构在数据文件中的大小
    unsigned long long location;//标准数据结构的头在数据文件中的定位
    _Bool lock;//标准数据文件是否被锁住
    List *pd_blocklst;//数据块储存链表
    List *pd_ctnlst;//数据块连接关系结构的储存链表
}STD_DATA;

/*
 *消息的管理及操作的结构
 */
typedef struct message{
    SID *p_sid;//消息的ID
    time_t time;//消息的产生时间
    char titile[16];//消息标题
    unsigned long size;//消息的大小
    char content[0];//消息的正文
}MSG;




/************************************************
 相关结构体初始化: 初始化相关结构体有关函数
 ************************************************/

/*
 *以写的方式初始化数据文件管理结构
 *参数: route指示数据文件路径
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern D_FILE *initDataFileForWrite(char *route);

/*
 *以读的方式初始化数据文件管理结构
 *参数: route指示数据文件路径
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern D_FILE *initDataFileForRead(char *route);

/*
 *初始化数据块管理结构
 *参数: type指示数据块储存数据的数据类型,data_size指示数据块储存数据的大小
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern STD_BLOCKS *initStandardDBlocks(SID *p_sid, unsigned int type, unsigned long long data_size);

/*
 *初始化数据块链接关系管理结构
 *参数: f_sid指示第一个数据块的SID,s_sid指示第二个数据块的SID.
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern STD_CTN *initStandardDConnection(SID *f_sid, SID *s_sid);

/*
 *初始化标准数据结构管理结构
 *参数: type指示标准数据结构所储存的数据结构的数据类型, s_id指示所储存的数据结构的ID,
        若s_id为NULL,则另外分配一个ID.为了方便管理,标准数据结构必须有ID.
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern STD_DATA *initStandardData(unsigned int type, SID *s_id);





/************************************************
 相关结构体的组织: 组织相关结构体有关函数
 ************************************************/

/*
 *为数据块添加数据
 *参数: data为指向所添加数据所在内存空间的指针
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int dataForStandardDBlock(STD_BLOCKS *p_stdb,void *data);

/*
 *为数据文件添加标准数据结构
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int dataFileAddStandardData(D_FILE *p_dfile, STD_DATA *p_std);

/*
 *为标准数据结构添加数据块
 *参数: type指示所添加数据的数据类型, data为指向所添加数据所在内存空间的指针, data_size指示所添加数据的大小
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int standardDataAddBlock(STD_DATA *p_std, SID *p_sid ,unsigned int type, void *data, unsigned long long data_size);

/*
 *为标准数据结构添加数据块链接关系结构体
 *参数: f_sid指示第一个数据块的SID,s_sid指示第二个数据块的SID.
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int standardDataAddConnection(STD_DATA *p_std, SID *f_sid, SID *s_sid);





/************************************************
 数据文件管理结构的整体写入与读出: 对数据文件管理结构的操作
 ************************************************/

/*
 *将数据文件管理结构写入到相关数据文件中,以储存.
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int dataFileWriteIn(D_FILE *p_dfile);

/*
 *将相关数据文件中的内容,读出到数据文件管理结构中,等待操作.
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int dataFileReadOut(D_FILE *p_dfile);







/************************************************
 相关结构的释放操作: 释放相关结构体所占内存空间的相关函数
 ************************************************/

/*
 *释放数据块所占内存空间
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int releaseSTDBlocks(STD_BLOCKS *p_stdb);

/*
 *释放标准数据结构管理结构所占的内存空间
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int releaseStandardData(STD_DATA *p_std);

/*
 *释放数据块链接关系管理结构所占的内存空间
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int releaseSTDConnection(STD_CTN *p_stdc);

/*
 *释放数据文件管理结构所占的内存空间
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int releaseDFile(D_FILE *p_file);





/************************************************
 结构类型的转换: 其他数据结构与标准数据结构的转换相关函数
 ************************************************/

/*
 *将链表转化为标准数据结构
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern STD_DATA *listToSTD(List *);

/*
 *将标准数据结构转换成链表
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern List *standardDataToList(STD_DATA *);

//STD_DATA *stackToSTD(Stack *);

//STD_DATA *treeToSTD(Tree *);





/************************************************
 标准数据结构的随机存取: 标准数据结构的随机存取相关函数
 ************************************************/

/*
 *读取数据文件的简略信息,为随机存取准备必要信息
 *说明: 该函数只会在数据文件管理结构中建立一个框架,不会读入实际的数据块以及数据块链接关系.
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int readDataFileInfo(D_FILE *p_dfile);

/*
 *读取数据文件中的特定标准数据结构
 *参数: p_std为指向框架中的相关标准数据所在内存空间的指针
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int readStandardData(D_FILE *p_dfile, STD_DATA *p_std);

/*
 *读取数据文件中的特定标准数据结构中的数据块
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int readSTDBlocks(STD_BLOCKS *p_stdb);

/*
 *读取文件头,检验文件是否为数据文件
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int checkIfDataFile(D_FILE *p_dfile);

/*
 *通过标准数据结构的ID,在数据文件中读入特定的标准数据结构
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int readStandardDataBySid(D_FILE *p_dfile, SID *p_sid);





/************************************************
 标准数据结构信息: 获取标准数据结构信息相关函数
 ************************************************/

/*
 *打印标准数据结构信息
 */
extern void printStandardData(void *value);





/************************************************
 消息的操作: 消息的操作相关函数
 ************************************************/

/*
 *创建消息
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern MSG *createMessage(char *title, void *data, unsigned long data_size);

/*
 *通过ipv4地址发送消息
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int sendMessageIPv4(MSG *p_msg, char *ip, unsigned int port);




#endif /* communicate_h */
