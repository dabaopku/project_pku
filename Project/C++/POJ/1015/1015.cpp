#include "stdio.h"
#include "iostream"
using namespace std;

int n,m;	//��¼��ѡ������Ҫѡ��������
int pro[210],def[210];	//�ط��ͱ緽�ķ���
int scorecurrent[1000],scorenext[1000];	//��ǰ�÷�״̬����һ���÷�״̬
bool usedcurrent[1000][210],usednext[1000][210];	//��¼ÿһ�ֲַ����Ƿ�ʹ��ĳ����
int mini,maxi;	//�ֲ��������,��500����ƫ��
int transTable[1000];	//��¼����̬����̬��ת����ϵ

bool init()
//��ȡ���ݺͽ��г�ʼ��
{
	cin>>n>>m;
	if(n==0 && m==0)
		return false;
	mini=-20*m+500;		//����ֲ��������
	maxi=20*m+500;

	
	for(int i=mini;i<=maxi;i++){	//��ʼ������
		scorecurrent[i]=-1;
		transTable[i]=0;
		for(int j=1;j<=n;j++){
			usedcurrent[i][j]=false;
		}
	}

	for(int i=1;i<=n;i++){	//��ȡ����
		cin>>pro[i]>>def[i];
		if(scorecurrent[pro[i]-def[i]+500]<pro[i]+def[i]){	//���ÿ���˵ķ�����,��������ͬ��ֻ��¼�����ͽϴ���Ǹ���
			scorecurrent[pro[i]-def[i]+500]=pro[i]+def[i];
			transTable[pro[i]-def[i]+500]=i;
		}
	}
	for(int i=mini;i<=maxi;i++){
		if(transTable[i]>0)		//���Ȱ�����˼��뵽���������
			usedcurrent[i][transTable[i]]=true;
	}
	return true;
}

void print()
//������
{
	int i=0;
	while(scorecurrent[500-i]==-1 && scorecurrent[500+i]==-1)	//��0��ʼ������С�ķ�������Ч�ط�����
		i++;
	int forPoint,defPoint,difPoint;	//��¼�޳ɺͷ��Եķ����Լ�������
	if(scorecurrent[500-i]<scorecurrent[500+i]){	//������ķ�����ķ����Ͳ������ķ�����ķ�����
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
	for(int i=1;i<=n;i++){	//����������Ա
		if(usedcurrent[difPoint][i])
			cout<<" "<<i;
	}
	cout<<endl<<endl;
}
void solve()
{
	for(int i=1;i<m;i++){
		for(int j=mini;j<=maxi;j++){	//��ʼ����һ��״̬
			scorenext[j]=-1;
			transTable[j]=0;
			for(int k=1;k<=n;k++)
				usednext[j][k]=false;
		}

		for(int j=mini;j<=maxi;j++){	//�������еķֲ����,���Լ���ÿһ���˵õ��µķֲ�
			if(scorecurrent[j]==-1) continue;	//û�г��ֹ��ķֲ�,ֱ������
			for(int k=1;k<=n;k++){
				if(usedcurrent[j][k])		//�����Ѿ��������γɸ÷ֲ��������,����
					continue;
				if(scorecurrent[j]+pro[k]+def[k]>scorenext[j+pro[k]-def[k]]){	//���������֮����ִܷ���ʵ���ܷ�
					scorenext[j+pro[k]-def[k]]=scorecurrent[j]+pro[k]+def[k];	//���¸÷������µ��ܷ�
					transTable[j+pro[k]-def[k]]=j+k*1000;	//��¼���ܷ��Ǵ��ĸ�����������Ǹ��˵õ���,����λ�Ƿ�����,ǧλ�Ǽ������
				}
			}
		}
		for(int j=mini;j<=maxi;j++){
			if(scorenext[j]!=-1){	//����÷ֲ��Ӧ���ܷ���Ч,�ͱ�ʾ����������������,����̬���³�̬
				memcpy(usednext[j],usedcurrent[transTable[j]%1000],sizeof(bool)*(n+1));	//����̬����Ա���и��Ƶ���̬��
				usednext[j][transTable[j]/1000]=true;//�������ӵ���Ҳ��ӵ�������
			}
		}
		for(int j=mini;j<=maxi;j++){
			scorecurrent[j]=scorenext[j];	//�Ѵ�̬���Ƶ���̬��,������һ��ѭ��
			if(scorenext[j]!=-1){
				memcpy(usedcurrent[j],usednext[j],sizeof(bool)*(n+1));
			}
		}
	}
	print();	//������
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