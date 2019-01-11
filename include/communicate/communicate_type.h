#ifndef communicate_type_h
#define communicate_type_h

#include<type.h>

/*
 *文件头信息的管理及操作的结构
 */
typedef struct file_head{
    char head_test[18];//数据文件头部的验证信息
    uint32_t data_num;//数据文件中的标准数据结构的数目
}F_HEAD;

/*
 *数据文件的管理及操作的结构
 */
typedef struct data_file{
    FILE *fp;//数据文件
    F_HEAD *pf_head;//数据文件头
    Chain *pf_stdlst;//数据文件的标志数据结构的储存链表
}D_FILE;

/*
 *标准数据结构的管理及操作的结构
 */
typedef struct standard_data_blocks{
    uint16_t type;//数据块的类型
    uint32_t location;//数据块在数据文件中的定位
    char *sid;//数据块的ID
    _Bool if_data;//数据块是否赋值
    unsigned int blocks_num;//数据块字节大小
    char *buff;//指向数据块储存值内存空间的指针
}STD_BLOCKS;

/*
 *标准数据结构中数据块的连接关系的管理及操作的结构
 */
typedef struct standard_data_connection{
    uint32_t location;//数据块链接关系结构在文件中的定位
    char *f_sid;//前一个数据块的ID
    char *s_sid;//后一个数据块的ID
}STD_CTN;

/*
 *标准数据结构头的管理及操作的结构
 */
typedef struct standard_data_head{
    uint32_t data_blk_num;//数据块的数目
    uint32_t data_ctn_num;//数据块链接关系结构的数目
}STD_HEAD;

/*
 *标准数据结构的管理及操作的结构
 */
typedef struct standard_data{
    SID *s_id;//标准数据结构的ID
    int read_data;//标准数据结构是否已经读取完整
    uint16_t type;//标准数据结构所对应的类型
    uint32_t size;//标准数据结构在数据文件中的大小
    uint32_t location;//标准数据结构的头在数据文件中的定位
    _Bool lock;//标准数据文件是否被锁住
    Chain *pd_blocklst;//数据块储存链表
    Chain *pd_ctnlst;//数据块连接关系结构的储存链表
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

#endif /* communicate_type_h */
