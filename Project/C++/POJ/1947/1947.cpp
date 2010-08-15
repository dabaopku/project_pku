/*
#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
struct tree
{
	int sons;
	tree *son[152],*parent;
};
tree  data[152];
int num[152][152]={0};
int n;
int count(int start,int barns,tree *head)
{
	if(start<1 || start > n || barns<=0 ) return 0;
	if(num[start][barns]!=-1) return num[start][barns]; 
	int i,min=200;
	for()
}
int main()
{
	int p,i,j;
	int father,son;
	cin>>n>>p;
	for(i=0;i<152;i++){
		data[i].parent=NULL;
		data->sons=1;
	}
	while(cin>>father>>son){
		data[father].sons++;
		data[father].son[data[father].sons-1]=&data[son];
		data[son].parent=&data[father];
	}
	tree *head=&data[1];
	while(head->parent)
		head=head->parent;
	memset(num,-1,sizeof(num));
	father = count(1,p,head);
	return 0;
}*/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAXN 200
#define MAX 100000

struct Node
{
	int first,next,parent,count;
};

Node node[MAXN];

int a[MAXN][MAXN],b[MAXN][MAXN];
void count(int root,int num)
{
	if(root==0)
		return;     
	int i,min;
	count(node[root].first,num);
	count(node[root].next,num);
	if(node[root].next==0)
		a[root][num]=b[root][num];
	else 
	{
		min=a[node[root].next][num]+1;
		for(i=0;i<=num;i++)
			if(a[node[root].next][i]+b[root][num-i]<min)
				min=a[node[root].next][i]+b[root][num-i];
		a[root][num]=min;
	}
	if(num+1>node[root].count)
		b[root][num+1]=MAX;
	else
		b[root][num+1]=a[node[root].first][num];
}
void visit(int root)
{
	if(root==0)
		return;
	int r;
	visit(node[root].first);
	visit(node[root].next);
	r=node[root].first;
	node[root].count=1;
	while(r){
		node[root].count+=node[r].count;
		r=node[r].next;	}
}

int main()
{
	int i,n,p,s1,s2,root,min;
	while(scanf("%d%d",&n,&p)!=EOF){
		memset(node,0,sizeof(node));
		for(i=0;i<n-1;i++){
			scanf("%d%d",&s1,&s2);
			node[s2].next=node[s1].first;
			node[s1].first=s2;
			node[s2].parent=s1;
		}

		for(i=1;i<=n;i++)
			if(node[i].parent==0)
			{
				root=i;
				break;
			}
			visit(root);
			for(i=0;i<=n;i++)
				b[i][0]=1;
			for(i=0;i<p;i++)
				count(root,i);
			min=b[1][p];
			for(i=2;i<=n;i++)
			{
				if(i!=root)
					b[i][p]++;
				if(b[i][p]<min)
					min=b[i][p];
			}
			printf("%d\n",min);
	}
	return 0;
}