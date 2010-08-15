//Êä³ö½á¹û
//1 2 6 7 8 9
#include "iostream"
#include "set"
using namespace std;
int main()
{
	int a[] = {8,7,8,9,6,2,1};
	set<int> v;
	for( int i = 0;i < 7;i ++ )
		v.insert(a[i]);
	ostream_iterator<int> o(cout," ");
	copy( v.begin(),v.end(),o);
}

