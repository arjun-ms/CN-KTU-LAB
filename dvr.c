#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i,j,k,l,n;
int costMatrix[20][20];

struct Router{
	int dist[20];
	int nextHop[20];
}node[20];

void readCostMatrix(){
	printf("Enter the cost matrix");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&costMatrix[i][j]);
			if (i==j){
				costMatrix[i][j] = 0;
			}
			node[i].dist[j] = costMatrix[i][j];
			node[i].nextHop[j] = j;
		}
	}
}

void calculateDistance(){
	for (l=1;l<n;l++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				for(k=0;k<n;k++){
					if(node[i].dist[k]+node[k].dist[j] < node[i].dist[j]){
						node[i].dist[j] = node[i].dist[k]+node[k].dist[j];
						node[i].nextHop[j] = k;
					}			
				}
			}
		}
	}
}

void displayMatrix(){
	for(i=0;i<n;i++){
		printf("Router %d \n",i+1);
		
		for (j=0;j<n;j++){
			printf("Node %d via %d | distance = %d",j+1,node[i].nextHop[j]+1,node[i].dist[j]);
			printf("\n");
		}
	}
}

int main(){
	printf("Enter a number: ");
	scanf("%d",&n);
	readCostMatrix();
	calculateDistance();
	displayMatrix();
}
