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

// 项目名：ACM2251
// 创建时间：2009－9－26


//文件名称：2251.cpp
//项目名称：2251.vcproj
//创建者：	郭聪
//创建时间：2009-9-26
//最后修改时间：2009-9-26
//功能：	求解ACM2251
//文件中的函数名称和简单功能描述：见具体注释
//文件中定义的全局变量和简单功能描述：见具体注释
//文件中用到的他处定义的全局变量及其出处：无
//与其他文件的依赖关系：无

//				运行结果
//	Problem: 2251		User: 00846086
//	Memory: 456K		Time: 63MS
//	Language: C++		Result: Accepted


#include "iostream"
#include "queue"

using namespace std;

struct point				//表示一个点的结构体
{
	int x,y,z;
	point(int x_=0,int y_=0,int z_=0):x(x_),y(y_),z(z_){};
};

int maze[35][35][35];		//记录迷宫
							//存储为走到每一个格子最短需要几步
int l,r,c;					//迷宫规格
point ps,pe;				//起点与终点位置
const int dir[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
							//存储走到相邻格子时坐标的变化情况
const int inf=1000000;		//没有被访问过标记

bool init()			//初始化函数,负责读取数据
{
	//函数名称：	init
	//函数功能描述：初始化函数,负责读取数据
	//函数调用之前的预备条件：无
	//返回后的处理：			无
	//返回值（如果有的话）：	如果输入 0 0 0 返回false,否则返回true
	//函数的输入参数：			无
	//函数的输出参数：			无
	//函数的抽象算法（伪码）： 无
	//函数与其他对象中函数的调用和被调用关系：无

	cin>>l>>r>>c;
	if(!(l || r || c)) return false;
	memset(maze,-1,sizeof(maze));	//不可行位置设置为-1
	char ch;
	for(int i=1;i<=l;i++){
		for(int j=1;j<=r;j++){
			for(int k=1;k<=c;k++){
				cin>>ch;
				if(ch=='.'){
					maze[i][j][k]=inf;
				}
				else if(ch=='S'){
					maze[i][j][k]=0;	//起始点初始化为0
					ps=point(i,j,k);
				}
				else if(ch=='E'){
					maze[i][j][k]=inf;
					pe=point(i,j,k);
				}
			}	//end for k
		}	//end for j
	} //end i

	return true;
}

int bfs()	//广度优先搜索求走到终点的最少步数
{
	//函数名称：	bfs
	//函数功能描述：广度优先搜索求走到终点的最少步数
	//函数调用之前的预备条件：	无
	//返回后的处理：			无
	//返回值（如果有的话）：	走到终点的最少步数,失败返回-1
	//函数的输入参数：			无
	//函数的输出参数：			无
	//函数的抽象算法（伪码）： 广度优先搜索
	//函数与其他对象中函数的调用和被调用关系：无

	queue<point> que;	//广搜队列,使用 STL 模板库
		//考虑到程序数据规模,为了减少程序的实现难度
		//没有用 priority_queue和估价函数
	que.push(ps);		//起点进队列
	point cur;			//当前位置

	while(maze[pe.x][pe.y][pe.z]==inf && !que.empty()){	
			//广搜

		cur=que.front();
		que.pop();	//队列弹出第一个节点

		for(int i=0;i<6;i++){	//枚举六个方向,如果没有被访问过就更新该节点并进队列
			if(maze[cur.x+dir[i][0]][cur.y+dir[i][1]][cur.z+dir[i][2]]==inf){
				maze[cur.x+dir[i][0]][cur.y+dir[i][1]][cur.z+dir[i][2]]=
					maze[cur.x][cur.y][cur.z]+1;	//走到它的步数等于当前步数加1
				que.push(point(cur.x+dir[i][0],cur.y+dir[i][1],cur.z+dir[i][2]));
			} //end if
		} //end for
	} //end while
	if(maze[pe.x][pe.y][pe.z]==inf)	//如果无解
		return -1;
	else
		return maze[pe.x][pe.y][pe.z];
}

void solve()  //求解问题框架并打印结果
{
	//函数名称：	solve
	//函数功能描述：求解问题框架并打印结果
	//函数调用之前的预备条件：无
	//返回后的处理：			无
	//返回值（如果有的话）：	无
	//函数的输入参数：			无
	//函数的输出参数：			无
	//函数的抽象算法（伪码）：  无
	//函数与其他对象中函数的调用和被调用关系：无

	int ans=bfs();
	//输出结果
	if(ans==-1)
		cout<<"Trapped!\n";
	else
		cout<<"Escaped in "<<ans<<" minute(s).\n";
}
int main()
{
	//freopen("data.txt","r",stdin);
	while(init()){ //多 case 处理
		solve();
	}
	return 0;	//程序结束
}