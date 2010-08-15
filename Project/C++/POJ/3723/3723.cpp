#include "iostream"
#include "stdio.h"

using namespace std;
int dir[4][2]={0,1,0,-1,1,0,-1,0};
int total[110][110]={0};
char a[110][110];
int n;
int count(int x,int y,char col)
{
	int num=1;
	int i;
	a[x][y]='#';
	for(i=0;i<4;i++){
		if(a[x+dir[i][0]][y+dir[i][1]] !='.' &&
		a[x+dir[i][0]][y+dir[i][1]] !=col ) continue;
		num+=count(x+dir[i][0],y+dir[i][1],col);
		
	}
	return num;
}
int main()
{
	
	int nb,nw;
	int i,j;
	nb=0;nw=0;
	memset(a,'#',sizeof(a));
	cin>>n;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)
			cin>>a[i][j];
			
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(a[i][j]=='.' || a[i][j]=='#') continue;
			char sign=a[i][j];
			int num=count(i,j,sign);
			if(sign=='B') nb+=num;
			else nw+=num;
		}
	}
	cout<<nb<<' '<<nw<<endl;
	return 0;
}