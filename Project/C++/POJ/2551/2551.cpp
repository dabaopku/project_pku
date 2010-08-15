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

int n;
void solve(int n)
{
	int len=1;
	int s=1;
	while(s){
		len++;
		s=s*10+1;
		s%=n;
	}
	cout<<len<<endl;
}
int main()
{
	while(cin>>n)
		solve(n);
}