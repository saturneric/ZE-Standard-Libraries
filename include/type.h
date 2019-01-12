#ifndef type_h
#define type_h

#define list_quick_enable
#define id_enable

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>

#ifdef UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif




/************************************************
 *库相关类型的编号
 ************************************************/

#define VOID 0
#define INT 1
#define DOUBLE 2
#define STRING 3
#define POINTER 4
#define LIST 5
#define TREE 7
#define LIST_NODE 8
#define TREE_NODE 9
#define STACK_NODE 10
#define T_SID 11
#define UINT 12
#define STANDARD_DATA 13
#define DATA_FILE 14
#define MESSAGE 15
#define ULLINT 17





/************************************************
 *库相关参数的定义
 ************************************************/

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
#define STD_TEXT_LEN 4
#define HIGH 0x3
#define STANDARD 0x2
#define LOW 0x1





/************************************************
 *库相关操作宏的定义
 ************************************************/

#define ABS(x) ((x>0)?(x):(-x))


#endif /* type_h */
