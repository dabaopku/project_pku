
#include "stdio.h"
#include "string.h"
#include "iostream"
using namespace std;
#define pathnum 150001
#define nodenum 30001
struct node
{
	int v,num;
	node *next;
};


long n,m,distance1[nodenum],stack1[nodenum],used[nodenum],top;

node point[pathnum];
void insert(int a,int b,int c){
	node *s=new node;
	s->v=b;s->num=c;
	s->next=point[a].next;
	point[a].next=s;
}
int main(){
	int i,a,b,c;
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(point,0,sizeof(point));
		for(i=1;i<=m;i++){
			scanf("%d%d%d",&a,&b,&c);
			insert(a,b,c);
		}
		memset(used,0,sizeof(used));
		top=0;
		stack1[++top]=1;
		memset(distance1,999999,sizeof(distance1));
		distance1[1]=0;
		used[1]=1;
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
		printf("%d\n",distance1[n]);
	}

}
