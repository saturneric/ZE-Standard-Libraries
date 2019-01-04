#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>
//长链表模式可能启用则包含以下头文件
#ifdef list_quick_enable
#include <list/list_quick.h>
#endif


/**
 通过节点中储存的整型值来找到链表中第一个符合条件的节点

 @param p_list 指向目标链表的指针
 @param target 目标节点中储存的整型值
 @return 返回指向目标节点的指针
 */
Node *findByIntForNode(List *p_list, int target) {
    Node *t_node;
    int *p_target = (int *)malloc(sizeof(int));
    *p_target = target;
    t_node = findByValue(p_list, INT, p_target);
    free(p_target);
    return t_node;
}

/**
 通过节点中储存的双精度浮点值来找到链表中第一个符合条件的节点

 @param p_list 指向目标链表的指针
 @param target 目标节点中储存的双精度浮点值
 @return 返回指向目标节点的指针
 */
Node *findByDoubleForNode(List *p_list, double target) {
    Node *t_node;
    double *p_target = (double *)malloc(sizeof(double));
    *p_target = target;
    t_node = findByValue(p_list, DOUBLE, p_target);
    free(p_target);
    return t_node;
}

/**
 通过节点中储存的字符串值来找到链表中第一个符合条件的节点

 @param p_list 指向目标链表的指针
 @param target 目标节点中储存的字符数组值
 @return 返回指向目标节点的指针
 */
Node *findByStringForNode(List *p_list, char *target) {
    Node *t_node;
    char *p_temp = (char *)malloc(sizeof(char)*(strlen(target) + 1));
    strcpy(p_temp, target);
    t_node = findByValue(p_list, STRING, p_temp);
    free(p_temp);
    return t_node;
}


/**
 通过节点中储存的指针值来找到链表中第一个符合条件的节点

 @param p_list 指向目标链表的指针
 @param target 目标节点中储存的字符指针值
 @return 返回指向目标节点的指针
 */
Node *findByPointerForNode(List *p_list, void *target) {
    Node *t_node = findByValue(p_list, POINTER, target);
    return t_node;
}


/**
 通过节点中储存的整型值来找到链表中所有符合条件的节点

 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的整型值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
List *mply_findByInt(List* p_list, int temp) {
    int *p_temp = (int *)malloc(sizeof(int));
    if(p_temp == NULL){
        return NULL;
    }
    List *t_list;
    *p_temp = temp;
    t_list = mply_findByValue(p_list, INT, (void *)p_temp);
    free(p_temp);
    return t_list;
}

/**
 通过节点中储存的双精度浮点值来找到链表中所有符合条件的节点

 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的双精度浮点值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
List *mply_findByDouble(List* p_list, double temp) {
    List *t_list;
    double *p_temp = (double *)malloc(sizeof(double));
    if(p_temp == NULL){
        return NULL;
    }
    *p_temp = temp;
    t_list = mply_findByValue(p_list, DOUBLE, (void *)p_temp);
    free(p_temp);
    return t_list;
}

/**
 通过节点中储存的字符串值来找到链表中所有符合条件的节点

 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的字符串值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
List *mply_findByString(List* p_list, char *temp) {
    List *t_list;
    char *p_temp = (char *)malloc(sizeof(char)*(strlen(temp) + 1));
    if(p_temp == NULL){
        return NULL;
    }
    strcpy(p_temp, temp);
    t_list = mply_findByValue(p_list, STRING, (void *)p_temp);
    free(p_temp);
    return t_list;
}


/**
 通过节点中储存的指针值来找到链表中所有符合条件的节点

 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的指针值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
List *mply_findByPointer(List* p_list, void *temp) {
    List *t_list = mply_findByValue(p_list, DOUBLE, (void *)temp);
    return t_list;
}


/**
 通过节点中储存的整型值来找到链表中所有符合条件的节点
 
 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的整型值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
inline List *mply_findByIntForNode(List* p_list, int temp) {
    return mply_findByInt(p_list, temp);
}

/**
 通过节点中储存的双精度浮点值来找到链表中所有符合条件的节点
 
 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的双精度浮点值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
inline List *mply_findByDoubleForNode(List* p_list, double temp) {
    return mply_findByDouble(p_list, temp);
}

/**
 通过节点中储存的字符串值来找到链表中所有符合条件的节点
 
 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的字符串值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
inline List *mply_findByStringForNode(List* p_list, char *temp) {
    return mply_findByString(p_list, temp);
}

/**
 通过节点中储存的指针值来找到链表中所有符合条件的节点
 
 @param p_list 指向目标链表的指针
 @param temp 目标节点中储存的指针值
 @return 返回包含所有符合条件的节点的新的重组链表
 */
inline List *mply_findByPointerForNode(List* p_list, void *temp) {
    return mply_findByPointer(p_list, temp);
}


/**
 通过节点在链表中的序号位置来找到符合条件的节点

 @param p_list 指向目标链表的指针
 @param m_index 序号位置
 @return 返回指向符合条件的链表的指针
 */
Node *findByIndexForNode(List *p_list, unsigned long long m_index) {
    if(p_list == NULL) return NULL;
//当长链表模式可能启用时编译以下语句
#ifdef list_quick_enable
    if(p_list->p_lq != NULL){
        register struct list_quick *p_lq = p_list->p_lq;
        if(p_lq->fn_node != NULL) return getNodeByFnNode(p_list, m_index);
    }
#endif
    Node *p_node = p_list->head;
    unsigned long long i;
    for (i = 0; i < m_index; i++) {
        p_node = p_node->next;
    }
    return p_node;
}
