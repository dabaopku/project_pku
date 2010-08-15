#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
template <class T>
class MyMax
{
public:
	T * pMax;  //指向用于存放最大值的变量
	bool bFirst; //记录最大值时会用到的标记
	MyMax (T * p):bFirst(true),pMax(p) { };
	//开头
		MyMax<T> & operator = ( T & tValue )
		{
			if(bFirst){
				*pMax = tValue ;
				bFirst = false;
			}
			else if ( *(this->pMax) < tValue ) {

				*pMax = tValue ;
				
			}
			return *this;
		}
		MyMax<T> &operator ++ ( )
		{
			return *this;
		}
		MyMax<T> &operator ++ ( int )
		{
			return *this;
		}
		MyMax<T> & operator * ()
		{
			return *this;
		}
		T & operator() ()
		{
			return *(this->pMax);
		}

	//……
	//结尾
};
class A {
public:

	int i;
	
	A( int n) :i(n) { };
	A() { };
};
bool operator < ( const A & a1, const A & a2)
{
	return a1.i < a2.i ;
}
ostream & operator<<( ostream & o, const A & a)
{
	o << a.i;
	return o;
}
int main()
{
	A a[5] = {A(1),A(5),A(3),A(4),A(2)};
	int b[9] = {1,5,30,40,2,136,80,20,6};
	int nMax; 
	A aMax; 
	MyMax<A> outputa( & aMax);
	copy(a,a+5,outputa); 
	cout << outputa() << endl;
	MyMax<int> output( & nMax);
	copy(b,b+9,output);
	cout << output() << endl;
}

