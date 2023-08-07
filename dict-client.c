#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addrSize;
	
	clientSocket = socket(AF_INET,SOCK_STREAM,0);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
	
	addrSize = sizeof(serverAddr);
	connect(clientSocket,(struct sockaddr*)&serverAddr,addrSize);
	printf("Connected");
	
	while(1){
		printf("\nWord: ");
		scanf("%s",buffer);
		send(clientSocket,buffer,sizeof(buffer),0);

		if(strcmp(buffer,"exit")==0)
			exit(0);

		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("Meaning: %s\n",buffer);
		
		recv(clientSocket,buffer,sizeof(buffer),0);
		printf("Antonym: %s\n",buffer);
	}
	

}
