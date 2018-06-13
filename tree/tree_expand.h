#ifndef TREE_EXPAND_H
#define TREE_EXPAND_H

#include "tree.h"

TNode *tnodeWithInt(int);
TNode *tnodeWithDouble(double);
TNode *tnodeWithString(char *);
TNode *tnodeWithPointer(void *);

int getValueByIntForTree(TNode *);
double getValueByDoubleForTree(TNode *);
char *getValueByStringForTree(TNode *);
void *getValueByPointerForTree(TNode *);

int printTree(Tree *p_tree);
int printTNodeWithHome(TNode *p_tnode, int priority);
int printTNodeWithFamily(TNode *p_tnode, int priority);
int printTNode(TNode *p_tnode, int priority);

#endif
