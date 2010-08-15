#include "iostream"
using namespace std;
int a[10];
int b[10]={0};
int c[10];
int mini=100000;
void solve()
{
	int i;
	for(i=1;i<=9;i++)
	cin>>a[i];
	for(b[1]=0;b[1]<4;b[1]++){
		for(b[2]=0;b[2]<4;b[2]++){
			for(b[3]=0;b[3]<4;b[3]++){
				b[4]=(400-a[1]-b[1]-b[2])%4;
				b[5]=(400-a[2]-b[1]-b[2]-b[3])%4;
				b[6]=(400-a[3]-b[2]-b[3])%4;
				b[7]=(400-a[4]-b[1]-b[4]-b[5])%4;
				b[8]=(400-a[7]-b[4]-b[7])%4;
				b[9]=(400-a[9]-b[6]-b[8])%4;
			//	for(i=1;i<=9;i++)
			//		cout<<b[i]<<" ";
			//	cout<<endl;
				if((a[5]+b[1]+b[3]+b[5]+b[7]+b[9])%4==0
					&& (a[6]+b[3]+b[5]+b[6]+b[9])%4==0
					&& (a[8]+b[5]+b[7]+b[8]+b[9])%4==0){
						int sum=0;
						for(i=1;i<=9;i++)
							sum+=b[i];
						if(sum<mini){
					//		cout<<sum<<endl;
							mini=sum;
							for(i=1;i<=9;i++)
								c[i]=b[i];
						} 
				}
			}
		}
	}
}
void print()
{
	bool flag=0;
	for(int i=1;i<=9;i++){
		while(c[i]--){
			if(flag) cout<<" ";
			else flag=1;
			cout<<i;
		}
	}
	cout<<endl;
}
int main()
{	
	solve();
	print();
}