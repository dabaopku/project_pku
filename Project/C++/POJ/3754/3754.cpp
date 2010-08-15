#include "stdio.h"
#include "iostream"
#include "string"
using namespace std;
int main()
{
	int i,j;
	int alen,blen;
	string a,b,c,d;
	do{
		cin>>a>>b;
		alen=a.length();blen=b.length();
		if(alen==1 || blen==1) break;
		d.clear();
		a+=a;b+=b;
		if(alen>blen)
			a.swap(b);
			i=0;j=1;
			while(i<alen){
				while(j<=alen){
					c=a.substr(i,j);
		//			cout<<c<<endl;
					if(b.find(c)!=string::npos){
						if(c.length()>d.length()) d=c;
						j++;
					}
					else{
						j=1;
						break;
					}
				}
				i++;
			}
			cout<<d.length()<<endl;		
			
		
	}while(true);
}