#include "list_expand.h"

Node *nodeWithInt(int m_int, _Bool if_sid) {
	Node *p_node;
	int *p_int = (int *)malloc(sizeof(int));
    if(p_int == NULL){
        showError(pushError(INT, STANDARD, initInfo(__FUNCTION__, "Error in getting the memory of int.")));
        return NULL;
    }
	*p_int = m_int;
	p_node = initNode(if_sid);
	initMallocValueForNode(p_node, INT, (void *)p_int);
	return p_node;
}

Node *nodeWithUInt(unsigned int m_uint, _Bool if_sid){
    Node *p_node;
    unsigned int *pu_int = (unsigned int *)malloc(sizeof(unsigned int));
    if(pu_int == NULL){
        showError(pushError(INT, STANDARD, initInfo(__FUNCTION__, "Error in getting the memory of int.")));
        return NULL;
    }
    *pu_int = m_uint;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, INT, (void *)pu_int);
    return p_node;
}

Node *nodeWithULLInt(unsigned long long m_ullint, _Bool if_sid) {
    Node *p_node;
    unsigned long long *p_ullint = (unsigned long long *)malloc(sizeof(unsigned long long));
    if(p_ullint == NULL){
        showError(pushError(INT, STANDARD, initInfo(__FUNCTION__, "Error in getting the memory of int.")));
        return NULL;
    }
    *p_ullint = m_ullint;
    p_node = initNode(if_sid);
    initMallocValueForNode(p_node, ULLINT, (void *)p_ullint);
    return p_node;
}

Node *nodeWithDouble(double m_double, _Bool if_sid) {
	Node *p_node;
	double *p_double = (double *)malloc(sizeof(double));
    if(p_double == NULL){
        showError(pushError(DOUBLE, STANDARD, initInfo(__FUNCTION__, "Error in getting the memory of double.")));
        return NULL;
    }
	*p_double = m_double;
	p_node = initNode(if_sid);
	initMallocValueForNode(p_node, DOUBLE, (void *)p_double);
	return p_node;
}

Node *nodeWithString(const char *m_string, _Bool if_sid) {
	Node *p_node;
	char *p_string = (char *)malloc(sizeof(char)*(strlen(m_string) + 1));
    if(p_string == NULL){
        showError(pushError(STRING, STANDARD, initInfo("initWithString()", "Error in getting the memory of string.")));
        return NULL;
    }
	strcpy(p_string, m_string);
	p_node = initNode(if_sid);
	initMallocValueForNode(p_node, STRING, (void *)p_string);
	return p_node;
}

Node *nodeWithPointer(const void *m_pointer, _Bool if_sid) {
	Node *p_node = initNode(if_sid);
	initMallocValueForNode(p_node, POINTER, m_pointer);
	return p_node;
}

Node *nodeWithComplex(void) {
	Node *p_node = initNode(0);
	p_node->type = LIST;
	p_node->value = initList(0);
	return p_node;
}

Node *findByIndexForNode(List *p_list, unsigned long long m_index) {
    if(p_list == NULL) return NULL;
    if(p_list->p_lq != NULL){
        register struct list_quick *p_lq = p_list->p_lq;
        if(p_lq->fn_node != NULL) return getNodeByFnNode(p_list, m_index);
    }
    Node *p_node = p_list->head;
    unsigned long long i;
    for (i = 0; i < m_index; i++) {
        p_node = p_node->next;
    }
    return p_node;
}

s_Node *s_findByIndexForNode(List *p_list, unsigned long long m_index) {
    s_Node *s_p_node = p_list->s_head;
    unsigned long long i;
    for (i = 0; i < m_index; i++) {
        s_p_node = s_p_node->next;
    }
    return s_p_node;
}

