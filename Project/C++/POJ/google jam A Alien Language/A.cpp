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

const int MAXN=100000;
int prime[MAXN/10];
bool notprime[MAXN];

void gen_prime(){
	int i,j;
	int cnt=0;
	memset(notprime,0,sizeof(notprime));
	for(i=2;i<MAXN;i++){
		if(!notprime[i]){
			prime[cnt++]=i;
		}
		for(j=0;j<cnt && prime[j]*i<MAXN ;j++)
			notprime[prime[j]*i]=1;
	}
	//	for(i=0;i<100;i++)
	//		cout<<prime[i]<<endl;
}


int Euler(int num)
{
	int ret=num;
	int i;
	for(i=0;i<MAXN;i++){
		if(num<prime[i]){
			if(num>1) ret-=ret/num;
			break;
		}
		if(num%prime[i]) continue;
		ret-=ret/prime[i];
		while(num%prime[i]==0)
			num/=prime[i];
	}
	return ret;
}

vector<int> Factors(int num)
{
	vector<int> ret;
	int i;
	for(i=1;i*i<=num;i++){
		if(num%i) continue;
		ret.push_back(i);
		if(i!=num/i) ret.push_back(num/i);
	}
	sort(ret.begin(),ret.end());

//	vector<int>::iterator  vi;
//	for(vi=ret.begin();vi!=ret.end();vi++)
//		cout<<*vi<<" ";
//	cout<<endl;

	return ret;
}
int main()
{
//	gen_prime();
	int i;
	i=19891219;
	//for(int i=1;i<100;i++)
	//cout<<i<<" "<<FactorNum(i)<<endl;
	Factors(i);
;}


