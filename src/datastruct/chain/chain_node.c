#include <type.h>
#include <chain/chain.h>


/**
 直接使用一个整型值初始化一个新的节点

 @param m_int 整型值
 @param if_sid 新的节点有无id
 @return 返回指向新节点的指针
 */
Node *nodeWithInt(int m_int, _Bool if_sid) {
    Node *p_node;
    int *p_int = (int *)malloc(sizeof(int));
    if(p_int == NULL){
        return NULL;
    }
    *p_int = m_int;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, INT, (void *)p_int);
    return p_node;
}


/**
 直接使用一个无符号整型值初始化一个新的节点

 @param m_uint 无符号整型值
 @param if_sid 新的节点有无id
 @return 返回指向新节点的指针
 */
Node *nodeWithUInt(uint32_t m_uint, _Bool if_sid){
    Node *p_node;
    unsigned int *pu_int = (uint32_t *)malloc(sizeof(uint32_t));
    if(pu_int == NULL){
        return NULL;
    }
    *pu_int = m_uint;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, UINT, (void *)pu_int);
    return p_node;
}


/**
 直接使用一个无符号长整型值（占用8个字节）初始化一个新的节点

 @param m_ullint 无符号长整型值
 @param if_sid 新的节点有无id
 @return 返回指向新节点的指针
 */
Node *nodeWithULLInt(uint64_t m_ullint, _Bool if_sid) {
    Node *p_node;
    unsigned long long *p_ullint = (uint64_t *)malloc(sizeof(uint64_t));
    if(p_ullint == NULL){
        return NULL;
    }
    *p_ullint = m_ullint;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, ULLINT, (void *)p_ullint);
    return p_node;
}


/**
 直接使用一个双精度浮点值初始化一个新的节点

 @param m_double 双精度浮点值
 @param if_sid 新的节点有无id
 @return 返回指向新节点的指针
 */
Node *nodeWithDouble(double m_double, _Bool if_sid) {
    Node *p_node;
    double *p_double = (double *)malloc(sizeof(double));
    if(p_double == NULL){
        return NULL;
    }
    *p_double = m_double;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, DOUBLE, (void *)p_double);
    return p_node;
}


/**
 直接使用一个字符串值初始化一个新的节点

 @param m_string 字符串值
 @param if_sid 新的节点有无id
 @return 返回指向新节点的指针
 */
Node *nodeWithString(const char *m_string, _Bool if_sid) {
    Node *p_node;
    char *p_string = (char *)malloc(sizeof(char)*(strlen(m_string) + 1));
    if(p_string == NULL){
        return NULL;
    }
    strcpy(p_string, m_string);
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, STRING, (void *)p_string);
    return p_node;
}


/**
 直接使用一个指针值初始化一个新的节点

 @param m_pointer 指针值
 @param if_sid 新的节点有无id
 @return 返回指向新节点的指针
 */
Node *nodeWithPointer(const void *m_pointer, _Bool if_sid) {
    Node *p_node = initNode(if_sid);
    initMallocValueForNode(p_node, POINTER, m_pointer);
    return p_node;
}

