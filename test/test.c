#include "test.h"


int list(void) {
    List *p_list = initList(1);
    for(int i = 0; i < 12; i++){
        insertInTail(p_list, nodeWithInt(i, 0));
    }
    D_FILE *pd_file = initDataFileForWrite("data.db");
    STD_DATA *p_std = listToSTD(p_list);
    STD_DATA *pa_std = listToSTD(p_list);
    dataFileAddStandardData(pd_file, p_std);
    dataFileAddStandardData(pd_file, pa_std);
    dataFileWriteIn(pd_file);
    releaseList(p_list);
    releaseDFile(pd_file);

	return 0;
}

/*int _useTreeThroughDown(TNode *p_tnode, unsigned long long height) {
	printTNode(p_tnode,0);
	return  0;
}*/

/*int tree(void) {
	TNode *t_tnode, *cr_tnode, *cl_tnode;
	Tree *t_tree;
	TNode *gs_tnode;
	safeModeForTree(1);
	t_tree = initTree();
	t_tnode = tnodeWithInt(1);
	cr_tnode = tnodeWithInt(3);
	cl_tnode = tnodeWithInt(2);
	addChildInRight(t_tnode, cl_tnode);
	addChildInRight(t_tnode, cr_tnode);
	addChildInRight(cl_tnode, tnodeWithInt(4));
	gs_tnode = tnodeWithInt(5);
	addChildInRight(cl_tnode,gs_tnode);
	addChildInRight(cr_tnode, tnodeWithInt(6));
	addChildInRight(cr_tnode, tnodeWithInt(7));
	addChildInRight(gs_tnode, tnodeWithInt(8));
	setRoot(t_tree, t_tnode);
	TreeThroughUp(t_tree, _useTreeThroughDown);
	//printTNodeWithFamily(t_tnode, 0);
	releaseAllForTree();
	return 0;
}*/


int main(int argc, char **argv) {
    while(1){
        List *p_list = initList(0);
        for(int i = 0; i < 65535; i++){
            insertInTail(p_list, nodeWithInt(i, 1));
        }
        releaseList(p_list);
    }
	return 0;
}
