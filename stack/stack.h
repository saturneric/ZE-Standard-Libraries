#ifndef STACK_H
#define STACK_H
#include "../type/type.h"
#include "../list/list_expand.h"

Stack *initStack(void);
SNode *initSNode(void);
int initMallocValueForSNode(SNode *p_snode, unsigned int type, void *value);

SNode *popStack(Stack *p_stack);
int pushStack(Stack *p_stack, SNode *p_snode);

int releaseStack(Stack *p_stack);
int releaseSNode(SNode *p_snode);

#endif /* stack_h */
