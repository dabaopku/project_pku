#include "stdio.h"
#include "iostream"
using namespace std;

int n,m;	//记录候选人数和要选出的人数
int pro[210],def[210];	//控方和辩方的分数
int scorecurrent[1000],scorenext[1000];	//当前得分状态和下一个得分状态
bool usedcurrent[1000][210],usednext[1000][210];	//记录每一种分差下是否使用某个人
int mini,maxi;	//分差的上下限,加500进行偏置
int transTable[1000];	//记录从现态到次态的转换关系

bool init()
//读取数据和进行初始化
{
	cin>>n>>m;
	if(n==0 && m==0)
		return false;
	mini=-20*m+500;		//求出分差的上下限
	maxi=20*m+500;

	
	for(int i=mini;i<=maxi;i++){	//初始化数据
		scorecurrent[i]=-1;
		transTable[i]=0;
		for(int j=1;j<=n;j++){
			usedcurrent[i][j]=false;
		}
	}

	for(int i=1;i<=n;i++){	//读取数据
		cin>>pro[i]>>def[i];
		if(scorecurrent[pro[i]-def[i]+500]<pro[i]+def[i]){	//获得每个人的分数差,分数差相同的只记录分数和较大的那个人
			scorecurrent[pro[i]-def[i]+500]=pro[i]+def[i];
			transTable[pro[i]-def[i]+500]=i;
		}
	}
	for(int i=mini;i<=maxi;i++){
		if(transTable[i]>0)		//首先把这个人加入到结果数组中
			usedcurrent[i][transTable[i]]=true;
	}
	return true;
}

void print()
//输出结果
{
	int i=0;
	while(scorecurrent[500-i]==-1 && scorecurrent[500+i]==-1)	//从0开始查找最小的分数和有效地分数差
		i++;
	int forPoint,defPoint,difPoint;	//记录赞成和反对的分数以及分数差
	if(scorecurrent[500-i]<scorecurrent[500+i]){	//如果负的分数差的分数和不如正的分数差的分数和
		forPoint=(scorecurrent[500+i]+i)/2;
		defPoint=scorecurrent[500+i]-forPoint;
		difPoint=500+i;
	}
	else{
		defPoint=(scorecurrent[500-i]+i)/2;
		forPoint=scorecurrent[500-i]-defPoint;
		difPoint=500-i;
	}
	cout<<"Best jury has value "<<forPoint<<" for prosecution and value "<<defPoint<<" for defence:\n";
	for(int i=1;i<=n;i++){	//输出参与的人员
		if(usedcurrent[difPoint][i])
			cout<<" "<<i;
	}
	cout<<endl<<endl;
}
void solve()
{
	for(int i=1;i<m;i++){
		for(int j=mini;j<=maxi;j++){	//初始化下一个状态
			scorenext[j]=-1;
			transTable[j]=0;
			for(int k=1;k<=n;k++)
				usednext[j][k]=false;
		}

		for(int j=mini;j<=maxi;j++){	//对于所有的分差情况,尝试加入每一个人得到新的分差
			if(scorecurrent[j]==-1) continue;	//没有出现过的分差,直接跳过
			for(int k=1;k<=n;k++){
				if(usedcurrent[j][k])		//该人已经出现在形成该分差的序列中,跳过
					continue;
				if(scorecurrent[j]+pro[k]+def[k]>scorenext[j+pro[k]-def[k]]){	//加入这个人之后的总分大于实际总分
					scorenext[j+pro[k]-def[k]]=scorecurrent[j]+pro[k]+def[k];	//更新该分数差下的总分
					transTable[j+pro[k]-def[k]]=j+k*1000;	//记录该总分是从哪个分数差加上那个人得到的,后三位是分数差,千位是加入的人
				}
			}
		}
		for(int j=mini;j<=maxi;j++){
			if(scorenext[j]!=-1){	//如果该分差对应的总分有效,就表示存在序列满足条件,用现态更新初态
				memcpy(usednext[j],usedcurrent[transTable[j]%1000],sizeof(bool)*(n+1));	//把现态的人员序列复制到次态中
				usednext[j][transTable[j]/1000]=true;//将新增加的人也添加到序列中
			}
		}
		for(int j=mini;j<=maxi;j++){
			scorecurrent[j]=scorenext[j];	//把次态复制到现态中,进入下一层循环
			if(scorenext[j]!=-1){
				memcpy(usedcurrent[j],usednext[j],sizeof(bool)*(n+1));
			}
		}
	}
	print();	//输出结果
}

int main()
{
	int caseid=1;
	while(init()){
		cout<<"Jury #"<<caseid<<endl;
		caseid++;
		solve();
	}
}