#include "iostream"
#include "cstdio"
#include"string"
#include "algorithm"
#include "vector"
using namespace std;

class num
{
	int three,four;
public:
	num(int a=0,int b=0):three(a),four(b){};
	friend ostream & operator<<(ostream &output,num &input){
		output.width(3);
		output.fill('0');
		output<<input.three
			<<'-';
		output.width(4);
		output.fill('0');
		output<<input.four;
		return output;
	}
	friend void printf(num &n){
		printf("%03d-%04d",n.three,n.four);
	}
	friend bool operator<(const num & a,const num & b){
		if(a.three<b.three || (a.three==b.three && a.four<b.four))
			return true;
		return false;
	}
	friend bool operator==(const num & a,const num & b){
		if(a.three==b.three && a.four==b.four) return true;
		return false;
	}
};
int main()
{
	int ch[26]={2,2,2,3,3,3,4,4,4,5,5,5,6
		,6,6,7,7,7,7,8,8,8,9,9,9,9};
	
	int cs,i,j;
	char line[200];
	int num3,num4;
	vector<num> data;
	cin>>cs;
	cin.get();
	while(cs--){
		cin.getline(line,200,'\n');
		j=0;
		string str(line);
		string::size_type pos=0;
		while((pos=str.find("-",pos))!=string::npos)
		{
			str.replace(pos,1,"");
			
		}
		for(i=0;i<7;i++){
			if(str[i]<='Z' && str[i]>='A')
				str[i]='0'+ch[str[i]-'A'];
		}
	
		string s3=str.substr(0,3);
		num3=atoi(s3.c_str());
		string s4=str.substr(3,8);
	
		num4=atoi(s4.c_str());
		num temp(num3,num4);
		data.push_back(temp);
	}
	sort(data.begin(),data.end());
	vector<num>::iterator mi=data.begin(),mj=mi;
	bool outp=false;
	while(mj!=data.end()){
		if(*mj==*mi) {mj++;continue;}
		if(mj-mi==1) {mi=mj;continue;}
		
		printf(*mi);
		printf(" %d\n",mj-mi);
		mi=mj;
		outp=true;
	}
	if(mj-mi>1){
		printf(*mi);
		printf(" %d\n",mj-mi);
		
	}
	else if(!outp) cout<<"No duplicates.\n";
	return 0;
}