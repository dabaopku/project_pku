#include "stdio.h"
#include "iostream"
#include "string.h"
#include "math.h"
#include "string"

using namespace std;

class BigNum
{
private:
	const static int MODULE=10000000;
	const static int MAXN=1000;

public:
	int len;
	int digit[MAXN];
	int sign;

	////////////////////////////////////////////////////////////////
	//
	//              构造函数
	//
	////////////////////////////////////////////////////////////////

	BigNum(){
		len=0;
		sign=1;
		memset(digit,0,sizeof(digit));
	}
	BigNum(string snum){
		int i,j;
		sign=0;
		if(snum[0]=='-'){
			sign=-1;
			snum=snum.substr(1,snum.size()-1);
		}
		else if(snum[0]=='+'){
			sign=1;
			snum=snum.substr(1,snum.size()-1);
		}
		if(sign==0) sign=1;
		int slen=snum.size();
		memset(digit,0,sizeof(digit));
		len=(slen+6)/7;
		for(i=0;i<len;i++){
			digit[i]=0;
			for(j=0;j<7 ;j++){
				if(slen-i*7-(7-j)<0) continue;
				digit[i]=digit[i]*10+snum[slen-i*7-(6-j)-1]-'0';
			}
		}
		while(digit[len-1]==0 && len>1)
			len--;
	}
	BigNum(char * snum){
		int i,j;
		sign=0;
		int slen=strlen(snum);
		if(snum[0]=='-'){
			sign=-1;
			for(i=0;i<slen;i++)
				snum[i]=snum[i+1];
		}
		else if(snum[0]=='+'){
			sign=1;
			for(i=0;i<slen;i++)
				snum[i]=snum[i+1];
		}
		if(sign==0) sign=1;
		slen=strlen(snum);
		memset(digit,0,sizeof(digit));
		len=(slen+6)/7;
		for(i=0;i<len;i++){
			digit[i]=0;
			for(j=0;j<7 ;j++){
				if(slen-i*7-(7-j)<0) continue;
				digit[i]=digit[i]*10+snum[slen-i*7-(6-j)-1]-'0';
			}
		}
		while(digit[len-1]==0 && len>1)
			len--;
	}


	BigNum( long long n ){
		sign=1;
		if(n<0){
			sign=-1;
			n=-n;
		}
		memset(digit,0,sizeof(digit));
		if(n<MODULE){
			len=1;
			digit[0]=0;
			return ;
		}
		len=2;
		digit[0]=(int)(n%MODULE);
		digit[1]=(int)(n/MODULE);
	}

	////////////////////////////////////////////////////////////////
	//
	//              输入输出比较
	//
	////////////////////////////////////////////////////////////////

