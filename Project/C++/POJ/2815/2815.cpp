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

using namespace std;

int m,n;
bool wall[60][60][4]={0};
int num[60][60]={0};
int dir[4][2]={0,-1,-1,0,0,1,1,0};
int cnt=1;

void tran(int sum,int x,int y)
{
	int i;
	for(i=0;i<4;i++){
		wall[x][y][i]=wall[x+dir[i][0]][y+dir[i][1]][(i+2)%4]=1-sum%2;
		sum/=2;
	}
}
void init()
{
	cin>>n>>m;
	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			int tmp;
			cin>>tmp;
			tran(tmp,i,j);
		}
	//	for(j=0;j<4;j++)
	//		cout<<wall[i][2][j]<<" ";
	//	cout<<endl;
	}
}

int dfs(int x,int y)
{
	int i,j;
	if(num[x][y]) return 0;
	num[x][y]=cnt;
	int sum=1;
	for(i=0;i<4;i++){
		if(wall[x][y][i] && !num[x+dir[i][0]][y+dir[i][1]] ){
			sum+=dfs(x+dir[i][0],y+dir[i][1]);
		}
	}
	return sum;
}
void solve()
{
	int i,j;
	int maxi=0;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(num[i][j]) continue;
			int tmp=dfs(i,j);
			cnt++;
			if(tmp>maxi) maxi=tmp;
		}
	}
	cout<<cnt-1<<endl<<maxi<<endl;

}	
int main()
{
	init();	
	solve();
}