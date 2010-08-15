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
	int a[5][5];
	bool find=false;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			cin>>a[i][j];
	for(int i=0;i<5;i++){
		int max=-INT_MAX;
		int col;
		for(int j=0;j<5;j++){
			if(a[i][j]>max) {
				max=a[i][j];
				col=j;
			}
		}
		find =true;
		for(int j=0;j<5;j++){
			if(a[j][col] < max){
				find=false;
				break;
			}
		}
		if(find){
			cout<<i+1<<" "<<col+1<<" "<<a[i][col]<<endl;
			break;
		}
	}
	if(!find) cout<<"not found\n";

}