
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){
    int clientSocket;
    char buffer[1024];
    int choice;
    struct sockaddr_in serverAddr;
    socklen_t addrSize;

    clientSocket = socket(AF_INET,SOCK_STREAM,0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7898);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));

    addrSize = sizeof(serverAddr);
    connect(clientSocket,(struct sockaddr *)&serverAddr,addrSize);
    printf("Connected\n");

	while(1){
		recv(clientSocket,buffer,1024,0);

		if (strcmp(buffer,"exit")==0){
			printf("Exiting..\n");
			exit(0);
		}
		
		printf("Frame Recieved : %s\n",buffer);
		
		printf("If there is error - (0-no , 1-yes): ");
		scanf("%d",&choice);
		
		
		if (choice==0){
			strcpy(buffer,"0");
			send(clientSocket,buffer,1024,0);
		}
		else{
			printf("\nEnter the frame where error is found: ");
			scanf("%s",buffer);
			send(clientSocket,buffer,1024,0);
		}
	}
    
}
