#ifndef communicate_h
#define communicate_h

#include "../type/type.h"
#include "../list/list_expand.h"

D_FILE *initDataFileForWrite(char *route);
D_FILE *initDataFileForRead(char *route);
STD_BLOCKS *initStandardDBlocks(SID *p_sid, unsigned int type, unsigned long long data_size);
STD_CTN *initStandardDConnection(SID *f_sid, SID *s_sid);
STD_DATA *initStandardData(unsigned int type, SID *s_id);

int dataForStandardDBlock(STD_BLOCKS *p_stdb,void *data);
int dataFileAddStandardData(D_FILE *p_dfile, STD_DATA *p_std);
int standardDataAddBlock(STD_DATA *p_std, SID *p_sid ,unsigned int type, void *data, unsigned long long data_size);
int standardDataAddConnection(STD_DATA *p_std, SID *f_sid, SID *s_sid);
int dataFileWriteIn(D_FILE *p_dfile);
int dataFileReadOut(D_FILE *p_dfile);
__CALLBACK_STATE(dataFileReadOut);

int releaseSTDBlocks(STD_BLOCKS *p_stdb);
int releaseStandardData(STD_DATA *p_std);
int releaseSTDConnection(STD_CTN *p_stdc);
int releaseDFile(D_FILE *p_file);
unsigned long long calStandardData(STD_DATA *p_std);
__CALLBACK_STATE(calStandardDataCTN);
__CALLBACK_STATE(calStandardDataBLK);

__CALLBACK_STATE(StandardDataInfoWrite);
__CALLBACK_STATE(StandardDataWrite);
__CALLBACK_STATE(StandardDConnectionWrite);
__CALLBACK_STATE(StandardDBlockWrite);

STD_DATA *listToSTD(List *);
List *standardDataToList(STD_DATA *);
__CALLBACK_STATE(StandardDataToList);

int readDataFileInfo(D_FILE *p_dfile);
int readStandardData(D_FILE *p_dfile, STD_DATA *p_std);
int readSTDBlocks(STD_BLOCKS *p_stdb);
int checkIfDataFile(D_FILE *p_dfile);
int readStandardDataBySid(D_FILE *p_dfile, SID *p_sid);
__CALLBACK_STATE(findStandardDataBySid);

MSG *createMessage(char *title, void *data, unsigned long data_size);
int sendMessageIPv4(MSG *p_msg, char *ip, unsigned int port);
void printStandardData(void *value);
//STD_DATA *stackToSTD(Stack *);
//STD_DATA *treeToSTD(Tree *);

#endif /* communicate_h */
