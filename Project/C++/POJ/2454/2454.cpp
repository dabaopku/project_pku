#include "stdio.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "algorithm"
#include "math.h"
using namespace std;
int n;
struct cow
{
	int num1,id;
};
cow num[185];
int order1[185];
int cmp(const void *a,const void *b)
{
	return ((cow*)b)->num1 - ((cow *)a)->num1;
}
int main()
{
	int i,j;
	cin>>n;
	for(i=0;i<n*3;i++){
		cin>>num[i].num1;
		num[i].id=i+1;
	}
	for(i=0;i<=3*n;i++)
		order1[i]=i;
	qsort(num,3*n,sizeof(cow),cmp);
	while(true){
		random_shuffle(order1,order1+2*n);
		int big=0;
		for(j=0;j<2;j++){
			int sum=0;
			for(i=0;i<n;i++)
				sum+=num[order1[j*n+i]].num1;
			if(sum>1000*n/2) big++;
		}
	if(big>=2) break;
	}
	for(i=0;i<n*3;i++)
		cout<<num[order1[i]].id<<endl;
}