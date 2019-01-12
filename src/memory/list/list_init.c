#include <type.h>
#include <list/list.h>


/**
 创建一个新的链式结构节点，并为其分配内存空间

 @param if_sid 新的链式结构节点是否带ID
 @return 返回指向新的链式结构节点的内存地址指针
 */
#ifdef id_enable
Node *initNode(_Bool if_sid)
#else
Node *initNode(void)
#endif
{
    Node *p_node = (Node *)malloc(sizeof(Node));
    if(p_node == NULL){
        return NULL;
    }
    Node *prec_node = NULL;
//如果ID模块可能启用则编译以下代码
#ifdef id_enable
    if (if_sid)p_node->s_id = getS_id(LIST_NODE, 1);
    else p_node->s_id = NULL;
#endif
    p_node->next = NULL;
    p_node->last = NULL;
    p_node->type = VOID;
//    链式结构内存安全模式相关操作
    if (if_safeModeForNode) {
        if_safeModeForNode = 0;
        prec_node = initNode(0);
        if_safeModeForNode = 1;
        initMallocValueForNode(prec_node, POINTER, (void *)p_node);
        insertInTail(node_list, prec_node);
    }
    return p_node;
}

/**
 创建一个新的链式结构，并为其分配内存空间
 
 @param if_sid 新的链式结构是否带ID
 @return 返回指向新的链式结构的内存地址指针
 */
#ifdef id_enable
List *initList(_Bool if_sid)
#else
List *initList(void)
#endif
{
    Node *p_node = NULL;
    List *p_list = (List *)malloc(sizeof(List));
    if(p_list == NULL){
        return NULL;
    }
//如果ID模块可能启用则编译以下代码
#ifdef id_enable
    if(if_sid) p_list->s_id = getS_id(LIST, 1);
    else p_list->s_id = NULL;
#endif
    p_list->head = NULL;
    p_list->tail = NULL;
    if (if_safeModeForNode) {
        if_safeModeForNode = 0;
        p_node = initNode(0);
        if_safeModeForNode = 1;
        initMallocValueForNode(p_node, POINTER, (void *)p_list);
        insertInTail(list_list, p_node);
    }
    return p_list;
}

/**
 为新的链式结构节点设定初始值

 @param p_node 指向目标链式结构节点的指针
 @param type 值得类型
 @param p_value 指向目标值的内存空间的指针
 @return 执行成功则返回0
 */
inline int initMallocValueForNode(Node *p_node, unsigned int type, const void *p_value) {
    p_node->type = type;
    p_node->value = (void *)p_value;
    return 0;
}
