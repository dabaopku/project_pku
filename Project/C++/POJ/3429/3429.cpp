#include"stdio.h"
#include "map"
#include "algorithm"
using namespace std;

int main()
{
	map<int,int> da;
	int cs;
	char cmd[5];
	int num;

	scanf("%d",&cs);
	while(cs--){
		scanf("%s%d",cmd,&num);
		if(strcmp(cmd,"add")==0){
			if(da.count(num)==0)
				da.insert(make_pair(num,1));
			else da[num]++;
			printf("%d\n",da[num]);

		}
		else if(strcmp(cmd,"del")==0){
			if(da.count(num)==0) printf("0\n");
			else{
				printf("%d\n",da[num]);
				da[num]=0;
			}
			
		}
		else{
			if(da.count(num)==0) printf("0 0\n");
			else printf("1 %d\n",da[num]);
			
		}
		

	}
	return 0;
}