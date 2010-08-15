#include "iostream"
#include "stdio.h"
#include "algorithm"
using namespace std;

int main()
{
	int cs;
	int n,i,j,k,a[110];
	cin>>cs;
	while(cs--){
		cin>>n;
		memset(a,0,sizeof(a));
		for(i=0;i<n;i++)
			cin>>a[i];
		//sort(a,a+n);
		bool br=false;
		int num=0;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(j==i) continue;
				for(k=0;k<n;k++){
					if(k==j || k==i) continue;
					if(a[j]+a[k]==a[i]){
						br=true;
						num++;
						break;
					}
				}
				if(br) break;
			}
			br=false;
		}
		cout<<num<<endl;
	}
	return 0;
}