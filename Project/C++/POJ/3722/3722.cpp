#include "iostream"
#include "stdio.h"

using namespace std;

int main()
{
	long m,n;
	long a,am;
	int cs;
	int i,j;
	bool exist=false;
	cin>>cs;
	while(cs--){
		cin>>n>>m;
	
		exist=false;
		for(i=1;i<=n;i++){
			if(n%i) continue;
			if(n%(m-i)) continue;
			exist=true;
			break;
		}
		if(exist) cout<<i<<endl;
		else cout<<"-1\n";
	}
	return 0;
}