#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
int main()
{
	int m,n,a,i,j,max,min;
	cin>>m>>n;
	max=INT_MIN;min=INT_MAX;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>a;
			if(a>max) max=a;
			if(a<min) min=a;
		}
	}
	cout<<max<<" "<<min<<endl;
}