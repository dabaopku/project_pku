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

// 项目名：ACM2388
// 创建时间：2009-11-14


//文件名称：2388.cpp
//创建者：	郭聪
//创建时间：2009-11-14
//最后修改时间：2009-11-14
//功能：	求解ACM2388
//文件中的函数名称和简单功能描述：见具体注释
//文件中定义的全局变量和简单功能描述：见具体注释
//文件中用到的他处定义的全局变量及其出处：无
//与其他文件的依赖关系：无


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
const int maxn=10010;	//数组的最大范围
int tmp[maxn];
void Merge(int *a,int size)	//合并排序a数组
{
	int i,j,k;
	for(i=0,j=size/2,k=0;i<size/2 && j<size;k++){	//两个数组合并,每次取小者
		if(a[i]<=a[j]){
			tmp[k]=a[i];
			i++;
		}
		else{
			tmp[k]=a[j];
			j++;
		}
	}
	while(i<size/2){	//前半个数组剩余部分取出
		tmp[k]=a[i];
		i++;
		k++;
	}
	while(j<size){		//后半个数组剩余部分取出
		tmp[k]=a[j];
		j++;
		k++;
	}
	for(i=0;i<size;i++){
		a[i]=tmp[i];
	}
}
void MergeSort(int * lst,int size)
//将lst开始的其后size长度的数组进行归并排序
{
	if(size<=1) 
		return ;
	MergeSort(lst,size/2);		//归并排序
	MergeSort(lst+size/2,size-size/2);
	Merge(lst,size);	//合并数组
	return ;
}
int main()
{
	int n;					//数据数量
	int data[maxn];			//数据
	cin>>n;
	for(int i=0;i<n;i++){	//数据输入
		cin>>data[i];
	}
	MergeSort(data,n);		//对数据排序
	cout<<data[(n-1)/2]<<endl;
}