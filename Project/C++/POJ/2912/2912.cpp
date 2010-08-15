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

set<int> t,s;

int ins(int n)
{
	while(n){
		s.insert(n%10);
		n/=10;
	}
	return s.size();
}
int main()
{
	int maxi;
	cin>>maxi;
	int a=361,b=529,c=784;
	if(a<maxi) cout<<a;
	if(b<maxi) cout<<" "<<b;
	if(c<maxi) cout<<" "<<c;
	cout<<endl;
}