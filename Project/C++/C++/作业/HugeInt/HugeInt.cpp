#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
using std::ostream; 
using std::cout; 
using std::cin; 
using std::endl; 
const int MAX = 110; 

class CHugeInt
{
private:
	char *p ; int len;
public:

	////////            构造与析构         //////////
	CHugeInt(){}
	CHugeInt(const char *s){
		len=strlen(s)+1;
		p=new char [len];
		memset(p,0,len*sizeof(char));
		strcpy(p,s);
	}
	CHugeInt(long s ){
		p=new char [11];
		memset(p,0,11*sizeof(char));
		itoa(s,p,10);
		len=strlen(p)+1;
	}
	CHugeInt(CHugeInt & a )
	{
		len=a.len;
		p=new char [len];
		memset(p,0,len*sizeof(char));
		strcpy(p,a.p);len=strlen(p)+1;
	}
	~CHugeInt(){ if(p) delete []p ; }

	///////         加法重载          /////////
	CHugeInt & operator + ( long s )
	{
		char *tm;
		int i;
		tm=new char[11]; 
		memset(tm,0,11*sizeof(char));
		itoa(s,tm,10);
		int tmlen=strlen(tm)+1;
		strrev(tm);strrev(p);
		for(i=0;i<len-1 && i<tmlen-1;i++)
			*(p+i)+=*(tm+i)-'0';
		if(len<tmlen){
			for(i=0;i<len-1;i++) *(tm+i)=*(p+i);
			len = tmlen ;
			delete []p;p=tm;
		}
		for(i=0;i<len-2;i++){
			if(p[i]-'0'>9) {
				p[i+1]+=(p[i]-'0')/10;
				p[i]=(p[i]-'0')%10+'0';
			}
		}
		len=strlen(p)+1;
		if(p[len-2]-'0'>9){
			tm=p;len++;p=new char[len];
			memset(p,0,len*sizeof(char));
			for(i=0;i<len-2;i++)
				p[i]=tm[i];p[len-2]=(p[len-3]-'0')/10+'0';
			delete []tm;
			p[len-3]=(p[len-3]-'0')%10+'0';
		}
		strrev(p);
		return *this;
	}

	friend CHugeInt & operator+ ( long s,CHugeInt & a){
		return a+s;
	}

	CHugeInt & operator + (CHugeInt & a){
		int i;
		if(a.len>len) return a+*this;
		strrev(p);strrev(a.p);
		for( i=0;i<a.len-1;i++){
			p[i]+=*(a.p+i)-'0';
		}
		for(i=0;i<len-2;i++){
			if(p[i]-'0'>9){
				p[i+1]+=(p[i]-'0')/10;
				p[i]=(p[i]-'0')%10+'0';
			}
		}
		if(p[len-2]-'0'>9){
			char *tm=p;
			len++;
			p=new char[len];
			memset(p,0,len*sizeof(char));
			for(i=0;i<len-2;i++) p[i]=tm[i];
			delete []tm;
			p[len-2]=(p[len-3]-'0')/10;
			p[len-3]=(p[len-3]-'0')%10+'0';
		}
		strrev(p);
		return *this;
	}
	////////          其他符号             /////////////
	friend ostream & operator << ( ostream & out ,CHugeInt & a){
		out<<a.p;
		return out;
	}
	CHugeInt & operator ++(){
		*this+1;
		return *this;
	}
	CHugeInt operator ++(int t){
		CHugeInt  tm=*this;
		*this+1;
		return tm;
	}
	CHugeInt & operator += (long s){
		*this+s;
		return *this;
	}
	CHugeInt & operator = ( CHugeInt &b )
	{
		len=b.len;delete []p;
		p=new char [len];
		strcpy(p,b.p);
		return *this;
	}

};
void main() 
{ 
	CHugeInt a("1234545436342424354354365289899834234235"); 
	CHugeInt d(9999); 
	CHugeInt temp = CHugeInt("100000088888888") + 111112; 
	CHugeInt temp2 = 111112 + CHugeInt("100000088888888"); 
	cout << "1)" << temp << endl; 
	cout << "2)" << temp2 << endl; 
	cout << "3)" << ++d << endl; 
	cout << "4)" << d++ << endl; 
	cout << "5)" << d << endl; 
	d += 5; 
	cout << "6)" << d << endl; 
	cout << "7)" << d + temp; 

}
