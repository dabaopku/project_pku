#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
# define MaxSize 2005
# define MaxPath 10005
struct node
{
	node * parent;

};
struct path
{
	int a,b;
	int len;
};
int cmp(const void *a,const void *b)
{
	path * pa, *pb;
	pa=(path*)a;
	pb=(path*)b;
	return pa->len - pb->len ;
}
int main()
{
	int n,m;
	int i,j;
	int max=0;
	node pt[MaxSize];
	path pa[MaxPath];
	node *root1,*root2;
	cin>>n>>m;
	for(i=0;i<m;i++){
		cin>>pa[i].a>>pa[i].b>>pa[i].len;
	}
	qsort(pa,m,sizeof(path),cmp);
	for(i=1;i<=n;i++)
		pt[i].parent=NULL;
	for(i=0;i<m;i++){
		node * na, *nb;
		na=&pt[pa[i].a];
		nb=&pt[pa[i].b];
		while(na->parent) na=na->parent;
		while(nb->parent) nb=nb->parent;
		if(na==nb) continue;
		root1=na;
		nb->parent=na;
		na=&pt[pa[i].a];
		while(na->parent) {
			root2=na->parent;
			na->parent=root1;
			na=root2;
		}
		na=&pt[pa[i].b];
		while(na->parent) {
			root2=na->parent;
			na->parent=root1;
			na=root2;
		}
		if(pa[i].len>max) max=pa[i].len;
	}
	cout<<max<<endl;
}