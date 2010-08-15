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
int w,h;
char a[25][25];
int sx,sy;
int dir[4][2]={1,0,-1,0,0,1,0,-1};

bool init()
{
	cin>>w>>h;
	if(!(w || h)) return 0;
	for(int i=0;i<25;i++){
		for(int j=0;j<25;j++){
			a[i][j]='#';
		}
	}
	int i,j;
	char ch;
	for(i=1;i<=h;i++){
		for(j=1;j<=w;j++){
			cin>>a[i][j];
			if(a[i][j]=='@'){
				sx=i;sy=j;
			}
		}
	}
	return 1;
}
int solve(int x,int y)
{
	int i;
	if(a[x][y]=='#') return 0;
	a[x][y]='#';
	int sum=1;
	for(i=0;i<4;i++)
		sum+=solve(x+dir[i][0],y+dir[i][1]);
	return sum;
}
int main()
{

	while(init()){
		cout<<solve(sx,sy)<<endl;
	}	
}