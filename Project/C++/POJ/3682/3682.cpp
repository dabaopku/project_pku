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
	int n[10];
	int odd[10],even[10];
	bool flag;
	while(true){
		flag=false;
		for(int i=0;i<10;i++){
			if(!(cin>>n[i])) {
				flag=true;
				break;
			}
		}
		if(flag) break;
		for(int i=0;i<10;i++){
			even[i]=-10;
			odd[i]=200;
			if(n[i]%2) 	even[i]=n[i];
			else odd[i]=n[i];
		}
		sort(odd,odd+10);
		sort(even,even+10);
		for(int i=9;i>=0;i--)
		{
			if(even[i]>=0) cout<<even[i];
			else break;
			if(i==0) break;
			else cout<<" ";
		}
		for(int i=0;i<10;i++)
		{
			if(odd[i]<=100) cout<<odd[i];
			else {
				cout<<'\n';
				break;
			}
			if(i==9) cout<<"\n";
			else cout<<" ";
		}
	}
}