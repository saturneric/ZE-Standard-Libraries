#ifndef list_type_h
#define list_type_h

#ifdef id_enable
#include <id/id.h>
#endif

/*
 *节点的管理及操作的结构
 */
typedef struct Node{
#ifdef list_quick_enable
    unsigned long long f_number;//长链表模式下,分派的数组节点编号
#endif
    unsigned int type;//类型
    void *value;//值指针
    struct Node *next;//指向下一个节点
    struct Node *last;//指向上一个节点
#ifdef id_enable
    SID *s_id;
#endif
} Node;

/*
 *单向节点的管理及操作的结构
 */
typedef struct simple_Node{
    void *value;//值指针
    struct simple_Node *next;//指向下一个节点
}s_Node;

/*
 *链表的管理及操作的结构
 */
typedef struct List{
    Node *head;//指向第一个节点
    Node *tail;//指向最后一个节点
#ifdef list_simple_h
    s_Node *s_head;//指向第一个单向节点
    s_Node *s_tail;//指向最后一个单向节点
#endif
#ifdef list_quick_enable
    /*如果长链表模式开启则指向对应的长链表模式的管理结构,如果未开启则为NULL*/
    struct list_quick *p_lq;
    unsigned long long length;//链表的长度
#endif
#ifdef id_enable
    SID *s_id;
#endif
} List;

#endif /* list_type_h */
