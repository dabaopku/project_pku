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

void print(int n,int line)
{
	int i,j,k;
	for(i=1;i<=2*n+1;i++){
		for(j=1;j<=2*n+1;j++){
			k=abs(n+1-line)+abs(i-n-1)+abs(j-n-1);
			if(k>n) printf(".");
			else printf("%d",k);
		}
		printf("\n");
	}
}
int main()
{
	int cs,n;
	int ii;
	scanf("%d",&cs);
	for(ii=1;ii<=cs;ii++){
		scanf("%d",&n);
		printf("Scenario #%d:\n",ii);
		int i,j,k;
		for(k=1;k<=n+1;k++){
			printf("slice #%d:\n",k);
			print(n,k);
		}
		for(k=n;k>0;k--){
			printf("slice #%d:\n",2*n+2-k);
			print(n,k);
		}
		printf("\n");
	}
}