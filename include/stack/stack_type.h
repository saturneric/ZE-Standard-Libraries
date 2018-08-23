#ifndef stack_type_h
#define stack_type_h

#ifdef id_enable
#include <id/id.h>
#endif

/*
 *栈节点的管理及操作的结构
 */
typedef struct stack_node{
    unsigned int type;//栈节点的类型
    void *value;//值指针
    struct stack_node *next;//下一个栈节点
#ifdef id_enable
    SID *s_id;//栈节点的ID
#endif
} SNode;

/*
 *栈的管理及操作的结构
 */
typedef struct stack{
    unsigned long long length;//栈的长度
    SNode *top;//指向栈顶的栈节点
#ifdef id_enable
    SID *s_id;//栈的ID
#endif
} Stack;

#endif /* stack_type_h */
