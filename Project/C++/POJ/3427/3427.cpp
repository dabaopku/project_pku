#include"iostream"
#include "stdio.h"
#include "map"
#include "list"
using namespace std;

int main()
{
	map<int,list<int> > data;
	int cs;
	char cmd[10];
	int num,val;
	list<int>::iterator i;
	scanf("%d",&cs);
	while(cs-- ){
		scanf("%s%d",cmd,&num);
		if(cmd[0]=='n')
			continue;
		else if(cmd[0]=='a'){
			scanf("%d",&val);
			data[num].push_back(val);
		}
		else if(cmd[0]=='o'){
			data[num].sort();
			i=data[num].begin();
			for(;i!=data[num].end();i++)
				cout<<*i<<" ";
			cout<<endl;
		}
		else if(cmd[0]=='m'){
			scanf("%d",&val);
				data[num].merge(data[val]);
		}
		else if(cmd[0]=='u'){
			data[num].sort();
			data[num].unique();
		}
	}
	return 0;
}