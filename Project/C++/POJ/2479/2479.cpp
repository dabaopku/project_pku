#include "stdio.h"
#include "iostream"
using namespace std;

int main()
{
	int cs;
	int n,i,j,k,l;
	long a[50005];
	long ans,temp;
	cin>>cs;
	while(cs--){
		cin>>n;
		ans=0;
		long min,max;
		memset(a,0,sizeof(a));
		a[0]=10050;
		scanf("%ld",&a[1]);
		max=min=a[1];
		for(i=2;i<=n;i++){
			scanf("%ld",&a[i]);
			a[i]+=a[i-1];
			if(a[i]<min) min=a[i];
			else if(a[i]>max) max=a[i];
		}
		long min1=a[1],max1=a[2],min2=a[3],max2=a[4];
		for(i=1;i<n-2 ;i++){
			if(a[i-1]==min) break;
			if(a[i]>min1) continue;
			min1=a[i];
			max1=a[i+1];
			for(j=i+1;j<n-1;j++){
				if(a[j-1]==max) break;
				if(a[j]<max1) continue;
				max1=a[j];
				min2=a[j+1];
				for(k=j+1;k<n;k++){
					if(a[k-1]==min) break;
					if(a[k]>min2) continue;
					min2=a[k];
					max2=a[k+1];
					for(l=k+1;l<=n;l++){
						if(a[l-1]==max) break;
						if(a[l]<max2) continue;
						max2=a[l];
						temp=a[j]-a[i]+a[l]-a[k];
						if(temp>ans) {ans=temp;}
						
					}
				}
			}
		}
		cout<<ans<<endl;

	}
}