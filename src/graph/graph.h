#ifndef GRAPH_H
#define GRAPH_H

#include "../list/list_expand.h"

typedef struct GNode{
    SID *s_id;
	void *value;
	List *routes;
	int if_setValue;
}GNode;

typedef struct route{
    SID *s_id;
	double distance;
	int if_setValue;
	GNode from, to;
}Route;

GNode *initGNode(void);
Route *initRoute(void);


#endif