List *listThrough(List *p_list, List *(*p_func)(unsigned int, void *, List *), List *expand_resources) {
	Node *p_node = p_list->head;
    List *m_rtnlst = NULL;
    unsigned long long index = 0;
    insertInTail(expand_resources, nodeWithULLInt(index, 0));
    insertInTail(expand_resources, nodeWithULLInt(p_list->length, 0));
	while (p_node != NULL) {
		if (p_node->value != NULL) {
			m_rtnlst = (*p_func)(p_node->type, p_node->value, expand_resources);
            int status = getByIntForNode(findByIndexForNode(m_rtnlst, 0));
			if (status == -1) break;
			else if (status == 1) {
				p_node = p_node->last;
                releaseList(m_rtnlst);
                m_rtnlst = NULL;
				continue;
			}
			else {
                releaseList(m_rtnlst);
                m_rtnlst = NULL;
			}
		}
        lupdull(expand_resources,expand_resources->length-2,++index);
		p_node = p_node->next;
	}
    releaseList(expand_resources);
    if(m_rtnlst != NULL) releaseNode(popFromHead(m_rtnlst));
	return m_rtnlst;
}

unsigned long long getInfoForListThrough(List *expand_resources, int type){
    Node *p_node = NULL;
    if (type == 0) {
        p_node = findByIndexForNode(expand_resources, expand_resources->length-1);
    }else{
        p_node = findByIndexForNode(expand_resources, expand_resources->length-2);
    }
    return *((unsigned long long *)p_node->value);
}

int getByIntForNode(Node *p_node) {
	if (p_node->type == INT) return *(int *)(p_node->value);
	else return -1;
}

unsigned int getByUIntForNode(Node *p_node){
    if (p_node->type == UINT) return *(unsigned int *)(p_node->value);
    else return -1;
}

char *getByStringForNode(Node *p_node) {
	if (p_node->type == STRING) return (char *)(p_node->value);
	else return NULL;
}

double getByDoubleForNode(Node *p_node) {
	if (p_node->type == DOUBLE) return *(double *)(p_node->value);
	else return -1;
}

void *getByPointerForNode(Node *p_node) {
	return (void *)(p_node->value);
}

void printListInfo(List *p_list, int priority) {
	int i = 0;
	Node *p_node;
	for (i = 0; i < priority; i++) printf("   ");
	printf("###LIST(location:%p, id:%s){\n", p_list, s_idToASCIIString(p_list->s_id));
	for (i = 0; i < priority + 1; i++) printf("   ");
	printf("HEAD->%p / Tail->%p / Length:%llu\n", p_list->head, p_list->tail, p_list->length);
	p_node = p_list->head;
	while (p_node != NULL) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("%d.... \n", i);
		printNodeInfo(p_node, priority + 1);
		p_node = p_node->next;
		i++;
	}
	for (i = 0; i < priority; i++) printf("   ");
	printf("}\n");

}

void printList(List *p_list) {
	int if_nearLast = 0;
	Node *p_node = p_list->head;
	printf("[");
	while (p_node != NULL) {
		if (!if_nearLast && p_node->next == NULL) if_nearLast = 1;
		if (p_node->type == INT) {
			printf("%d", *(int *)(p_node->value));
		}
		else if (p_node->type == DOUBLE) {
			printf("%a", *(double *)(p_node->value));
		}
		else if (p_node->type == STRING) {
			printf("%s", (char *)(p_node->value));
		}
		else if (p_node->type == POINTER) {
			printf("%p", (char *)(p_node->value));
		}
		else if (p_node->type == LIST) {
			printList((List *)p_node->value);
		}
		if (!if_nearLast) {
			printf(", ");
		}
		p_node = p_node->next;
	}
	printf("]");
}

void printNodeInfo(Node *p_node, int priority) {
	int i;
	for (i = 0; i < priority; i++) printf("   ");
	printf("#NODE(location:%p, id:%s){\n", p_node, s_idToASCIIString(p_node->s_id));
	for (i = 0; i < priority + 1; i++) printf("   ");
	printf("NEXT->%p / LAST->%p\n", p_node->next, p_node->last);
	if (p_node->type == INT) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(int):%d\n", *(int *)(p_node->value));
	}
	else if (p_node->type == DOUBLE) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(double):%a\n", *(double *)(p_node->value));
	}
	else if (p_node->type == STRING) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(string):%s\n", (char *)(p_node->value));
	}
	else if (p_node->type == POINTER) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(pointer):%s\n", (char *)(p_node->value));
	}
	else if (p_node->type == LIST) {
		for (i = 0; i < priority + 1; i++) printf("   ");
		printf("VALUE(List):\n");
		printListInfo((List *)p_node->value, priority + 2);
	}
	for (i = 0; i < priority; i++) printf("   ");
	printf("}\n");
}

