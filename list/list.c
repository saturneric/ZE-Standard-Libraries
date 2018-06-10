/* ********************************************************
 * This file is used to test the header file(list.h).
 * When the project is finished, this file will be deleted.
 * This file create by saturneric at 20:04 on Feb 7th.
 * *******************************************************/

#include "list.h"
#include "list_expand.h"

int main(int argc, char **argv){	
	rand_init();
	List *t_list = init_list();
	
	/*for(int i = 0; i < 9; i++){
		Node *t_node = init_node();
		int *t_i = (int *)malloc(sizeof(int));
		*t_i = i;
        initMallocValue(t_node,"int",(void *)t_i);
		insertInTail(t_list,t_node);
	}*/
	
	/*Node *t_node = init_node();
	insertInTail(t_list,t_node);
	initMalllocValue(t_node,(void *)"there");*/
    
    for(int i = 0; i < 12; i++){
        insertInHead(t_list, nodeWithInt(i));
    }
    
    
    Node *t_node = nodeWithComplex();
    addIntForComplex(t_node, 32);
    addIntForComplex(t_node, 64);
    insertInTail(t_list, t_node);
    insertInTail(t_list, nodeWithDouble(32.5));
    insertInTail(t_list, nodeWithString("There"));
    printNodeInfo(findByString(t_list, "There"), 0);
    printListInfo(t_list,0);
    printList(t_list);
    printf("\n");
    releaseList(t_list);
	
	return 0;
}
