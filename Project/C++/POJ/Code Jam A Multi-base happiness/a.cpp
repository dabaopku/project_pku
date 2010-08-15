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

int cnt;
int base[20];
bool used[50000000];
int a[10000];

bool trys(int num,int ba)
{
	if(num==1) return true;
	if(used[num]) return false;
	used[num]=1;
	int t=0;
	while(num){
		a[t]=num%ba;
		t++;
		num/=ba;
	}
	num=0;
	for(int i=0;i<t;i++)
		num+=a[i]*a[i];
	return trys(num,ba);
}

bool check(int num)
{
	for(int i=0;i<cnt;i++){
		memset(used,0,sizeof(used));

		if(!trys(num,base[i]))
			return false;
	}
	return true;
}
int solve()
{
	int cur=2;
	while(!check(cur)){
		cur++;
	}

	return cur;
}
int main()
{
	freopen("a.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int cs;
	cin>>cs;
	for(int ii=1;ii<=cs;ii++){
		cout<<"Case #"<<ii<<": ";
		int i;
		cnt=0;
		cin.ignore();
		while(cin.peek()!='\n'){
			cin>>base[cnt++];
		}
	//	for(i=0;i<cnt;i++)
	//		cout<<base[i];
		cout<<solve();
		cout<<endl;
	}
}