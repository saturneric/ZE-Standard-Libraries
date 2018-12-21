#include <type.h>
#include <stack/stack.h>

Stack *initStack(void) {
    Stack *p_stack = (Stack *)malloc(sizeof(Stack));
#ifdef id_enable
    p_stack->s_id = getS_id(STACK, 1);
#endif
    p_stack->length = 0;
    p_stack->top = NULL;
    return p_stack;
}

SNode *initSNode(void) {
    SNode *p_snode = (SNode *)malloc(sizeof(SNode));
#ifdef id_enable
    p_snode->s_id = getS_id(STACK_NODE, 1);
#endif
    p_snode->next = NULL;
    p_snode->value = NULL;
    return p_snode;
}

SNode *popStack(Stack *p_stack) {
    if (p_stack->top != NULL) {
        SNode *p_snode = p_stack->top;
        p_stack->top = p_snode->next;
        p_snode->next = NULL;
        p_stack->length -= 1;
        return p_snode;
    }
    else return NULL;
}

int pushStack(Stack *p_stack, SNode *p_snode) {
    SNode *pn_snode = p_stack->top;
    p_stack->top = p_snode;
    p_snode->next = pn_snode;
    p_stack->length -= 1;
    return 0;
}

int releaseStack(Stack *p_stack) {
    SNode *p_sndoe = p_stack->top;
    while (p_sndoe != NULL) {
        SNode *pl_snode = p_sndoe;
        p_sndoe = p_sndoe->next;
        releaseSNode(pl_snode);
    }
#ifdef id_enable
    freeS_id(p_stack->s_id);
#endif
    p_stack->top = NULL;
    p_stack->length = 0;
    free(p_stack);
    return 0;
}

int releaseSNode(SNode *p_snode) {
#ifdef id_enable
    freeS_id(p_snode->s_id);
#endif
    free(p_snode->value);
    p_snode->value = NULL;
    p_snode->type = VOID;
    free(p_snode);
    return 0;
}

int initMallocValueForSNode(SNode *p_snode, unsigned int type, void *value) {
    p_snode->type = type;
    p_snode->value = value;
    return  0;
}
