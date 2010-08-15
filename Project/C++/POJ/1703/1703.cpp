
#include "stdio.h"
#include "iostream"
using namespace std;
struct Node
{
	Node * parent;
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
			
			Node *temp1,*temp2;
			int t1=0,t2=0;
			temp1=&cri[n1];
			while(temp1->parent){
				t1+=temp1->num;
				temp1=temp1->parent;
				
			}
			temp2=&cri[n2];
			while(temp2->parent){
				t2+=temp2->num;
				temp2=temp2->parent;
			}
			
			if(cmd=='D'){
				if(temp2!=temp1){
				temp2->parent=temp1;
				temp2->num=(t2-t1+1)%2;
				}
			}
			else{
				if(temp2!=temp1)
					printf("Not sure yet.\n");
				else if((t2-t1)%2)
					printf("In different gangs.\n");
				else printf("In the same gang.\n");
			}
		}

	}
}