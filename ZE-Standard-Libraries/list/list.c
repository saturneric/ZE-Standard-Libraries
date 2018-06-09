/* ********************************************************
 * This file is used to test the header file(list.h).
 * When the project is finished, this file will be deleted.
 * This file create by saturneric at 20:04 on Feb 7th.
 * *******************************************************/

#include "list.h"

int main(int argc, char **argv){	
	rand_init();
	safeMode(1);
	List *t_list = init_list();
	
	for(int i = 0; i < 9; i++){
		Node *t_node = init_node();
		int *t_i = (int *)malloc(sizeof(int));
		*t_i = i;
		init_value(t_node,"int",(void *)t_i);
		insertInTail(t_list,t_node);
	}
	
	/*Node *t_node = init_node();
	insertInTail(t_list,t_node);
	init_value(t_node,(void *)"there");*/
	
	int *f_i = (int *)malloc(sizeof(int));
	*f_i = 3;
    //releaseMalloc();
	releaseAll();
	
	return 0;
}
