#ifndef type_h
#define type_h

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#define VOID 0
#define INT 1
#define DOUBLE 2
#define STRING 3
#define POINTER 4
#define LIST 5
#define STACK 6
#define TREE 7
#define LIST_NODE 8
#define TREE_NODE 9
#define STACK_NODE 10
#define T_SID 11
#define UINT 12
#define STANDARD_DATA 13
#define DATA_FILE 14

#define  DEEPC 1
#define  DEEPB 2
#define  DEEPA 3
#define TYPE_LEN 5
#define  DEEPC_LEN 4
#define  DEEPB_LEN 8
#define  DEEPA_LEN 32
#define DATA_BIT 5
#define DEEP_LEN 25
#define DEEPER_LEN 65
#define DEEPEST_LEN 225
#define FILE_TSET_LEN 18
#define HEAD_TEST_LEN 9


#define HIGH 0x3
#define STANDARD 0x2
#define LOW 0x1

typedef struct s_id{
    unsigned int type;
    unsigned int *value;//4
    unsigned int *value_deeper;//8
    unsigned int *value_deepest;//32
    unsigned int deep;
}SID;

typedef struct Node{
    SID *s_id;
    void *value;
    _Bool if_malloc;
    _Bool if_sid;
    unsigned int type;
    struct Node *next;
    struct Node *last;
} Node;


typedef struct List{
    SID *s_id;
    Node *head;
    Node *tail;
    _Bool if_sid;
    unsigned long long length;
} List;

typedef struct Info{
    char head[64];
    char body[256];
}Info;

typedef struct Error{
    unsigned int type;
    int priority;
    Info info;
    time_t time;
}Error;

typedef struct Notice{
    unsigned int type;
    Info info;
    time_t time;
}Notice;

typedef struct Log{
    FILE *fp;
    int if_enable;
    unsigned long int id;
}Log;

typedef struct stack_node{
    SID *s_id;
    _Bool if_malloc;
    _Bool if_sid;
    unsigned int type;
    void *value;
    struct stack_node *next;
} SNode;

typedef struct stack{
    SID *s_id;
    unsigned long long length;
    SNode *top;
    _Bool if_sid;
} Stack;

typedef struct tree_node
{
    SID *s_id;
    List *home;
    struct tree_node *father;
    Node *room;
    unsigned long long child_num;
    unsigned int type;
    void *value;
    _Bool if_malloc;
    _Bool if_sid;
}TNode;

typedef struct tree
{
    SID *s_id;
    _Bool if_sid;
    TNode *root;
}Tree;

typedef struct file_head{
    char head_test[18];
    unsigned long long data_num;
}F_HEAD;

typedef struct data_file{
    FILE *fp;
    F_HEAD *pf_head;
    List *pf_stdlst;
}D_FILE;

typedef struct standard_data_blocks{
    unsigned int type;
    char *sid;
    _Bool if_data;
    unsigned int blocks_num;
    char *buff;
}STD_BLOCKS;

typedef struct standard_data_connection{
    char *f_sid;
    char *s_sid;
}STD_CTN;

typedef struct standard_data_head{
    unsigned long long data_blk_num;
    unsigned long long data_ctn_num;
}STD_HEAD;

typedef struct standard_data{
    SID *s_id;
    unsigned int type;
    _Bool lock;
    List *pd_blocklst;
    List *pd_ctnlst;
}STD_DATA;

#endif /* type_h */
