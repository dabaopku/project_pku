#include"iostream"
using namespace std;

int  main()

{
	char a[150]={'\0'};
	char b[20][10]={'\0'};
	int i,j;
	int ap,bp;
	long ans;
	int mil,thou,digit;
	while(gets(a)){
		for(i=0;i<20;i++)
			for(j=0;j<10;j++)
				b[i][j]=0;
		ap=bp=i=mil=thou=ans=digit=0;
		while(a[ap]){
			if(a[ap]==' '){
				bp++;
				i=0;
			}
			else {
				b[bp][i]=a[ap];
				i++;
			}
			ap++;
		}
		for(i=0;i<=bp;i++){
			if(strcmp(b[i],"zero")==0) digit+=0;
			else if(strcmp(b[i],"one")==0) digit+=1;
			else if(strcmp(b[i],"two")==0) digit+=2;
			else if(strcmp(b[i],"three")==0) digit+=3;
			else if(strcmp(b[i],"four")==0) digit+=4;
			else if(strcmp(b[i],"five")==0) digit+=5;
			else if(strcmp(b[i],"six")==0) digit+=6;
			else if(strcmp(b[i],"seven")==0) digit+=7;
			else if(strcmp(b[i],"eight")==0) digit+=8;
			else if(strcmp(b[i],"nine")==0) digit+=9;
			else if(strcmp(b[i],"ten")==0) digit+=10;
			else if(strcmp(b[i],"eleven")==0) digit+=11;
			else if(strcmp(b[i],"twelve")==0) digit+=12;
			else if(strcmp(b[i],"thirteen")==0) digit+=13;
			else if(strcmp(b[i],"fourteen")==0) digit+=14;
			else if(strcmp(b[i],"fifteen")==0) digit+=15;
			else if(strcmp(b[i],"sixteen")==0) digit+=17;
			else if(strcmp(b[i],"eighteen")==0) digit+=16;
			else if(strcmp(b[i],"seventee")==0) digit+=18;
			else if(strcmp(b[i],"nineteen")==0) digit+=19;
			else if(strcmp(b[i],"twenty")==0) digit+=20;
			else if(strcmp(b[i],"thirty")==0) digit+=30;
			else if(strcmp(b[i],"forty")==0) digit+=40;
			else if(strcmp(b[i],"fifty")==0) digit+=50;
			else if(strcmp(b[i],"sixty")==0) digit+=60;
			else if(strcmp(b[i],"seventy")==0) digit+=70;
			else if(strcmp(b[i],"eighty")==0) digit+=80;
			else if(strcmp(b[i],"ninety")==0) digit+=90;
			else if(strcmp(b[i],"hundred")==0) {
				if(mil+thou>0) ans+=digit*100;
				else ans=(ans+digit)*100;
				digit=0;
			}
			else if(strcmp(b[i],"thousand")==0) {
				if (mil>0) ans+=digit*1000;
				else ans=(ans+digit)*1000;
				digit=0;
				thou=1;
			}
			else if(strcmp(b[i],"million")==0) {ans=(ans+digit)*1000000;mil=1;digit=0;}

		}
		ans+=digit;
		if(strcmp(b[0],"negative")==0) cout<<'-';
		cout<<ans<<endl;

	}

	return 0;
}

