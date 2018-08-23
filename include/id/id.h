#ifndef id_h
#define id_h

#include <type.h>
#include <id/md5.h>


/*
 *SID的初始值管理及操作的结构
 */
struct sid_raw{
    unsigned int type;
    unsigned int *value;//4
    unsigned int *value_deeper;//8
    unsigned int *value_deepest;//32
};

/*
 *SID的管理及操作的结构
 */
typedef struct s_id{
    struct sid_raw *sr;//指向SID初始值
    unsigned int deep;//SID初始值的复杂度
    MD5_CTX *md5;//指向MD5结构
    unsigned char *decrypt_hex;//指向MD5的Hex信息
    char *decrypt_str;//指向MD5的Hex信息转化成的字符串
    
}SID;




/************************************************
 初始化: 初始化有关函数
 ************************************************/

/*
 *获得一个新的SID
 *参数: deep_level指示原始ID的复杂度,type指示SID所绑定的数据结构的数据类型
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern SID *getS_id(unsigned int type, unsigned int deep_level);

/*
 *通过SID原始数据转换而成的字符串形式的MD5获得一个新的SID
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern SID *setS_idWithString(char *);

/*
 *获得一个新的ID
 */
extern unsigned long long getId(void);





/************************************************
 比较: ID的比较函数
 ************************************************/

/*
 *比较两个SID
 *返回: 返回strcmp风格的返回值
 */
extern int fitS_id(SID * const fs_id, SID * const ss_id);\

/*
 *比较两个SID
 *返回: 相同返回1,不相同返回0
 */
extern int simFitS_id(SID * fs_id, SID * ss_id);





/************************************************
 比较: ID的转换函数
 ************************************************/

/*
 *将SID中的Hex形式的MD5数据转化成字符串形式的MD5
 */
extern void setSidToASCIIString(SID * const s_id);

char *s_idToASCIIString(SID * const s_id);



/************************************************
 复制: 复制ID的函数
 ************************************************/

/*
 *复制一个既有的SID,得到一个相同的崭新的SID
 */
extern SID *copyS_id(SID *f_sid);





/************************************************
 释放: 释放ID的函数
 ************************************************/

/*
 *释放SID原始数据所占的内存空间
 */
extern int freeSidRaw(SID *s_id);

/*
 *释放SID所有已占用的内存空间
 */
extern int freeS_id(SID *s_id);





#endif /* id_h */
