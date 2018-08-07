#ifndef STACK_EXPAND_H
#define STACK_EXPAND_H

#include "stack.h"

SNode *snodeWithInt(int);
SNode *snodeWithDouble(double);
SNode *snodeWithString(char *);
SNode *snodeWithPointer(void *);

int getValueByIntForSNode(SNode *);
double getValueByDoubleForSNode(SNode *);
char *getValueByStringForSNode(SNode *);
void *getValueByPointerForSNode(SNode *);

#endif /* stack_expand_h */
