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
	int cs;
	cin>>cs;
	cin.ignore();
	while(cs--){
		char a[81];
		cin.getline(a,sizeof(a),'\n');
		int n=strlen(a);
		if(!(a[0]<='z' && a[0]>='a' || a[0]<='Z' && a[0]>='A' || a[0]=='_')){
			cout<<0<<endl;
			continue;
		}
		int i;
		for(i=1;i<n;i++){
			if(!(a[i]<='z' && a[i]>='a' || a[i]<='Z' && a[i]>='A' 
				|| a[i]=='_' || a[i]<='9' && a[i]>='0')){
				cout<<0<<endl;
				break;
			}
		}

		if(i<n) continue;
		else cout<<1<<endl;
	}
}