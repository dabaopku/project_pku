
#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;

bool key[1002][102]={0};
int m=0,n=0;
int initpig[1002]={0};
int customer[102][102]={0};
int maxflow=0;
int stack[202]={0};
int cur;
bool used[102]={0};
int top=0;
int main()
{
	int i,j,tmp1,tmp2;
	cin>>m>>n;
	for(i=1;i<=m;i++)
		cin>>initpig[i];
	for(i=1;i<=n;i++){
		cin>>tmp1;
		for(j=0;j<tmp1;j++){
			cin>>tmp2;
			key[tmp2][i]=true;
		}
		cin>>customer[i][n+1];
	}
	for(i=1;i<=m;i++){
		j=1;
		while(j<=n&&!key[i][j])
			j++;
		if(j<=n)
			customer[0][j]+=initpig[i];
	}
	for(i=1;i<=n;i++){
		if(customer[0][i]==0) continue;
		for(j=1;j<=m;j++){
			if(!key[j][i]) continue;
			for(int k=i+1;k<=n;k++){
				if(!key[j][k]) continue;
				customer[i][k]=INT_MAX;
			}
		}
	}
	while(true){
		memset(used,false,sizeof(used));
		top=-1;
		stack[++top]=0;
		cur=stack[top];
		used[0]=true;
		while(cur!=n+1){;
/*			if(customer[cur][n+1]!=0){
				cur=n+1;
				stack[++top]=cur;
				break;
			}*/
			for(i=1;i<=n+1;i++){
				if(customer[cur][i]==0 || used[i]) continue;
				cur=i;
				stack[++top]=cur;
				used[cur]=true;
				break;
			}
			if(i>n+1){
				if(top){
					cur=stack[--top];
				}
				else break;
			}
		}
		if(cur!=n+1) break;
		int minflow=INT_MAX;
		for(i=0;i<top;i++)
			if(customer[stack[i]][stack[i+1]]<minflow && customer[stack[i]][stack[i+1]]>0) minflow=customer[stack[i]][stack[i+1]];
		maxflow+=minflow;
		for(i=0;i<top;i++){
		if(customer[stack[i]][stack[i+1]]<INT_MAX) customer[stack[i]][stack[i+1]]-=minflow;
		
		if( customer[stack[i+1]][stack[i]]<INT_MAX ) customer[stack[i+1]][stack[i]]+=minflow;}
	}
	
	cout<<maxflow<<endl;
}