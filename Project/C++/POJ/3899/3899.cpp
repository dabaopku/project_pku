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

const int maxn=1000000;
const __int64 inf=1e12;

__int64 q[maxn]={0};
__int64 qtmp[maxn];
int tail=0;
void init()
{
	int head=0;
	int i,j;
	__int64 cur;
	__int64 l;
	set<__int64> stmp;

	q[tail++]=4;
	q[tail++]=7;
	while(head!=tail){
		cur=q[head++];
		l=cur*10+4;
		if(l>inf) continue;
		else{
			q[tail++]=l;
			q[tail++]=l+3;
		}
	}
	for(i=0;i<tail;i++){
		qtmp[i]=q[i];
		stmp.insert(q[i]);
	}
	
	int n=tail;
	head=0;
	while(head<=tail){
		cur=q[head];
		for(i=0;i<n;i++){
			l=cur*qtmp[i];
			if(l>inf) break;
			else{
				if(stmp.find(l)==stmp.end()){
					stmp.insert(l);
					q[tail++]=l;
				}
			}
		}
		head++;
	}
//	cout<<tail<<" "<<"ok";
	
	set<__int64>::iterator si;
	tail=0;
	si=stmp.begin();
	si++;
	for(;si!=stmp.end();si++){
		q[tail++]=*si;
	}
}
int main()
{
	init();
	int cs;
	__int64 a,b;
	scanf("%d",&cs);
	int i,j;
	while(cs--){
		scanf("%I64d%I64d",&a,&b);
		printf("%d\n",upper_bound(q,q+tail,b)-lower_bound(q,q+tail,a));
	}
}