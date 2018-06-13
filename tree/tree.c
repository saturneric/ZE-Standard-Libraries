#include"tree.h"

unsigned long long target_id = 0;
TNode *target_value_id = NULL;
int if_safeModeForTree = 0;

int safeModeForTree(int ifon) {
	if (ifon == 1) {
		if (tnode_list == NULL && tree_list == NULL) {
			tnode_list = (List *)malloc(sizeof(List));
			tree_list = (List *)malloc(sizeof(List));

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
	TNode *p_tnode = (TNode *)malloc(sizeof(TNode));
	p_tnode->id = getId();
	p_tnode->child_num = 0;
	p_tnode->father = NULL;
	p_tnode->if_malloc = 0;
	p_tnode->value = NULL;
	p_tnode->type = NULL;
	p_tnode->home = initList();
	p_tnode->room = NULL;
	if (if_safeModeForTree) {
		if (if_safeModeForNode) {
			if_safeModeForNode = 0;
			Node *s_node = initNode();
			initMallocValueForNode(s_node, "pointer", (void *)p_tnode);
			insertInTail(tnode_list, s_node);
			if_safeModeForNode = 1;
		}
		else
		{
			Node *s_node = initNode();
			initMallocValueForNode(s_node, "pointer", (void *)p_tnode);
			insertInTail(tnode_list, s_node);
		}
	}
	return p_tnode;
}

Tree *initTree(void) {
	Tree *p_tree = (Tree *)malloc(sizeof(Tree));
	p_tree->id = getId();
	p_tree->root = NULL;
	if (if_safeModeForTree) {
		if (if_safeModeForNode) {
			if_safeModeForNode = 0;
			Node *s_node = initNode();
			initMallocValueForNode(s_node, "pointer", (void *)p_tree);
			if_safeModeForNode = 1;
			insertInTail(tree_list, s_node);
		}
		else
		{
			Node *s_node = initNode();
			initMallocValueForNode(s_node, "pointer", (void *)p_tree);
			insertInTail(tree_list, s_node);
		}
	}
	return p_tree;
}

int *initMallocValueForTNode(TNode *p_tnode, char *type, void *value) {
	p_tnode->type = type;
	p_tnode->value = value;
	p_tnode->if_malloc = 1;
	return 0;
}

int addChildInLeft(TNode *f_tnode, TNode *c_tnode) {
	Node *p_node = initNode();
	initMallocValueForNode(p_node, "pointer", c_tnode);
	insertInHead(f_tnode->home, p_node);
	c_tnode->father = f_tnode;
	c_tnode->room = p_node;
	f_tnode->child_num++;
	return 0;
}

int addChildInRight(TNode *f_tnode, TNode *c_tnode) {
	Node *p_node = initNode();
	initMallocValueForNode(p_node, "pointer", c_tnode);
	insertInTail(f_tnode->home, p_node);
	c_tnode->father = f_tnode;
	c_tnode->room = p_node;
	f_tnode->child_num++;
	return 0;
}

TNode *getBrotherInLeft(TNode *p_tnode) {
	List *p_home = p_tnode->father->home;
	Node *p_node = p_home->head;
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


TNode *getChildById(TNode *p_tnode, unsigned long long id) {
	List *p_home = p_tnode->home;
	target_id = 0;
	target_value_id = NULL;
	listThrough(p_home, _dogetChildById);
	if (target_value_id != NULL) {
		return target_value_id;
	}
	return NULL;
}

int _dogetChildById(const char *type, void *value) {
	if (!strcmp(type, "pointer")) {
		TNode *p_tode = (TNode *)value;
		if (p_tode->id == target_id) {
			target_value_id = p_tode;
			return -1;
		}
	}
	return 0;
}

char *target_type = NULL;
void *target_value = NULL;
TNode *target_value_value = NULL;
int _dogetChildByValue(const char *type, void *value);

TNode *getChildByValue(TNode *p_tnode, char *type, void *value) {
	List *p_home = p_tnode->home;
	target_value = value;
	target_type = type;
	target_value_value = NULL;
	listThrough(p_home, _dogetChildByValue);
	if (target_value_value != NULL) {
		return target_value_value;
	}
	return NULL;
}

int _dogetChildByValue(const char *type, void *value) {
	if (!strcmp(type, target_type)) {
		TNode *p_tode = (TNode *)value;
		if (!strcmp(target_value, "int")) {
			if (*(int *)p_tode->value == *(int *)target_value)
			{
				target_value_value = p_tode;
				return -1;
			}
		}
		else if (!strcmp(target_value, "double"))
		{
			if (*(double *)p_tode->value == *(double *)target_value)
			{
				target_value_value = p_tode;
				return -1;
			}
		}
		else if (!strcmp(target_value, "string"))
		{
			if (!strcmp((char *)p_tode->value, (char *)target_value))
			{
				target_value_value = p_tode;
				return -1;
			}
		}
		else if (!strcmp(target_value, "pointer"))
		{
			if (p_tode->value == target_value)
			{
				target_value_value = p_tode;
				return -1;
			}
		}

	}
	return 0;
}

int removeChildById(TNode *p_tnode, unsigned long long id) {
	TNode *t_tnode = getChildById(p_tnode, id);
	if (t_tnode != NULL) {
		TNode *p_fnode = t_tnode->father;
		p_fnode->child_num--;
		removeById(p_fnode->home, t_tnode->room->id);
		releaseOnlyNode(t_tnode->room);
		t_tnode->room = NULL;
		return 0;
	}
	return -1;
}

int removeChildByValue(TNode *p_tnode, char *type, void *value) {
	TNode *t_tnode = getChildByValue(p_tnode, type, value);
	if (t_tnode != NULL) {
		TNode *p_fnode = t_tnode->father;
		p_fnode->child_num--;
		removeById(p_fnode->home, t_tnode->room->id);
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
	if (index < p_tnode->child_num - 1)
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
		if (p_tnode->id == c_tnode->id) {
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
		removeById(p_fnode->home, t_tnode->room->id);
		releaseOnlyNode(t_tnode->room);
		t_tnode->room = NULL;
		return 0;
	}
	return -1;
}


int TreeThroughUp(Tree *p_tree, int(*func)(TNode *, unsigned long long height)) {
	TNode *p_tnode = p_tree->root;
	if (p_tnode != NULL) {
		func(p_tnode, 0);
		if (p_tnode->child_num > 0) {
			for (int i = 0; i < p_tnode->child_num; i++) {
				if (_doTreeThroughUp(getChildByIndex(p_tnode, i), 1, func) == -1) {
					break;
				}
			}
		}
	}
	return 0;
}

int _doTreeThroughUp(TNode *p_tnode, int height, int(*func)(TNode *, unsigned long long height)) {
	if (p_tnode->child_num > 0) {
		for (int i = 0; i < p_tnode->child_num; i++) {
			if (_doTreeThroughUp(getChildByIndex(p_tnode, i), height + 1, func)) return -1;
		}
	}
	int func_back = func(p_tnode, height);
	if (func_back == -1)return -1;
	return 0;
}


int TreeThroughDown(Tree *p_tree, int(*func)(TNode *, unsigned long long height)) {
	TNode *p_tnode = p_tree->root;
	if (p_tree->root != NULL) {
		if (p_tree->root->child_num > 0) {
			func(p_tnode, 0);
			for (int i = 0; i < p_tnode->child_num; i++) {
				if (_doTreeThroughDown(getChildByIndex(p_tnode, i), 1, func) == -1) {
					break;
				}
			}
		}
	}
	return 0;
}

int _doTreeThroughDown(TNode *p_tnode, int height, int(*func)(TNode *, unsigned long long height)) {
	int func_back = func(p_tnode, height);
	if (p_tnode->child_num > 0) {
		for (int i = 0; i < p_tnode->child_num; i++) {
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
			removeChildById(p_tnode->father, p_tnode->id);
		}
		if (strcmp(p_tnode->type, "pointer")) {
			if (!strcmp(p_tnode->type, "list")) {
				releaseList((List *)p_tnode->value);
			}
			else {
				free(p_tnode->value);
			}
		}
		p_tnode->value = NULL;
		p_tnode->type = NULL;
		p_tnode->id = 0;
		p_tnode->if_malloc = 0;
		free(p_tnode);
	}
	return 0;
}

int releaseTree(Tree *p_tree) {
	TreeThroughUp(p_tree, _doreleaseTree);
	p_tree->root = NULL;
	p_tree->id = 0;
	free(p_tree);
	return 0;
}

int _doreleaseTree(TNode *p_tnode, unsigned long long height) {
	releaseTNode(p_tnode);
	return 0;
}

int releaseOnlyTree(Tree *p_tree) {
	p_tree->id = 0;
	p_tree->root = NULL;
	free(p_tree);
	return 0;
}

int releaseOnlyTNode(TNode *p_tnode) {
	releaseList(p_tnode->home);
	if (p_tnode->if_malloc) {
		if (strcmp(p_tnode->type, "pointer")) {
			if (!strcmp(p_tnode->type, "list")) {
				releaseList((List *)p_tnode->value);
			}
			else {
				free(p_tnode->value);
			}
		}
	}
	p_tnode->value = NULL;
	p_tnode->type = NULL;
	p_tnode->id = 0;
	p_tnode->if_malloc = 0;
	free(p_tnode);
	return 0;
}

int releaseAllForTree(void) {
	if (if_safeModeForTree) {
		if_safeModeForTree = 0;
		Node *p_node = tnode_list->head;
		while (p_node != NULL) {
			TNode *p_tnode = (TNode *)p_node->value;
			releaseOnlyTNode(p_tnode);
			p_node = p_node->next;
		}
		p_node = tree_list->head;
		while (p_node != NULL) {
			Tree *p_tree = (Tree *)p_node->value;
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
