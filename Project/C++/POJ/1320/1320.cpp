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
	__int64 k=2;
	int cnt=10;
	__int64 pro;
	while(cnt--){
		__int64 n;
		while(true){
			pro=k*k*(k*k+1)/2;
			n=(__int64)(sqrt(pro*1.0)+0.1);
			if(n*n==pro) break;
			pro=k*k*(k*k-1)/2;
			n=(__int64)(sqrt(pro*1.0)+0.1);
			if(n*n==pro) break;
			k++;
		}
		n--;
		__int64 p=(__int64)(sqrt(8.0*n*n+16.0*n+9.0)+0.1);
		__int64 m=(p-2*n-3)/2;
		int a=n+1,b=n+1+m;
		printf("%10d%10d\n",a,b);
		k++;
	}
}