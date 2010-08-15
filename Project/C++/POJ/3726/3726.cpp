#include "iostream"
#include "stdio.h"
using namespace std;
#define size 1000000
char a[25][25];
struct position
{
	int x,y;
	position(int x_,int y_):x(x_),y(y_){};
	position(){};
};
int main()
{
	int m,n;
	
	int num[25][25];
	int i,j;
	int dir[4][2]={0,1,0,-1,1,0,-1,0};
	int curx,cury,golx,goly,stx,sty;
	do{
		position step[size];
		position curp;
		int shead,stail;
		cin>>m>>n;
		if(m==0 && n==0)
			break;
		memset(a,'#',sizeof(a));
		memset(num,-1,sizeof(num));
		for(i=1;i<=m;i++)
			for(j=1;j<=n;j++){
				cin>>a[i][j];
				if(a[i][j]=='@'){
					stx=i;sty=j;
					num[i][j]=0;
				}
				else if(a[i][j]=='*'){
					golx=i;goly=j;
					num[i][j]=0;
				}
				else if(a[i][j]=='.')
					num[i][j]=0;
			}
		shead=stail=0;
		step[shead]=position(golx,goly);
		stail++;
		num[golx][goly]=1;
		curx=golx;cury=goly;
		curp.x=curx;
		curp.y=cury;
		while(num[stx][sty]==0){
			if(shead==stail && (curx!=stx || cury!=sty )){
			num[stx][sty]=-1;
				continue;
			}
			curp=step[shead];
			curx=curp.x;
			cury=curp.y;
			shead++;
			for(i=0;i<4;i++){
				int nt=num[curx+dir[i][0]][cury+dir[i][1]];
				if(nt==-1) continue;
				if(nt!=0 && nt<num[curx][cury]+1) continue;
				num[curx+dir[i][0]][cury+dir[i][1]]=num[curx][cury]+1;
				step[stail]=position(curx+dir[i][0],cury+dir[i][1]);
				stail++;
			}
		}
		if(num[stx][sty]!=-1) num[stx][sty]--;
		cout<<num[stx][sty]<<endl;
	}while(true);
	return 0;
}

