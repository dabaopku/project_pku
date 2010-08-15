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

void insert(char *p)
{
	while(*p)
		cout<<*(p++)<<" ";
	cout<<endl;
}
int main()
{
	char str[100];
	while(cin.getline(str,100,'\n'))
		insert(str);
}