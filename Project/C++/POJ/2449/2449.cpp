#include "set"
#include "stdio.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "math.h"
using namespace std;

struct node{
	int v,w;
	node* next;
}*adj[1010],*ddj[1010],pool[200010],*pp=pool;

node* create(int v,int w,node* next){
	pp->v=v;
	pp->w=w;
	pp->next=next;
	return pp++;
}
int n,SS,TT,K;
void dij();
int astar();
int main(){
	int m,t,v,s;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d%d",&s,&t,&v);
		adj[s]=create(t,v,adj[s]);
		ddj[t]=create(s,v,ddj[t]);
	}
	scanf("%d%d%d",&SS,&TT,&K);
	if(SS==TT)++K;
	dij();
	printf("%d\n",astar());
	return 0;
}
int dist[1010];
struct cmp{
	bool operator()(const int& a,const int& b)const{
		return dist[a]<dist[b]||dist[a]==dist[b]&&a<b;
	}
};
set<int,cmp> S;
void dij(){
	S.clear();
	memset(dist,0x3f,sizeof(dist));
	dist[TT]=0;
	S.insert(TT);
	while(!S.empty()){
		int i=*S.begin();
		S.erase(S.begin());
		for(node* p=ddj[i];p;p=p->next){
			if(dist[p->v]>dist[i]+p->w){
				S.erase(p->v);
				dist[p->v]=dist[i]+p->w;
				S.insert(p->v);
			}
		}
	}
}
struct box{
	int v,sd,td;
}h[1000000];
int len=0;
bool operator<(const box& a,const box& b){
	return a.td<b.td;
}
void adjust(int n){
	box rc=h[0];
	int i;
	for(i=1;i<n;i=(i<<1)+1){
		if(i<len-1&&h[i+1]<h[i])++i;
		if(rc<h[i])break;
		h[(i-1)>>1]=h[i];
	}
	h[(i-1)>>1]=rc;
}
void upheap(int n){
	box rc=h[n-1];
	int i,s=n-1;
	for(i=((s-1)>>1);i>=0;i=((i-1)>>1)){
		if(h[i]<rc)break;
		h[s]=h[i];s=i;
	}
	h[s]=rc;
}
int astar(){
	box t;
	t.v=SS;
	t.sd=0;
	t.td=t.sd+dist[t.v];
	h[len++]=t;
	while(len){
		t=h[0];
		if(!(K-=(t.v==TT))){
			return t.td;
		}
		h[0]=h[--len];
		adjust(len);
		for(node* p=adj[t.v];p;p=p->next){
			box nt;
			nt.v=p->v;
			nt.sd=t.sd+p->w;
			nt.td=nt.sd+dist[nt.v];
			h[len++]=nt;
			upheap(len);
		}
	}
	return -1;
}
