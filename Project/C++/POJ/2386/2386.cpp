#include "iostream"
#include "stdio.h"
using namespace std;
int num=0;
int c,r;
char a[103][103]={0};

int dir[8][2]={-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
void find(int y,int x)
{
	for(int i=0;i<8;i++){
		if(a[y+dir[i][0]][x+dir[i][1]]=='.') continue;
		a[y+dir[i][0]][x+dir[i][1]]='.';
		find(y+dir[i][0],x+dir[i][1]);
	}
	return;
}
int main()
{
	int i,j;
	memset(a,'.',sizeof(a));
	cin>>r>>c;
	for(i=1;i<=r;i++)
		for(j=1;j<=c;j++)
			cin>>a[i][j];
	for(i=1;i<=r;i++){
		for(j=1;j<=c;j++){
			if(a[i][j]=='W'){
				num++;
				a[i][j]='.';
				find(i,j);
			}
		}
	}
	cout<<num<<endl;	
	return 0;
}