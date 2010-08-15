#include "iostream"
#include "stdio.h"
using namespace std;
void swap(int &x,int &y)
{
	int temp=x;
	x=y;
	y=temp;
}
int main()
{
	int x,y;
	cin>>x>>y;
	if(x>y)
		swap(x,y);
	while(x!=y){
		y=y/2;
		if(x>y) swap(x,y);
	}
	cout<<x<<endl;
}