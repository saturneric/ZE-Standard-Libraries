#include"tree.h"

static int if_safeModeForTree = 0;

int safeModeForTree(int ifon) {
	if (ifon == 1) {
		if (tnode_list == NULL && tree_list == NULL) {
			tnode_list = (List *)malloc(sizeof(List));
            if(tnode_list == NULL){
                showError(pushError(TREE_NODE, HIGH, initInfo("safeModeForTree()", "Error in get the memory of tnode_list.")));
                return -1;
            }
			tree_list = (List *)malloc(sizeof(List));
            if(tree_list == NULL){
                showError(pushError(TREE_NODE, HIGH, initInfo("safeModeForTree()", "Error in get the memory of tree_list.")));
                return -1;
            }
			tree_list->head = NULL;
			tree_list->length = 0;
			tree_list->tail = NULL;

			tnode_list->head = NULL;
			tnode_list->length = 0;
			tnode_list->tail = NULL;

			if_safeModeForTree = 1;
		}
		else {
			return -1;
		}
	}

	return ifon;
}

TNode *initTNode(void) {
	Node *s_node;
	TNode *p_tnode = (TNode *)malloc(sizeof(TNode));
    if(p_tnode == NULL){
        showError(pushError(TREE_NODE, STANDARD, initInfo("initTNode()", "Error in getting the memory of tnode.")));
        return NULL;
    }
    p_tnode->s_id = getS_id(TREE_NODE, 1);
    p_tnode->if_sid = 1;
	p_tnode->child_num = 0;
	p_tnode->father = NULL;
	p_tnode->if_malloc = 0;
	p_tnode->value = NULL;
	p_tnode->type = VOID;
	p_tnode->home = initList();
	p_tnode->room = NULL;
	if (if_safeModeForTree) {
		if (if_safeModeForNode) {
			if_safeModeForNode = 0;
			s_node = initNode();
			initMallocValueForNode(s_node, POINTER, (void *)p_tnode);
			insertInTail(tnode_list, s_node);
			if_safeModeForNode = 1;
		}
		else
		{
			s_node = initNode();
			initMallocValueForNode(s_node, POINTER, (void *)p_tnode);
			insertInTail(tnode_list, s_node);
		}
	}
	return p_tnode;
}

Tree *initTree(void) {
	Node *s_node;
	Tree *p_tree = (Tree *)malloc(sizeof(Tree));
    if(p_tree == NULL){
        showError(pushError(TREE, STANDARD, initInfo("initTree()", "Error in getting the memory of tree.")));
        return NULL;
    }
    p_tree->s_id = getS_id(TREE, 1);
    p_tree->if_sid = 1;
	p_tree->root = NULL;
	if (if_safeModeForTree) {
		if (if_safeModeForNode) {
			if_safeModeForNode = 0;
			s_node = initNode();
			initMallocValueForNode(s_node, POINTER, (void *)p_tree);
			if_safeModeForNode = 1;
			insertInTail(tree_list, s_node);
		}
		else
		{
			s_node = initNode();
			initMallocValueForNode(s_node, POINTER, (void *)p_tree);
			insertInTail(tree_list, s_node);
		}
	}
	return p_tree;
}

int *initMallocValueForTNode(TNode *p_tnode, unsigned int type, void *value) {
	p_tnode->type = type;
	p_tnode->value = value;
	p_tnode->if_malloc = 1;
	return 0;
}

int addChildInLeft(TNode *f_tnode, TNode *c_tnode) {
	Node *p_node = initNode();
	initMallocValueForNode(p_node, POINTER, c_tnode);
	insertInHead(f_tnode->home, p_node);
	c_tnode->father = f_tnode;
	c_tnode->room = p_node;
	f_tnode->child_num++;
	return 0;
}

int addChildInRight(TNode *f_tnode, TNode *c_tnode) {
	Node *p_node = initNode();
	initMallocValueForNode(p_node, POINTER, c_tnode);
	insertInTail(f_tnode->home, p_node);
	c_tnode->father = f_tnode;
	c_tnode->room = p_node;
	f_tnode->child_num++;
	return 0;
}

