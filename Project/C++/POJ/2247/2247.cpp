#include "iostream"
#include "stdio.h"
#include <algorithm>
using namespace std;
__int64 a[5850]={0};
#define max 2000000000

int comp(const void *x,const void *y)
{
	return *(__int64*)x-*(__int64*)y;
}
int main()
{
	a[0]=1;
	int num=1;
	int i1,i2,i3,i4;
	__int64 b1=1,b2,b3,b4;
	for(i1=0;i1<32;i1++){
		if(i1) b1*=2;
		if(b1>max) break;
		for(b2=1,i2=0;i2<25;i2++){
			if(i2) b2*=3;
			if(b1*b2>max ) break;
			for(b3=1,i3=0;i3<25;i3++){
				if(i3) b3*=5;
				if(b1*b2*b3>max) break;
				for(b4=1,i4=0;i4<25;i4++){
					if(i4) b4*=7;
					if(b1*b2*b3*b4>max) break;
					a[num++]=b1*b2*b3*b4;
					}
				}
			}
		}
	qsort(a,num,sizeof(__int64),comp);
	int n;
	while(cin>>n,n){
		cout<<"The "<<n;
		if(n%10==1 && n%100!=11) cout<<"st";
		else if(n%10==2 && n%100!=12 ) cout<<"nd";
		else if(n%10==3 && n%100!=13 ) cout<<"rd";
		else cout<<"th";
		cout<<" humble number is ";
		printf("%I64d.\n",a[n]);
	}
	return 0;
	
}