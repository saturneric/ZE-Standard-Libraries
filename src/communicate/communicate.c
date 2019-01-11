#include <type.h>
#include <id/id.h>
#include <list/list_type.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate.h>
#include <communicate/communicate_file.h>


MSG *createMessage(char *title, void *data, unsigned long data_size){
    MSG *p_msg = malloc(sizeof(MSG) + data_size);
    p_msg->p_sid = getS_id(MESSAGE, 1);
    p_msg->time = time(NULL);
    return p_msg;
}

/*int sendMessageIPv4(MSG *p_msg, char *ip, unsigned int port){
    int client_sockfd;
    struct sockaddr_in remote_addr;
    char buf[BUFSIZ];
    memcpy(buf, "ZEMSG", 5);
    memset(&remote_addr,0,sizeof(remote_addr));
    remote_addr.sin_family=AF_INET;
    remote_addr.sin_addr.s_addr=inet_addr(ip);
    remote_addr.sin_port=htons(port);
    client_sockfd=socket(PF_INET,SOCK_STREAM,0);
    connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr));
    send(client_sockfd,buf,strlen(buf),0);
    unsigned long bkmsg_len = 0;
    bkmsg_len = recv(client_sockfd, buf, BUFSIZ, 0);
    buf[bkmsg_len] = '\0';
    if(!strcmp(buf, "TITLE_REV_READY")){
        memcpy(buf, p_msg->titile, strlen(p_msg->titile));
        bkmsg_len = recv(client_sockfd, buf, BUFSIZ, 0);
        buf[bkmsg_len] = '\0';
        if(!strcmp(buf, "CONTENT_LEN_REV_READY")){
            memcpy(buf, (char *)p_msg->size, sizeof(unsigned int));
            send(client_sockfd,buf,sizeof(unsigned int),0);
            bkmsg_len = recv(client_sockfd, buf, BUFSIZ, 0);
            buf[bkmsg_len] = '\0';
            if(!strcmp(buf, "CONTENT_REV_READY")){
                memcpy(buf, p_msg->content, p_msg->size);
                send(client_sockfd,buf,p_msg->size,0);
                close(client_sockfd);
                return 0;
            }
        }
    }
    close(client_sockfd);
    return -1;
}*/
