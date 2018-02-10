/* ********************************************************
 * This file is used to test the header file(list.h).
 * When the project is finished, this file will be deleted.
 * This file create by saturneric at 20:04 on Feb 7th.
 * *******************************************************/

#include "list.h"

int main(int argc, char **argv){	
	rand_init();
	List *t_list = init_list();
	
	for(int i = 0; i < 9; i++){
		Node *t_node = init_node();
		int *t_i = (int *)malloc(sizeof(int));
		*t_i = i;
		init_value(t_node,(void *)t_i);
		insertInTail(t_list,t_node);
	}
	int *f_i = (int *)malloc(sizeof(int));
	*f_i = 3;
	Node *f_node = findByValue(t_list,"int",(void *)f_i);
	releaseList(t_list);
		
	return 0;
}
