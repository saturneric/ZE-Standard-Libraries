#ifndef error_h
#define error_h

#include <type.h>

/*
 *错误管理中信息的管理及操作的结构
 */
typedef struct Info{
    char head[64];//信息头
    char body[256];//信息内容
}Info;

/*
 *错误管理中错误的管理及操作的结构
 */
typedef struct Error{
    unsigned int type;//错误类型号
    int priority;//优先级
    time_t time;//错误产生的时间
    Info info;//信息指针
}Error;

/*
 *错误管理中警告的管理及操作的结构
 */
typedef struct Notice{
    unsigned int type;//警告类型号
    time_t time;//警告产生的时间
    Info info;//信息指针
}Notice;

/***********************************************
 *错误的提示:出现错误时,以下函数用于快捷地通报错误信息,
 *         以便根据信息快速找到错误原因.
 **********************************************/

extern int pushInfo(Info *p_info, const char *head,const char *body);

extern Error *pushError(unsigned int type, int pri, Info *p_info);

extern Notice *pushNotice(unsigned int type, Info *p_info);

extern Info *initInfo(const char *head, const char *body);

extern Error *createError(Info *info,unsigned int type,int pri);

extern Notice *createWarning(Info *info, unsigned int type, int pri);

extern int showError(Error *);

extern int showWarning(Notice *);

#endif /* error_h */
