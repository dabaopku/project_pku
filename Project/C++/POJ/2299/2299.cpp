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

// ��Ŀ����ACM2299
// ����ʱ�䣺2009-11-14


//�ļ����ƣ�2299.cpp
//�����ߣ�	����
//����ʱ�䣺2009-11-14
//����޸�ʱ�䣺2009-11-14
//���ܣ�	���ACM2299
//�ļ��еĺ������ƺͼ򵥹���������������ע��
//�ļ��ж����ȫ�ֱ����ͼ򵥹���������������ע��
//�ļ����õ������������ȫ�ֱ��������������
//�������ļ���������ϵ����

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

int n;
const int maxn=500010;
int data[maxn],tmp[maxn];
bool init()
//��������
{
	cin>>n;
	if(n==0) return false;
	for(int i=0;i<n;i++)
		scanf("%d",&data[i]);
	return true;
}
__int64 Merge(int *a,int size)	//�ϲ�����a����,�����������
{
	int i,j,k;
	__int64 ans=0;
	for(i=0,j=size/2,k=0;i<size/2 && j<size;k++){	//��������ϲ�,ÿ��ȡС��
		if(a[i]<=a[j]){
			tmp[k]=a[i];
			i++;
		}
		else{
			tmp[k]=a[j];
			ans+=size/2-i;
			j++;
		}
	}
	while(i<size/2){	//ǰ�������ʣ�ಿ��ȡ��
		tmp[k]=a[i];
		i++;
		k++;
	}
	while(j<size){		//��������ʣ�ಿ��ȡ��
		tmp[k]=a[j];
		j++;
		k++;
	}
	for(i=0;i<size;i++){
		a[i]=tmp[i];
	}
	return ans;
}
__int64 MergeSort(int *lst,int size)
//��lst��ʼ�����size���ȵ�������й鲢����,�����������
{
	if(size<=1) 
		return 0;
	__int64 ans=0;						//ͳ���������,����ǰ��벿�ּ�������������
	ans+=MergeSort(lst,size/2);		//�鲢����
	ans+=MergeSort(lst+size/2,size-size/2);
	ans+=Merge(lst,size);	//�ϲ�����
	return ans;
}

void solve()
//�����������
{
	__int64 total=MergeSort(data,n);
	printf("%I64d\n",total);
}
int main()
{
	while(init()){
		solve();
	}
}