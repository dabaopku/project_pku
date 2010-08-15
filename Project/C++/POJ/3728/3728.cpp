#include "iostream"
#include "stdio.h"
using namespace std;
int main()
{
	int a,n;
	while(cin>>a>>n){
		int *num=new int[n+2];
		int i2,i3;
		int tail;
		num[1]=a;
		tail=i2=i3=1;
		tail++;
		while(tail<=n){
			if(2*num[i2]<3*num[i3]){
				num[tail]=2*num[i2]+1;
				i2++;
				tail++;
			}
			else if(2*num[i2]>3*num[i3]){
				num[tail]=3*num[i3]+1;
				tail++;
				i3++;
			}
			else{
				num[tail]=2*num[i2]+1;
				tail++;
				i2++;
				i3++;
			}
		}
		cout<<num[tail-1]<<endl;
		delete []num; 
	}
	return 0;
}