#ifndef list_quick_h
#define list_quick_h

#include <list/list_type.h>

/*
 *长链表模式下链表缓存块的记录结构
 */
struct lst_std_id{
    unsigned long long start_idx;
    unsigned long long end_idx;
#ifdef id_enable
    SID *sid;
#endif
};

struct list_quick;

/*
 *长链表模式下链表改动偏移量的记录结构
 */
struct index_change{
    unsigned long long c_index;//偏移量,有正负之分
    int f_count;//偏移量所对应的数组的节点
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

/***********************************************
 *长链表模式:当链表长度很长时,链表查找的代价将会很大.
 *         该模式用于优化长链表的查找过程.降低时间复杂度.
 ***********************************************/
/*
 *打开长链表模式
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int enableListQuick(List *p_list);

/*
 *关闭长链表模式
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int disableListQuick(List *p_list);

extern Node *getNodeByFnNode(List *p_list, unsigned long long index);

extern void digHole(List *p_list, Node *p_node);

extern Node *findFnNode(List *p_list, Node *p_node);

extern int indexChange(List *p_list, unsigned long long c_index, int move);

//Node *getListTail(List *);

#endif /* list_quick_h */
