#ifndef list_type_h
#define list_type_h

#ifdef id_enable
#include <id/id.h>
#endif

/*
 *链式结构节点的管理及操作的结构
 */
typedef struct Node{
    unsigned int type;//类型
    void *value;//值指针
    struct Node *next;//指向下一个链式结构节点
    struct Node *last;//指向上一个链式结构节点
#ifdef id_enable
    SID *s_id;
#endif
} Node;

/*
 *链式结构的管理及操作的结构
 */
typedef struct List{
    Node *head;//指向第一个链式结构节点
    Node *tail;//指向最后一个链式结构节点
    uint64_t length;
#ifdef id_enable
    SID *s_id;
#endif
} List;

#endif /* list_type_h */
