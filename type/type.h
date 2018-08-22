#ifndef type_h
#define type_h

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdarg.h>

/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
*/
 
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
#define MESSAGE 15
#define HOLE 16
#define ULLINT 17

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
#define SID_LEN 33
#define FILE_TSET_LEN 18
#define HEAD_TEST_LEN 9
#define INFO_TEST_LEN 8
#define ENABLE_LIST_QUICK 65535
#define FN_NODE_SPARE 500
#define INDEX_CHANGE_MAX 500
#define INDEX_DISTANCE_MAX 120
#define STD_TEXT_LEN 4

#define HIGH 0x3
#define STANDARD 0x2
#define LOW 0x1

#define ABS(x) ((x>0)?(x):(-x))

typedef struct md5_ctx{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;

struct sid_raw{
    unsigned int type;
    unsigned int *value;//4
    unsigned int *value_deeper;//8
    unsigned int *value_deepest;//32
};

typedef struct s_id{
    struct sid_raw *sr;
    unsigned int deep;
    MD5_CTX *md5;
    unsigned char *decrypt_hex;
    char *decrypt_str;
    
}SID;

typedef struct Node{
    unsigned long long f_number;
    unsigned int type;
    void *value;
    struct Node *next;
    struct Node *last;
    SID *s_id;
} Node;

typedef struct simple_Node{
    void *value;
    struct simple_Node *next;
}s_Node;

struct lst_std_id{
    unsigned long long start_idx;
    unsigned long long end_idx;
    SID *sid;
};

struct list_quick;

typedef struct List{
    Node *head;
    Node *tail;
    s_Node *s_head;
    s_Node *s_tail;
    struct list_quick *p_lq;
    unsigned long long length;
    SID *s_id;
} List;

struct index_change{
    unsigned long long c_index;
    int f_count;
};

struct list_quick{
    Node **fn_node;
    _Bool if_sort;
    unsigned int idxc_count;
    unsigned long long fn_len;
    struct index_change *idxc_lst[INDEX_CHANGE_MAX];
    unsigned long long rlst_len;
    FILE *fp;
    List *stdid_lst;
};

typedef struct Info{
    char head[64];
    char body[256];
}Info;

typedef struct Error{
    unsigned int type;
    int priority;
    time_t time;
    Info info;
}Error;

typedef struct Notice{
    unsigned int type;
    time_t time;
    Info info;
}Notice;

typedef struct Log{
    FILE *fp;
    int if_enable;
    unsigned long int id;
}Log;

typedef struct stack_node{
    unsigned int type;
    void *value;
    struct stack_node *next;
    SID *s_id;
} SNode;

typedef struct stack{
    unsigned long long length;
    SNode *top;
    SID *s_id;
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
}TNode;

typedef  struct simple_tree_node{
    void *value;
    struct simple_tree_node *childs[2];
}s_TNode;

typedef struct tree
{
    SID *s_id;
    TNode *root;
    s_TNode *s_root;
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
    unsigned long long location;
    char *sid;
    _Bool if_data;
    unsigned int blocks_num;
    char *buff;
}STD_BLOCKS;

typedef struct standard_data_connection{
    unsigned long long location;
    char *f_sid;
    char *s_sid;
}STD_CTN;

typedef struct standard_data_head{
    unsigned long long data_blk_num;
    unsigned long long data_ctn_num;
}STD_HEAD;

typedef struct standard_data{
    SID *s_id;
    int read_data;
    unsigned int type;
    unsigned long long size;
    unsigned long long location;
    _Bool lock;
    List *pd_blocklst;
    List *pd_ctnlst;
}STD_DATA;

#endif /* type_h */
