#include "stack.h"

Stack *initStack(void) {
    Stack *p_stack = (Stack *)malloc(sizeof(Stack));
    if(p_stack == NULL){
        showError(pushError(STACK, STANDARD, initInfo("initStack()", "Error in getting the memory of stack.")));
        return NULL;
    }
    p_stack->s_id = getS_id(STACK, 1);
    p_stack->length = 0;
    p_stack->top = NULL;
    return p_stack;
}

SNode *initSNode(void) {
    SNode *p_snode = (SNode *)malloc(sizeof(SNode));
    if(p_snode == NULL){
        showError(pushError(STACK_NODE, STANDARD, initInfo("initSNode()", "Error in getting the memory of snode.")));
        return NULL;
    }
    p_snode->s_id = getS_id(STACK_NODE, 2);
    p_snode->if_malloc = 0;
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
    freeS_id(p_stack->s_id);
    p_stack->top = NULL;
    p_stack->length = 0;
    free(p_stack);
    return 0;
}

int releaseSNode(SNode *p_snode) {
    freeS_id(p_snode->s_id);
    free(p_snode->value);
    p_snode->if_malloc = 0;
    p_snode->value = NULL;
    p_snode->type = VOID;
    free(p_snode);
    return 0;
}

int initMallocValueForSNode(SNode *p_snode, unsigned int type, void *value) {
    p_snode->if_malloc = 1;
    p_snode->type = type;
    p_snode->value = value;
    return  0;
}
