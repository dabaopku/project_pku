#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
struct node
{
	node * next;
};
struct li
{
	int len;
	int pos;
};
node pt[105];
li line[10005];
int cmp(const void *a,const void *b)
{
	return ((li*)a)->len-((li*)b)->len;
}
int main()
{
	int n;
	while(cin>>n){
		int i,j,k;
		for(i=0;i<n*n;i++){
				cin>>line[i].len;
			line[i].pos=i;
		}
		qsort(line,n*n,sizeof(li),cmp);
		for(i=0;i<n;i++){
			pt[i].next=&(pt[i]);
		}
		k=0;
		int num=0;
		int length=0;
		int a,b;
		while(line[k].len==0) k++;
		node * pi;
		while(k<=n*n-1){
			a=line[k].pos/n;
			b=line[k].pos%n;
			k++;
			if(a<b) continue;
			pi=&pt[a];
			while(pi->next != &pt[a]){
					if(pi==&pt[b]) break;
				pi=pi->next;
			}
			if(pi==&pt[b]) continue;
			(*pi).next=&pt[b];
			pi=&pt[b];
			while(pi->next != &pt[b])
				pi=pi->next;
			(*pi).next=&pt[a];
			length+=line[k-1].len;
		}
		cout<<length<<endl;
	}
	return 0;
}