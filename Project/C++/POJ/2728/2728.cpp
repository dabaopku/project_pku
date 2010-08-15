#include "stdio.h"
#include "math.h"

int n;		//村庄的数目
double maxrate=0.0;		//路的最大费用比率,二分答案的上限
double x[1010],y[1010],h[1010];	//各个村庄的位置
double cost[1010][1010],length[1010][1010],relativecost[1010][1010];	//每条路的费用,长度,以及加权后的费用
double weight[1010]={};	//结点的权值,用于prim算法
const double INF=1e8;	//无穷大值
bool usedcurrent[1010]={};		//记录结点有没有被访问过


double prim(double currate)
//用currate加权求最小生成树,返回树的权值
{
	for (int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			relativecost[i][j]=cost[i][j]-currate*length[i][j];	//求出加权之后的费用
		}
	}
	for(int i=0;i<n;i++){	//初始化各节点,权重设为无穷大
		usedcurrent[i]=0;
		weight[i]=INF;
	}
	weight[0]=0.0;
	int curid=0;	//当前访问的结点
	usedcurrent[curid]=1;
	double ans=0.0;	//树的权重
	for(int i=0;i<n-1;i++){	//获得n-1条边
		double mini=INF;	
		int id;		//存储找到的权值最小的结点
		for(int j=0;j<curid;j++){	//对所有的结点,如果连向它的边权值小于节点权重,就更新节点权重
			if(usedcurrent[j]) continue;
			if(weight[j]>relativecost[j][curid]){
				weight[j]=relativecost[j][curid];
			}
			if(weight[j]<mini){		//获得权重最小的结点,作为下一个结点
				mini=weight[j];
				id=j;
			}
		}
		for(int j=curid+1;j<n;j++){
			if(usedcurrent[j]) continue;
			if(weight[j]>relativecost[curid][j]){
				weight[j]=relativecost[curid][j];
			}
			if(weight[j]<mini){
				mini=weight[j];
				id=j;
			}
		}
		curid=id;		//设置要处理的下一个结点
		usedcurrent[curid]=1;
		ans+=weight[curid];	//将边添加到树中
	}
	return ans;
}

bool init()
//读取数据并进行初始化
{
	scanf("%d",&n);
	if(n==0) return false;
	for(int i=0;i<n;i++){
		scanf("%lf%lf%lf",&x[i],&y[i],&h[i]);
	}
	//计算任意两点间的距离和费用,并求出每条路的最大费用比率
	for (int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			length[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			cost[i][j]=fabs(h[i]-h[j]);
			
			if(cost[i][j]/length[i][j]>maxrate)
				maxrate=cost[i][j]/length[i][j];
		}
	}
	return true;
}
void solve()
//二分法求结果
{
	double leftrate=0.0,rightrate=maxrate;		//二分枚举答案的左右端点
	while(fabs(rightrate-leftrate)>5e-5){	//二分答案的容限设置为1e-5
		double rate=(rightrate+leftrate)/2.0;	//取rate为中间值
		double mintree=prim(rate);			//求出在当前rate下的最小生成树的权值

		if(mintree>0)		//如果权值大于0就说明选的rate不够大,将leftrate更新为rate
			leftrate=rate;
		else rightrate=rate;	//否则rightrate更新为rate
	}
	printf("%.3lf\n",(rightrate+leftrate)/2.0);	//输出答案
}

int main()
{
	while(init()){
		solve();
	}
}