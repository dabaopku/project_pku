#include "iostream"
#include "stdio.h"
#include"string.h"
using namespace std;

int main()
{
	char a[12]={0},b[12]={0};
	while(cin>>a,cin>>b,a[0]!='0'||b[0]!='0'){
		if(strlen(a)<strlen(b)){
			char c[12];
			strcpy(c,a);
			strcpy(a,b);
			strcpy(b,c);
		}
		_strrev(a);_strrev(b);
		int i=0;
		int num=0;
		while(a[i] && b[i]){
			if(a[i]+b[i]-'0'-'0'>9){
				num++;
				b[i+1]++;
				if(b[i+1]==1) b[i+1]='1';
			}
			i++;
		}
		if(a[i]>'9' || b[i]>'9') num++;
		if(num==0) cout<<"No";
		else cout<<num;
		cout<<" carry operation";
		if(num>=2) cout<<"s";
		cout<<".\n";
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
	}
	return 0;
}

