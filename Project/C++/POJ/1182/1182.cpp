#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
struct animal 
{
	int parent,num;
};
int main()
{
	int cs,fake=0,n,d,x,y;
	animal ani[50001];
	memset(ani,0,sizeof(ani));
	scanf("%d%d",&n,&cs);
	while(cs--){
		scanf("%d%d%d",&d,&x,&y);
		if(x>n || x<1 || y>n || y<1){
			fake++;
			continue;
		}
		int t1,t2,n1,n2;
		t1=t2=0;
		n1=x;
		n2=y;
		while(ani[n1].parent!=0){
			t1+=ani[n1].num;
			n1=ani[n1].parent;
		}
		while(ani[n2].parent!=0){
			t2+=ani[n2].num;
			n2=ani[n2].parent;
		}
		if(d==2) t1++;
		if(n1==n2){
			if((d==2 && (t2-t1+999)%3!=0) || (d==1 && (t2-t1+999)%3!=0))
				fake++;
			continue;
		}
		if(t2>t1){
			ani[n1].parent=n2;
			ani[n1].num=(t2-t1+999)%3;
		}
		else{
			ani[n2].parent=n1;
			ani[n2].num=(t1-t2+999)%3;
		}

	}
	cout<<fake<<endl;
}