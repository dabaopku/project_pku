#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "iostream"

using namespace std;
unsigned long pow(unsigned long a,unsigned long b)
{
	long num=1;
	while(b--)
		num*=a;
	return num;
}

unsigned long MCF( const unsigned long x_, const unsigned long y_ )
//求两个数的最大公约数
//返回正数解
{
	unsigned long x=x_, y=y_;
	unsigned long temp;
	if( !x || !y ) return 0;
	if( x < 0 )
		x = -x;
	if( y < 0 )
		y = -y;
	if( x < y ){
		temp =x;
		x = y;
		y = temp;
	}
	while( x % y ){
		temp = x % y;
		x = y;
		y = temp;
	}
	return y;
}
int main()
{
	unsigned long c,n,num;
	while(cin>>c>>n,c!=0 || n!=0){
		if(c==0 || n==0){
			cout<<'0'<<endl;
			continue;
		}
		if(n==1){
			cout<<c<<endl;
			continue;
		}
		if(c==1){
			cout<<'1'<<endl;
			continue;
		}
		num=0;
		for(unsigned long i=1;i<=n;i++)
			num+=pow(c,MCF(i,n));
		if(n%2){
			num+=n*pow(c,(n+1)/2);
			num/=2*n;
		}
		else{
			num+=n/2*pow(c,n/2)+n/2*pow(c,n/2+1);
			num/=2*n;
		}
		cout<<num<<endl;
	}
	return 0;
}