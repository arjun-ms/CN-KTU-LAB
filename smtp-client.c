
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
	int clientSocket;
	char from[20],to[20],message[1000],c;
	struct sockaddr_in serverAddr;
	socklen_t addrSize;
	
	clientSocket = socket(AF_INET,SOCK_STREAM,0);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
	
	addrSize = sizeof(serverAddr);
	connect(clientSocket,(struct sockaddr*)&serverAddr,addrSize);
	
	printf("Enter from address mail: ");
	scanf("%s",from);
	send(clientSocket,from,sizeof(from),0);
	
	printf("\nEnter to address mail: ");
	scanf("%s",to);
	send(clientSocket,to,sizeof(to),0);
	
	printf("Enter mail content: \n");
	while((c=getchar())!= '\n'){}
	// memset(message,0,sizeof(message));
	fgets(message,sizeof(message),stdin);

	send(clientSocket,message,sizeof(message),0);
	
	printf("\nMAIL SENT");
}
