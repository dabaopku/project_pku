#include "iostream"
#include "vector"
#include "stdio.h"
#include "string"
using namespace std;
#define END "# End of the config file"
class config 
{
public:
		string kind,val;
		config(char *k,char *v):kind(k),val(v) {};
		config(){};
		friend ostream & operator<<(ostream &out,config &input){
			out<<input.kind<<" "<<input.val<<endl;
			return out;
		}

};
int main()
{
	vector<config> info;
	vector<config>::iterator i;
	
	char cline[100],kind[100],val[100],temp[100];
	int num=0;
	do{
		cin.getline(cline,100,'\n');
		if(cline[0]=='#' || cline[0]=='\0') continue;
		sscanf(cline,"%s%s%s",temp,kind,val);
		config one(kind,val);
		info.push_back(one);
		num++;
	}while(strcmp(cline,END)!=0);
	cout<<num<<endl;
	for(i=info.begin();i!=info.end();i++)
		cout<<*i;
	return 0;
}