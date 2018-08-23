#ifndef list_simple_h
#define list_simple_h

#include <list/list_type.h>


/************************************************
 *单向节点的快速初始化: 为新节点分配内存空间,
 *                  并使用输入值对其进行初始化.
 ************************************************/

/*
 *为新单向节点获取内存空间, 并使用整型值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithInt(int);

/*
 *为新单向节点获取内存空间, 并使用无符号整型值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithUInt(unsigned int);

/*
 *为新单向节点获取内存空间, 并使用浮点值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithDouble(double);

/*
 *为新单向节点获取内存空间, 并使用字符串值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithString(const char *);

/*
 *为新单向节点获取内存空间, 并使用指针值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithPointer(const void *);


/*
 *初始化单向链表节点,该种类节点可以与普通储存在List结构中.
 *单向链表的引入主要在于对于简单问题提供更小开销的解决方案.但相应的操作函数较少,不如一般链表方便.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern s_Node *s_initNode(void);

/*在单项链表的头部插入一个节点
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int s_insertInHead(List *p_list, s_Node *s_p_node);

/*
 *在单项链表的尾部插入一个节点
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int s_insertInTail(List *p_list, s_Node *s_p_node);

/*
 *释放单向节点所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseNode(s_Node *s_p_node);

/*
 *释放单向链表所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseList(List *p_list);

/*
 *自定义释放单向链表所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放节点时调用,
 *     接收储存在节点中的值的指针,释放用户自定义的结构体的所占用内存.
 *     回调函数返回0代表释放成功,返回-1代表释放失败.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseListForCustom(List *p_list, int (*func)(void *));

/*
 *自定义释放单向节点所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放单项节点时调用,
 *     接收储存在单项节点中的值得指针,释放用户自定义的结构体的所占用内存.
 *     回调函数返回0代表释放成功,返回-1代表释放失败.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseNodeForCustom(s_Node *s_p_node, int (*func)(void *));

#endif /* list_simple_h */
