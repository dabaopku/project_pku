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

using namespace std;

int main()
{
	int a[5];
	for(a[0]=0;a[0]<5;a[0]++){
		if(a[0]==0) continue;
		for(a[1]=0;a[1]<5;a[1]++){
			if(a[1]!=1 || a[1]==a[0]) continue;
			for(a[2]=0;a[2]<5;a[2]++){
				if(a[2]<2 && a[0]!=4) continue;
				if(a[2]==a[1] || a[2]==a[0]) continue;
				for(a[3]=0;a[3]<5;a[3]++){
					if(a[3]==1 && a[2]==0 ) continue;
					if(a[3]==a[1] || a[3]==a[0] || a[3]==a[2]) continue;
					for(a[4]=0;a[4]<5;a[4]++){
						if(a[4]<=2) continue;
						if(a[4]==a[1] || a[4]==a[0] || a[4]==a[2] || a[4]==a[3]) continue;
						if(a[4]>1 && a[3]==0) continue;
						for(int i=0;i<5;i++)
							cout<<a[i]+1<<endl;
					}
				}
			}
		}
	}
}