#include "iostream"
#include "list"
#include "stdio.h"
using namespace std;

class person
{
	string name;
	int days;
public:
	person(char * n,int num=0):name(n),days(num){};
	person(){};
	friend int count(int y1,int m1,int d1,int y2,int m2,int d2,person &p);
	friend ostream & operator<<(ostream &output,person &input);
	friend bool operator>(const person & a , const person & b){
		return a.days>b.days;
	}
};

bool isRun(int year)
{
	if(year%4 || (year%400 && !(year%100))) return false;
	return true;
}
ostream& operator<<(ostream &output,person &input)
{
	output<<input.name.c_str()<<" "<<input.days;
	return output;
}
int count(int y1,int m1,int d1,int y2,int m2,int d2,person &p)
{
	int days=0,i;
	int mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	for(i=y1+1;i<y2;i++)
		if(isRun(i)) days+=366;
		else days+=365;
		if(y2>y1){
			for(i=m1+1;i<13;i++){
				days+=mon[i];
				if(i==2 && isRun(y1)) days++;
			}
			for(i=1;i<m2;i++){
				days+=mon[i];
				if(i==2 && isRun(y2)) days++;
			}
			days+=mon[m1]-d1+d2;
			if(m1==2 && isRun(y1)) days++;
	}
	else {
		for(i=m1+1;i<m2;i++)
			days+=mon[i];
		if(m1!=m2){
			days+=mon[m1]-d1+d2;
			if(m1==2 && isRun(y1)) days++;

		}
		else days+=d2-d1;
	}
	days++;
	p.days=days;
	return 1;
}
typedef list<person> ml;

int main()
{
	ml info;
	char line[100];
	int y1,y2,m1,m2,d1,d2;
	char name[100];
	int n,i;
	cin>>n;
	cin.get();
	for(i=0;i<n;i++){
		cin.getline(line,100,'\n');
		sscanf(line,"%s%d%d%d%d%d%d",name,&y1,&m1,&d1,&y2,&m2,&d2);
		person p(name);
		count(y1,m1,d1,y2,m2,d2,p);
		info.push_back(p);
	}
	info.sort(greater<person>());
	ml::iterator j;
	for(j=info.begin();j!=info.end();j++)
		cout<<*j<<endl;
	return 0;
}