TNode *getBrotherInLeft(TNode *p_tnode) {
	List *p_home = p_tnode->father->home;
	Node *p_node = p_tnode->room;
	unsigned long long index = getIndexByNode(p_home, p_node);
	if (index > 0) return (TNode *)(findByIndexForNode(p_home, index - 1)->value);
	return NULL;
}

TNode *getBrotherInRight(TNode *p_tnode) {
	List *p_home = p_tnode->father->home;
	Node *p_node = p_home->head;
	unsigned long long index = getIndexByNode(p_home, p_node);
	if (index < p_home->length - 1) return (TNode *)(findByIndexForNode(p_home, index + 1)->value);
	return NULL;
}

int removeChildInLeft(TNode *p_tnode) {
	TNode *c_tnode = (TNode *)p_tnode->home->head->value;
	c_tnode->father = NULL;
	releaseOnlyNode(c_tnode->room);
	c_tnode->room = NULL;
	p_tnode->child_num--;
	popFromHead(p_tnode->home);
	return 0;
}

int removeChildInRight(TNode *p_tnode) {
	TNode *c_tnode = (TNode *)p_tnode->home->tail->value;
	c_tnode->father = NULL;
	releaseOnlyNode(c_tnode->room);
	c_tnode->room = NULL;
	p_tnode->child_num--;
	popFromTail(p_tnode->home);
	return 0;
}


TNode *getChildById(TNode *p_tnode, const SID *s_id) {
	List *p_home = p_tnode->home;
	target_value_sid = NULL;
    List *er_list = initList();
    insertInTail(er_list, nodeWithPointer(s_id));
	List *rtnc_list = listThrough(p_home, _dogetChildById, er_list);
    free(er_list);
    Node *p_node= findByIndexForNode(rtnc_list, 1);
	if (p_node != NULL) {
        TNode *p_tnode = getByPointerForNode(p_node);
        free(rtnc_list);
		return p_tnode;
	}
	return NULL;
}

List *_dogetChildById(unsigned int type, void *value, List *er_list) {
    SID *target_sid = getByPointerForNode(findByIndexForNode(er_list, 0));
    List *rtn_list = initList();
	if (type == POINTER) {
		TNode *p_tode = (TNode *)value;
		if (simFitS_id(p_tode->s_id, target_sid)) {
			target_value_sid = p_tode;
            insertInTail(rtn_list, nodeWithInt(-1));
            insertInTail(rtn_list, nodeWithPointer(target_value_sid));
			return rtn_list;
		}
	}
    insertInTail(rtn_list, nodeWithInt(0));
	return rtn_list;
}

TNode *getChildByValue(TNode *p_tnode, unsigned int type, void *value) {
	List *p_home = p_tnode->home;
	target_value = value;
	target_type = type;
	target_value_value = NULL;
    List *er_list = initList();
    insertInTail(er_list, nodeWithUInt(type));
    insertInTail(er_list, nodeWithPointer(value));
    List *rtnc_list = listThrough(p_home, _dogetChildByValue,er_list);
    free(er_list);
    Node *p_node = NULL;
	if ((p_node = findByIndexForNode(rtnc_list, 1)) != NULL) {
        TNode *p_tnode = getByPointerForNode(p_node);
        free(rtnc_list);
		return p_tnode;
	}
	return NULL;
}

