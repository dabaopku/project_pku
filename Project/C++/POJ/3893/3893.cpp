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
const int maxn=100008;

int seq[maxn];
int ans[maxn];
int cur;
int n;
int solve()
{
	int i,j;
	cur=1;
	ans[0]=seq[0];
	for(i=1;i<n;i++){
		if(seq[i]>ans[cur-1]){
			ans[cur++]=seq[i];
			continue;
		}
		j=cur-1;
		while(j>=0 && ans[j]>=seq[i]) j--;
		ans[j+1]=seq[i];
			
	}
	return cur;
}
int main()
{
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++)
			scanf("%d",&seq[i]);
		printf("%d\n",solve());
	}
}