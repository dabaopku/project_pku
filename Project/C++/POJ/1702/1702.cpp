#include "iostream"
#include "stdio.h"
#include "set"
#include "algorithm"
using namespace std;

int main()
{
	unsigned long num;
	int cs;
	set<unsigned long> sl,sr;
	cin>>cs;
	while(cs--){
		cin>>num;
		unsigned long power=1;
		sl.clear();
		sr.clear();
		while(num){
			if(num%3==1){
				sr.insert(power);
				num/=3;
			}
			else if(num%3==2){
				sl.insert(power);
				num/=3;
				num++;
			}
			else num/=3;
			power*=3;
		}
		ostream_iterator<unsigned long> output(cout,",");
		if(sl.empty()) cout<<"empty ";
		else copy(sl.begin(),sl.end(),output);
		cout<<'\b'<<' ';
		if(sr.empty()) cout<<"empty ";
		else copy(sr.begin(),sr.end(),output);
		cout<<'\b'<<'\0'<<endl;
	}
	return 0;
}