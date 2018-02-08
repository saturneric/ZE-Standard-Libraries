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


int insertInHead(List *p_list, Node *p_node){
	p_list->head->last = p_node;
	//p_node->last = NULL;
	p_node->next = p_list->head;
	p_list->head = p_node;
	return 0;
}

int insertInTail(List *p_list, Node *p_node){
	p_list->tail->next = p_node;
	//p_node->next = NULL;
	p_node->last = p_list->tail;
	p_list->tail = p_node;
	return 0;
}

int removeById(List *p_list, unsigned long id){
	Node *tmp = p_list->head;
	if(tmp == NULL)
		return -1;//这说明p_list指向空列表

	do{	
		if( *(tmp->value) == id ){
			tmp->last->next = tmp->next;
			tmp->next->last = tmp->last;
			return 1;//找到了
		}
		else
			tmp = tmp->next;
	}while(tmp != NULL)

	return 0;//没找到
}

int removeByNode(List *p_list, Node *p_node){
	Node *tmp = p_list->head;
	if(tmp == NULL)
		return -1;//这说明p_list指向空列表

	do{
		if(tmp == p_node){
			tmp->last->next = tmp->next;
			tmp->next->last = tmp->last;
			return 1;//找到了
		}
		else
			tmp = tmp->next;
	}while(tmp != NULL)

	return 0;//没找到
}

int popFromHead(List *p_list){
	if(p_list->head == NULL)
		return -1;

	if(p_list->head->next == NULL){
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	else{
		p_list->head->next->last = NULL;
		p_list->head = p_list->head->next;
	}
	return 0;
}

int popFromTail(List *p_list){
	if(p_list->head == NULL)
		return -1;

	if(p_list->head->next == NULL){
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	else{
		p_list->tail->last->next = NULL;
		p_list->tail = p_list->tail->last;
	}
	return 0;
}
