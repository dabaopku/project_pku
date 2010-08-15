#include "stdio.h"
#include "math.h"

int n;		//��ׯ����Ŀ
double maxrate=0.0;		//·�������ñ���,���ִ𰸵�����
double x[1010],y[1010],h[1010];	//������ׯ��λ��
double cost[1010][1010],length[1010][1010],relativecost[1010][1010];	//ÿ��·�ķ���,����,�Լ���Ȩ��ķ���
double weight[1010]={};	//����Ȩֵ,����prim�㷨
const double INF=1e8;	//�����ֵ
bool usedcurrent[1010]={};		//��¼�����û�б����ʹ�


double prim(double currate)
//��currate��Ȩ����С������,��������Ȩֵ
{
	for (int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			relativecost[i][j]=cost[i][j]-currate*length[i][j];	//�����Ȩ֮��ķ���
		}
	}
	for(int i=0;i<n;i++){	//��ʼ�����ڵ�,Ȩ����Ϊ�����
		usedcurrent[i]=0;
		weight[i]=INF;
	}
	weight[0]=0.0;
	int curid=0;	//��ǰ���ʵĽ��
	usedcurrent[curid]=1;
	double ans=0.0;	//����Ȩ��
	for(int i=0;i<n-1;i++){	//���n-1����
		double mini=INF;	
		int id;		//�洢�ҵ���Ȩֵ��С�Ľ��
		for(int j=0;j<curid;j++){	//�����еĽ��,����������ı�ȨֵС�ڽڵ�Ȩ��,�͸��½ڵ�Ȩ��
			if(usedcurrent[j]) continue;
			if(weight[j]>relativecost[j][curid]){
				weight[j]=relativecost[j][curid];
			}
			if(weight[j]<mini){		//���Ȩ����С�Ľ��,��Ϊ��һ�����
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
		curid=id;		//����Ҫ�������һ�����
		usedcurrent[curid]=1;
		ans+=weight[curid];	//������ӵ�����
	}
	return ans;
}

bool init()
//��ȡ���ݲ����г�ʼ��
{
	scanf("%d",&n);
	if(n==0) return false;
	for(int i=0;i<n;i++){
		scanf("%lf%lf%lf",&x[i],&y[i],&h[i]);
	}
	//�������������ľ���ͷ���,�����ÿ��·�������ñ���
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
//���ַ�����
{
	double leftrate=0.0,rightrate=maxrate;		//����ö�ٴ𰸵����Ҷ˵�
	while(fabs(rightrate-leftrate)>5e-5){	//���ִ𰸵���������Ϊ1e-5
		double rate=(rightrate+leftrate)/2.0;	//ȡrateΪ�м�ֵ
		double mintree=prim(rate);			//����ڵ�ǰrate�µ���С��������Ȩֵ

		if(mintree>0)		//���Ȩֵ����0��˵��ѡ��rate������,��leftrate����Ϊrate
			leftrate=rate;
		else rightrate=rate;	//����rightrate����Ϊrate
	}
	printf("%.3lf\n",(rightrate+leftrate)/2.0);	//�����
}

int main()
{
	while(init()){
		solve();
	}
}