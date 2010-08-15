#include "stdio.h"
#include "iostream"
#include "string"
#include "vector"
#include "queue"
using namespace std;

struct
{
	vector<int> parents,sons;
}cow[10002];
struct  
{
	int parent;
	vector<int> sons;
}tree[10002];
int m,n;
int stack[10002]={0};
int top=0;
bool used[10002]={0};
vector<int>::iterator vi;
queue<int> que;
int num=0;
int main()
{
	cin>>n>>m;
	int i,j,a,b;
	for(i=0;i<m;i++){
		cin>>a>>b;
		cow[a].parents.push_back(b);
		cow[b].sons.push_back(a);
	}
	b=INT_MAX;
	for(i=1;i<=n;i++){
		if(cow[i].parents.size()<b){
			b=cow[i].parents.size();
			a=i;
		}
	}
//	a=1;
	used[a]=true;
	while(!cow[a].parents.empty()){
		a=*(cow[a].parents.begin());
		if(used[a]){
			for(vi=cow[a].parents.begin();vi!=cow[a].parents.end();vi++){
				if(used[*vi]) continue;
				else {a=*vi;break;}
			}
			if(used[a]) break;
		}
		used[a]=true;
	}
	memset(used,false,sizeof(used));
	top=0;
	stack[top]=a;
	used[a]=true;

	while(top>=0){
		a=stack[top--];
		for(vi=cow[a].sons.begin();vi!=cow[a].sons.end();vi++){
			if(!used[*vi]){
				used[*vi]=true;
				stack[++top]=*vi;
				tree[*vi].parent=a;
			}
		}
		tree[a].sons=cow[a].sons;
		
	}
	for(i=1;i<=n;i++){
		if(tree[i].parent==0) {num++;a=i;}
	}
	if(num>1) cout<<0<<endl;
	else{
		memset(used,false,sizeof(used));
		que.push(a);
		used[a]=true;
		num=1;
		while(!que.empty()){
			a=que.front();
			que.pop();
			for(vi=cow[a].parents.begin();vi!=cow[a].parents.end();vi++){
				if(!used[*vi]){
					used[*vi]=true;
					que.push(*vi);
					num++;
				}
			}
		}
		cout<<num<<endl;
	}

}