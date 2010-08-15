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

int mp[26]={0,1,2,3,0,1,2,0,0,2,2,4,5,5,0,1,2,6,2,3,0,1,0,2,0,2};

char a[30];
int main()
{
	while(cin>>a){
		int i=-1;
		int pre=-1;
		int cur;
		while(i++,a[i]){
			cur=mp[a[i]-'A'];
			if(cur==0){
				pre=-1;
				continue;
			}
			if(cur==pre) continue;
			cout<<cur;
			pre=cur;
		}
		cout<<endl;
	}
}