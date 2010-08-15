#include "iostream"
#include "stdio.h"
#include "math.h"
using namespace std;

struct point
{
	double x,y;
	int link;
};

double dis[101][101];
int comp(const void *a,const void *b)
{
	point *pa,*pb;
	pa=(point*)a;
	pb=(point *)b;
	if(pa->x>pb->x) return 1;
	else if(pa->x==pb->x) return 0;
	else return -1;
}
int main()
{
	int n;
	cin>>n;
	double sum=0.0;
	point *pt=new point[n];
	memset(pt,0,n*sizeof(point));
	int i,j;
	for(i=0;i<n;i++)
		cin>>pt[i].x>>pt[i].y;
	qsort(pt,n,sizeof(point),comp);
	pt[0].link=1;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++)
			dis[i][j]=sqrt((pt[i].x-pt[j].x)*(pt[i].x-pt[j].x)+(pt[i].y-pt[j].y)
				*(pt[i].y-pt[j].y));
	}
	for(i=1;i<n;i++){
		double min=1234567890.0;
		int a,b;
		for(j=1;j<n;j++){
			
			if(pt[j].link==1) continue;
			for(int k=0;k<j;k++){
				if(pt[k].link==0) continue;
				if(dis[k][j]<min){
					min=dis[k][j];
					a=k;b=j;
				}
			}
			for(int k=j+1;k<n;k++){
				if(pt[k].link==0) continue;
				if(dis[j][k]<min){
					min=dis[j][k];
					a=k;b=j;
				}
			}
			
		}
		sum+=min;
		pt[b].link=1;
	}
	printf("%.2f\n",sum);
	delete []pt;

}