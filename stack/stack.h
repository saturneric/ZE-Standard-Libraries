//
//  stack.h
//  ZE-Standard-Libraries
//
//  Created by 胡一兵 on 2018/6/11.
//  Copyright © 2018年 ZE. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include "list.h"

typedef struct stack_node{
    unsigned long long id;
    int if_malloc;
    void *value;
    struct stack_node *next;
} SNode;

typedef struct stack{
    unsigned long long id;
    unsigned long long length;
    SNode *top;
} Stack;

Stack *initStack(void);
SNode *initSNode(void);

SNode *popStack(Stack *p_stack);
int pushStack(Stack *p_stack, SNode *p_snode);

int releaseStack(Stack *p_stack);
int releaseSNode(SNode *p_snode);


#endif /* stack_h */
