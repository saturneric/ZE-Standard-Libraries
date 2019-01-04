#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>
//长链表模式可能启用则包含以下头文件
#ifdef list_quick_enable
#include <list/list_quick.h>
#endif

/**
 直接获得节点中储存的字符串

 @param p_node 指向目标节点的指针
 @return 返回节点中储存的字符串
 */
char *getByStringForNode(Node *p_node) {
	if (p_node->type == STRING) return (char *)(p_node->value);
	else return NULL;
}

/**
 直接获得节点中储存的双精度浮点值
 
 @param p_node 指向目标节点的指针
 @return 返回节点中储存的双精度浮点值
 */
double getByDoubleForNode(Node *p_node) {
	if (p_node->type == DOUBLE) return *(double *)(p_node->value);
	else return -1.0;
}

/**
 直接获得节点中储存的指针值
 
 @param p_node 指向目标节点的指针
 @return 返回节点中储存的指针值
 */
void *getByPointerForNode(Node *p_node) {
	return (void *)(p_node->value);
}


/**
 通过链表中相应的节点获得其在链表中的排列序号

 @param p_list 指向目标链表
 @param p_node 指向目标节点的指针
 @return 成功返回相应排列序号，失败则会返回0
 */
unsigned long long getIndexByNode(List *p_list, Node *p_node) {
//    长链表模式可能启用则编译以下代码
#ifdef list_quick_enable
    if (p_list->p_lq != NULL){
        register Node **p_fn_node = p_list->p_lq->fn_node;
        register Node *rp_node = p_node;
        for (register int i = 0; i < p_list->length; i++) if (p_fn_node[i] == rp_node) return i;
    }
#endif
    register Node *t_node = p_list->head;
    register unsigned long long index = 0;
    while (t_node != NULL) {
//        id模块可能启用的时候则编译以下代码
#ifdef id_enable
        if (p_node->s_id == t_node->s_id) return index;
#endif
        index++;
        t_node = t_node->next;
    }
	return 0;
}
