#include "iostream"
#include "string"
#include "set"
using std::set;
using std::endl;
using std::cout;
using std::string;
using std::ostream;
using std::_Outit;

template<class T>
class MyOstream_iterator//:public _Outit
{
public:string cDivider;		//分隔符
	ostream  & oStr;			//输出流
public:
	
	MyOstream_iterator( ostream & output , const char *div="")
		: oStr(output),cDivider(div){};

	MyOstream_iterator<T> & operator = ( const T & a ){
		oStr << a << cDivider;
		return *this;
	}

	MyOstream_iterator<T> &operator *()
	{
		return *this;
	}
	MyOstream_iterator<T> &operator++()
	{
		return *this;
	}
	MyOstream_iterator<T> operator++(int)
	{
		return *this;
	}
	
};


//////////////////////////////////////////////////////////////////////
//	以下是从网上找的一段代码,原来使用 ostream_iterator,现在改为		//
//	MyOstream_iterator												//
//////////////////////////////////////////////////////////////////////
class Person
{
public:
	Person(const string& firstname,const string& lastname)
	{
		this->firstname=firstname;
		this->lastname=lastname;
	}
	friend ostream& operator <<(ostream& os,const Person& p)
	{
		os<<p.lastname<<" "<<p.firstname;
		return os;
	}
private: 
	string firstname ; 
	string lastname ;
	friend class PersonSort;
};

class PersonSort
{   
public:
bool operator()(const Person& p1,const Person& p2) const
{
return (p1.lastname<p2.lastname ||(p1.lastname==p2.lastname) && (p1.firstname <p1.firstname));
}
};

int main()
{
	typedef set<Person,PersonSort> PersonSet;
	PersonSet ps;
	ps.insert(Person("Cong","Guo"));
	ps.insert(Person("Yilei","Wang"));
	ps.insert(Person("Ziyi","Su"));
	ps.insert(Person("Yexin","Ding"));

	copy(ps.begin(),ps.end(),MyOstream_iterator<Person>(cout,"\n"));
	
	return 0;
}