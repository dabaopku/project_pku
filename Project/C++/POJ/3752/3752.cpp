#include "stdio.h"
#include "iostream"
#include "string"
#include"queue"
using namespace std;
struct point
{
	int x,y,len;
	point(int x_=0,int y_=0,int len_=0){
		x=x_;y=y_;len=len_;
	}
};
int main()
{
	int m,n;
	int i,j;
	char a[42][42];
	int dir[4][2]={1,0,0,1,-1,0,0,-1};
	queue<point> que;
	point pcur;
	cin>>m>>n;
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			cin>>a[i][j];
	que.push(point(1,1,1));
	a[1][1]='#';
	pcur=point(1,1,1);
	while(!que.empty() && (pcur.x!=m||pcur.y!=n)){
		pcur=que.front();
		que.pop();
		for(i=0;i<4;i++){
			int t1=pcur.x+dir[i][0],t2=pcur.y+dir[i][1];
			if(t1==m && t2==n) break;
			if(a[t1][t2]!='.') continue;
			a[t1][t2]='#';
			que.push(point(t1,t2,pcur.len+1));
		}
		if(i<4) break;
	}
	cout<<pcur.len+1<<endl;
}