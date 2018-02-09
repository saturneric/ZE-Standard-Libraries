typedef struct Node{
	unsigned long long id;
	void *value;
	int if_setvalue;
	struct Node *next;
	struct Node *last;
}Node;

typedef struct List{
	Node *head;
	Node *tail;
	unsigned long long length;
}List;

int safeMode(int ifon);//Safe mode is used to make sure that all malloced will be freed. 
List *init_list(void);
Node *init_node(void);
int init_value(Node *,void *);
unsigned long long getId(void);
int insertInHead(List *p_list, Node *p_node);
int insertInTail(List *p_list, Node *p_node);
int removeById(List *p_list, unsigned long id);
int removeByNode(List *p_list, Node *p_node);
int popFromHead(List *p_list);
int popFromTail(List *p_list);
unsigned long long len(List *p_list);
Node *findById(List *p_list, const unsigned long long id);
Node *findByValue(List *p_list, const char *type, const void *value);
int releaseList(List *p_list);
int releaseNode(Node *p_node);

/*Something about safe mode*/
int if_safeMode = 0;
List *node_list; //Store nodes which haven't been freed.
List *list_list; //Store lists which haven't been freed. 

Node *init_node(void){
	Node *p_node = (Node *) malloc(sizeof(Node));
	p_node->id = getId();
	p_node->if_setvalue = 0;
	if(if_safeMode) insertInTail(node_list,p_node);
	return p_node;
}

List *init_list(void){
	List *p_list = (List *) malloc(sizeof(List));
	p_list->head = NULL;
	p_list->tail = NULL;
	Node *p_node = init_node();
	init_value(p_node,(void *)p_list);
	if(if_safeMode) insertInHead(list_list,p_node);
	return p_list;
}

unsigned long long getId(void){
	unsigned long long id = 0;
	srand(time(0));
	id = ((random()%9)+1)*10;
	for(int i = 0; i < 18; i++){
		id = random()%10;
		id *= 10;
	}
	return id;
}

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

int removeById(List *p_list, unsigned long id){
	Node *tmp = p_list->head;
	if(tmp == NULL) return -1;//这说明p_list指向空列表
	do{	
		if(tmp->id == id) {
			tmp->last->next = tmp->next;
			tmp->next->last = tmp->last;
			return 1;//找到了
		}
		else{
			tmp = tmp->next;
		}
	} while(tmp != NULL);

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
		else{
			tmp = tmp->next;
		}	
	}while(tmp != NULL);

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

/*The method in this function won't be better than going through the list 
 * node by node.The worst situation happens when the matched node is in 
 * the middle of the list.*/
Node *findById(List *p_list, const unsigned long long id){
	Node *ph_node = p_list->head;
	Node *pt_node = p_list->tail;
	int direction = 0;
	while(ph_node != pt_node){
		if (direction == 0){
			if (ph_node->id == id){
				return ph_node;
			}
			else{
				ph_node = ph_node->next;
			}
			direction = 1;
		}
		else{
			if (pt_node->id == id){
				return pt_node;
			}
			else{
				pt_node = pt_node->last;
			}
		}
	}
	return NULL;
}

Node *findByValue(List *p_list, const char *type, const void *value){
	Node *p_node = p_list->head;
	while(p_node != NULL){
		if(!strcmp(type,"int")){
			if(*((int *)p_node) == *((int *)value)){
				return p_node;
			}
		}
		else if(!strcmp(type,"double")){
			if(*((double *)p_node) == *((double *)value)){
				return p_node;
			}
		}
		else if(!strcmp	(type,"string")){
			if(!strcmp((char *)p_node->value,(char *)value))
			{
				return p_node;
			}
		}
		else{
			return NULL;
		}
		
	}
	return NULL;
}
