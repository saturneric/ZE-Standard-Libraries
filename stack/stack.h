#include <stdlib.h>

#ifndef STACK_H
#define STACK_H
#include "../list/list_expand.h"

typedef struct stack_node{
    SID *s_id;
    _Bool if_malloc;
    _Bool if_sid;
    unsigned int type;
    void *value;
    struct stack_node *next;
} SNode;

typedef struct stack{
    SID *s_id;
    unsigned long long length;
    SNode *top;
    _Bool if_sid;
} Stack;

Stack *initStack(void);
SNode *initSNode(void);
int initMallocValueForSNode(SNode *p_snode, unsigned int type, void *value);

SNode *popStack(Stack *p_stack);
int pushStack(Stack *p_stack, SNode *p_snode);

int releaseStack(Stack *p_stack);
int releaseSNode(SNode *p_snode);

#endif /* stack_h */
