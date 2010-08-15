#include "stdio.h"
#include "iostream"
#include "string"
#include "cstdio"
using namespace std;

__int64 num[12][12];
__int64 dp[2200][12];
int max1;
int able[146]={0,3,6,12,15,24,27,30,48,51,54,60,63,96,99,102,108,111,120,123,126,192,195,198,204,207,216,219,222,240,243,246,252,255,384,387,390,396,399,408,411,414,432,435,438,444,447,480,483,486,492,495,504,507,510,768,771,774,780,783,792,795,798,816,819,822,828,831,864,867,870,876,879,888,891,894,960,963,966,972,975,984,987,990,1008,1011,1014,1020,1023,1536,1539,1542,1548,1551,1560,1563,1566,1584,1587,1590,1596,1599,1632,1635,1638,1644,1647,1656,1659,1662,1728,1731,1734,1740,1743,1752,1755,1758,1776,1779,1782,1788,1791,1920,1923,1926,1932,1935,1944,1947,1950,1968,1971,1974,1980,1983,2016,2019,2022,2028,2031,2040,2043,2046};


int r,c;


long pow(long a,long b)
{
	
	long num=1;
	while(b--)
		num*=a;
	return num;
}
/*bool belong(int n)
{
	for(int i=0;i<145;i++){
		if(able[i]==n) return true;
		//if(n<able[i]) break;
	}
	return false;
}*/
bool belong(int n){
	if(n==0) return true;
	char a[13];
	memset(a,0,sizeof(a));
		_itoa(n,a,2);
		int s;
		s=0;
		while(a[s]!=0){
			while(a[s]!='1' && a[s]!=0)
				s++;
			if(a[s]==0){
				return true;
			}
			if(a[s+1]==0) return false;;
			if(a[s+1]!='1') return false;;
			s+=2;
			if(a[s]==0){
				return true;
			}
		}
		return true;
}
void solve(int state,int n)
{	
	if(dp[state][n]!=-1) return;
	if(n==1){
		if(belong(state)) dp[state][n]=1;
		else dp[state][n]=0;
		return ;
	}
	
	int i;
	dp[state][n]=0;
	for(i=0;i<=max1;i++){
		if((i|state)!=max1) continue;
		if(!belong(i&state)) continue; 
		solve(i,n-1);
		dp[state][n]+=dp[i][n-1];
	}
	return;
}
int main()
{
	
	while(cin>>r>>c,r&&c){
		memset(dp,-1,sizeof(dp));
		if((r*c)%2 || r==0 || c==0){
			cout<<"0\n";
			continue;
		}
		else{
			if(r>c){
				int temp=r;
				r=c;
				c=temp;
			}
			max1=pow(2,c)-1;
			solve(max1,r);
			printf("%I64d\n",dp[max1][r]);
			continue;
		}
	}
}