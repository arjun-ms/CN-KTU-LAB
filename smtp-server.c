#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
	int welcomeSocket,newSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addrSize;
	
	welcomeSocket = socket(AF_INET,SOCK_STREAM,0);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
	bind(welcomeSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	
	if(listen(welcomeSocket,5)==0)
		printf("Listening\n");
	else
		printf("Error");
	
	addrSize = sizeof(serverStorage);
	newSocket = accept(welcomeSocket,(struct sockaddr*)&serverStorage,&addrSize);
	printf("Connected\n");
	
	recv(newSocket,buffer,1024,0);
	printf("FROM: %s\n",buffer);
	recv(newSocket,buffer,1024,0);
	printf("TO: %s\n",buffer);
	recv(newSocket,buffer,sizeof(buffer),0);
	printf("MAIL Content: %s\n",buffer);
	

}

