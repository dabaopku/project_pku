#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
# define MAXLEN 1000000000
int main()
{
	int max=0,i,j,k,l,farm[2005],road[10005][3],n,m,min;
	bool visited[2005]={0};
	cin>>n>>m;
	for(i=0;i<=n;i++)
		farm[i]=INT_MAX;
	for(i=0;i<m;i++)
		cin>>road[i][0]>>road[i][1]>>road[i][2];
	visited[1]=true;
	k=1;						//当前节点
	for(i=1;i<n;i++){			//寻找每个节点的最近节点
		min=INT_MAX;
		for(j=0;j<m;j++){
			if(road[j][0]==k && !visited[road[j][1]] && farm[road[j][1]]>road[j][2]){
				farm[road[j][1]]=road[j][2];
				if(min>road[j][2]){
					min=road[j][2];
					
				}
			}
			else if(road[j][1]==k && !visited[road[j][0]] && farm[road[j][0]]>road[j][2]){
				farm[road[j][0]]=road[j][2];
				if(min>road[j][2]){
					min=road[j][2];
					
				}
			}
		}
		min=INT_MAX;
		for(l=1;l<=n;l++){
			if(visited[l]) continue;
			if(farm[l]<min){
				min=farm[l];
				k=l;
			}
		}
		visited[k]=true;
	}
	for(i=2;i<=n;i++)
	{
		if(farm[i]!=INT_MAX && farm[i]>max) max=farm[i];
	}
	cout<<max<<endl;
}
