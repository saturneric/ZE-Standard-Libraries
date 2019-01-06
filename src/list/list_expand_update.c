#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>


/**
 用一个整型值更新一个现有节点的值

 @param p_node 指向目标节点的指针
 @param value 整型值
 @return 操作成功则返回0
 */
int updateValueWithIntForNode(Node *p_node,int value){
    int *p_value = (int *)malloc(sizeof(int));
    if(p_value == NULL){
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}


/**
 用一个无符号长整型（8个字节）更新一个现有节点的值

 @param p_node 指向目标节点的指针
 @param value 无符号长整型值
 @return 操作成功则返回0
 */
int updateValueWithULLIntForNode(Node *p_node, uint64_t value){
    uint64_t *p_value = (uint64_t *)malloc(sizeof(uint64_t));
    if(p_value == NULL){
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}


/**
 用一个双精度浮点值更新一个现有节点的值

 @param p_node 指向目标节点的指针
 @param value 双精度浮点值
 @return 操作成功则返回0
 */
int updateValueWithDoubleForNode(Node *p_node, double value){
    double *p_value = (double *)malloc(sizeof(double));
    if(p_value == NULL){
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}


/**
 用一个字符串值更新一个现有节点的值

 @param p_node 指向目标节点的指针
 @param string 字符串值
 @return 操作成功则返回0
 */
int updateValueWithStringForNode(Node *p_node, char *string){
    char *p_value = (char *)malloc(sizeof(strlen(string)) + 1);
    if(p_value == NULL){
        return -1;
    }
    strcpy(p_value, string);
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}


/**
 用一个指针值更新一个现有节点的值

 @param p_node 指向目标节点的指针
 @param pointer 指针值
 @return 操作成功则返回0
 */
int updateValueWithPointerForNode(Node *p_node, void *pointer){
    free(p_node->value);
    p_node->value = pointer;
    return 0;
}
