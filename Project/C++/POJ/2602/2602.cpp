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

int n;
int i;
int a,b;
int ans[1000010]={0};
int main()
{
	scanf("%d",&n);
	getchar();
	for(i=0;i<n;i++){
		a=getchar();
		getchar();
		b=getchar();
		getchar();
		ans[i]=a+b-'0'-'0';
	}

	for(i=n-1;i>0;i--)
		if(ans[i]>=10){
			ans[i-1]++;
			ans[i]-=10;
		}
	printf("%d",ans[0]);
	for(i=1;i<n;i++)
		putchar('0'+ans[i]);
	printf("\n");
}