#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#ifdef DOMAIN_INET
#include<netinet/in.h>
#include<arpa/inet.h>
#endif

#ifdef DOMAIN_UNIX
#include<sys/un.h>

#define SOCK_PATH "server_socket"
#endif

int main(){
    int server_sockfd, client_sockfd;
    int server_len, client_len;

#ifdef DOMAIN_INET
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
#endif
    
#ifdef DOMAIN_UNIX
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    unlink(SOCK_PATH);
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, SOCK_PATH);
#endif

    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr*)&server_address, server_len);
    listen(server_sockfd, 5);
    while(1){
	char ch;
	printf("server waiting\n");
	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd,
		(struct sockaddr*)&client_address, &client_len);
	read(client_sockfd, &ch, 1);
        ch++;
	write(client_sockfd, &ch, 1);
	close(client_sockfd);
    }
    exit(0);
}
