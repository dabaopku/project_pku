#include "stdio.h"
#include "iostream"
#include "string.h"
#include "math.h"
#include "string"
#include "vector"
#include "set"
#include "map"
#include "queue"
#include "list"
#include "stack"

using namespace std;

int n;
short maze[2][20][20];
const int inf=100000;
const int dir[4][2]={1,0,0,1,-1,0,0,-1};
void init()
{
	cin>>n;
	int i,j;
	memset(maze,0,sizeof(maze));
	char ch;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			cin>>ch;
			if(ch=='w') maze[0][i][j]=1;
		}
}

int paint(int num)
{
	int i,j;
	i=1;
	int ans=0;
	while(num){
		if(num%2){
			ans++;
			for(int k=0;k<4;k++){
				maze[1][1+dir[k][0]][i+dir[k][1]]=1-maze[1][1+dir[k][0]][i+dir[k][1]];
			}
			maze[1][1][i]=1-maze[1][1][i];
		}
		num/=2;
		i++;
	}
	for(i=2;i<=n;i++){
		for(j=1;j<=n;j++){
			if(maze[1][i-1][j]){
				ans++;
				for(int k=0;k<4;k++){
					maze[1][i+dir[k][0]][j+dir[k][1]]=1-maze[1][i+dir[k][0]][j+dir[k][1]];
				}
				maze[1][i][j]=1-maze[1][i][j];
			}
		}
	}

	for(i=1;i<=n;i++){
		if(maze[1][n][i]) return inf;
	}
	return ans;
}
void solve()
{
	int i,j;
	int mini=inf;
	int pow=1;
	for(i=0;i<n;i++)
		pow*=2;
	for(pow--;pow>=0;pow--){
		for(i=0;i<=n+1;i++)
			for(j=0;j<=n+1;j++)
				maze[1][i][j]=maze[0][i][j];
		int t=paint(pow);
		if(t<mini) mini=t;
	}
	if(mini<inf) cout<<mini<<endl;
	else cout<<"inf\n";
}
int main()
{
	int cs;
	cin>>cs;
	while(cs--){
		init();
		solve();
	}
}