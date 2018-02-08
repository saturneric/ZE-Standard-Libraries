typedef struct Node{
	unsigned long int id;//what's this?
	void *value;
	Node *next;
	Node *last;
};

typedef struct List{
	Node *head;
	Node *tail;
	unsigned long int length;
};

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


int insertInHead(List *p_list, Node *p_node){
	p_list->head->last = p_node;
	//p_node->last = NULL;
	p_node->next = p_list->head;
	p_list->head = p_node;
}

int insertInTail(List *p_list, Node *p_node){
	p_list->tail->next = p_node;
	//p_node->next = NULL;
	p_node->last = p_list->tail;
	p_list->tail = p_node;
}
