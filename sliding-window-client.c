#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SIZE 4

int main(){
	
	int clientSocket;
	int choice;
	char str[20],err[20];
	struct sockaddr_in serverAddr;
	//socklen_t addrSize;
	
	clientSocket = socket(AF_INET,SOCK_STREAM,0);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//memset(serverAddr,0,sizeof(serverAddr))
	
	//addrSize = sizeof(clientAddr);
	connect(clientSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
		
	for(;;){
		read(clientSocket,str,20);
		if(strcmp(str,"exit")==0){
			break;
		}
		printf("\nReceived: %s\n1. Do you want to report an error? (1-Yes, 0-No): ", str);

		scanf("%d", &choice);

		if (!choice)

			write(clientSocket, "-1", sizeof("-1"));

		else {

			printf("Enter the sequence number of the frame where the error has occurred: ");

			scanf("%s", err);

			write(clientSocket, err, sizeof(err));

		}
	}
		close(clientSocket);

		return 0;
}
