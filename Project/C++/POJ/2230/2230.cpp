#include "stdio.h"
#include "iostream"
#include "string"
#include "vector"
#include "stack"
using namespace std;
stack<int> st;
vector<int> v[10005];
vector<int>::iterator i;
int main()
{
	int n,cs;
	int a,b;
	scanf("%d%d",&n,&cs);
	while(cs--){
		scanf("%d%d",&a,&b);
		v[a].push_back(b);
		v[b].push_back(a);
	}
	a=1;
	st.push(1);
	while(!st.empty()){
		while(v[a].empty()){
			printf("%d\n",a);
			st.pop();
			if(st.empty()) break;
			a=st.top();
		}
		if(st.empty()) break;
		i=v[a].end();
		i--;
		b=*i;
		v[a].erase(i);
		a=b;
		st.push(a);
	}
	return 0;
}