#include "stdio.h"
#include "iostream"
#include "string"
#include "math.h"
#include "stdlib.h"
using namespace std;
#define pi 3.14159265358979
class point
{
public:
	int x,y;
	point(int x_=0, int y_=0):x(x_),y(y_){};
	bool operator<(point &a){
		if(y<a.y) return true;
		else if(y==a.y && x<a.x) return true;
		return false;
	}
	double angle(point &a){
		double z;
		if(a.x==x) return pi/2.0;
		else z=atan((double)(a.y-y)/(double)(a.x-x));
		if(z>=0) return z;
		else return pi+z;
	}
	double dist(point &a){
		return sqrt((double)(a.x-x)*(a.x-x)+(a.y-y)*(a.y-y));
	}
} pt[1002];
int n,l;
int stack[1003];
int top;
int cmp(const void *a,const void *b)
{
	double z1=pt[0].angle(*(point*)a);
	double z2=pt[0].angle(*(point*)b);
	if(z1-z2 < -0.00001) return -1;
	else if(z1-z2 > 0.00001 ) return 1;
	else {
		z1=pt[0].dist(*(point*)a);
		z2=pt[0].dist(*(point*)b);
		if(z1<z2) return -1;
		else return 1;
	}
}

bool left(const point &p,const point &q,const point &r)
{

	int z=(p.x-r.x)*(q.y-r.y)-(p.y-r.y)*(q.x-r.x);
	if(z<0) return true;
	else return false;


}

int main()
{
	int i,j;
	int t1,t2;
	//while(cin>>n>>l){
	cin>>n>>l;
	for(i=0;i<n;i++)
		cin>>pt[i].x>>pt[i].y;
	point pmin(10005,10005);
	for(i=0;i<n;i++){
		if(pt[i]<pmin) {pmin=pt[i];t1=i;}}
	pt[t1]=pt[0];
	pt[0]=pmin;
	qsort(pt+1,n-1,sizeof(pt[0]),cmp);
	for(i=1;i<n;i++){
		if(fabs(pt[0].angle(pt[i])-pt[0].angle(pt[i+1]))<0.00001) pt[i].x=1<<31;
	}
	stack[0]=0;
	t1=1;
	while(pt[t1].x==1<<31) t1++;
	stack[1]=t1;
	top=1;
	for(i=t1+1;i<n;i++){
		if(pt[i].x==1<<31) continue;
		if(left(pt[i],pt[stack[top]],pt[stack[top-1]])){
			stack[++top]=i;
		}
		else {top--;i--;}
	}
	double len=pt[stack[top]].dist(pt[stack[0]]);
	for(i=0;i<top;i++){
		len+=pt[stack[i]].dist(pt[stack[i+1]]);
	}
	len+=2.0*pi*l;
	t1=len;
	len-=t1;
	t2=len*10;
	if(t2>4) t1++;
	cout<<t1<<endl;
}
