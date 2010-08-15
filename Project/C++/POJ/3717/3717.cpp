#include "iostream"
#include "stdio.h"
using namespace std;

int main()
{
	int m,n;
	int num[21][21];
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		num[i][1]=1;
	for(int i=1;i<=n;i++)
		num[1][i]=1;
	for(int i=2;i<=m;i++){
		for(int j=2;j<=n;j++)
			num[i][j]=num[i-1][j]+num[i][j-1];
	}
	cout<<num[m][n]<<endl;
}