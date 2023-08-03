	#include <stdio.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>

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
		
		while(1){
			printf("your message: ");
			fgets(buffer,100,stdin);
			send(clientSocket,buffer,strlen(buffer),0);
		}
		

	}
