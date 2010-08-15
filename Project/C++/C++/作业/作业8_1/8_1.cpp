#include <vector>
#include <iostream>
using namespace std;
class A {
private :
	int nId;
public:

	A(int n) { 
		nId = n; 
		cout << nId << " contructor" << endl; 
	};
	A( const A & a ) {
		nId = a.nId ;
		cout << nId << " copy constructor" << endl;
	}

	~A( ) {
		cout << nId << " destructor" << endl;
	}
};
int main()
{
	vector<A*> vp;
	vp.push_back(new A(1));
	vp.push_back(new A(2));
	vector<A> v;
	v.push_back (3);
	delete vp[0];
	delete vp[1];
}
