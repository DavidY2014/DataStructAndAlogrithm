#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>
using namespace std;

#define SERV_PORT 9001

int main(){
    int listenfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int result;
    result = bind(listenfd,(struct  sockaddr*)&serv_addr,sizeof(serv_addr));
    if(result == -1){
        char *perrorinfo = strerror(errno);
        printf("bind 返回值为%d,错误码为%d,错误信息为%s",result,errno,perrorinfo);
        return -1;
    }
    result = listen(listenfd,32);
    if(result == -1){
        char *perrorinfo = strerror(errno);
        printf("bind 返回值为%d,错误码为%d,错误信息为%s",result,errno,perrorinfo);
        return -1;
    }

    int connfd;
    const char* pcontent ="I send sth to client";

    for(;;){
        connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
        char recvline[1000+1];
        read(connfd,recvline,1000);
        printf("服务器给客户发送了一个消息");
        write(connfd,pcontent,strlen(pcontent));
        close(connfd);
    }
    close(listenfd);

    return 0;
}