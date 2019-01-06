#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>


/**
 顺序遍历链表的操作函数，不对用户开放。回调函数返回-1退出遍历，返回1继续向后遍历，返回其他值则暂停向下遍历。
 回调函数接受一个整数、一个指向节点内容的指针、一个而外的参数链表，且回调函数需要返回一个链表，链表的第一个值作为函数的实际返回值。
 @param p_list 指向目标链表的指针
 @param p_func 指向回调函数的指针
 @return 返回参数链表
 */
List *listThrough(List *p_list, List *(*p_func)(uint32_t, void *, List *), List *expand_resources) {
    Node *p_node = p_list->head;
    List *m_rtnlst = NULL;
    uint64_t index = 0;
    insertInTail(expand_resources, nodeWithULLInt(index, 0));
    insertInTail(expand_resources, nodeWithULLInt(p_list->length, 0));
    while (p_node != NULL) {
        if (p_node->value != NULL) {
            m_rtnlst = (*p_func)(p_node->type, p_node->value, expand_resources);
            int status = getByIntForNode(findByIndexForNode(m_rtnlst, 0));
            if (status == -1) break;
            else if (status == 1) {
                p_node = p_node->last;
                releaseList(m_rtnlst);
                m_rtnlst = NULL;
                continue;
            }
            else {
                releaseList(m_rtnlst);
                m_rtnlst = NULL;
            }
        }
        lupdull(expand_resources,expand_resources->length-2,++index);
        p_node = p_node->next;
    }
    releaseList(expand_resources);
    if(m_rtnlst != NULL) releaseNode(popFromHead(m_rtnlst));
    return m_rtnlst;
}

unsigned long long getInfoForListThrough(List *expand_resources, int type){
    Node *p_node = NULL;
    if (type == 0) {
        p_node = findByIndexForNode(expand_resources, expand_resources->length-1);
    }else{
        p_node = findByIndexForNode(expand_resources, expand_resources->length-2);
    }
    return *((unsigned long long *)p_node->value);
}

int getByIntForNode(Node *p_node) {
    if (p_node->type == INT) return *(int *)(p_node->value);
    else return -1;
}

unsigned int getByUIntForNode(Node *p_node){
    if (p_node->type == UINT) return *(unsigned int *)(p_node->value);
    else return -1;
}

List *newReturn(int if_status ,int status, char *argc, ...){
    List *p_list = initList(0);
    if(if_status){
        lisrti(p_list, status);
    }
    if(status != 0){
        va_list args;
        va_start(args, argc);
        char p_ch = argc[0];
        char t_ch[256];
        int count = 0, t_count = 0;
        while(p_ch != '\0'){
            if(p_ch == '%'){
                switch (argc[count + 1]) {
                    case 'd':
                        lisrti(p_list, va_arg(args, int));
                        break;
                    case 's':
                        t_count = 0;
                        while ((t_ch[t_count] = va_arg(args, int)) != '\0') t_count++;
                        t_ch[t_count] = '\0';
                        lisrts(p_list, t_ch);
                        break;
                    case 'f':
                        lisrtd(p_list, va_arg(args, double));
                        break;
                    case 'p':
                        lisrtp(p_list, va_arg(args, void *));
                        break;
                    case 'u':
                        if(argc[count + 2] == 'l'){
                            if(argc[count + 3] == 'l'){
                                lisrtull(p_list, va_arg(args, unsigned long long));
                                count += 2;
                            }
                            else{
                                count++;
                            }
                        }
                        else{
                            lisrtu(p_list, va_arg(args, unsigned int));
                        }
                        break;
                    default:
                        break;
                }
                count++;
            }
            p_ch = argc[++count];
        }
        va_end(args);
    }
    return p_list;
}

List *newCReturn(void){
    return newReturn(1, 0, NULL);
}
