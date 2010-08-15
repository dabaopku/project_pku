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

int main()
{
	stack<string> fore,bac;
	string a;
	string cur="http://www.acm.org/";
	while(cin>>a,a!="QUIT"){
		if(a=="VISIT"){
			cin>>a;
			bac.push(cur);
			cur=a;
			while(!fore.empty())
				fore.pop();
			cout<<a<<endl;
		}
		else if(a=="BACK"){
			if(bac.empty()){
				cout<<"Ignored\n";
			}
			else{
				fore.push(cur);
				cur=bac.top();
				bac.pop();
				cout<<cur<<endl;
			}
		}
		else{
			if(fore.empty()){
			cout<<"Ignored\n";
		}
		else{
			bac.push(cur);
			cur=fore.top();
			fore.pop();
			cout<<cur<<endl;
		}

		}
	}
}