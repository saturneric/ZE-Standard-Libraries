//
//  stack.c
//  ZE-Standard-Libraries
//
//  Created by 胡一兵 on 2018/6/11.
//  Copyright © 2018年 ZE. All rights reserved.
//

#include "stack_expand.h"

int main(int argc, char **argv){
    Stack *t_stack = initStack();
    for(int i = 0; i < 10; i++){
        pushStack(t_stack, snodeWithInt(i));
    }
    for(int i = 0; i < 10; i++){
        printf("%d",getValueByIntForSNode(popStack(t_stack)));
    }
    releaseStack(t_stack);
    return 0;
}
