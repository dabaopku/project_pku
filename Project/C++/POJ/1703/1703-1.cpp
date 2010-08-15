/*
#include "stdio.h"
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "iostream"
using namespace std;

struct Node
{
	int parent;
	int num;
};
int main()
{
	int cs;
	int n,m,i;

	Node cri[100001];

	scanf("%d",&cs);
	while(cs--){
		memset(cri,0,sizeof(cri));
		scanf("%d%d",&n,&m);
		char cmd;
		int n1,n2;

		for(i=0;i<m;i++){
			do{
				cmd=getchar();
			}while(cmd!='A' && cmd!='D');
			scanf("%d%d",&n1,&n2);

			int temp1,temp2;
			int t1=0,t2=0;
			temp1=n1;
			while(cri[temp1].parent){
				t1+=cri[temp1].num;
				temp1=cri[temp1].parent;
			}
			temp2=n2;
			while(cri[temp2].parent){
				t2+=cri[temp2].num;
				temp2=cri[temp2].parent;
			}
	
			if(cmd=='D'){
				if(temp2!=temp1){
					if(t1>t2){
						cri[temp2].parent=temp1;
						cri[temp2].num=(t1-t2+1)%2;
					}
					else{
						cri[temp1].parent=temp2;
						cri[temp1].num=(t2-t1+1)%2;
					}
				}
			}
			else{
				if(temp2!=temp1)
					printf("Not sure yet.\n");
				else if((t2-t1)%2==0)
					printf("In the same gang.\n");					
				else 
					printf("In different gangs.\n");
			}
		}
	}
}*/
