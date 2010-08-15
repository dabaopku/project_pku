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

int tonum(string s)
{
	int ans=0;
	for(int i=0;i<8;i++)
		ans=ans*2+s[i]-'0';
	return ans;
}
void solve(char *a)
{
	string s;
	for(int i=0;i<4;i++){
		s="";
		for(int j=0;j<8;j++)
			s+=a[i*8+j];
		int t=tonum(s);
		cout<<t<<(i==3?'\n':'.');
	}
}
int main()
{
	int cs;
	cin>>cs;
	while(cs--){
		char a[40];
		cin>>a;
		solve(a);
	}
}