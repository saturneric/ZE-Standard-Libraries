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

int stack(void) {
	int i;
	Stack *t_stack = initStack();
	for (i = 0; i < 10; i++) {
		pushStack(t_stack, snodeWithInt(i));
	}
	for (i = 0; i < 10; i++) {
		printf("%d", getValueByIntForSNode(popStack(t_stack)));
	}
	releaseStack(t_stack);
	return 0;
}


int main(int argc, char **argv) {
    
    for (int i = 0; i < 65535; i++){
        list();
        /*D_FILE *p_dfile = initDataFileForRead("data.db");
        readDataFileInfo(p_dfile);
        SID *temp_sid =  setS_idWithString("f7dd8f0a75a0c20e4dca1b78347083cf");
        readStandardDataBySid(p_dfile, temp_sid);
        freeS_id(temp_sid);
        printListForCustom(p_dfile->pf_stdlst, printStandardData);
        List *t_list = standardDataToList(p_dfile->pf_stdlst->head->value);
        printList(t_list);
        releaseList(t_list);
        releaseDFile(p_dfile);*/
        usleep(500);
    }
	return 0;
}