List *_dogetChildByValue(unsigned int type, void *value, List *er_list) {
    List *rtn_list = initList();
    unsigned int target_type = getByUIntForNode(findByIndexForNode(rtn_list, 0));
    void *target_value = getByPointerForNode(findByIndexForNode(rtn_list, 1));
	if (type == target_type) {
		TNode *p_tode = (TNode *)value;
		if (target_type == INT) {
			if (*(int *)p_tode->value == *(int *)target_value)
			{
                insertInTail(rtn_list, nodeWithInt(-1));
                insertInTail(rtn_list, nodeWithPointer(p_tode));
				return rtn_list;
			}
		}
		else if (target_type == DOUBLE)
		{
			if (*(double *)p_tode->value == *(double *)target_value)
			{
                insertInTail(rtn_list, nodeWithInt(-1));
                insertInTail(rtn_list, nodeWithPointer(p_tode));
				return rtn_list;
			}
		}
		else if (target_type == STRING)
		{
			if (!strcmp((char *)p_tode->value, (char *)target_value))
			{
                insertInTail(rtn_list, nodeWithInt(-1));
                insertInTail(rtn_list, nodeWithPointer(p_tode));
				return rtn_list;
			}
		}
		else if (target_type == POINTER)
		{
			if (p_tode->value == target_value)
			{
                insertInTail(rtn_list, nodeWithInt(-1));
                insertInTail(rtn_list, nodeWithPointer(p_tode));
				return rtn_list;
			}
		}

	}
    insertInTail(rtn_list, nodeWithInt(0));
	return rtn_list;
}

int removeChildById(TNode *p_tnode, const SID *s_id) {
	TNode *t_tnode = getChildById(p_tnode, s_id);
	if (t_tnode != NULL) {
		TNode *p_fnode = t_tnode->father;
		p_fnode->child_num--;
		removeById(p_fnode->home, t_tnode->room->s_id);
		releaseOnlyNode(t_tnode->room);
		t_tnode->room = NULL;
		return 0;
	}
	return -1;
}

int removeChildByValue(TNode *p_tnode, unsigned int type, void *value) {
	TNode *t_tnode = getChildByValue(p_tnode, type, value);
	if (t_tnode != NULL) {
		TNode *p_fnode = t_tnode->father;
		p_fnode->child_num--;
		removeById(p_fnode->home, t_tnode->room->s_id);
		releaseOnlyNode(t_tnode->room);
		t_tnode->room = NULL;
		return 0;
	}
	return -1;
}

TNode *getChildByIndex(TNode *p_tnode, unsigned long long index) {
	List *p_home = p_tnode->home;
	Node *p_node = p_home->head;
	int m_index = 0;
	if (index < p_tnode->child_num)
	{
		while (p_node != NULL && m_index < index) {
			m_index++;
			p_node = p_node->next;
		}
		return (TNode *)p_node->value;
	}
	return NULL;
}

unsigned long long getIndexByChild(TNode *f_tnode, TNode *c_tnode) {
	List *p_home = f_tnode->home;
	Node *p_node = p_home->head;
	int m_index = 0;
	while (p_node != NULL) {
		TNode *p_tnode = (TNode *)p_node->value;
		if (p_tnode->s_id == c_tnode->s_id) {
			return m_index;
		}
		m_index++;
		p_node = p_node->next;
	}
	return -1;
}

int removeChildByIndex(TNode *p_tnode, unsigned long long index) {
	TNode *t_tnode = getChildByIndex(p_tnode, index);
	if (t_tnode != NULL) {
		TNode *p_fnode = t_tnode->father; 
		p_fnode->child_num--;
		removeById(p_fnode->home, t_tnode->room->s_id);
		releaseOnlyNode(t_tnode->room);
		t_tnode->room = NULL;
		return 0;
	}
	return -1;
}


int TreeThroughUp(Tree *p_tree, int(*func)(TNode *, unsigned long long height)) {
	int i;
	TNode *p_tnode = p_tree->root;
	if (p_tnode != NULL) {
		if (p_tnode->child_num > 0) {
			for (i = 0; i < p_tnode->child_num; i++) {
				if (_doTreeThroughUp(getChildByIndex(p_tnode, i), 1, func) == -1) {
					break;
				}
			}
		}
		func(p_tnode, 0);
	}
	return 0;
}

int _doTreeThroughUp(TNode *p_tnode, int height, int(*func)(TNode *, unsigned long long height)) {
	int i, func_back;

	if (p_tnode->child_num > 0) {
		for (i = 0; i < p_tnode->child_num; i++) {
			if (_doTreeThroughUp(getChildByIndex(p_tnode, i), height + 1, func)) return -1;
		}
	}
	func_back = func(p_tnode, height);
	if (func_back == -1)return -1;
	return 0;
}


