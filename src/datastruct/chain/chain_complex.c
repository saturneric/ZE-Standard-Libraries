#include <type.h>
#include <chain/chain.h>


/**
 创建一个新的且内容为链表的节点

 @return 返回指向新节点的指针
 */
CNode *nodeWithComplex(void) {
    CNode *p_node = initNode(0);
    p_node->type = LIST;
    p_node->value = initList(0);
    return p_node;
}


/**
 为一个内容为链表的节点中的链表中添加节点并指定内容

 @param p_node 指向该节点的指针
 @param type 内容的类型
 @param value 指向该内容所在内存的指针
 @return 操作成功则返回一个非负整数
 */
int addValueForComplex(CNode * p_node, int type, void *value) {
    List *c_list;
    CNode *c_node;
    if (p_node->type == LIST) {
        c_list = (List *)p_node->value;
        c_node = initNode(0);
        initMallocValueForNode(c_node, type, value);
        insertInTail(c_list, c_node);
        return  0;
    }
    return  -1;
}


/**
 为一个内容为链表的节点中的链表中添加整型类型的节点并初始化为相应的值

 @param p_node 指向该节点的指针
 @param temp 相应的整型值
 @return 操作成功则返回非负整数
 */
int addIntForComplex(CNode *p_node, int temp) {
    if (p_node->type == LIST) {
        int *p_temp = (int *)malloc(sizeof(int));
        if(p_temp == NULL){
            return -1;
        }
        *p_temp = temp;
        addValueForComplex(p_node, INT, p_temp);
        return 0;
    }
    return -1;
}


/**
 为一个内容为链表的节点中的链表中添加双精度浮点类型的节点并初始化为相应的值

 @param p_node 指向该节点的指针
 @param temp 相应的双精度浮点值
 @return 操作成功则返回非负整数
 */
int addDoubleForComplex(CNode *p_node, double temp) {
    if (p_node->type == LIST) {
        double *p_temp = (double *)malloc(sizeof(double));
        if(p_temp == NULL){
            return -1;
        }
        *p_temp = temp;
        addValueForComplex(p_node, DOUBLE, p_temp);
        return 0;
    }
    return -1;
}


/**
 为一个内容为链表的节点中的链表中添加字符串类型的节点并初始化为相应的值

 @param p_node 指向该节点的指针
 @param temp 相应的字符数组
 @return 操作成功则返回非负整数
 */
int addStringForComplex(CNode *p_node, char *temp) {
    if (p_node->type == LIST) {
        char *p_temp = (char *)malloc(sizeof(strlen(temp) + 1));
        if(p_temp == NULL){
            return -1;
        }
        strcpy(p_temp, temp);
        addValueForComplex(p_node, STRING, p_temp);
        return 0;
    }
    return -1;
}


/**
 为一个内容为链表的节点中的链表中添加指针类型的节点并初始化为相应的值

 @param p_node 指向该节点的指针
 @param temp 相应的指针
 @return 操作成功则返回非负整数
 */
int addPointerForComplex(CNode *p_node, void *temp) {
    if (p_node->type == LIST) {
        addValueForComplex(p_node, POINTER, temp);
        return 0;
    }
    return -1;
}
