#include "stdio.h"
#include "iostream"
#include "string"
#include "stdlib.h"
#include "math.h"
using namespace std;
#define maxlen 20000000
int n,nc;
bool ch[256]={0};
char word[maxlen];
int digit[256];
bool num[maxlen]={0};
int main()
{
	scanf("%d%d",&n,&nc);
	scanf("%s",word);
	int i,j,len;
	len=strlen(word);
	for(i=0;i<len;i++){
		ch[word[i]]=true;
	}
	j=0;
	for(i=0;i<256;i++){
		if(ch[i]){
			digit[i]=j++;
		}
	}
	int sum=0;
	int tmp=0;
	for(i=0;i<n;i++){
		tmp=tmp*nc+digit[word[i]];
	}
	sum++;
	num[tmp]=true;
	int pow=1;
	for(j=0;j<n-1;j++)
		pow*=nc;
	for(i=1;i<=len-n;i++){
		tmp-=pow*digit[word[i-1]];
		tmp*=nc;
		tmp+=digit[word[i+n-1]];
		if(!num[tmp]){
			num[tmp]=true;
			sum++;
		}

	}
	cout<<sum<<endl;
}