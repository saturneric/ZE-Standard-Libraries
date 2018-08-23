#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>

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

Node *nodeWithUInt(unsigned int m_uint, _Bool if_sid){
    Node *p_node;
    unsigned int *pu_int = (unsigned int *)malloc(sizeof(unsigned int));
    if(pu_int == NULL){
        return NULL;
    }
    *pu_int = m_uint;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, INT, (void *)pu_int);
    return p_node;
}

Node *nodeWithULLInt(unsigned long long m_ullint, _Bool if_sid) {
    Node *p_node;
    unsigned long long *p_ullint = (unsigned long long *)malloc(sizeof(unsigned long long));
    if(p_ullint == NULL){
        return NULL;
    }
    *p_ullint = m_ullint;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, ULLINT, (void *)p_ullint);
    return p_node;
}

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

Node *nodeWithPointer(const void *m_pointer, _Bool if_sid) {
    Node *p_node = initNode(if_sid);
    initMallocValueForNode(p_node, POINTER, m_pointer);
    return p_node;
}

