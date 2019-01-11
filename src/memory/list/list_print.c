#include <type.h>
#include <list/list.h>
#include <list/list_print.h>

#ifdef id_enable
#include <id/id.h>
#endif

/**
 打印链表及链表中节点的相关数据

 @param p_list 指向目标链表的指针
 @param priority 行缩进次数
 */
void printListInfo(List *p_list, int priority) {
    int i = 0;
    Node *p_node;
    for (i = 0; i < priority; i++) printf("   ");
    printf("###LIST(location:%p",p_list);
//    如果可能使用到ID模块则编译以下代码
#ifdef id_enable
    printf(",id:%s",s_idToASCIIString(p_list->s_id));
#endif
    printf("){\n");
    for (i = 0; i < priority + 1; i++) printf("   ");
    printf("HEAD->%p / Tail->%p / Length:%llu\n", p_list->head, p_list->tail, p_list->length);
    p_node = p_list->head;
    while (p_node != NULL) {
        for (i = 0; i < priority + 1; i++) printf("   ");
        printf("%d.... \n", i);
        printNodeInfo(p_node, priority + 1);
        p_node = p_node->next;
        i++;
    }
    for (i = 0; i < priority; i++) printf("   ");
    printf("}\n");
    
}


/**
 打印链表及其节点写详细信息

 @param p_list 指向目标链表的指针
 */
void printList(List *p_list) {
    int if_nearLast = 0;
    Node *p_node = p_list->head;
    printf("[");
    while (p_node != NULL) {
        if (!if_nearLast && p_node->next == NULL) if_nearLast = 1;
        if (p_node->type == INT) {
            printf("%d", *(int *)(p_node->value));
        }
        else if (p_node->type == DOUBLE) {
            printf("%a", *(double *)(p_node->value));
        }
        else if (p_node->type == STRING) {
            printf("%s", (char *)(p_node->value));
        }
        else if (p_node->type == POINTER) {
            printf("%p", (char *)(p_node->value));
        }
        else if (p_node->type == LIST) {
            printList((List *)p_node->value);
        }
        if (!if_nearLast) {
            printf(", ");
        }
        p_node = p_node->next;
    }
    printf("]");
}


/**
 打印节点的信息

 @param p_node 指向目标节点的指针
 @param priority 行缩进次数
 */
void printNodeInfo(Node *p_node, int priority) {
    int i;
    for (i = 0; i < priority; i++) printf("   ");
    printf("#NODE(location:%p",p_node);
#ifdef id_enable
    printf(", id:%s", s_idToASCIIString(p_node->s_id));
#endif
    printf("){\n");
    for (i = 0; i < priority + 1; i++) printf("   ");
    printf("NEXT->%p / LAST->%p\n", p_node->next, p_node->last);
    if (p_node->type == INT) {
        for (i = 0; i < priority + 1; i++) printf("   ");
        printf("VALUE(int):%d\n", *(int *)(p_node->value));
    }
    else if (p_node->type == DOUBLE) {
        for (i = 0; i < priority + 1; i++) printf("   ");
        printf("VALUE(double):%a\n", *(double *)(p_node->value));
    }
    else if (p_node->type == STRING) {
        for (i = 0; i < priority + 1; i++) printf("   ");
        printf("VALUE(string):%s\n", (char *)(p_node->value));
    }
    else if (p_node->type == POINTER) {
        for (i = 0; i < priority + 1; i++) printf("   ");
        printf("VALUE(pointer):%s\n", (char *)(p_node->value));
    }
    else if (p_node->type == LIST) {
        for (i = 0; i < priority + 1; i++) printf("   ");
        printf("VALUE(List):\n");
        printListInfo((List *)p_node->value, priority + 2);
    }
    for (i = 0; i < priority; i++) printf("   ");
    printf("}\n");
}

/**
 打印节点的详细信息

 @param p_node 指向目标节点的指针
 */
void printNode(Node *p_node) {
    int i;
    printf("#NODE(location:%p",p_node);
#ifdef id_enable
    printf(", id:%s",s_idToASCIIString(p_node->s_id));
#endif
    printf("){\n");
    printf("   ");
    printf("NEXT->%p / LAST->%p\n", p_node->next, p_node->last);
    for (i = 0; i < 1; i++) printf("   ");
    printf("ifMalloc: ");
    if (p_node->value != NULL) {
        printf("YES\n");
        for (i = 0; i < 1; i++) printf("   ");
        printf("Value(type: %d): ", p_node->type);
        if (p_node->type == INT) {
            printf("%d", *(int *)(p_node->value));
        }
        else if (p_node->type == DOUBLE) {
            printf("%a\n", *(double *)(p_node->value));
        }
        else if (p_node->type == STRING) {
            printf("%s\n", (char *)(p_node->value));
        }
        else if (p_node->type == POINTER) {
            printf("%p\n", (char *)(p_node->value));
        }
        else if (p_node->type == LIST) {
            printList((List *)p_node->value);
        }
    }
    else printf("NO\n");
    
    printf("}\n");
}


/**
 遍历链表并自定义打印节点信息

 @param p_list 指向目标链表的指针
 @param func 指向自定义打印函数的指针，函数接受指向目标节点的指针
 */
void printListForCustom(List *p_list,void (*func)(void *value)){
    printf("###LIST (LEN:%llu ",p_list->length);
#ifdef id_enable
    if(p_list->s_id != NULL) printf("SID:%s",p_list->s_id->decrypt_str);
#endif
    printf(")\n");
    listThrough(p_list, __CALLBACK_CALL(printListForCustom), __SEND_ARG("%p", func));
}


__CALLBACK_DEFINE(printListForCustom){
    void (*func)(void *) = __ARGS_P(0, void);
    printf("NODE (IDX:%llu ",__NOW_INDEX);
    printf(")\n");
    func(__VALUE(void *));
    printf("\n");
    return __CRETURN__;
}
