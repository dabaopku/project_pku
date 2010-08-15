#include "stdio.h"
#include "iostream"
#include "string.h"
#include "math.h"
#include "string"
#include "vector"
#include "set"
#include "map"
#include "queue"
#include "list"

using namespace std;

bool isprime(int n)
{
	if(n==1) return false;
	if(n==2 || n==3) return true;
	int i;
	if(n%2==0) return false;
	int t=sqrt(1.0*n);
	while(t*t<n) t++;
	for(i=3;i<=t;i+=2){
		if(n%i==0) return false;
	}
	return true;
}

int solve(int a,int p)
{
	if(a>p) return solve(a%p,p);
	if(a==1) return 1;
	if(a==-1){
		int t=(p-1)/2;
		if(t%2) return -1;
		else return 1;
	}
	if(a==2){
		int t=(p*p-1)/8;
		if(t%2) return -1;
		else return 1;
	}
	if(a<0) return solve(-1,p)*solve(-a,p);
	if(a*2>p) return solve(a-p,p);
	if(isprime(a)){
		int t=(a-1)*(p-1)/4;
		int s=solve(p,a);
		if(t%2) return -s;
		else return s;
	}
	int i;
	for(i=2;i<a;i++){
		if(a%i==0){
			return solve(i,p)*solve(a/i,p);
		}
	}
}
int main()
{
	int cs;
	int ii;
	cin>>cs;
	int a,b;
	for(ii=1;ii<=cs;ii++){
		cin>>a>>b;
		cout<<"Scenario #"<<ii<<":\n";
		cout<<solve(a,b)<<endl<<endl;
	}
}