#ifndef TEST_H
#define TEST_H

#include <sys/time.h>

#include "type/type.h"
#include "list/list_expand.h"
#include "stack/stack_expand.h"
//#include "tree/tree_expand.h"
#include "communicate/communicate.h"

int stack(void);
int list(void);
int tree(void);
int time_avg(void);

#endif // TEST_H
