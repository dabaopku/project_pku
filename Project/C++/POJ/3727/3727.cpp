#include "iostream"
#include "stdio.h"

using namespace std;

int main()
{
	int cs;
	int r,c;
	int a[110][110];
	int i,j;
	cin>>cs;
	while(cs--){
		memset(a,0,sizeof(a));
		cin>>r>>c;
		for(i=1;i<=r;i++)
			for(j=1;j<=c;j++)
				cin>>a[i][j];
		for(i=1;i<=r;i++)
			for(j=1;j<=c;j++){
				if(a[i-1][j]>a[i][j-1]) a[i][j]+=a[i-1][j];
				else a[i][j]+=a[i][j-1];
			}
		cout<<a[r][c]<<endl;
	}
	return 0;
}