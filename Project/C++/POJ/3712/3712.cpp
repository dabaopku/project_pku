#include "iostream"
#include "stdio.h"

using namespace std;

int main()
{
	int cs;
	char str[25],num[25];
	int ch[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
	cin>>cs;
	while(cs--){
		cin>>str>>num;
		if(strlen(str)!=strlen(num)){
			cout<<'N'<<endl;
			continue;
		}
		_strlwr(str);
		int i=0;
		bool yes=true;
		while(str[i]){
			if(ch[str[i]-'a']!=num[i]-'0'){
				cout<<'N'<<endl;
				yes=false;
				break;
			}
			i++;
		}
		if(yes) cout<<'Y'<<endl;
	}
	return 0;
}