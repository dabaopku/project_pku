#include "iostream"
#include "stdio.h"
using namespace std;
void solve(int a,int b,int n,int &x,int &y)
{
	int x1,x2,y1,y2;
	y1=-1;
	while((n-b*y1)%a) y1--;
	x1=(n-b*y1)/a;
	x2=-1;
	while((n-a*x2)%b) x2--;
	y2=(n-a*x2)/b;
	if(x1-y1<y2-x2){
		x=x1;y=y1;
	}
	else {
		x=x2;y=y2;
	}
}

void pour(char fill,char empty,int a,int b,int x,int y)
{
	int na=0,nb=0;
	for(int i=0;i<x;i++){
		cout<<"fill "<<fill<<endl;
		na+=a;
		cout<<"pour "<<fill<<" "<<empty<<endl;
		if(na>=(b-nb)){
			na-=b-nb;
			nb=0;
			cout<<"empty "<<empty<<endl;
		}
		else{
			nb+=na;
			na=0;
		}
	}
	if(fill=='A') cout<<"pour A B\n";
	cout<<"success\n";
}
int main()
{
	int a,b,n;
	while(cin>>a>>b>>n){
		int x,y;
		if(n==b){
			cout<<"fill B\n";
			cout<<"success\n";
			continue;
		}
		if(n%a==0){
			for(int i=0;i<n/a;i++)
				cout<<"fill A\npour A B\n";
			cout<<"success\n";
			continue;
		}
		solve(a,b,n,x,y);
		if(x>0) pour('A','B',a,b,x,-y);
		else pour('B','A',b,a,y,-x);

	}
	return 0;
}