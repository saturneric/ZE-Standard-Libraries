#include <type.h>
#include <error/error.h>

int pushInfo(Info *p_info, const char *head, const char *body) {
    strcpy(p_info->head, head);
    strcpy(p_info->body, body);
    return 0;
}

Error *pushError(unsigned int type, int pri, Info *p_info) {
    Error *p_error  = (Error *)malloc(sizeof(Error));
    p_error->type = type;
    p_error->priority = pri;
    p_error->info = *p_info;
    p_error->time = time(NULL);
    free(p_info);
    return p_error;
}

Notice *pushNotice(unsigned int type, Info *p_info) {
    Notice *p_notice = (Notice *)malloc(sizeof(Notice));
    p_notice->type = type;
    p_notice->info = *p_info;
    p_notice->time = time(NULL);
    free(p_info);
    return p_notice;
}

Info *initInfo(const char *head, const char *body){
    Info *p_info = (Info *)malloc(sizeof(Info));
    pushInfo(p_info, head, body);
    return p_info;
}

int showError(Error *p_error){
    printf("\n");
    for (int i = 0; i < p_error->priority; i++) {
        printf("!");
    }
    
    printf("(Error) %s\n",asctime(localtime(&p_error->time)));
    printf("%s: %s.\n",p_error->info.head,p_error->info.body);
    free(p_error);
    return 0;
}

int showWarning(Notice *p_notice){
    printf("\n@");
    printf("(Warning) %s\n",asctime(localtime(&p_notice->time)));
    printf("%s: %s.\n",p_notice->info.head,p_notice->info.body);
    free(p_notice);
    return 0;
}
