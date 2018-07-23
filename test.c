#include "test.h"


int list(void) {
	List *t_list, *m_list;;
	init_rand();
	safeModeForNode(1);
	t_list = initList();

	/*for(int i = 0; i < 9; i++){
	Node *t_node = initNode();
	int *t_i = (int *)malloc(sizeof(int));
	*t_i = i;
	initMallocValue(t_node,"int",(void *)t_i);
	insertInTail(t_list,t_node);
	}*/

	/*Node *t_node = initNode();
	insertInTail(t_list,t_node);
	initMalllocValue(t_node,(void *)"there");*/

	for (int i = 0; i < 12; i++) {
		insertInHead(t_list, nodeWithInt(i));
		insertInTail(t_list, nodeWithInt(i));
	}



	printListInfo(t_list, 0);
	printList(t_list);
	
	m_list = m_findByIntForNode(t_list, 5);
	printList(m_list);
	printf("\n");

	releaseAllForNode();

	return 0;
}

int _useTreeThroughDown(TNode *p_tnode, unsigned long long height) {
	printTNode(p_tnode,0);
	return  0;
}


int tree(void) {
	TNode *t_tnode, *cr_tnode, *cl_tnode;
	Tree *t_tree;
	TNode *gs_tnode;
	safeModeForTree(1);
	t_tree = initTree();
	t_tnode = tnodeWithInt(1);
	cr_tnode = tnodeWithInt(3);
	cl_tnode = tnodeWithInt(2);
	addChildInRight(t_tnode, cl_tnode);
	addChildInRight(t_tnode, cr_tnode);
	addChildInRight(cl_tnode, tnodeWithInt(4));
	gs_tnode = tnodeWithInt(5);
	addChildInRight(cl_tnode,gs_tnode);
	addChildInRight(cr_tnode, tnodeWithInt(6));
	addChildInRight(cr_tnode, tnodeWithInt(7));
	addChildInRight(gs_tnode, tnodeWithInt(8));
	setRoot(t_tree, t_tnode);
	TreeThroughUp(t_tree, _useTreeThroughDown);
	//printTNodeWithFamily(t_tnode, 0);
	releaseAllForTree();
	return 0;
}

int stack(void) {
	int i;
	Stack *t_stack = initStack();
	for (i = 0; i < 10; i++) {
		pushStack(t_stack, snodeWithInt(i));
	}
	for (i = 0; i < 10; i++) {
		printf("%d", getValueByIntForSNode(popStack(t_stack)));
	}
	releaseStack(t_stack);
	return 0;
}


int main(int argc, char **argv) {
	tree();
	getchar();
	return 0;
}
