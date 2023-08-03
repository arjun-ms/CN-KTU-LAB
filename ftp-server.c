#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	int welcomeSocket,newSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addrSize;
	FILE *fp;
	
	welcomeSocket = socket(AF_INET,SOCK_STREAM,0);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
	
	bind(welcomeSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	
	if(listen(welcomeSocket,5)==0){
		printf("Listening...\n");
	}
	else{
		printf("Error...\n");
	}
	
	addrSize = sizeof(serverAddr);
	newSocket = accept(welcomeSocket,(struct sockaddr *)&serverAddr,&addrSize);
	printf("Connected");
	
	//recieveing from file name to open
	recv(newSocket,buffer,1024,0);
	
	fp = fopen(buffer,"r");
	
	//read contents inside the file and send it
	while(fgets(buffer,sizeof(buffer),fp)){
		send(newSocket,buffer,1024,0);
	}
	
	strcpy(buffer,"completed");
	send(newSocket,buffer,1024,0);
	return 0;
}
