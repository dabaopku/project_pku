#include"iostream"
using namespace std;
#define N 10000
int change(char *a,int *b)
{
	int i=0,j=0;

	int point=0;
	while(a[i]!='.')
		i++;
	point=i;
	j=4;
	for(i=0;i<6;i++)
	{
		if(i==point) continue;
		b[j]=a[i]-'0';
		j--;
	}
	return point;
}

void multi(int a[N],int b[N],int c[N])
{
	int i,j;
	memset(c,0,sizeof(int)*N);
	for(i=0;i<N;i++){
		if(a[i]==0) continue;
		for(j=0;j<N;j++){
			if(b[j]==0) continue;
			c[i+j]+=a[i]*b[j];

		}
	}
	for(i=0;i<N-1;i++){
		c[i+1]+=c[i]/10;
		c[i]=c[i]%10;
	}
	return;
}

void solve(int a[N],int n,int ans[N])
{
	int i,b[N]={0};
	memset(ans,0,sizeof(int)*N);
	if(n==1){
		memcpy(ans,a,sizeof(int)*N);
		return;
	}
	else{
		multi(a,a,b);
		solve(b,n/2,ans);
		if(n%2==0)	return;
		else {
			memcpy(b,ans,sizeof(int)*N);
			multi(a,b,ans);
			return;

		}
	}
}

void print(int ans[N],int point,int n)
{
	int i,start,end;
	i=N-1;
	while(ans[i]==0 && i>=0) i--;
	start=i;
	i=0;
	while(ans[i]==0) i++;
	end=i;
	if(start<0) {cout<<'0'<<endl;return;}
	if(start+1<=point*n){
		cout<<".";
		for(i=0;i<point*n-1-start;i++)
			cout<<'0';
		for(i=start;i>=end;i--)
			cout<<ans[i];
		cout<<endl;
		return;
	}
	else{
		for(i=start;i>=point*n;i--)
			cout<<ans[i];
		if(point*n==end) {cout<<endl;return;}
		if(point*n-1>=end) cout<<'.';
		for(i=point*n-1;i>=end;i--)
			cout<<ans[i];
		cout<<endl;
		return;
	}
}

int  main()
{
	char a[N]={0};
	int i=0,j=0,n=0,ans[N]={0},num[N]={0},point=0;;
	while(cin>>a>>n){
		point=5-change(a,num);
		solve(num,n,ans);
		print(ans,point,n);
		memset(a,0,sizeof(a));
		memset(ans,0,sizeof(ans));
		memset(num,0,sizeof(num));


	}

	return 0;
}



