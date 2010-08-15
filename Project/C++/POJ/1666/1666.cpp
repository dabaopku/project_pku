#include"iostream"
#include "stdio.h"
using namespace std;

bool isSame(int *a,int n)
{
	for(int i=1;i<n;i++)
		if(a[i]!=a[0]) return false;
	return true;
}
int main()
{
	int n;
	while(cin>>n,n){
		int * candy = new int[n];
		int * take = new int[n];
		memset(candy,0,sizeof(int)*n);
		memset(take,0,sizeof(int)*n);
		int i=0;
		for(i=0;i<n;i++)
			cin>>candy[i];
		int round=0;
		while(!isSame(candy,n)){
			round++;
			for(i=0;i<n;i++){
				candy[i]=candy[i]/2;
				take[i]=candy[i];
			}
			for(i=0;i<n-1;i++){
				candy[i+1]+=take[i];
			}
			candy[0]+=take[n-1];
			for(i=0;i<n;i++){
				if(candy[i]%2)
					candy[i]+=1;
			}
		}
		
		cout<<round<<" "<<candy[0]<<endl;
		delete []candy;
		delete []take;
	}
}