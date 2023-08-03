#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){
	int welcomeSocket,newSocket,found = 0,pos = -1;
	char buffer[1024];
	char dict[7][3][1024]={
		{"artificial", "made or produced by human beings rather than occurring naturally.","natural"},
		{"despair", "the complete loss or absence of hope.", "hope"},
		{"humble", "having or showing a modest or low estimate of one's importance.", "proud"},
		{"love", "an intense feeling of deep affection.", "hatred"},
		{"optimistic", "hopeful and confident about the future.", "pessimistic"},
		{"real", "actually existing as a thing or occurring in fact.", "imaginary"},
		{"vice", "immoral or wicked behaviour.", "virtue"}
	};
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
	
	while(1){
		recv(newSocket,buffer,sizeof(buffer),0);
		if(strcmp(buffer,"exit")==0)
			exit(0);
		printf("\nWord: %s",buffer);
		
		for(int i=0;i<7;i++){
			if(strcmp(buffer,dict[i][0])==0){
				found = 1;
				pos = i;
				break;
			}
		}
		if(found==1){
			strcpy(buffer,dict[pos][1]);
			send(newSocket,buffer,sizeof(buffer),0);
			strcpy(buffer,dict[pos][2]);
			send(newSocket,buffer,sizeof(buffer),0);
			found=0;
		}
		else{
			strcpy(buffer,"NOT FOUND");
			send(newSocket,buffer,sizeof(buffer),0);
			send(newSocket,buffer,sizeof(buffer),0);
		}
	}
	

}
