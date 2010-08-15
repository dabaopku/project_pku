#include "iostream"
#include "stdio.h"

using namespace std;
int isRun( const int year )
//判断某年是否是闰年
{
	if(year%4 || (year%400 && !(year%100))) return 0;
	return 1;
}
int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
class cTime
{
public:
	int y,mo,d,h,m,s;
	cTime (){};
	cTime (unsigned long t):y(0),mo(0),d(0),h(0),m(0),s(0){
		s=t%60;
		t/=60;
		m=t%60;
		t/=60;
		h=t%24;
		t/=24;
		y=1970;
		while(t>=365+isRun(y)){
			t-=365+isRun(y);
			y++;
		}

			/*if(t==366 && isRun(y)){
				y++;
				mo=1;
				d=1;
			}
			else if(t==366 && !isRun(y)){
				y++;
				mo=1;
				d=2;
			}
			else if(t==365 && isRun(y)){
				mo=12;
				d=31;
			}
			else if(t==365 && !isRun(y)){
				mo=1;
				d=1;
				y++;
			}
			else{*/
				t++;
				mo=1;
				while(t){
					if(mo==2 && isRun(y) && t==29){
						mo=2;
						d=29;
						break;
					}
					if(mo==2 && isRun(y) && t>29){
						t-=29;
						mo=3;
					}
					else if(t>month[mo]){
						t-=month[mo];
						mo++;
					}
					else{
						d=t;
						t=0;
					}
				}
			


	}
	friend void print(cTime a)
	{
		printf("%d-%02d-%02d %02d:%02d:%02d\n",a.y,a.mo,a.d,a.h,a.m,a.s);
	}
};
int main()
{
	unsigned long t;

	while(cin>>t){

		cTime tm(t);
		print(tm);

	}
	return 0;
}