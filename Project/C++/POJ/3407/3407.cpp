#include "stdio.h"
#include "iostream"
#include "string"
#include "queue"
#include "vector"
using namespace std;

struct PATH{
	int y;
	int b,e,c;
};

struct NODE{
	int id;
	int tm;

	NODE(){};
	NODE(int id0,int tm0){
		id=id0;
		tm=tm0;
	}	
};

bool operator < (NODE a,NODE b){
	return a.tm > b.tm;
}
typedef priority_queue<NODE> prique;
prique que;


int n,m,s,t;
const int inf = 1<<30 , maxsize = 105 ;
//int map[maxsize][maxsize];
int len[maxsize];

PATH p;
vector<PATH> node[maxsize];

int bfs(int starttime){
	int i,j;
	int cur;
	NODE nd,nd2;
	PATH pt;
	while(!que.empty()) que.pop();
	for(i=1;i<=n;i++){
		len[i]=inf;
	}
	len[s]=0;
	que.push(NODE(s,starttime));
	while(!que.empty()){
		nd=que.top();
		que.pop();
		cur=nd.id;
		if(cur==t) return len[cur];
		int num=node[cur].size();
		for(i=0;i<num;i++){
			pt=node[cur][i];
			if(pt.b<nd.tm) continue;
			if(nd.tm+pt.c>pt.e) continue;
			nd2.tm=nd.tm+pt.c;
			nd2.id=pt.y;
			if(len[cur]+pt.b-nd.tm+pt.c< len[pt.y]){
				len[pt.y]=pt.b-nd.tm + pt.c+len[cur];
				que.push(nd2);
			}
		}
	}
	return inf;
}

int find(){
	int i,j,num=node[s].size(),min=inf;
	int late=0,tmp;

	for(i=0;i<num;i++){
		tmp=node[s][i].e-node[s][i].c;
		if(tmp>late) late=tmp;
	}
	//cout<<late<<endl;
	for(i=0;i<=late;i++){
		tmp=bfs(i);
		if(tmp<min) min=tmp;
	}
	//cout<<min<<endl;
	return min;
}

int main()
{
	int x;

	scanf("%d%d%d%d",&n,&m,&s,&t);
	while(m--){
		scanf("%d%d%d%d%d",&x,&p.y,&p.b,&p.e,&p.c);
		if(p.b+p.c>p.e) continue;
		node[x].push_back(p);
	}

	int len = find();
	if(len==inf) printf("Impossible\n");
	else printf("%d\n",len);

	return 0;
}