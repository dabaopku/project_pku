#include"iostream"
#include"stdio.h"
using namespace std;

int f(int m,int n,int min)
{
	if(n==0) return 0;
	if(m<min) return 0;
	if(m==min*n) return 1;
	if(n==1&& m>=min) return 1;
	int num=0,i;
	for(i=min;i<=m/n;i++){
		num+=f(m-i,n-1,i);
	}
	return num;
}
int main()
{
	int cs;
	int m,n;
	cin>>cs;
	while(cs--){
		cin>>m>>n;
		cout<<f(m,n,0)<<endl;
	}

}