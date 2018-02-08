typedef struct Node{
	unsigned long int id;
	void *value;
	struct Node *next;
	struct Node *last;
}Node;

typedef struct List{
	Node *head;
	Node *tail;
	unsigned long int length;
}List;

List *init_list();
Node *init_node();
int insertInHead(List *p_list, Node *p_node);
int insertInTail(List *p_list, Node *p_node);
int removeById(List *p_list, unsigned long id);
int removeByNode(List *p_list, Node *p_node);
int popFromHead(List *p_list);
int popFromTail(List *p_list);
unsigned long int len(List *p_list);
Node *findById(List *p_list, unsigned long int id);
Node *findByValue(List *p_list, char type[], void *value);
int releaseList(List *p_list);
int releaseNode(Node *p_node);

int insertInHead(List *p_list, Node *p_node){
	p_list->head->last = p_node;
	p_node->last = NULL;
	p_node->next = p_list->head;
	p_list->head = p_node;
	return 0;
}

int insertInTail(List *p_list, Node *p_node){
	p_list->tail->next = p_node;
	p_node->next = NULL;
	p_node->last = p_list->tail;
	p_list->tail = p_node;
	return 0;
}

int releaseNode(Node *p_node){
	free(p_node->value);
	free(p_node);
	return 0;
}

int releaseList(List *p_list){
	Node *p_node, *pl_node;
	p_node = p_list->head;
	while (p_node != NULL){
		pl_node = p_node;
		p_node = p_node->next;
		releaseNode(pl_node);
	}
	free(p_list);
	return 0;
}