void printNode(Node *p_node) {
	int i;
	printf("#NODE(location:%p, id:%s){\n", p_node, s_idToASCIIString(p_node->s_id));
	printf("   ");
	printf("NEXT->%p / LAST->%p\n", p_node->next, p_node->last);
	for (i = 0; i < 1; i++) printf("   ");
	printf("ifMalloc: ");
	if (p_node->value != NULL) {
		printf("YES\n");
		for (i = 0; i < 1; i++) printf("   ");
		printf("Value(type: %d): ", p_node->type);
		if (p_node->type == INT) {
			printf("%d", *(int *)(p_node->value));
		}
		else if (p_node->type == DOUBLE) {
			printf("%a\n", *(double *)(p_node->value));
		}
		else if (p_node->type == STRING) {
			printf("%s\n", (char *)(p_node->value));
		}
		else if (p_node->type == POINTER) {
			printf("%p\n", (char *)(p_node->value));
		}
		else if (p_node->type == LIST) {
			printList((List *)p_node->value);
		}
	}
	else printf("NO\n");
	
	printf("}\n");
}


Node *findByIntForNode(List *p_list, int target) {
	Node *t_node;
	int *p_target = (int *)malloc(sizeof(int));
	*p_target = target;
	t_node = findByValue(p_list, INT, p_target);
	free(p_target);
	return t_node;
}

Node *findByDoubleForNode(List *p_list, double target) {
	Node *t_node;
	double *p_target = (double *)malloc(sizeof(double));
	*p_target = target;
	t_node = findByValue(p_list, DOUBLE, p_target);
	free(p_target);
	return t_node;
}

Node *findByStringForNode(List *p_list, char *target) {
	Node *t_node;
	char *p_temp = (char *)malloc(sizeof(char)*(strlen(target) + 1));
	strcpy(p_temp, target);
	t_node = findByValue(p_list, STRING, p_temp);
	free(p_temp);
	return t_node;
}

Node *findByPointerForNode(List *p_list, void *target) {
	Node *t_node = findByValue(p_list, POINTER, target);
	return t_node;
}

int addValueForComplex(Node * p_node, int type, void *value) {
	List *c_list;
	Node *c_node;
	if (p_node->type == LIST) {
		c_list = (List *)p_node->value;
		c_node = initNode(0);
		initMallocValueForNode(c_node, type, value);
		insertInTail(c_list, c_node);
		return  0;
	}
	return  -1;
}

int addIntForComplex(Node *p_node, int temp) {
	if (p_node->type == LIST) {
		int *p_temp = (int *)malloc(sizeof(int));
        if(p_temp == NULL){
            showError(pushError(INT, STANDARD, initInfo("addIntForComplex()", "Error in getting the memory of int.")));
            return -1;
        }
		*p_temp = temp;
		addValueForComplex(p_node, INT, p_temp);
		return 0;
	}
	return -1;
}

int addDoubleForComplex(Node *p_node, double temp) {
	if (p_node->type == LIST) {
		double *p_temp = (double *)malloc(sizeof(double));
        if(p_temp == NULL){
            showError(pushError(DOUBLE, STANDARD, initInfo("addDoubleForComplex()", "Error in getting the memory of double.")));
            return -1;
        }
		*p_temp = temp;
		addValueForComplex(p_node, DOUBLE, p_temp);
		return 0;
	}
	return -1;
}

int addStringForComplex(Node *p_node, char *temp) {
    if (p_node->type == LIST) {
		char *p_temp = (char *)malloc(sizeof(strlen(temp) + 1));
        if(p_temp == NULL){
            showError(pushError(STRING, STANDARD, initInfo("addStringForComplex()", "Error in getting the memory of string.")));
            return -1;
        }
		strcpy(p_temp, temp);
		addValueForComplex(p_node, STRING, p_temp);
		return 0;
	}
	return -1;
}

int addPointerForComplex(Node *p_node, void *temp) {
	if (p_node->type == LIST) {
		addValueForComplex(p_node, POINTER, temp);
		return 0;
	}
	return -1;
}

