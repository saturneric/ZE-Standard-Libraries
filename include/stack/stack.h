#ifndef stack_h
#define stack_h

#include <stack/stack_type.h>

extern Stack *initStack(void);
extern SNode *initSNode(void);

extern int initMallocValueForSNode(SNode *p_snode, unsigned int type, void *value);

extern SNode *popStack(Stack *p_stack);

extern int pushStack(Stack *p_stack, SNode *p_snode);

extern int releaseStack(Stack *p_stack);

extern int releaseSNode(SNode *p_snode);

#endif /* stack_h */
