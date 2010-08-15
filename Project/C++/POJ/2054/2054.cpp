// 我真诚地保证：

// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢 XXX, …, XXX对我的启发和帮助。下面的报告中，我还会具体地提到
// 他们在各个方法对我的帮助。

// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。

// 郭聪

// 项目名：ACM1017
// 创建时间：2009-10-25


//文件名称：2054.cpp
//创建者：	郭聪
//创建时间：2009-10-25
//最后修改时间：2009-10-25
//功能：	求解ACM2054
//文件中的函数名称和简单功能描述：见具体注释
//文件中定义的全局变量和简单功能描述：见具体注释
//文件中用到的他处定义的全局变量及其出处：无
//与其他文件的依赖关系：无

//				运行结果
//	Problem: 2054		User: 00846086
//	Memory: 248K		Time: 32MS
//	Language: C++		Result: Accepted

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

class TreeNode 
{
public:
	int num;//记录结点是由几个节点合并而成
	int sum; //结点的权值
	bool used;	//记录结点是否被合并
	int par;	//父亲的序号
	vector<int> son;
}tree[1010];	//树结点类,以及儿子列表
int n,r;	//结点个数和根的序号

bool init()	//进行必要初始化和数据读入
{
	cin>>n>>r;
	if( n==0 && r==0 )
		return false;
	r--;
	for(int i=0;i<n;i++){	//读取结点权值并清空儿子列表
		cin>>tree[i].sum;
		tree[i].num=1;
		tree[i].son.clear();
		tree[i].used=false;
	}
	for(int i=0;i<n-1;i++){	//读取边信息
		int a,b;
		cin>>a>>b;
		tree[a-1].son.push_back(b-1);
		tree[b-1].par=a-1;
	}
	return true;
}

void solve()
{
	int total=0;	//花费代价
	
	for(int i=0;i<n-1;i++){		//需要合并n-1次
		double maxi=0;				//最大权值
		int id;		//最大权值结点的序号
		for(int j=0;j<n;j++){	//枚举所有的结点,寻找权值最大的结点,因为只在儿子结点中寻找,所以不会找到根节点
			if(tree[j].used)	//结点已经被合并,相当于此节点已经不存在
				continue;
			if(tree[j].son.size()==0)	//结点没有儿子
				continue;
			vector<int>::iterator vi;
			for(vi=tree[j].son.begin();vi!=tree[j].son.end();vi++){
				if(tree[*vi].used)		//儿子已经不存在
					continue;
				if(tree[*vi].sum*1.0/tree[*vi].num>maxi){	//儿子的权值比最大值大,更新最大值
					maxi=tree[*vi].sum*1.0/tree[*vi].num;
					id=*vi;
				}
			}
		}
		//合并权值最大的点
		total+=tree[id].sum*tree[tree[id].par].num;
		tree[tree[id].par].num+=tree[id].num;
		tree[tree[id].par].sum+=tree[id].sum;
		vector<int>::iterator vi;
		for(vi=tree[id].son.begin();vi!=tree[id].son.end();vi++){//将儿子的儿子放入父亲的儿子序列中
			if(!tree[*vi].used){
				tree[tree[id].par].son.push_back(*vi);
				tree[*vi].par=tree[id].par;
			}
		}
		tree[id].used=true;
	}
	total+=tree[r].sum;
	cout<<total<<endl;
}
int main()
{
	while(init()){
		solve();
	}
}
