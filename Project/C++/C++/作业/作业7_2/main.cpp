#include <iostream>
using namespace std;
template <class T>  //(a)
class myclass { 
	T i;
public:
	myclass (T a)  
	{ i = a; }
	void show( ) 
	{ cout << i << endl;	}
};
void main() {
	myclass<char*> obj("This"); //(b)
	obj.show();
}
