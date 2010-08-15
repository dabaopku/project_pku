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
int num(int i)
{
 int len=1;
 while(i!=1){
	 if(i%2) i=i*3+1;
	 else i/=2;
	 len++;
 }
 return len;
}
int main()
{
	int a,b;
	while(cin>>a>>b){
		cout<<a<<" "<<b<<" ";
		int cnt=0;
		if(a>b){
			int t=a;
			a=b;
			b=t;
		}
		for(int i=a;i<=b;i++){
			int t=num(i);
			if(t>cnt) cnt=t;
		}
		cout<<cnt<<endl;
	}
}