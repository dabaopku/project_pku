#include <iostream>

using namespace std;

char line[255];
char tmp[255*88];
int cnt;

int find()
{
	int i=-1;
	for(int s=0;s<cnt;s++){
		if(tmp[s]=='"' && (s==0 ||  tmp[s-1]!='\\') ) i=s;
	}
	return i;
}

void print()
{
	int i,j;
	int flag=0;
	j=find();
	for(i=0;i<cnt;i++){

		if(tmp[i]=='"' && (i==0 || tmp[i-1]!='\\')){
			if(flag)
				printf("''");
			else if(i!=j)
				printf("``");
			flag=1-flag;
		}
		else printf("%c",tmp[i]);
	}
	cnt=0;
}
int main()
{
	int i;
	cnt=0;
	while(gets(line)>0){
		if(!line[0]){
			print();
			printf("\n");
			continue;
		}
			for(i=0;line[i];i++){
				if(line[i]=='\\' && line[i+1]=='p' && line[i+2]=='a' && line[i+3]=='r'){
					print();
					printf("\\par");
					i+=3;
					continue;
				}
					tmp[cnt++]=line[i];
			}
			tmp[cnt++]='\n';
		}
	print();
	return 0;
}