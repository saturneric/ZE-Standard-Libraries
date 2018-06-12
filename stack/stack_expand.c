#include "stack_expand.h"

SNode *snodeWithInt(int temp) {
	SNode *p_snode = initSNode();
	int *p_temp = (int *)malloc(sizeof(int));
	*p_temp = temp;
	initMallocValueForSNode(p_snode, "int", p_temp);
	return p_snode;
}

SNode *snodeWithDouble(double temp) {
	SNode *p_snode = initSNode();
	double *p_temp = (double *)malloc(sizeof(double));
	*p_temp = temp;
	initMallocValueForSNode(p_snode, "double", p_temp);
	return p_snode;
}

SNode *snodeWithString(char *temp) {
	SNode *p_snode = initSNode();
	char *p_temp = (char *)malloc(sizeof(char)*(strlen(temp) + 1));
	strcpy_s(p_temp, strlen(p_temp), temp);
	initMallocValueForSNode(p_snode, "string", p_temp);
	return p_snode;
}

SNode *snodeWithPointer(void *temp) {
	SNode *p_snode = initSNode();
	initMallocValueForSNode(p_snode, "pointer", temp);
	return p_snode;
}

int getValueByIntForSNode(SNode *p_snode) {
	if (!strcmp(p_snode->type, "int")) return *(int *)p_snode->value;
	else return  -1;
}

double getValueByDoubleForSNode(SNode *p_snode) {
	if (!strcmp(p_snode->type, "double")) return *(double *)p_snode->value;
	else return  -1;
}

char *getValueByStringForSNode(SNode *p_snode) {
	if (!strcmp(p_snode->type, "int")) return (char *)p_snode->value;
	else return  NULL;
}

void *getValueByPointerForSNode(SNode *p_snode) {
	if (!strcmp(p_snode->type, "int")) return (void *)p_snode->value;
	else return  NULL;
}