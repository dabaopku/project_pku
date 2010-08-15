#include "iostream"
using namespace std;
int solve(int *b , int nn )
{
	if(nn==0 ) return 0;
	if(nn==1 ) return 1;
	int a[310];
	int n=nn;
	memcpy(a,b,sizeof(a));
	int i=0,j=0,min=62352;
	for(i=1,j=1;j<=17 && i<n ;j++,i++){
		if(a[i]==-1) {j--;continue;}
		int d=a[i]-a[0];
		int num=a[0];
		int cur=0;
		bool able=true;
		while(num<60){
			while(a[cur]!=num && cur<n )
				cur++;
			if(cur>=n){
				able=false;
				break;
			}
			num+=d;
		}
		if(!able) continue;
		cur=0;
		num=a[0];
		while(num<60){
			while(a[cur]!=num && cur<n )
				cur++;
			a[cur]=-1;
			num+=d;
		}
		while(a[0]==-1 && n ){
			for(i=1;i<n;i++)
				a[i-1]=a[i];
			n--;
		}
		num=solve(a,n)+1;
		if(num<min) min=num;
	}
	return min;

}
int main()
{
	int num;
	int n;
	int a[310];
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	num=solve(a,n);
	cout<<num<<endl;
	
}