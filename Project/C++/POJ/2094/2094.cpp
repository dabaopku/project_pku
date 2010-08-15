#include "stdio.h"
#include "iostream"
#include "string.h"
#include "math.h"
#include "string"
#include "vector"
#include "set"
#include "map"
#include "queue"
#include "list"
#include "stack"

using namespace std;

const int base=10000000;

char a[1010];
char b[12][1010];

class BigNum
{
public:
	int digit[160];
//	int m;


	BigNum(int n =0){
		int i;
		for(i=1;i<160;i++)
			digit[i]=0;
		digit[0]=n;
		i=0;
		while(digit[i]>=base){
			digit[i+1]+=digit[i]/base;
			digit[i]%=base;
			i++;
		}
	}

	BigNum(char * t )
	{
		int i,j,k;
		for(i=0;i<160;i++)
			digit[i]=0;
		int len=strlen(t),num;
		

		for(i=0,j=len-1;j>=0 ;j-=7,i++){
			if(0>j-6) k=0;
			else
				k=j-6;
			for(;k<=j;k++)
				digit[i]=digit[i]*10+t[k]-'0';
		}

	}

	void add(BigNum & a)
	{
		int i;
		for(i=0;i<160;i++){
			digit[i]+=a.digit[i];
		}
		for(i=0;i<159;i++){
			digit[i+1]+=digit[i]/base;
			digit[i]%=base;
		}
	}

	void operator ++ (int k){
		digit[0]++;
		int i=0;
		for(i=0;i<159;i++){
			digit[i+1]+=digit[i]/base;
			digit[i]%=base;
		}
	}

	void mult(BigNum a){
		__int64 tmp[160]={0};
		int i,j;
		for(i=0;i<160;i++){
			for(j=0;j<160;j++){
				if(j+i>158) break;
				tmp[i+j]+=(__int64)digit[i]*(__int64)a.digit[j];
			}
		}

		for(i=0;i<159;i++){
			digit[i]=tmp[i]%base;
			tmp[i+1]+=tmp[i]/base;
		}
	}

	void print(){
		int i;
		int sum=0,num;
		for(i=0;i<160;i++){
			num=digit[i];
			while(num>0){
				sum+=(num%10)*(num%10);
				num/=10;
			}
		}
		printf("%d\n",sum);
	}

} xishu[12];
int main()
{
	freopen("1.txt","r",stdin);
	int n,k,m;
	while(scanf("%d%s%d%d",&n,a,&k,&m)!=EOF){
		int i;
		BigNum x(a);

		for(i=n;i>=0;i--){
			scanf("%s",&b[i]);
			xishu[i]=BigNum(b[i]);
			for(int j=143;j>=0;j--)
				cout<<xishu[i].digit[j];
			cout<<endl<<endl<<endl<<endl;;
		}

		while(k--){
			BigNum powx(1),sum=xishu[0];

			for(i=1;i<=n;i++){
				powx.mult(x);
				BigNum tmp;
				tmp=powx;
				tmp.mult(xishu[i]);
				sum.add(tmp);
			}
			sum.print();
			x++;
		}
	}
}
