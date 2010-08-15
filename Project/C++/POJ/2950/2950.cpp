#include "iostream"
#include "stdio.h"
using namespace std;
int m,n,time;
int num[52][52];
int sum;
int x=-1,y=-1,nx,ny;
int abs(int _x,int _y)
{
	if (_x<_y )
		return _y-_x;
	return _x-_y;
}
void findnext()
{
	int max=0;
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (num[i][j]>max)
			{
				max=num[i][j];
				nx=i;ny=j;
			}
		}
	}
	if (max==0)
	{
		nx=-1;ny=-1;
	}
}

int step()
{
	if (x<0)
	{
		return 1+nx;
	}
	return abs(x,nx)+abs(y,ny);
}
int main()
{
	int cs;
	cin>>cs;
	while(cs--){
		cin>>m>>n>>time;
		memset(num,0,sizeof(num));
		sum=0;x=-1;y=-1;
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				scanf("%d",&num[i][j]);
		while(time){
			findnext();
			if(nx==-1) break;
			int nextstep=step()+nx+2;
			if(nextstep>time) break;
			time-=nextstep-nx-1;
			sum+=num[nx][ny];
			num[nx][ny]=0;
			x=nx;y=ny;
		}
		cout<<sum<<endl;

	}
	return 0;

}