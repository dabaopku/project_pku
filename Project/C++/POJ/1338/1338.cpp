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

priority_queue<int,vector<int>,greater<int>> que;
int num[1650];

void pre()
{
	int t;
	que.push(1);
	int i=1;
	while(i<1610){
		t=que.top();
		que.pop();
		while(!que.empty() && t==que.top() )
			que.pop();

		num[i]=t;
		i++;
		if(t*2>0) que.push (t*2);
		if(t*3>0) que.push(t*3);
		if(t*5>0) que.push(t*5);
	}

}
int main()
{
	pre();
	int n;
	while(cin>>n,n!=0){
		cout<<num[n]<<endl;
	}
}