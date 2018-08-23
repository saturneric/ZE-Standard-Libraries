#ifndef id_h
#define id_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../type/type.h"
#include "md5.h"





/************************************************
 伪随机数初始化: 伪随机数初始化有关函数
 ************************************************/

/*
 *用当前时间初始化伪随机数发生器
 */
static void init_rand(void);





/************************************************
 初始化: 初始化有关函数
 ************************************************/

/*
 *为一个新的SID管理结构分配内存空间
 *参数: deep_level指示原始ID的复杂度
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
static SID *initS_id(unsigned int deep_level);

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
 *获得一个新的SID原始数据
 */
static void getRawS_id(SID *s_id, unsigned int type, unsigned int deep_level);

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
 *将原始SID数据转化成字符串
 *返回: 执行成功相关字符串,不成功则返回NULL
 */
static char *s_idToASCIIRawString(SID * const s_id);

/*
 *将SID中的Hex形式的MD5数据转化成字符串形式的MD5
 */
extern void setSidToASCIIString(SID * const s_id);

/*
 *将原始SID数据转换成的SID转化回原始SID数据
 *返回: 执行成功相关指向数据结构内存空间的指针,不成功则返回NULL
 */
static SID *asciiRawStringToS_id(char * const string);

/*
 *将原始SID数据转化成MD5的Hex形式的数据
 */
static void s_idToMD5(SID *s_id);

/*
 *将10进制数字,转化成字符型的16位进制数字
 */
static char hexToChar(unsigned int);





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





/************************************************
 相关全局变量
 ************************************************/

static _Bool if_rand;




#endif /* id_h */
