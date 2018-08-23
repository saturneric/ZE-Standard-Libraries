#ifndef communicate_h
#define communicate_h

#include "../type/type.h"
#include "../list/list_expand.h"





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
 *数据文件管理结构中标准数据结构管理结构的简略信息的写入函数
 */
__CALLBACK_STATE(StandardDataInfoWrite);

/*
 *数据文件管理结构中标准数据结构管理结构的内容的写入函数
 */
__CALLBACK_STATE(StandardDataWrite);

/*
 *标准数据结构管理结构中的数据块链接关系管理结构的写入函数
 */
__CALLBACK_STATE(StandardDConnectionWrite);

/*
 *标准数据结构管理结构中的数据块管理结构的写入函数
 */
__CALLBACK_STATE(StandardDBlockWrite);

/*
 *将相关数据文件中的内容,读出到数据文件管理结构中,等待操作.
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int dataFileReadOut(D_FILE *p_dfile);

/*
 *数据文件管理结构的读出函数的回调函数声明
 */
__CALLBACK_STATE(dataFileReadOut);





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

/*
 *计算标准数据结构在文件中占用的空间,以字节为单位.
 */
static unsigned long long calStandardData(STD_DATA *p_std);

/*
 *计算数据块链接关系在文件中的大小
 */
__CALLBACK_STATE(calStandardDataCTN);

/*
 *计算数据块在文件中的大小
 */
__CALLBACK_STATE(calStandardDataBLK);





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

/*
 *将标准数据结构转换成链表的回调函数
 */
__CALLBACK_STATE(StandardDataToList);

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

/*
 *通过标准数据结构的ID,在数据文件中读入特定的标准数据结构函数的回调函数
 */
__CALLBACK_STATE(findStandardDataBySid);





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
