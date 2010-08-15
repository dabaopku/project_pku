#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
int m,n;
int path[202][202];
int flow;
int que[505],pre[205];
int top,tail;
int cur;
bool used[202];
int main()
{
	int i,j;
	int t1,t2;
	while(scanf("%d%d",&n,&m)==2){
	flow=0;
	memset(path,0,sizeof(path));
	top=0;
	for(i=0;i<n;i++){
		scanf("%d%d%d",&t1,&t2,&j);
		path[t1][t2]+=j;
	}
	do{
		
		memset(used,false,sizeof(used));
		top=0;
		tail=1;
		que[1]=1;
		while(top!=tail){
			cur=que[++top];
			if( path[cur][m]) {
				tail++;
				pre[m]=cur;
				break;
			}
			for(i=m-1;i>=1;i--){
				if(!used[i] && path[cur][i]){
					que[++tail]=i;
					pre[i]=cur;
					used[i]=true;
				}
			}
			if(top==tail) break;
			used[cur]=true;
		}
		if(top==tail) break;
		int min=INT_MAX;
		for(i=m;i!=1;i=pre[i]){
			if(path[pre[i]][i]<min) min=path[pre[i]][i];
		}
		for(i=m;i!=1;i=pre[i]){
			path[pre[i]][i]-=min;
			path[i][pre[i]]+=min;
		}
		flow+=min;
	}while(1);
	printf("%d\n",flow);
	}
}