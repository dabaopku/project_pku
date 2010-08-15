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
	string a[5];
	for(int i=0;i<5;i++)
		cin>>a[i];
	sort(a,a+5);
	for(int i=0;i<5;i++)
		cout<<a[i]<<endl;
}