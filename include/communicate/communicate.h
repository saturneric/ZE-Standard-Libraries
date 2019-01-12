#ifndef communicate_h
#define communicate_h

#include <communicate/communicate_type.h>





/************************************************
 消息的操作: 消息的操作相关函数
 ************************************************/

/*
 *创建消息
 *返回: 处理成功则返回指向相关结构体所在内存空间的指针,不成功则返回NULL.
 */
extern MSG *createMessage(char *title, void *data, unsigned long data_size);

/*
 *通过ipv4地址发送消息
 *返回: 处理成功则返回0,不成功则返回-1.
 */
extern int sendMessageIPv4(MSG *p_msg, char *ip, unsigned int port);




#endif /* communicate_h */
