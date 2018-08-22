#ifndef type_h
#define type_h

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdarg.h>

/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
*/




/************************************************
 *库相关类型的编号
 ************************************************/

#define VOID 0
#define INT 1
#define DOUBLE 2
#define STRING 3
#define POINTER 4
#define LIST 5
#define STACK 6
#define TREE 7
#define LIST_NODE 8
#define TREE_NODE 9
#define STACK_NODE 10
#define T_SID 11
#define UINT 12
#define STANDARD_DATA 13
#define DATA_FILE 14
#define MESSAGE 15
#define HOLE 16
#define ULLINT 17





/************************************************
 *库相关参数的定义
 ************************************************/

#define  DEEPC 1
#define  DEEPB 2
#define  DEEPA 3
#define TYPE_LEN 5
#define  DEEPC_LEN 4
#define  DEEPB_LEN 8
#define  DEEPA_LEN 32
#define DATA_BIT 5
#define DEEP_LEN 25
#define DEEPER_LEN 65
#define DEEPEST_LEN 225
#define SID_LEN 33
#define FILE_TSET_LEN 18
#define HEAD_TEST_LEN 9
#define INFO_TEST_LEN 8
#define ENABLE_LIST_QUICK 65535
#define FN_NODE_SPARE 500
#define INDEX_CHANGE_MAX 500
#define INDEX_DISTANCE_MAX 120
#define STD_TEXT_LEN 4
#define HIGH 0x3
#define STANDARD 0x2
#define LOW 0x1





/************************************************
 *库相关操作宏的定义
 ************************************************/

#define ABS(x) ((x>0)?(x):(-x))





/************************************************
 *库相关结构的定义
 ************************************************/

/*
 *MD5的管理及操作的结构
 */
typedef struct md5_ctx{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;

/*
 *SID的初始值管理及操作的结构
 */
struct sid_raw{
    unsigned int type;
    unsigned int *value;//4
    unsigned int *value_deeper;//8
    unsigned int *value_deepest;//32
};

/*
 *SID的管理及操作的结构
 */
typedef struct s_id{
    struct sid_raw *sr;//指向SID初始值
    unsigned int deep;//SID初始值的复杂度
    MD5_CTX *md5;//指向MD5结构
    unsigned char *decrypt_hex;//指向MD5的Hex信息
    char *decrypt_str;//指向MD5的Hex信息转化成的字符串
    
}SID;

/*
 *节点的管理及操作的结构
 */
typedef struct Node{
    unsigned long long f_number;//长链表模式下,分派的数组节点编号
    unsigned int type;//类型
    void *value;//值指针
    struct Node *next;//指向下一个节点
    struct Node *last;//指向上一个节点
    SID *s_id;
} Node;

/*
 *单向节点的管理及操作的结构
 */
typedef struct simple_Node{
    void *value;//值指针
    struct simple_Node *next;//指向下一个节点
}s_Node;

/*
 *长链表模式下链表缓存块的记录结构
 */
struct lst_std_id{
    unsigned long long start_idx;
    unsigned long long end_idx;
    SID *sid;
};

struct list_quick;

/*
 *链表的管理及操作的结构
 */
typedef struct List{
    Node *head;//指向第一个节点
    Node *tail;//指向最后一个节点
    s_Node *s_head;//指向第一个单向节点
    s_Node *s_tail;//指向最后一个单向节点
    /*如果长链表模式开启则指向对应的长链表模式的管理结构,如果未开启则为NULL*/
    struct list_quick *p_lq;
    unsigned long long length;//链表的长度
    SID *s_id;
} List;

/*
 *长链表模式下链表改动偏移量的记录结构
 */
struct index_change{
    unsigned long long c_index;//偏移量,有正负之分
    int f_count;//偏移量所对应的数组对的节点
};

/*
 *长链表模式的管理及操作的结构
 */
struct list_quick{
    Node **fn_node;//指向链表各个节点的映射数组
    unsigned long long fn_len;//映射数组的总长度
    unsigned long long rlst_len;//在映射数组实际被占用的长度
    _Bool if_sort;//链表是否有序
    unsigned int idxc_count;//链的删减增的操作次数
    struct index_change *idxc_lst[INDEX_CHANGE_MAX];//储存链表的删减增操作的记录
    FILE *fp;//链表缓存文件
    List *stdid_lst;
};

/*
 *错误管理中信息的管理及操作的结构
 */
typedef struct Info{
    char head[64];//信息头
    char body[256];//信息内容
}Info;

/*
 *错误管理中错误的管理及操作的结构
 */
typedef struct Error{
    unsigned int type;//错误类型号
    int priority;//优先级
    time_t time;//错误产生的时间
    Info info;//信息指针
}Error;

/*
 *错误管理中警告的管理及操作的结构
 */
typedef struct Notice{
    unsigned int type;//警告类型号
    time_t time;//警告产生的时间
    Info info;//信息指针
}Notice;

/*
 *错误管理中日志信息的管理及操作的结构
 */
typedef struct Log{
    FILE *fp;//日志文件的指针
    int if_enable;//日志文件是否启用
    unsigned long int id;//日志文件的ID
}Log;

/*
 *栈节点的管理及操作的结构
 */
typedef struct stack_node{
    unsigned int type;//栈节点的类型
    void *value;//值指针
    struct stack_node *next;//下一个栈节点
    SID *s_id;//栈节点的ID
} SNode;

/*
 *栈的管理及操作的结构
 */
typedef struct stack{
    unsigned long long length;//栈的长度
    SNode *top;//指向栈顶的栈节点
    SID *s_id;//栈的ID
} Stack;

/*
 *超级树节点的管理及操作的结构
 */
typedef struct tree_node
{
    SID *s_id;//超级树节点的ID
    List *home;//超级树节点的子节点列表
    struct tree_node *father;//超级树节点的父节点
    Node *room;//超级树节点的父节点的子节点列表
    unsigned long long child_num;//超级树节点的子节点数量
    unsigned int type;//超级树节点的类型
    void *value;//值指针
}TNode;

/*
 *二叉树节点的管理及操作的结构
 */
typedef  struct simple_tree_node{
    void *value;//值指针
    struct simple_tree_node *childs[2];//子节点
}s_TNode;

/*
 *树的管理及操作的结构
 */
typedef struct tree
{
    SID *s_id;//超级树的SID
    TNode *root;//超级树根节点
    s_TNode *s_root;//二叉树的根节点
}Tree;

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

#endif /* type_h */
