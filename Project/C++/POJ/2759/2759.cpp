#include "iostream"
#include "stdio.h"
using namespace std;

int a[210]={0};
int b[410][210];

int solve(int sum,int n)
{
	if(sum<0 || n<0) return 0;
	if(b[sum][n]!=-1) return b[sum][n];
	if(sum==0) return 1;
	
	if( n==0 && sum==a[0] ) return 1;
	if( n==0 && sum!=a[0] ) return 0;
	b[sum][n]=(solve(sum-a[n],n-1)%10000+solve(sum,n-1)%10000)%10000;
	return b[sum][n];
	
}
int comp(const void *x,const void *y)
{
	return *(int*)x-*(int*)y;
}
int main()
{
	int i,n;
	cin>>n;
	memset(b,-1,sizeof(b));
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	qsort(a,n,sizeof(int),comp);
	cout<<solve(400,n-1)<<endl;
}