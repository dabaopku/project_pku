#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
int main()
{
	int m,n,k;
	do{
		cin>>m;
		if(m==0) break;
		n=180*(m-2);
		m--;
		while(m--){
			cin>>k;
			n-=k;
		}
		cout<<n<<endl;
	}while(true);
}