List *mply_findByInt(List* p_list, int temp) {
	int *p_temp = (int *)malloc(sizeof(int));
    if(p_temp == NULL){
        showError(pushError(INT, STANDARD, initInfo("m_findByInt()", "Error in getting the memory of int.")));
        return NULL;
    }
	List *t_list;
	*p_temp = temp;
	t_list = mply_findByValue(p_list, INT, (void *)p_temp);
	free(p_temp);
	return t_list;
}

List *mply_findByDouble(List* p_list, double temp) {
	List *t_list;
	double *p_temp = (double *)malloc(sizeof(double));
    if(p_temp == NULL){
        showError(pushError(DOUBLE, STANDARD, initInfo("m_findByDouble()", "Error in getting the memory of double.")));
        return NULL;
    }
	*p_temp = temp;
	t_list = mply_findByValue(p_list, DOUBLE, (void *)p_temp);
	free(p_temp);
	return t_list;
}

List *mply_findByString(List* p_list, char *temp) {
	List *t_list;
	char *p_temp = (char *)malloc(sizeof(char)*(strlen(temp) + 1));
    if(p_temp == NULL){
        showError(pushError(STRING, STANDARD, initInfo("m_findByString()", "Error in getting the memory of string.")));
        return NULL;
    }
	strcpy(p_temp, temp);
	t_list = mply_findByValue(p_list, STRING, (void *)p_temp);
	free(p_temp);
	return t_list;
}

List *mply_findByPointer(List* p_list, void *temp) {
	List *t_list = mply_findByValue(p_list, DOUBLE, (void *)temp);
	return t_list;
}

unsigned long long getIndexByNode(List *p_list, Node *p_node) {
    if (p_list->p_lq != NULL){
        register Node **p_fn_node = p_list->p_lq->fn_node;
        register Node *rp_node = p_node;
        for (register int i = 0; i < p_list->length; i++) if (p_fn_node[i] == rp_node) return i;
    }
    else{
        register Node *t_node = p_list->head;
        register unsigned long long index = 0;
        while (t_node != NULL) {
            if (p_node->s_id == t_node->s_id) return index;
            index++;
            t_node = t_node->next;
        }
    }
	return 0;
}

List *mply_findByIntForNode(List* p_list, int temp) {
    int *p_temp = (int *)malloc(sizeof(int));
    if(p_temp == NULL){
        showError(pushError(INT, STANDARD, initInfo("m_findByIntForNode()", "Error in getting the memory of int.")));
        return NULL;
    }
	*p_temp = temp;
	return mply_findByValue(p_list, INT, (void *)p_temp);
}

List *mply_findByDoubleForNode(List* p_list, double temp) {
	double *p_temp = (double *)malloc(sizeof(double));
    if(p_temp == NULL){
        showError(pushError(DOUBLE, STANDARD, initInfo("m_findByDoubleForNode()", "Error in getting the memory of double.")));
        return NULL;
    }
	*p_temp = temp;
	return mply_findByValue(p_list, DOUBLE, (void *)p_temp);
}

List *mply_findByStringForNode(List* p_list, char *temp) {
	char *p_temp = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
    if(p_temp == NULL){
        showError(pushError(STRING, STANDARD, initInfo("m_findByStringForNode()", "Error in getting the memory of string.")));
        return NULL;
    }
	strcpy(p_temp, temp);
	return mply_findByValue(p_list, STRING, (void *)p_temp);
}

List *mply_findByPointerForNode(List* p_list, void *temp) {
	return mply_findByValue(p_list, POINTER, (void *)temp);
}

unsigned long long calListMemory(List * p_list){
    Node *p_node = p_list->head;
    unsigned long long nodes_size = 0LL;
    unsigned long long list_size = sizeof(p_list);
    while(p_node != NULL){
        nodes_size += sizeof(p_node);
        p_node = p_node->next;
    }
    return  list_size + nodes_size;
}

