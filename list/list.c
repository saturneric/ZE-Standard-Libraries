/* ********************************************************
 * This file is used to test the header file(list.h).
 * When the project is finished, this file will be deleted.
 * This file create by saturneric at 20:04 on Feb 7th.
 * *******************************************************/

#include "list.h"
#include "list_expand.h"

int main(int argc, char **argv){	
	rand_init();
    safeMode(1);
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
        insertInTail(t_list, nodeWithInt(i));
    }
    
    
   
    printListInfo(t_list,0);
    printList(t_list);
    List *m_list;
    m_list = m_findByInt(t_list, 5);
    printList(m_list);
    printf("\n");
    
    releaseAll();
	
	return 0;
}
