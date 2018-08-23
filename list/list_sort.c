#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>
#ifdef list_quick_enable
#include <list/list_quick.h>
#endif

/*
 *内部函数: 通过节点中的值查找相关多个节点.
 *参数: type指明相关值的类型;value为指向储存相关值的内存的指针.
 *返回: 如果成功返回0,如果失败则返回-1.*/
static int sortList(List *p_list, unsigned long long begin, unsigned long long end, int(*func)(Node *f_node, Node *s_node));

static int sortList(List *p_list, unsigned long long begin, unsigned long long end, int(*func)(Node *f_node, Node *s_node)){
    unsigned long long target_index = begin;
    register Node *t_node = findByIndexForNode(p_list, target_index);
    register Node *i_node = NULL, *j_node = NULL;
    
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
        if(t_node->f_number - begin > 2)
            sortList(p_list, begin, t_node->f_number, func);
        if(end - t_node->f_number > 2)
            sortList(p_list, t_node->f_number, end, func);
    }
    return 0;
}

int sortListForCustom(List *p_list, int(*func)(Node *f_node, Node *s_node)){
#ifdef list_quick_enable
    if(p_list->p_lq != NULL && !p_list->p_lq->if_sort) p_list->p_lq->if_sort = 1;
#endif
    sortList(p_list, 0, p_list->length-1, func);
    return 0;
}
