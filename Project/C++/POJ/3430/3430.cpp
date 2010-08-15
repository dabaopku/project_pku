#include "iostream"
#include "vector"
#include"string"
#include "stdio.h"
using namespace std;
int findNum();
string findStr();
vector<string> str;

bool isNumber(const string s)
{
	int len=s.length();
	if(len>5) return false;
	for(int i=0;i<len;i++){
		if(s[i]>'9' || s[i]<'0') return false;
	}
	return true;
	
}
string findStr()
{
	string cmd;
	cin>>cmd;
	if(cmd!="copy" && cmd!="add"){
		return cmd;
	}
	else{
		if(cmd=="copy"){
			string strfather=str[findNum()-1];
			int start=findNum();
			int len=findNum();
			return strfather.substr(start,len);
		}
		else if(cmd=="add"){
			string s1=findStr(),s2=findStr();
			if(isNumber(s1) && isNumber(s2)){
				int num=atoi(s1.c_str())+atoi(s2.c_str());
				char ch[10];
				_itoa(num,ch,10);
				string s=ch;
				return s;
			}
			else {
				s1+=s2;
				return s1;
			}
		}
	}
}
int findNum()
{
	string cmd;
	cin>>cmd;
	if(cmd!="find" && cmd!="rfind"){
		int num=atoi(cmd.c_str());
		return num;
	}
	else{
		string strson=findStr();
		string strfather=str[findNum()-1];
		if(cmd=="find"){
			int num=strfather.find(strson);
			if(num==string::npos) return strfather.length();
			return num;
		}
		else{
			string strfather1=strfather;
			strfather1=string(_strrev((char*)strfather1.c_str()));
			string strson1=strson;
			strson1=string(_strrev((char*)strson1.c_str()));
			int num=strfather1.find(strson1);
			if(num==string::npos) return strfather1.length();
			return strfather1.length()-num-strson1.length();
		}
	}
}

int main()
{
	
	int i,n;
	string temp,cmd;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>temp;
		str.push_back(temp);
	}
	do 
	{
		cin>>cmd;
		if(cmd=="printall"){
			for(i=0;i<n;i++)
				cout<<str[i]<<endl;
		}
		else if(cmd=="print"){
			cout<<str[findNum()-1]<<endl;
		}
		else if(cmd=="insert"){
			string ins=findStr();
			int des=findNum();
			int pos=findNum();
			str[des-1].insert(pos,ins);
		}
		else if(cmd=="reset"){
			string rpl=findStr();
			int des=findNum();
			str[des-1]=rpl;
		}
	} while (cmd!="over");
	return 0;
}