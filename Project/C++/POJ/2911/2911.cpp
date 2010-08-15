#include "stdio.h"
#include "iostream"
#include "string.h"
#include "math.h"
#include "string"
#include "vector"
#include "set"
#include "map"
#include "queue"
#include "list"

using namespace std;

int main()
{
	int maxi;
	cin>>maxi;
	for(int i=32;i<100;i++){
		if(i*i>=maxi) break;
		for(int j=32;j<i;j++){
			int t=i*i-j*j;
			if(t<1000) continue;
			int d=t%10;
			while(t){
				if(t%10!=d) break;
				t/=10;
			}
			if(t==0) cout<<i*i<<endl;
		}
	}
}