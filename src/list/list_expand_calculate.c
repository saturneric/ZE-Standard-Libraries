#include <type.h>
#include <list/list_type.h>

/**
 计算链表占用的内存空间大小，以字节为单位输出。

 @param p_list 指向目标链表的指针
 @return 以字节为单位返回链表及链表内包含的节点所占的内存空间
 */
uint64_t calListMemory(List * p_list){
    Node *p_node = p_list->head;
    uint64_t nodes_size = 0LL;
    uint64_t list_size = sizeof(p_list);
    while(p_node != NULL){
        nodes_size += sizeof(p_node);
        p_node = p_node->next;
    }
    return  list_size + nodes_size;
}
