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
#include "stack"

using namespace std;
int main()
{
	int cs;
	scanf("%d",&cs);
	//	freopen("out.txt","w",stdout);

	for(int ii=1;ii<=cs;ii++){
		printf("Case #%d: ",ii);
		char a[1000],b[1000];
		scanf("%s",a);
		int n=strlen(a);
		int i,j;
		n--;
		int m=n;
		while(m>0 && a[m]<=a[m-1]) m--;
		if(m==0){
			m=n;
			while(a[m]=='0') m--;
			b[0]=a[m];
			b[1]='0';
			for(i=2,j=n;j>=0;i++,j--){
				if(j==m) j--;
				if(j>=0) b[i]=a[j];
				else i--;
			}
			b[i]=0;
			printf("%s\n",b);
			continue;
		}
		int l=n;
		m--;
		while(a[l]<=a[m]) l--;
		for(i=0;i<m;i++)
			b[i]=a[i];
		b[i]=a[l];
		for(i++,j=n;j>l;j--,i++)
			b[i]=a[j];
		b[i]=a[m];
		for(i++,j--;j>m;j--,i++)
			b[i]=a[j];
		b[i]=0;
		printf("%s\n",b);
	}

}
