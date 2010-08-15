#include "stdio.h"
#include "iostream"
#include "string"
#include"strstream"
using namespace std;
int main()
{
	char a[2600];
	char b[52][52];
	int i,j;
	while(gets(a)!=0){
		strstream s(a,2600,ios::in);
		i=0;
		while(s>>b[i++]);
		i--;
		i--;
		while(i)
			cout<<b[i--]<<" ";
		cout<<b[0]<<endl;
	}
}