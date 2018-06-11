//
//  stack_expand.h
//  ZE-Standard-Libraries
//
//  Created by 胡一兵 on 2018/6/11.
//  Copyright © 2018年 ZE. All rights reserved.
//

#ifndef stack_expand_h
#define stack_expand_h

#include "stack.h"

SNode *snodeWithInt(int);
SNode *snodeWithDouble(double);
SNode *snodeWithString(char *);
SNode *snodeWithPointer(void *);

int getValueByIntForSNode(SNode *);
double getValueByDoubleForSNode(SNode *);
char *getValueByStringForSNode(SNode *);
void *getValueByPointerForSNode(SNode *);

SNode *snodeWithInt(int temp){
    SNode *p_snode = initSNode();
    int *p_temp = (int *)malloc(sizeof(int));
    *p_temp = temp;
    initMallocValueForSNode(p_snode, "int", p_temp);
    return p_snode;
}

SNode *snodeWithDouble(double temp){
    SNode *p_snode = initSNode();
    double *p_temp = (double *)malloc(sizeof(double));
    *p_temp = temp;
    initMallocValueForSNode(p_snode, "double", p_temp);
    return p_snode;
}

SNode *snodeWithString(char *temp){
    SNode *p_snode = initSNode();
    char *p_temp = (char *)malloc(sizeof(char)*(strlen(temp)+1));
    strcpy(p_temp, temp);
    initMallocValueForSNode(p_snode, "string", p_temp);
    return p_snode;
}

SNode *snodeWithPointer(void *temp){
    SNode *p_snode = initSNode();
    initMallocValueForSNode(p_snode, "pointer", temp);
    return p_snode;
}

int getValueByIntForSNode(SNode *p_snode){
    if(!strcmp(p_snode->type, "int")) return *(int *)p_snode->value;
    else return  -1;
}

double getValueByDoubleForSNode(SNode *p_snode){
    if(!strcmp(p_snode->type, "double")) return *(double *)p_snode->value;
    else return  -1;
}

char *getValueByStringForSNode(SNode *p_snode){
    if(!strcmp(p_snode->type, "int")) return (char *)p_snode->value;
    else return  NULL;
}

void *getValueByPointerForSNode(SNode *p_snode){
    if(!strcmp(p_snode->type, "int")) return (void *)p_snode->value;
    else return  NULL;
}

#endif /* stack_expand_h */
