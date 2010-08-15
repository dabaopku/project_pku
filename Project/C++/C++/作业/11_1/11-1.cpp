#include "list"
#include "iostream"
using namespace std;
template <class T>
class MyClass:public list<T>
{
public:
	T & operator[] (int n)
	{
		iterator i;
		int k = 0;
		for( i = this->begin(); i != this->end(); i++) {
			if( k == n)
				return *i;
			k ++;
		}
	}
	MyClass(int n):list<T>(n) {
	}
};
int main()
{
	MyClass<int> obj(5);
	int a[] = { 5, 3, 4, 2,1 };
	copy( a, a + 5, obj.begin());
	ostream_iterator<int> output(cout,"*");
	copy( obj.begin(),obj.end(),output);
	cout << endl;
	obj.sort();
	copy( obj.begin(),obj.end(),output);
	cout << endl;
	obj[2] = 9;
	copy( obj.begin(),obj.end(),output);
}

