#include "iostream"
#include "stdio.h"
#include "math.h"
using namespace std;


int main()
{
	unsigned long m,n;
	do{
		scanf("%ld%ld",&m,&n);
		if(m==0 && n==0) return 0;
		int num=0;
		unsigned long rmax=m,lmax=m;
		while(rmax<n){
			lmax*=2;
			rmax=rmax*2+1;
			num++;
		}

		m=0;
		for(int i=0;i<=num;i++)
			m+=1<<i;
		//cout<<num<<" "<<max<<" "<<m<<endl;
		if(lmax<=n) cout<<m-(rmax-n)<<endl;
		else cout<<m-rmax+lmax-1<<endl;

	}while(true);
	return 0;
}