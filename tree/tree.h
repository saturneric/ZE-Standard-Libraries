#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include "../list/list_expand.h"

typedef struct tree_node
{
	unsigned long long id;
	List *home;
	struct tree_node *father;
	Node *room;
	unsigned long long child_num;
	int type;
	void *value;
	int if_malloc;
}TNode;

typedef struct tree
{
	unsigned long long id;
	TNode *root;
}Tree;


int safeModeForTree(int ifon);
int releaseAllForTree(void);

TNode *initTNode(void);
Tree *initTree(void);
int *initMallocValueForTNode(TNode *p_tnode, int type, void *value);

int addChildInLeft(TNode *f_tnode, TNode *c_tnode);
int addChildInRight(TNode *f_tnode, TNode *c_tnode);
TNode *getBrotherInLeft(TNode *p_tnode);
TNode *getBrotherInRight(TNode *p_node);
int removeChildInLeft(TNode *p_tnode);
int removeChildInRight(TNode *p_tnode);
TNode *getChildById(TNode *p_tnode, unsigned long long id);
TNode *getChildByValue(TNode *p_tnode, int type, void *value);
TNode *getChildByIndex(TNode *p_tnode, unsigned long long index);
unsigned long long getIndexByChild(TNode *f_tnode, TNode *c_tnode);
int removeChildById(TNode *p_tnode, unsigned long long id);
int removeChildByIndex(TNode *p_tnode, unsigned long long index);
int removeChildByValue(TNode *p_tnode, int type, void *value);
int TreeThroughDown(Tree *p_tree, int(*func)(TNode *, unsigned long long height));
int TreeThroughUp(Tree *p_tree, int(*func)(TNode *, unsigned long long height));
int TreeTravel(Tree *p_tree, int(*func)(TNode *, unsigned long long height));

int _dogetChildById(int type, void *value);
int _dogetChildByValue(int type, void *value);
int _doreleaseTree(TNode *p_tnode, unsigned long long height);
int _doTreeThroughDown(TNode *p_tnode, int height, int(*func)(TNode *, unsigned long long height));
int _doTreeThroughUp(TNode *p_tnode, int height, int(*func)(TNode *, unsigned long long height));

int releaseTree(Tree *p_tree);
int releaseOnlyTree(Tree *p_tree);
int releaseTNode(TNode *p_tnode);
int releaseOnlyTNode(TNode *p_tnode);

int setRoot(Tree *p_tree, TNode *p_tnode);

static int target_type;
static void *target_value;
static TNode *target_value_value;

static unsigned long long target_id;
static TNode *target_value_id;

static List *tree_list;
static List *tnode_list;
static int if_safeModeForTree;


#endif
