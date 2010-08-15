#include "iostream"
#include "stdio.h"

using namespace std;

int main()
{
	int first,second;
	int cs;
	char cmd[20];
	cin>>first>>cs;
	while(cs--){
		cin>>cmd>>second;
		switch (cmd[1])
		{
		case 'u':
			first*=second;
			break;
		case 'i':
			first-=second;
			break;
		case 'l':
			first+=second;
			break;
		}
	}
	cout<<first<<endl;
	return 0;
}