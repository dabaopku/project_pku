#include "stdio.h"
#include "stdlib.h"
int a[3][501][501];
int ran[501];
int n;
int anw[3][501];

int main()
{
	int i,j,k;
	scanf("%d",&n);
	for(i=0;i<3;i++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++)
				scanf("%d",&a[i][j][k]);
		}
	}
	bool yes=true;
	
	for(j=0;j<n;j++){
		
		ran[j]=a[0][0][j]; 
	}
	for(i=0;i<n;i++){
		anw[0][i]=0;
		for(j=0;j<n;j++){
			anw[0][i]+=ran[j]*a[0][j][i];
		}
	}
	for(i=0;i<n;i++){
		anw[1][i]=0;
		for(j=0;j<n;j++){
			anw[1][i]+=anw[0][j]*a[1][j][i];
		}
	}
	for(i=0;i<n;i++){
		anw[2][i]=0;
		for(j=0;j<n;j++){
			anw[2][i]+=ran[j]*a[2][j][i];
		}
	}
	for(j=0;j<n;j++){
		if(anw[1][j]!=anw[2][j]){
			yes=false;
			break;
		}
	}
	
	
	if(yes) puts("YES");
	else puts("NO");
}