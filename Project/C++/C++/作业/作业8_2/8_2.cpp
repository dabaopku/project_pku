//Êä³ö½á¹û
//Tom,Jack,Mary,John,

#include "string"
#include "iostream"
using namespace std;
template <class T , int T2 >
class MyClass 
{
	T array[T2];
public:
	MyClass( T * begin )   
	{
		copy( begin, begin + T2, array);
	}
	void List() {
		T * i;
		for( i = array; i != array + T2;i ++)
			cout << * i << "," ;
	}
};
int main()
{
	string array[4] = { "Tom","Jack","Mary","John"};
	MyClass< string , 4 > obj( array );
	obj.List();
} 

