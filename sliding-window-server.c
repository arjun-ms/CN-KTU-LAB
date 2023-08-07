
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define SIZE 4
int main(){
    int welcomeSocket,newSocket;
    char buffer[1024],str[1024],temp[1024];
    struct sockaddr_in serverAddr;
    socklen_t addrSize;

    welcomeSocket = socket(AF_INET,SOCK_STREAM,0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7898);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
    bind(welcomeSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr));

    if(listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error");

    addrSize = sizeof(serverAddr);

    newSocket = accept(welcomeSocket,(struct sockaddr *)&serverAddr,&addrSize);
    printf("Connected\n");
    
    printf("Enter a string: ");
    scanf("%s",str);
    
    int i=0;
    while(i<strlen(str)){
		memset(buffer,0,sizeof(buffer));
		//slicing
		strncpy(buffer,str+i,SIZE);
		
		//converting int to str
		int n=strlen(buffer);
		for(int j=0;j<n;j++){
			sprintf(temp,"%d",i+j);
			//concatinating
			strcat(buffer,temp);
		}

		printf("\nFRAME TRANSMITTED: %s\n",buffer);
		
		//sending
		send(newSocket,buffer,1024,0);
		
		//recieve status of error
		recv(newSocket,buffer,1024,0);
		int choice = atoi(buffer);
		//No error
		if (choice==0){
			printf("\nTransmission is successfull \n");
			i += SIZE;
		}
		else{
			printf("\nError in frame %d",choice);
			i = choice;
		}
	}
	
	strcpy(buffer,"exit");
	send(newSocket,buffer,1024,0);
	
	printf("Exiting\n");

    return 0;
}
