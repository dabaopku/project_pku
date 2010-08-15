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
#include "stack"

using namespace std;

int main()
{
	char a[4][100];
	int i,j;
	int cnt[26]={0};
	for(i=0;i<4;i++){
		cin.getline(a[i],100,'\n');
		j=0;
		while(a[i][j]){
			if(a[i][j]<='Z' && a[i][j]>='A')
				cnt[a[i][j]-'A']++;
			j++;
		}
	}

	int maxi=0;
	for(i=0;i<26;i++)
		if(cnt[i]>maxi) maxi=cnt[i];
	while(maxi){
		for(i=0;i<26;i++)
			if(cnt[i]>=maxi) cout<<"* ";
			else  cout<<"  ";
		cout<<endl;
		maxi--;
	}

	for(i=0;i<26;i++)
		cout<<(char)(i+'A')<<' ';
	cout<<endl;
}