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
#include "stack"

using namespace std;


struct node
{
	int valu;
	int x,y;
	node *pa;
}unio[110][110];
int maze[110][110];
int h,w;
const int dir[4][2]={-1,0,0,-1,0,1,1,0};

const int inf=1000000;

int main()
{
	freopen("1.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int cs;
	cin>>cs;
	for(int ii=1;ii<=cs;ii++){
		cout<<"Case #"<<ii<<":\n";
		cin>>h>>w;
		int i,j;
	//	cout<<h<<w<<endl;
		for(i=0;i<=h+1;i++)
			for(j=0;j<=w+1;j++)
				maze[i][j]=inf;
	//	cout<<"ok"<<endl;
		for(i=1;i<=h;i++){
			for(j=1;j<=w;j++){
				cin>>maze[i][j];
				unio[i][j].valu=-1;
				unio[i][j].pa=NULL;
				unio[i][j].x=i;
				unio[i][j].y=j;
			}
		}
		int k;
		for(i=1;i<=h;i++){
			for(j=1;j<=w;j++){
				int x=-1,y=-1;
				int mini=maze[i][j];
				for(k=0;k<4;k++){
					if(maze[i+dir[k][0]][j+dir[k][1]]<mini){
						x=i+dir[k][0];
						y=j+dir[k][1];
						mini=maze[x][y];
					}
				}
				if(mini<maze[i][j]){
					node *pa, *pb;
					int a=0,b=0;
					pa=&unio[i][j];
					pb=&unio[x][y];
					while(pa->pa!=NULL){
						a++;
						pa=pa->pa;
					}
					while(pb->pa!=NULL){
						b++;
						pb=pb->pa;
					}
					if(a<b){
						pa->pa=pb;
					}
					else pb->pa=pa;
				}
			}
		}
		int curlevel=0;
		for(i=1;i<=h;i++){
			for(j=1;j<=w;j++){
				node *p;
				p=&unio[i][j];
				while(p->pa!=NULL)
					p=p->pa;
				if(p->valu==-1){
					p->valu=curlevel;
					maze[p->x][p->y]=curlevel;
					curlevel++;
				}
				node *p2=&unio[i][j],* p3=p2;
				while(p3!=p){
					maze[p2->x][p2->y]=p->valu;
					p2->pa=p;
					p2=p3;
					p3=p3->pa;
				}
			}
		}

		for(i=1;i<=h;i++){
			for(j=1;j<=w;j++){
				cout<<(char)(maze[i][j]+'a');
				if(j==w)
					cout<<"\n";
				else
					cout<<" ";
			}
		}
	}
}