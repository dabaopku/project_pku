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

using namespace std;

int main()
{
	int a[6];
	for(int i=0;i<6;i++)
		cin>>a[i];
	int sum=0;
	for(int i=1;i<6;i++)
		if(a[i]<a[0]) sum+=a[i];
	cout<<sum<<endl;
}