	void print(){
		if(sign==-1) printf("-");
		printf("%d",digit[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%07d",digit[i]);
	}

	friend ostream & operator <<(ostream & o,BigNum n){
		n.print();
		return o;
	}

	friend istream & operator >>(istream & i,BigNum & n){
		string s;
		i>>s;
		n=BigNum(s);
		return i;
	}
	bool operator ==( BigNum par ){
		if(sign != par.sign ) return false;
		if(len!=par.len) return false;
		for(int i=0;i<len;i++)
			if(digit[i]!=par.digit[i]) return false;
		return true;
	}

	bool operator <( BigNum  par)  {
		if(sign==-1 && par.sign==1) return true;
		if(sign==1 && par.sign==-1) return false;
		if(sign==-1 && par.sign==-1) 
			return negative(par) < negative(*this);
		if(len<par.len) return true;
		if(len>par.len) return false;
		int i;
		for(i=len-1;i>=0;i--){
			if(digit[i]<par.digit[i]) return true;
			else if(digit[i]>par.digit[i]) return false;
		}
		return false;
	}

	bool operator >( BigNum  par)  {
		return !((*this)<par);
	}

	////////////////////////////////////////////////////////////////
	//
	//              运算符号
	//
	////////////////////////////////////////////////////////////////

	friend BigNum negative(BigNum & par){
		BigNum ans(par);
		ans.sign=-ans.sign;
		return ans;
	}
	friend BigNum abs(BigNum  par){
		if(par.sign==1) return par;
		else
			return negative(par);
	}

	BigNum add(BigNum  par){
		BigNum ans;
		if(sign==-1 && par.sign==-1){
			ans=negative(*this).add(negative(par));
			ans.sign=-1;
			return ans;
		}

		if(sign==-1 && par.sign==1){
			return par.sub(negative(*this));
		}

		if(sign==1 && par.sign==-1){
			return (*this).sub(negative(par));
		}

		if(len<par.len) ans.len=par.len;
		else ans.len=par.len;
		ans.sign=1;

		int i;
		for(i=0;i<ans.len;i++)
			ans.digit[i]=digit[i]+par.digit[i];
		for(i=0;i<ans.len;i++){
			if(ans.digit[i]>=MODULE){
				ans.digit[i+1]++;
				ans.digit[i]-=MODULE;
			}
		}
		while(ans.digit[ans.len])
			ans.len++;
		return ans;
	}

	BigNum operator +(BigNum  par){
		return (*this).add(par);
	}

	BigNum sub(BigNum  par){
		if(sign==-1){
			if(par.sign==1){
				BigNum ans=negative(*this)+par;
				ans.sign=-1;
				return ans;
			}
			else{
				return negative(par)- *this;
			}
		}
		if(par.sign==-1){
			return (*this).add(negative(par));
		}

		if((*this)<par){
			BigNum ans=par.sub(*this);
			ans.sign=-1;
			return ans;
		}
		BigNum ans;
		ans.sign=1;
		ans.len=len;
		int i;
		for(i=0;i<len;i++)
			ans.digit[i]=digit[i]-par.digit[i];
		for(i=0;i<len;i++){
			if(ans.digit[i]<0){
				ans.digit[i]+=MODULE;
				ans.digit[i+1]--;
			}
		}
		while(ans.digit[ans.len-1]==0 && ans.len>1)
			ans.len--;
		return ans;
	}

	BigNum operator -( BigNum par ){
		return (*this).sub(par);
	}

	BigNum mult( BigNum par ){
		BigNum ans;
		ans.sign=sign*par.sign;
		int i,j;
		ans.len=len+par.len+1;
		for(i=0;i<len;i++){
			for(j=0;j<par.len;j++){
				long long tmp=(long long)digit[i]*(long long)par.digit[j];
				ans.digit[i+j]+=(int)(tmp%MODULE);
				ans.digit[i+j+1]+=(int)(tmp/MODULE);
			}
		}
		for(i=0;i<ans.len;i++){
			if(ans.digit[i]>=MODULE){
				ans.digit[i+1]+=ans.digit[i]/MODULE;
				ans.digit[i]%=MODULE;
			}
		}
		ans.len=MAXN;
		while(ans.digit[ans.len-1]==0 && ans.len>1)
			ans.len--;
		return ans;
	}

	BigNum operator *( BigNum par ){
		return (*this).mult(par);
	}

	BigNum fulldivide( BigNum  par , BigNum & yu){
		BigNum sang;
		if(len==1 && digit[0]==0){
			sang.len=1;
			sang.digit[0]=0;
			sang.sign=1;
			yu=sang;
			return sang;
		}
		sang.sign=1;
		BigNum bei=abs(*this);
		BigNum cu=abs(par);

		int i;
		sang.len=bei.len-cu.len+1;
		BigNum tmpbei;
		for(i=1;i<=sang.len;i++){
			int lf=0,rh=MODULE-1;
			int mid;
			while(lf<rh){
				mid=(lf+rh)/2;
				sang.digit[sang.len-i]=mid;
				tmpbei=bei-sang*cu;
				if(tmpbei.sign==-1) rh=mid;
				else lf=mid;
				if(lf+1==rh){
					sang.digit[sang.len-i]=rh;
					tmpbei=bei-sang*cu;
					if(tmpbei.sign==-1) {
						sang.digit[sang.len-i]=lf;
						tmpbei=bei-sang*cu;
					}
					break;
				}
			}

		}
		yu=tmpbei;
		while(sang.digit[sang.len-1]==0 && sang.len>1) sang.len--;
		sang.sign=sign*par.sign;
		return sang;
	}

	BigNum divide( BigNum  par ){
		BigNum tmp;
		return (*this).fulldivide(par,tmp);
	}

	BigNum operator / ( BigNum par ){
		return (*this).divide(par);
	}

	BigNum mod( BigNum par ){
		BigNum ans;
		(*this).fulldivide(par,ans);
		return ans;
	}

	BigNum operator % ( BigNum par ){
		return (*this).mod(par);
	}

	BigNum power( int n ){
		BigNum ans=*this;
		while(n--)
			ans=ans*(*this);
		return ans;
	}
	BigNum operator ^ ( int n ){
		return (*this).power(n);
	}

	void decdivide(BigNum par,int prec){
		int flag=sign*par.sign;
		BigNum yu,sang,cu;
		cu=abs(par);
		sang=abs((*this)).fulldivide(cu,yu);

		if(flag==-1) 
			printf("-");
		printf("%d",sang.digit[sang.len-1]);
		int i;

		for(i=sang.len-2;i>=0;i--){
			printf("%07d",sang.digit[i]);
		}
		printf(".");

		//		求小数部分
		if(yu.len==1 && yu.digit[0]==0){
			for(i=0;i<prec;i++)
				printf("0");
			return ;
		}
		int nlen=prec/7+10;
		for(i=yu.len-1;i>=0;i--)
			yu.digit[i+nlen]=yu.digit[i];
		for(i=0;i<=nlen;i++)
			yu.digit[0]=0;
		yu.len+=nlen;
		sang=yu.divide(par);
		for(i=sang.len-1;i>=0 && prec>=7;i--,prec-=7){
			printf("%07d",sang.digit[i]);
		}
		if(prec>0){
			string tmp="0000000";
			int t=sang.digit[i];
			int s=6;
			while(t){
				tmp[s]=t%10+'0';
				t/=10;
				s--;
			}
			tmp=tmp.substr(0,prec);
			cout<<tmp;
		}
		return;
	}
};


int main()
{
	BigNum a,b;
	char ch[2];
	int n;
	char s1[400],s2[400];
	while(scanf("%s",s1)!=EOF){
		scanf("%s%s",ch,s2);
		if(ch[0]=='/') scanf("%d",&n);
		a=BigNum(s1);
		b=BigNum(s2);
		if(ch[0]=='+'){
			(a+b).print();
		}
		else if(ch[0]=='-'){
			(a-b).print();
		}
		else if(ch[0]=='*'){
			(a*b).print();
		}
		else{
			BigNum sang,yushu;
			sang=a.fulldivide(b,yushu);
			sang.print();
			putchar(' ');
			yushu.print();
			putchar(' ');
		//	printf("%s",(a.decdivide(b,n).c_str()));
			a.decdivide(b,n);
		}
		printf("\n");
	}
}
