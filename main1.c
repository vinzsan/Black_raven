#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <pthread.h>
#include <poll.h>
#include <netdb.h>

#define PORT 3000

int main(int argc,char **argv){
    struct addrinfo addr,*res;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        perror("Error made socket");
        return -1;
    }
    addr.ai_family = AF_INET;
    addr.ai_socktype = SOCK_STREAM;
    
    setsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,&(int){1},sizeof(int));
    int retval = getaddrinfo("google.com",NULL,&addr,&res);
    if(retval != 0){
        fprintf(stderr,"Error getaddrinfo %s",gai_strerror(retval));
        freeaddrinfo(res);
        return -1;
    }
    struct sockaddr_in *ip_conv = (struct sockaddr_in *)res->ai_addr;
    freeaddrinfo(res);
    ip_conv->sin_family = AF_INET;
    ip_conv->sin_port = htons(80);
    memset(&ip_conv->sin_zero,0,sizeof(ip_conv->sin_zero));
    socklen_t addrlen = sizeof(*ip_conv);
    if(connect(sockfd,(struct sockaddr *)ip_conv,addrlen) < 0){
        perror("Error connect");
        close(sockfd);
        return -1;
    }
    char ip_buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET,&ip_conv->sin_addr,ip_buffer,sizeof(ip_buffer));
    char header[128];
    snprintf(header,sizeof(header),"GET / HTTP1.1\r\nHost : %s\r\nConnection: close\r\n\r\n",ip_buffer);
    header[sizeof(header) - 1] = '\0';
    send(sockfd,header,sizeof(header),0);
    void *buffer = malloc(1024 * sizeof(char));
    if(buffer == NULL){
        perror("Error made buffer");
        close(sockfd);
        return -1;
    }
    size_t max = recv(sockfd,(char *)buffer,1024 * sizeof(char),0);
    write(STDOUT_FILENO,buffer,max);
    free(buffer);
    close(sockfd);
    return 0;
}