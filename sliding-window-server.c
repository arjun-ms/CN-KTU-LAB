#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SIZE 4

int main(){
	
	int welcomeSocket,newSocket;
	int i=0,j,status;
	char str[20],frame[20],ack[20];
	struct sockaddr_in serverAddr,clientAddr;
	socklen_t addrSize;
	
	welcomeSocket = socket(AF_INET,SOCK_STREAM,0);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//memset(serverAddr,0,sizeof(serverAddr))
	
	bind(welcomeSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	
	if (listen(welcomeSocket,5)<0){
		printf("Error\n");
	}
	
	addrSize = sizeof(clientAddr);
	newSocket= accept(welcomeSocket,(struct sockaddr *)&clientAddr,&addrSize);
	
	printf("Enter text: ");
	scanf("%s",str);
	
	while(i<strlen(str)){
		//strncpy is a function used to copy a specified 
		//number of characters from one string to another.
		//char *strncpy(char *destination, const char *source, size_t num);
		
		strncpy(frame,str+i,20);
		int len = strlen(frame);
		
		//for (j=0;j<len;j++){
			//sprintf(temp,"%d",i+j);
			//strcat(frame,temp);
		//}
		
		for (j = 0; j < len; j++) {
            sprintf(frame + len, "%d", i + j);
        }
		
		printf("Frame transmitted: %s\n",frame);
		
		write(newSocket,frame,sizeof(frame));
		read(newSocket,ack,20);
		sscanf(ack,"%d",&status);
		
		if (status==-1){
			printf(">> Transmission successful.\n");
			i += 20;
		}
		else{
			printf(">> Recieved error in %d.\n",status);
			i=status;
		}
		printf("\n");
	}
	write(newSocket,"exit",sizeof("exit"));
	printf("Exiting...");
	sleep(2);
	close(newSocket);
	close(welcomeSocket);
	return 0;
	
}
