#include "iostream"
#include"stdio.h"
#include "string"
using namespace std;

int main()
{
	int n;
	while(cin>>n,n){
		int i=1;
		int num=0;
		int x;
		string que="";
		string stack="0";
		for(;i<=n;i++){
			cin>>x;
			stack.append(1,x+'0');
		}
		for(i=n;i>=1;i--){
			if(stack[i]==i+'0') continue;
			int loc=stack.find(i+'0');
			if(loc!=1){
				que.append(1,' ');
				que.append(1,loc+'0');
				for(int j=1;j<=loc/2;j++){
					swap(stack[j],stack[loc+1-j]);
				}
				num++;
			}
			que.append(1,' ');
			que.append(1,i+'0');
			for(int j=1;j<=i/2;j++)
				swap(stack[j],stack[i+1-j]);
			num++;
		}
		cout<<num<<que<<endl;
	}
}