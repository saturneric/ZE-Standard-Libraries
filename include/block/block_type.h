#ifndef block_type_h
#define block_type_h

#include<type.h>
#ifdef id_enable
#include <id/id.h>
#endif

/*
 *块的管理及操作的结构
 */
typedef struct block{
    uint64_t size;
    uint32_t carve;
    void *data;
#ifdef id_enable
    SID *s_id;//栈节点的ID
#endif
} SNode;


#endif /* block_type_h */
