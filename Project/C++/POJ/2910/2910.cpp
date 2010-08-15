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

using namespace std;

int main()
{
	int cur=-1;
	char str[31];
	gets(str);
	char *p=str;
	while(*p){
		if(*p <='9' && *p>='0'){
			if(cur!=-1) cur=cur*10+*p-'0';
			else cur=*p-'0';
		}
		else if(cur!=-1){
			cout<<cur<<endl;
			cur=-1;
		}
		p++;
	}
	if(cur!=-1)
		cout<<cur<<endl;
}