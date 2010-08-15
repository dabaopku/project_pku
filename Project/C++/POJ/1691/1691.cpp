#include"iostream"
#include"stdio.h"
using namespace std;
#define maxlen 10000
struct point{
	int ax,ay,bx,by,col;
};

int comp1(const void*x,const void *y)
{
	point * a, *b ;
	a=(point *)x;
	b=(point *)y;
	return (a->ay)-(b->ay);
}
int comp2(const void*x,const void *y)
{
	point * a, *b ;
	a=(point *)x;
	b=(point *)y;
	if( (a->ay)==(b->ay)) return (a->ax-b->ax);
	return (a->ay)-(b->ay);
}
void print(point a)
{
	cout<<a.ax<<" "<<a.ay<<" "<<a.bx<<" "<<a.by<<" "<<a.col;
}
int main()
{
	int cs;
	cin>>cs;
	while(cs--){
		int n;
		cin>>n;
		int i,j;
		point * pts=new point[n];
		for(i=0;i<n;i++)
			cin>>pts[i].ay>>pts[i].ax>>pts[i].by>>pts[i].bx>>pts[i].col;
		qsort(pts,n,sizeof(point),comp1);
		qsort(pts,n,sizeof(point),comp2);
		int que[maxlen]={0};
		int head=0,tail=1;
		cout<<endl;
		for(i=0;i<n;i++){
			print(pts[i]);
			cout<<endl;
		}
		int * num=new int[n];
		num[0]=1;
		for(i=1;i<n;i++){
			if(pts[i].ay==pts[i-1].ay){
				if(pts[i].col==pts[i-1].col) num[i]=num[i-1];
				else num[i]=num[i-1]+1;
			}
			else{
				int flag=1;
				for(j=0;j<i;j++){
					if(pts[j].by<pts[i].ay ) continue;
					if(pts[j].bx<=pts[i].ax ) continue;
					if(pts[j].ax>=pts[i].bx ) continue;
					if(pts[j].col!=pts[i].col ) flag=0;
				}
				if(flag==1) num[i]=num[i-1];
				else num[i]=num[i-1]+1;
			}
		}
		cout<<num[n-1]<<endl;
		delete[]num;
	/*	que[0]=pts[0].col;
		for(i=1;i<n;i++){
			if(pts[i].ay>pts[0].ay) break;
			if(pts[i].col!=que[tail-1] )
				que[tail++]=pts[i].col;
		}
		while(head!=tail){
			
		}*/
		delete []pts;
	}
}