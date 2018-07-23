#include "tree_expand.h"

TNode *tnodeWithInt(int temp) {
	TNode *p_tnode = initTNode();
	int *p_temp = (int *)malloc(sizeof(int));
	*p_temp = temp;
	initMallocValueForTNode(p_tnode, INT, p_temp);
	return p_tnode;
}

TNode *tnodeWithDouble(double temp) {
	TNode *p_tnode = initTNode();
	double *p_temp = (double *)malloc(sizeof(double));
	*p_temp = temp;
	initMallocValueForTNode(p_tnode, DOUBLE, p_temp);
	return p_tnode;
}
TNode *tnodeWithString(char *temp) {
	TNode *p_tnode = initTNode();
	char *p_temp = (char *)malloc(sizeof(temp));
	strcpy(p_temp, temp);
	initMallocValueForTNode(p_tnode, STRING, p_temp);
	return p_tnode;
}

TNode *tnodeWithPointer(void *temp) {
	TNode *p_tnode = initTNode();
	initMallocValueForTNode(p_tnode, POINTER, temp);
	return p_tnode;
}

int getValueByIntForTree(TNode *p_tnode) {
	if (p_tnode->type == INT) {
		return *(int *)p_tnode->value;
	}
	return -1;
}

double getValueByDoubleForTree(TNode *p_tnode) {
	if (p_tnode->type == DOUBLE) {
		return *(double *)p_tnode->value;
	}
	return -1;
}

char *getValueByStringForTree(TNode *p_tnode) {
	if (p_tnode->type == STRING) {
		return (char *)p_tnode->value;
	}
	return NULL;
}

void *getValueByPointerForTree(TNode *p_tnode) {
	if (p_tnode->type == POINTER) {
		return p_tnode->value;
	}
	return NULL;
}

int printTNode(TNode *p_tnode, int priority) {
	int i;
	if (p_tnode != NULL) {
		for (i = 0; i < priority; i++) printf("   ");
		if (priority == 0) printf("###");
		else printf("#");

		printf("TNode(id: %llu)\n", p_tnode->id);
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("ifMalloc: ");
		if (p_tnode->if_malloc) {
			printf("YES\n");
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Value(type: %d): ", p_tnode->type);
			if (p_tnode->type == INT) {
				printf("%d\n", *(int *)(p_tnode->value));
			}
			else if (p_tnode->type == DOUBLE) {
				printf("%a\n", *(double *)(p_tnode->value));
			}
			else if (p_tnode->type == STRING) {
				printf("%s\n", (char *)(p_tnode->value));
			}
			else if (p_tnode->type == POINTER) {
				printf("%p\n", (char *)(p_tnode->value));
			}
		}
		else printf("NO\n");

		if (p_tnode->child_num > 0) {
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Child number: %llu\n", p_tnode->child_num);
		}
		return 0;
	}
	return -1;
}

int printTNodeWithHome(TNode *p_tnode,int priority) {
	int i;
	List *p_home;
	Node *p_node;
	if (p_tnode != NULL) {
		if (priority == 0) printf("###");
		else printf("#");
		printf("TNode(id: %llu)\n", p_tnode->id);
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("ifMalloc: ");
		if (p_tnode->if_malloc) {
			printf("YES\n");
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Value(type: %d): ", p_tnode->type);
			if (p_tnode->type == INT) {
				printf("%d\n", *(int *)(p_tnode->value));
			}
			else if (p_tnode->type == DOUBLE) {
				printf("%a\n", *(double *)(p_tnode->value));
			}
			else if (p_tnode->type == STRING) {
				printf("%s\n", (char *)(p_tnode->value));
			}
			else if (p_tnode->type == POINTER) {
				printf("%p\n", (char *)(p_tnode->value));
			}
		}
		else printf("NO\n");

		if (p_tnode->father != NULL) {
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Father id: %llu\n", p_tnode->father->id);
		}
		else
		{
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Father: NO\n");
		}

		if (p_tnode->child_num > 0) {
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Child(number: %llu):\n", p_tnode->child_num);
		}

		p_home = p_tnode->home;
		p_node = p_home->head;
		while (p_node != NULL) {
			printTNode((TNode *)p_node->value, priority + 2);
			p_node = p_node->next;
		}
		return 0;
	}
	return -1;
}

int printTNodeWithFamily(TNode *p_tnode, int priority) {
	int i;
	List *p_home;
	Node *p_node;
	if (p_tnode != NULL) {
		for (i = 0; i < priority; i++) printf("   ");
		if (priority == 0) printf("###");
		else printf("#");
		printf("TNode(id: %llu)\n", p_tnode->id);
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("ifMalloc: ");
		if (p_tnode->if_malloc) {
			printf("YES\n");
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Value(type: %d): ", p_tnode->type);
			if (p_tnode->type == INT) {
				printf("%d\n", *(int *)(p_tnode->value));
			}
			else if (p_tnode->type == DOUBLE) {
				printf("%a\n", *(double *)(p_tnode->value));
			}
			else if (p_tnode->type == STRING) {
				printf("%s\n", (char *)(p_tnode->value));
			}
			else if (p_tnode->type == POINTER) {
				printf("%p\n", (char *)(p_tnode->value));
			}
		}
		else printf("NO\n");

		if (p_tnode->father != NULL) {
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Father id: %llu\n", p_tnode->father->id);
		}
		else
		{
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Father: NO\n");
		}

		if (p_tnode->child_num > 0) {
			for (i = 0; i < priority + 1; i++) printf("   ");
			printf("Child(number: %llu):\n", p_tnode->child_num);
		}

		p_home = p_tnode->home;
		p_node = p_home->head;
		while (p_node != NULL) {
			printTNodeWithFamily((TNode *)p_node->value, priority + 2);
			p_node = p_node->next;
		}
		return 0;
	}
	return -1;
}

int printTree(Tree *p_tree) {
	printf("###");
	printf("Tree(id: %llu)",p_tree->id);
	printTNodeWithFamily(p_tree->root,0);
	return 0;
}
