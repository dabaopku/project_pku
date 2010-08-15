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

int n;
double csum[3010];
double a0,an1;
double c;

int main()
{
	int i,j;
	cin>>n;
	cin>>a0>>an1;
	csum[0]=0.0;
	for(i=1;i<=n;i++){
		cin>>c;
		csum[i]=csum[i-1]+c;
	}
	double sum=n*1.0*a0+an1;
	for(i=1;i<=n;i++)
		sum-=2.0*csum[i];
	printf("%.2lf\n",sum/(1.0*(n+1)));
}