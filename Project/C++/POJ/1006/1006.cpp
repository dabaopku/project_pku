#include "iostream"
using namespace std;

int main()
{
	int a,b,c;
	int i;
	long sum;
	int start;
	int cs=0;
	while(cin>>a>>b>>c>>start,!(a==-1&&b==-1&&c==-1&&start==-1)){
		cs++;
		sum=c;
		b%=28;
		while(sum%28!=b)
			sum+=33;
		a%=23;
		while(sum%23!=a)
			sum+=28*33;
		if(sum<=start) sum+=28*33*23;
		sum-=start;
		sum%=21252;
		if(sum==0) sum=21252;
		cout<<"Case "<<cs<<": the next triple peak occurs in "
			<<sum<<" days."<<endl;
	}
}