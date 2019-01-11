#include <type.h>
#include <chain/chain.h>

/*
 *内部函数: 通过节点中的值查找相关多个节点.
 *参数: type指明相关值的类型;value为指向储存相关值的内存的指针.
 *返回: 如果成功返回0,如果失败则返回-1.*/
static int sortList(Chain *p_list, uint64_t begin, uint64_t end, int(*func)(CNode *f_node, CNode *s_node));

/**
 链表排序函数，该函数不直接对用户开放。采用快速排序的算法。

 @param p_list 指向需要操作的链表的指针
 @param begin 开始的节点的序号
 @param end 结束的节点的序号
 @param func 指向判断条件的函数的函数指针，接受两个指向相关节点的指针，比较他们的大小并返回正负值。
 @return 成功进行操作则返回0
 */
static int sortList(Chain *p_list, uint64_t begin, uint64_t end, int(*func)(CNode *f_node, CNode *s_node)){
    unsigned long long target_index = begin;
    register CNode *t_node = findByIndexForNode(p_list, target_index);
    register CNode *i_node = NULL, *j_node = NULL;
    
    register unsigned long long i = end,j = begin;
    for(; i >= begin; i--){
        if(i <= j) break;
        i_node = findByIndexForNode(p_list, i);
        if(func(t_node, i_node) < 0){
            exchangeNode(p_list, t_node, i_node);
            for(; j <= end; j++){
                if(j >= i) break;
                j_node = findByIndexForNode(p_list, j);
                if(func(t_node, j_node) > 0){
                    exchangeNode(p_list, t_node, j_node);
                    break;
                }
            }
        }
    }
    if(end - begin > 3){
        if(getIndexForNode(p_list, t_node) - begin > 2)
            sortList(p_list, begin, getIndexForNode(p_list, t_node), func);
        if(end - getIndexForNode(p_list, t_node) > 2)
            sortList(p_list, getIndexForNode(p_list, t_node), end, func);
    }
    return 0;
}



/**
 向用户开放的链表排序函数

 @param p_list 指向需要操作的链表
 @param func 指向判断条件的函数的函数指针，接受两个指向相关节点的指针，比较他们的大小并返回正负值。
 @return 成功进行操作则返回0
 */
int sortListForCustom(Chain *p_list, int(*func)(CNode *f_node, CNode *s_node)){
    sortList(p_list, 0, p_list->length-1, func);
    return 0;
}
