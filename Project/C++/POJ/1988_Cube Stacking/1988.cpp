#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
struct stack 
{
	int parent,num;
};
int main()
{
	stack st[30001];
	int cs,n1,n2,n3;
	char cmd;
	int t1;
	scanf("%d",&cs);
	memset(st,0,sizeof(st));
	while(cs--){
		do{
			cmd=getchar();
		}while(cmd!='C' && cmd!='M');
		if(cmd=='C'){
			scanf("%d",&n1);
			t1=0;
			while(st[n1].parent){
				t1+=st[n1].num;
				n1=st[n1].parent;
			}
			printf("%d\n",t1);
			continue;
		}
		else{
			scanf("%d%d",&n1,&n2);
			n3=n1;
			if(st[n1].num==0) st[n1].num=1;
			if(st[n2].num==0) st[n2].num=1;
			while(st[n1].parent)
				n1=st[n1].parent;
			while(st[n2].parent)
			n2=st[n2].parent;
			st[n2].num+=st[n1].num;
			st[n1].num=st[n2].num-st[n1].num;
			st[n1].parent=n2;
		//***************************************
			while(n3!=n1){
				int n4=n3;
				do{
					n3=st[n3].parent;
					st[n4].num+=st[n3].num;
				}while(n3!=n1);
				n3=st[n4].parent;
				st[n4].parent=n2;
			}
		//*****************************************

		}
	}
	
}