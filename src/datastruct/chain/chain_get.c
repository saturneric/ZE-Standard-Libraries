#include <type.h>
#include <chain/chain.h>


/**
 直接获取储存整型数据的节点的值
 
 @param p_node 指向目标节点的指针
 @return 成功则返回对应整型值，失败返回0
 */
int getByIntForNode(CNode *p_node) {
    if (p_node->type == INT) return *(int *)(p_node->value);
    else return 0;
}


/**
 直接获取储存无符号整型数据的节点的值
 
 @param p_node 指向目标节点的指针
 @return 成功则返回对应无符号整型值，失败返回0
 */
unsigned int getByUIntForNode(CNode *p_node){
    if (p_node->type == UINT) return *(uint32_t *)(p_node->value);
    else return 0;
}

/**
 直接获得节点中储存的字符串

 @param p_node 指向目标节点的指针
 @return 返回节点中储存的字符串
 */
char *getByStringForNode(CNode *p_node) {
	if (p_node->type == STRING) return (char *)(p_node->value);
	else return NULL;
}

/**
 直接获得节点中储存的双精度浮点值
 
 @param p_node 指向目标节点的指针
 @return 返回节点中储存的双精度浮点值
 */
double getByDoubleForNode(CNode *p_node) {
	if (p_node->type == DOUBLE) return *(double *)(p_node->value);
	else return -1.0;
}

/**
 直接获得节点中储存的指针值
 
 @param p_node 指向目标节点的指针
 @return 返回节点中储存的指针值
 */
void *getByPointerForNode(CNode *p_node) {
	return (void *)(p_node->value);
}


/**
 通过链表中相应的节点获得其在链表中的排列序号

 @param p_list 指向目标链表
 @param p_node 指向目标节点的指针
 @return 成功返回相应排列序号，失败则会返回0
 */
uint64_t getIndexByNode(Chain *p_list, CNode *p_node) {
    register CNode *t_node = p_list->head;
    register uint64_t index = 0;
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

/**
 通过链表中相应的节点获得其在链表中的排列序号
 
 @param p_list 指向目标链表
 @param p_node 指向目标节点的指针
 @return 成功返回相应排列序号，失败则会返回0
 */
extern uint64_t getIndexForNode(Chain *p_list,CNode *p_node){
    return getIndexByNode(p_list, p_node);
    
}
