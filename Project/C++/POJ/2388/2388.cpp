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

// ��Ŀ����ACM2388
// ����ʱ�䣺2009-11-14


//�ļ����ƣ�2388.cpp
//�����ߣ�	����
//����ʱ�䣺2009-11-14
//����޸�ʱ�䣺2009-11-14
//���ܣ�	���ACM2388
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
const int maxn=10010;	//��������Χ
int tmp[maxn];
void Merge(int *a,int size)	//�ϲ�����a����
{
	int i,j,k;
	for(i=0,j=size/2,k=0;i<size/2 && j<size;k++){	//��������ϲ�,ÿ��ȡС��
		if(a[i]<=a[j]){
			tmp[k]=a[i];
			i++;
		}
		else{
			tmp[k]=a[j];
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
}
void MergeSort(int * lst,int size)
//��lst��ʼ�����size���ȵ�������й鲢����
{
	if(size<=1) 
		return ;
	MergeSort(lst,size/2);		//�鲢����
	MergeSort(lst+size/2,size-size/2);
	Merge(lst,size);	//�ϲ�����
	return ;
}
int main()
{
	int n;					//��������
	int data[maxn];			//����
	cin>>n;
	for(int i=0;i<n;i++){	//��������
		cin>>data[i];
	}
	MergeSort(data,n);		//����������
	cout<<data[(n-1)/2]<<endl;
}