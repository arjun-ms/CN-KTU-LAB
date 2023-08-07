
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int welcomeSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addrSize;

    welcomeSocket = socket(AF_INET,SOCK_DGRAM,0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7551);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
    bind(welcomeSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr));

    if(listen(welcomeSocket,5)<0)
        printf("Listening\n");
    else
        printf("Error");

    addrSize = sizeof(serverAddr);
	
    recvfrom(welcomeSocket,buffer,1024,0,(struct sockaddr *)&serverAddr,&addrSize);
    printf("IP: %s",buffer);

}
