#include "stdio.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "math.h"
using namespace std;
#define gold 0.6180339887498948482045
int main ()
{ 
	int x,m,n,y;
	while ( cin>>m>>n) { 
		if ( m==n )   
			cout<<1<<endl;  
		else {   
			if ( m>n ){  
				int t=m ;  
				m=n;   
				n=t;  
			}  
			x = n-m ;  
			y = int ( double(x)/gold ) ; 
			if ( y == m )   
				cout << 0 << endl ;  
			else    
				cout << 1 << endl ; 
		} 
	} 
	return 0 ;
}

