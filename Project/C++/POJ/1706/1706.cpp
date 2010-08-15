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

int id[1000]={0};

struct REFER
{
	int id;
	char cont[3][100];
	void prepare(){
		int i=0,j=0;
		while(cont[0][i]!=']') i++;
		i++;
		while(cont[0][i]){
			cont[0][j]=cont[0][i];
			i++;
			j++;
		}
		cont[j]=0;
	}

	void print(){
		printf("[%d] ",id);
		for(int i=0;i<3;i++)
			printf("%s\n",cont[i]);
	}

}ref[100];

struct 
int main()
{
	
}