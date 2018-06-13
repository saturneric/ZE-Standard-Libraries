#include "tree_expand.h"

TNode *tnodeWithInt(int temp) {
	TNode *p_tnode = initTNode();
	int *p_temp = (int *)malloc(sizeof(int));
	*p_temp = temp;
	initMallocValueForTNode(p_tnode, "int", p_temp);
	return p_tnode;
}

TNode *tnodeWithDouble(double temp) {
	TNode *p_tnode = initTNode();
	double *p_temp = (double *)malloc(sizeof(double));
	*p_temp = temp;
	initMallocValueForTNode(p_tnode, "double", p_temp);
	return p_tnode;
}
TNode *tnodeWithString(char *temp) {
	TNode *p_tnode = initTNode();
	char *p_temp = (char *)malloc(sizeof(temp));
	strcpy_s(p_temp, sizeof(p_temp), temp);
	initMallocValueForTNode(p_tnode, "double", p_temp);
	return p_tnode;
}

TNode *tnodeWithPointer(void *temp) {
	TNode *p_tnode = initTNode();
	initMallocValueForTNode(p_tnode, "pointer", temp);
	return p_tnode;
}

int getValueByIntForTree(TNode *p_tnode) {
	if (!strcmp(p_tnode->type, "int")) {
		return *(int *)p_tnode->value;
	}
	return -1;
}

double getValueByDoubleForTree(TNode *p_tnode) {
	if (!strcmp(p_tnode->type, "double")) {
		return *(double *)p_tnode->value;
	}
	return -1;
}

char *getValueByStringForTree(TNode *p_tnode) {
	if (!strcmp(p_tnode->type, "string")) {
		return (char *)p_tnode->value;
	}
	return NULL;
}

void *getValueByPointerForTree(TNode *p_tnode) {
	if (!strcmp(p_tnode->type, "pointer")) {
		return p_tnode->value;
	}
	return NULL;
}

int printTNode(TNode *p_tnode, int priority) {
	if (p_tnode != NULL) {
		for (int i = 0; i < priority; i++) printf("   ");
		if (priority == 0) printf("###");
		else printf("#");

		printf("TNode(id: %llu)\n", p_tnode->id);
		for (int i = 0; i < priority + 1; i++) printf("   ");
		printf("ifMalloc: ");
		if (p_tnode->if_malloc) {
			printf("YES\n");
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Value(type: %s): ", p_tnode->type);
			if (!strcmp(p_tnode->type, "int")) {
				printf("%d\n", *(int *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "double")) {
				printf("%a\n", *(double *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "string")) {
				printf("%s\n", (char *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "pointer")) {
				printf("%p\n", (char *)(p_tnode->value));
			}
		}
		else printf("NO\n");

		if (p_tnode->child_num > 0) {
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Child number: %llu\n", p_tnode->child_num);
		}
		return 0;
	}
	return -1;
}

int printTNodeWithHome(TNode *p_tnode,int priority) {
	if (p_tnode != NULL) {
		if (priority == 0) printf("###");
		else printf("#");
		printf("TNode(id: %llu)\n", p_tnode->id);
		for (int i = 0; i < priority + 1; i++) printf("   ");
		printf("ifMalloc: ");
		if (p_tnode->if_malloc) {
			printf("YES\n");
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Value(type: %s): ", p_tnode->type);
			if (!strcmp(p_tnode->type, "int")) {
				printf("%d\n", *(int *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "double")) {
				printf("%a\n", *(double *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "string")) {
				printf("%s\n", (char *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "pointer")) {
				printf("%p\n", (char *)(p_tnode->value));
			}
		}
		else printf("NO\n");

		if (p_tnode->father != NULL) {
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Father id: %llu\n", p_tnode->father->id);
		}
		else
		{
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Father: NO\n");
		}

		if (p_tnode->child_num > 0) {
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Child(number: %llu):\n", p_tnode->child_num);
		}

		List *p_home = p_tnode->home;
		Node *p_node = p_home->head;
		while (p_node != NULL) {
			printTNode((TNode *)p_node->value, priority + 2);
			p_node = p_node->next;
		}
		return 0;
	}
	return -1;
}

int printTNodeWithFamily(TNode *p_tnode, int priority) {
	if (p_tnode != NULL) {
		for (int i = 0; i < priority; i++) printf("   ");
		if (priority == 0) printf("###");
		else printf("#");
		printf("TNode(id: %llu)\n", p_tnode->id);
		for (int i = 0; i < priority + 1; i++) printf("   ");
		printf("ifMalloc: ");
		if (p_tnode->if_malloc) {
			printf("YES\n");
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Value(type: %s): ", p_tnode->type);
			if (!strcmp(p_tnode->type, "int")) {
				printf("%d\n", *(int *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "double")) {
				printf("%a\n", *(double *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "string")) {
				printf("%s\n", (char *)(p_tnode->value));
			}
			else if (!strcmp(p_tnode->type, "pointer")) {
				printf("%p\n", (char *)(p_tnode->value));
			}
		}
		else printf("NO\n");

		if (p_tnode->father != NULL) {
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Father id: %llu\n", p_tnode->father->id);
		}
		else
		{
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Father: NO\n");
		}

		if (p_tnode->child_num > 0) {
			for (int i = 0; i < priority + 1; i++) printf("   ");
			printf("Child(number: %llu):\n", p_tnode->child_num);
		}

		List *p_home = p_tnode->home;
		Node *p_node = p_home->head;
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