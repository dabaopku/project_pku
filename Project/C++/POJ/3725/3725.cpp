#include "iostream"
#include "stdio.h"
#include "vector"
#include "set"
using namespace std;

bool great(int a,int b)
{

	return a>b;
}

typedef multiset<int,greater<int>> gset;
typedef multiset<int,less<int>> lset;
int main()
{
	int n;
	gset data;
	lset  dive;
	cin>>n;
	int i,num,diff,max,order;
	for(i=0;i<n;i++){
		cin>>num;
		data.insert(num);
	}
	
	max=*(data.begin());
	num=n*max;
	gset::iterator gsi;
	for(i=1;i<n;i++){
		dive.clear();
		for(int j=0;j<i;j++)
			dive.insert(0);
		gsi=data.begin();
		while(gsi!=data.end()){
			int temp=*(dive.begin());
			dive.erase(dive.begin());
			dive.insert(temp+*gsi);
			gsi++;
		}
		lset::iterator si=dive.begin();
		diff=0;
		for(;si!=dive.end();si++){
			diff+=abs(*si-max);
		}
		if(diff<num){
			num=diff;
			order=i;
		}
		if(i>2 && *(dive.begin())+*(++dive.begin())<=max) break;
	}
	cout<<order<<endl;
	return 0;
}