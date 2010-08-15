#include "stdio.h"
#include "string.h"
#include "iostream"
using namespace std;
#define pathnum 10001
#define nodenum 101
struct node
{
	int v,num;
	node *next;
};

struct ans
{
	int start,len;
} answer;

int n,m,distance1[nodenum],stack1[nodenum],used[nodenum],top;

node point[pathnum];
void insert(int a,int b,int c){
	node *s=new node;
	s->v=b;s->num=c;
	s->next=point[a].next;
	point[a].next=s;
}

int shortestpath( int start )
{
	memset(used,0,sizeof(used));
	top=0;
	stack1[++top]=start;
	memset(distance1,999999,sizeof(distance1));
	distance1[start]=0;
	used[start]=1;
	while(top){
		int curnum=stack1[top--];
		used[curnum]=0;
		node *pnext=point[curnum].next;
		while(pnext){
			int tmp=pnext->v;
			if(distance1[tmp]>distance1[curnum]+pnext->num){
				distance1[tmp]=distance1[curnum]+pnext->num;
				if(!used[tmp]){
					stack1[++top]=tmp;
					used[tmp]=1;
				}
			}
			pnext=pnext->next;
		}
	}
	int max=0;
	for(int i=1;i<=n;i++){
		if(distance1[i]==999999) return 0;
		if(distance1[i]>max) max=distance1[i];
	}
	return max;
}
int main(){
	int i,j,a,b,c;
	while(cin>>n,n!=0){
		memset(point,0,sizeof(point));
		answer.len=999999;
		for(i=1;i<=n;i++){
			cin>>m;
			for(j=0;j<m;j++){
				cin>>b>>c;
				insert(i,b,c);
			}
		}
		for(i=1;i<=n;i++){
			int max=0;
			int curlen=shortestpath(i);
			if(curlen<999999 && curlen>max) max=curlen;
				
			if(max<answer.len && max>0){
				answer.len=max;
				answer.start=i;
			}
		}
		cout<<answer.start<<" "<<answer.len<<endl;
	}

}
