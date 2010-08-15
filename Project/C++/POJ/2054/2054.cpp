// ����ϵر�֤��

// ���Լ��������������������ӷ�������Ƶ���������й�����
// ��������������У���������ʲô���Ѷ�������ˣ���ô���ҽ��ڳ���ʵϰ������
// ��ϸ���о��������������⣬�Լ����˸��ҵ���ʾ��

// �ڴˣ��Ҹ�л XXX, ��, XXX���ҵ������Ͱ���������ı����У��һ��������ᵽ
// �����ڸ����������ҵİ�����

// �ҵĳ������з������õ�����������ĵ�֮����
// ����̲ġ����ñʼǡ����ϵ�Դ�����Լ������ο����ϵĴ����,
// �Ҷ��Ѿ��ڳ����ע����������ע�������õĳ�����

// �Ҵ�δ��Ϯ�����˵ĳ���Ҳû�е��ñ��˵ĳ���
// �������޸�ʽ�ĳ�Ϯ����ԭ�ⲻ���ĳ�Ϯ��

// �ұ�д������򣬴���û�����Ҫȥ�ƻ���������������ϵͳ��������ת��

// ����

// ��Ŀ����ACM1017
// ����ʱ�䣺2009-10-25


//�ļ����ƣ�2054.cpp
//�����ߣ�	����
//����ʱ�䣺2009-10-25
//����޸�ʱ�䣺2009-10-25
//���ܣ�	���ACM2054
//�ļ��еĺ������ƺͼ򵥹���������������ע��
//�ļ��ж����ȫ�ֱ����ͼ򵥹���������������ע��
//�ļ����õ������������ȫ�ֱ��������������
//�������ļ���������ϵ����

//				���н��
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
	int num;//��¼������ɼ����ڵ�ϲ�����
	int sum; //����Ȩֵ
	bool used;	//��¼����Ƿ񱻺ϲ�
	int par;	//���׵����
	vector<int> son;
}tree[1010];	//�������,�Լ������б�
int n,r;	//�������͸������

bool init()	//���б�Ҫ��ʼ�������ݶ���
{
	cin>>n>>r;
	if( n==0 && r==0 )
		return false;
	r--;
	for(int i=0;i<n;i++){	//��ȡ���Ȩֵ����ն����б�
		cin>>tree[i].sum;
		tree[i].num=1;
		tree[i].son.clear();
		tree[i].used=false;
	}
	for(int i=0;i<n-1;i++){	//��ȡ����Ϣ
		int a,b;
		cin>>a>>b;
		tree[a-1].son.push_back(b-1);
		tree[b-1].par=a-1;
	}
	return true;
}

void solve()
{
	int total=0;	//���Ѵ���
	
	for(int i=0;i<n-1;i++){		//��Ҫ�ϲ�n-1��
		double maxi=0;				//���Ȩֵ
		int id;		//���Ȩֵ�������
		for(int j=0;j<n;j++){	//ö�����еĽ��,Ѱ��Ȩֵ���Ľ��,��Ϊֻ�ڶ��ӽ����Ѱ��,���Բ����ҵ����ڵ�
			if(tree[j].used)	//����Ѿ����ϲ�,�൱�ڴ˽ڵ��Ѿ�������
				continue;
			if(tree[j].son.size()==0)	//���û�ж���
				continue;
			vector<int>::iterator vi;
			for(vi=tree[j].son.begin();vi!=tree[j].son.end();vi++){
				if(tree[*vi].used)		//�����Ѿ�������
					continue;
				if(tree[*vi].sum*1.0/tree[*vi].num>maxi){	//���ӵ�Ȩֵ�����ֵ��,�������ֵ
					maxi=tree[*vi].sum*1.0/tree[*vi].num;
					id=*vi;
				}
			}
		}
		//�ϲ�Ȩֵ���ĵ�
		total+=tree[id].sum*tree[tree[id].par].num;
		tree[tree[id].par].num+=tree[id].num;
		tree[tree[id].par].sum+=tree[id].sum;
		vector<int>::iterator vi;
		for(vi=tree[id].son.begin();vi!=tree[id].son.end();vi++){//�����ӵĶ��ӷ��븸�׵Ķ���������
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
