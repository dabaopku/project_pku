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

int n;
int a[2100][2100];
int b[2100][2100];
int maxi=-227000000;
void pre()
{
	scanf("%d",&n);
	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		}
	}

	for(i=0;i<=n;i++){
		b[i][0]=b[0][i]=0;
	}

	for(i=1;i<=n;i++){
		b[i][1]=b[i-1][1]+a[i][1];
		b[1][i]=b[1][i-1]+a[1][i];
	}
	for(i=2;i<=n;i++){
		for(j=2;j<=n;j++){
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
		}
	}
}
int main()
{
	int i,j,k,l;
	int t;
	pre();
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			for(k=i;k<=n;k++){
				for(l=j;l<=n;l++){
					t=b[k][l]+b[i-1][j-1]-b[k][j-1]-b[i-1][l];
					if(t>maxi){
					//	cout<<i<<" "<<j<<"  "<<k<<"  "<<l<<endl;
						maxi=t;
					}
				}
			}
		}
	}
	cout<<maxi<<endl;
}