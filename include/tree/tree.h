#ifndef TREE_H
#define TREE_H

#include <list/list_type.h>

/*
 *超级树节点的管理及操作的结构
 */
typedef struct tree_node
{
    SID *s_id;//超级树节点的ID
    List *home;//超级树节点的子节点列表
    struct tree_node *father;//超级树节点的父节点
    Node *room;//超级树节点的父节点的子节点列表
    unsigned long long child_num;//超级树节点的子节点数量
    unsigned int type;//超级树节点的类型
    void *value;//值指针
}TNode;

/*
 *二叉树节点的管理及操作的结构
 */
typedef  struct simple_tree_node{
    void *value;//值指针
    struct simple_tree_node *childs[2];//子节点
}s_TNode;

/*
 *树的管理及操作的结构
 */
typedef struct tree
{
    SID *s_id;//超级树的SID
    TNode *root;//超级树根节点
    s_TNode *s_root;//二叉树的根节点
}Tree;

int safeModeForTree(int ifon);
int releaseAllForTree(void);

TNode *initTNode(void);
Tree *initTree(void);
int *initMallocValueForTNode(TNode *p_tnode, unsigned int type, void *value);

int addChildInLeft(TNode *f_tnode, TNode *c_tnode);
int addChildInRight(TNode *f_tnode, TNode *c_tnode);
TNode *getBrotherInLeft(TNode *p_tnode);
TNode *getBrotherInRight(TNode *p_node);
int removeChildInLeft(TNode *p_tnode);
int removeChildInRight(TNode *p_tnode);
TNode *getChildById(TNode *p_tnode, const SID *s_id);
TNode *getChildByValue(TNode *p_tnode, unsigned int type, void *value);
TNode *getChildByIndex(TNode *p_tnode, unsigned long long index);
unsigned long long getIndexByChild(TNode *f_tnode, TNode *c_tnode);
int removeChildById(TNode *p_tnode, const SID *s_id);
int removeChildByIndex(TNode *p_tnode, unsigned long long index);
int removeChildByValue(TNode *p_tnode, unsigned int type, void *value);
int TreeThroughDown(Tree *p_tree, int(*func)(TNode *, unsigned long long height));
int TreeThroughUp(Tree *p_tree, int(*func)(TNode *, unsigned long long height));
int TreeTravel(Tree *p_tree, int(*func)(TNode *, unsigned long long height));

List *_dogetChildById(unsigned int type, void *value, List *er_list);
List *_dogetChildByValue(unsigned int type, void *value, List *er_list);
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

static SID *target_sid;
static TNode *target_value_sid;

static List *tree_list;
static List *tnode_list;
static int if_safeModeForTree;


#endif
