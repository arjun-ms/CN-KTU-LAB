
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	int clientSocket;
	char buffer[1024],fname[1024];
	struct sockaddr_in serverAddr;
	socklen_t addrSize;
	FILE *fp;
	
	clientSocket = socket(AF_INET,SOCK_STREAM,0);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
	
	
	addrSize = sizeof(serverAddr);
	connect(clientSocket,(struct sockaddr *)&serverAddr,addrSize);
	printf("Connected");
	
	printf("\nEnter the (from) file: ");
	scanf("%s",buffer);
	
	printf("Enter the (to) file: ");
	scanf("%s",fname);
	
	//sending from file name to open
	send(clientSocket,buffer,1024,0);
	
	fp = fopen(fname,"w");
	while(1){
		// recieve contents
		recv(clientSocket,buffer,1024,0);
		if (strcmp(buffer, "completed") == 0)
        {
            printf("\nFile Transferred \n");
            break;
        }
        //write contents into file fp
		fprintf(fp,"%s",buffer);
		printf("%s",buffer);
	}
	
	
	return 0;
}