int updateValueWithIntForNode(Node *p_node,int value){
    int *p_value = (int *)malloc(sizeof(int));
    if(p_value == NULL){
        showError(pushError(INT, STANDARD, initInfo("updateValueWithInt()", "Error in getting the memory of int.")));
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithULLIntForNode(Node *p_node, unsigned long long value){
    unsigned long long *p_value = (unsigned long long *)malloc(sizeof(unsigned long long));
    if(p_value == NULL){
        showError(pushError(INT, STANDARD, initInfo(__FUNCTION__, "Error in getting the memory of int.")));
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithDoubleForNode(Node *p_node, double value){
    double *p_value = (double *)malloc(sizeof(double));
    if(p_value == NULL){
        showError(pushError(DOUBLE, STANDARD, initInfo("updateValueWithDouble()", "Error in getting the memory of double.")));
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithStringForNode(Node *p_node, char *string){
    char *p_value = (char *)malloc(sizeof(strlen(string)) + 1);
    if(p_value == NULL){
        showError(pushError(STRING, STANDARD, initInfo("updateValueWithString()", "Error in getting the memory of string.")));
        return -1;
    }
    strcpy(p_value, string);
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithPointerForNode(Node *p_node, void *pointer){
    free(p_node->value);
    p_node->value = pointer;
    return 0;
}

inline s_Node *s_nodeWithInt(int t_int){
    s_Node *s_p_node = s_initNode();
    int *pt_int = malloc(sizeof(int));
    *pt_int = t_int;
    s_p_node->value = pt_int;
    return s_p_node;
}

inline s_Node *s_nodeWithUInt(unsigned int t_uint){
    s_Node *s_p_node = s_initNode();
    unsigned int *pt_uint = malloc(sizeof(unsigned int));
    *pt_uint = t_uint;
    s_p_node->value = pt_uint;
    return s_p_node;
}

inline s_Node *s_nodeWithDouble(double t_double){
    s_Node *s_p_node = s_initNode();
    unsigned int *pt_double = malloc(sizeof(double));
    *pt_double = t_double;
    s_p_node->value = pt_double;
    return s_p_node;
}

inline s_Node *s_nodeWithString(const char *t_string){
    s_Node *s_p_node = s_initNode();
    char *pt_string = malloc(strlen(t_string) + 1);
    strcpy(pt_string, t_string);
    s_p_node->value = pt_string;
    return s_p_node;
}

inline s_Node *s_nodeWithPointer(const void *t_pointer){
    s_Node *s_p_node = s_initNode();
    s_p_node->value = (void *) t_pointer;
    return s_p_node;
}



List *newReturn(int if_status ,int status, char *argc, ...){
    List *p_list = initList(0);
    if(if_status){
        lisrti(p_list, status);
    }
    if(status != 0){
        va_list args;
        va_start(args, argc);
        char p_ch = argc[0];
        char t_ch[256];
        int count = 0, t_count = 0;
        while(p_ch != '\0'){
            if(p_ch == '%'){
                switch (argc[count + 1]) {
                    case 'd':
                        lisrti(p_list, va_arg(args, int));
                        break;
                    case 's':
                        t_count = 0;
                        while ((t_ch[t_count] = va_arg(args, int)) != '\0') t_count++;
                        t_ch[t_count] = '\0';
                        lisrts(p_list, t_ch);
                        break;
                    case 'f':
                        lisrtd(p_list, va_arg(args, double));
                        break;
                    case 'p':
                        lisrtp(p_list, va_arg(args, void *));
                        break;
                    case 'u':
                        if(argc[count + 2] == 'l'){
                            if(argc[count + 3] == 'l'){
                                lisrtull(p_list, va_arg(args, unsigned long long));
                                count += 2;
                            }
                            else{
                                count++;
                            }
                        }
                        else{
                            lisrtu(p_list, va_arg(args, unsigned int));
                        }
                        break;
                    default:
                        break;
                }
                count++;
            }
            p_ch = argc[++count];
        }
        va_end(args);
    }
    return p_list;
}

List *newCReturn(void){
    return newReturn(1, 0, NULL);
}

void printListForCustom(List *p_list,void (*func)(void *value)){
    printf("###LIST (LEN:%llu ",p_list->length);
    if(p_list->s_id != NULL) printf("SID:%s",p_list->s_id->decrypt_str);
    printf(")\n");
    listThrough(p_list, __CALLBACK_CALL(printListForCustom), __SEND_ARG("%p", func));
}

__CALLBACK_DEFINE(printListForCustom){
    void (*func)(void *) = __ARGS_P(0, void);
    printf("NODE (IDX:%llu ",__NOW_INDEX);
    printf(")\n");
    func(__VALUE(void *));
    printf("\n");
    return __CRETURN__;
}