int TreeThroughDown(Tree *p_tree, int(*func)(TNode *, unsigned long long height)) {
	int i;
	TNode *p_tnode = p_tree->root;
	if (p_tree->root != NULL) {
		func(p_tnode, 0);
		if (p_tree->root->child_num > 0) {
			for (i = 0; i < p_tnode->child_num; i++) {
				if (_doTreeThroughDown(getChildByIndex(p_tnode, i), 1, func) == -1) {
					break;
				}
			}
		}
	}
	return 0;
}

int _doTreeThroughDown(TNode *p_tnode, int height, int(*func)(TNode *, unsigned long long height)) {
	int i;
	int func_back = func(p_tnode, height);
	if (p_tnode->child_num > 0) {
		for (i = 0; i < p_tnode->child_num; i++) {
			if (_doTreeThroughDown(getChildByIndex(p_tnode, i), height + 1, func)) return -1;
		}
	}
	if (func_back == -1)return -1;
	return 0;
}

int TreeTravel(Tree *p_tree, int(*func)(TNode *, unsigned long long height)) {
	TNode *p_tnode = p_tree->root;
	unsigned long long height = 0;
	if (p_tnode != NULL) {
		int func_back = func(p_tnode, height);
		while (func_back > -2) {
			if (func_back > -1) {
				p_tnode = getChildByIndex(p_tnode, func_back);
				func(p_tnode, height + 1);
			}
			else
			{
				p_tnode = p_tnode->father;
				func(p_tnode, height - 1);

			}
		}
	}
	return 0;
}
int releaseTNode(TNode *p_tnode) {
	if (p_tnode->child_num == 0) {
		releaseList(p_tnode->home);
		if (p_tnode->father != NULL) {
			removeChildById(p_tnode->father, p_tnode->s_id);
		}
		if (p_tnode->type != POINTER) {
			if (p_tnode->type == LIST) {
				releaseList((List *)p_tnode->value);
			}
			else {
				free(p_tnode->value);
			}
		}
		p_tnode->value = NULL;
		p_tnode->type = VOID;
        freeS_id(p_tnode->s_id);
		p_tnode->if_malloc = 0;
		free(p_tnode);
	}
	return 0;
}

int releaseTree(Tree *p_tree) {
	TreeThroughUp(p_tree, _doreleaseTree);
	p_tree->root = NULL;
    freeS_id(p_tree->s_id);
	free(p_tree);
	return 0;
}

int _doreleaseTree(TNode *p_tnode, unsigned long long height) {
	releaseTNode(p_tnode);
	return 0;
}

int releaseOnlyTree(Tree *p_tree) {
    freeS_id(p_tree->s_id);
	p_tree->root = NULL;
	free(p_tree);
	return 0;
}

int releaseOnlyTNode(TNode *p_tnode) {
	releaseList(p_tnode->home);
	if (p_tnode->if_malloc) {
		if (p_tnode->type != STRING) {
			if (p_tnode->type == LIST) {
				releaseList((List *)p_tnode->value);
			}
			else {
				free(p_tnode->value);
			}
		}
	}
	p_tnode->value = NULL;
	p_tnode->type = VOID;
    freeS_id(p_tnode->s_id);
	p_tnode->if_malloc = 0;
	free(p_tnode);
	return 0;
}

int releaseAllForTree(void) {
	Node *p_node;
	Tree *p_tree;
	if (if_safeModeForTree) {
		if_safeModeForTree = 0;
		p_node = tnode_list->head;
		while (p_node != NULL) {
			TNode *p_tnode = (TNode *)p_node->value;
			releaseOnlyTNode(p_tnode);
			p_node = p_node->next;
		}
		p_node = tree_list->head;
		while (p_node != NULL) {
			p_tree = (Tree *)p_node->value;
			releaseOnlyTree(p_tree);
			p_node = p_node->next;
		}
		releaseList(tnode_list);
		releaseList(tree_list);
	}
	return 0;
}

int setRoot(Tree *p_tree, TNode *p_tnode) {
	p_tree->root = p_tnode;
	return 0;
}
