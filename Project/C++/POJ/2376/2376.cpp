#include "stdio.h"
#include "iostream"
#include "string"
#include "algorithm"
using namespace std;
class cow
{
public:
	int a,b;
	cow(int a_=0,int b_=0):a(a_),b(b_){};
	
	bool operator<(cow & ob)
	{
		return (a<ob.a ||(a==ob.a && b>ob.b));
	}
};
int n,t,num;
cow c[25002];
int main()
{
	int i,j;
	int h,e;
	int max=0;
	scanf("%d%d",&n,&t);
	for(i=0;i<n;i++)
		scanf("%d%d",&c[i].a,&c[i].b);
	sort(c,c+n);
	i=j=0;
	h=1;
	num=1;
	e=c[0].b;
	if(c[0].a>1){
		cout<<-1<<endl;
		return 0;
	}
	while(e<t){
		max=e;
		
		while(c[j].a<=e+1 && j<n){
			if(c[j].b>max) {
				max=c[j].b;
				i=j;
			}
			j++;
		}
		if(j>=n && max!=t || c[j].a>max+1) break;
		if(e!=max){
			e=max;
			num++;
		}
	}
	if(e<t) cout<<-1<<endl;
	else cout<<num<<endl;
}