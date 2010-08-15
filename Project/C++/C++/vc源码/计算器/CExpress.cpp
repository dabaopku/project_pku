#include "CExpress.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

const string ErrCodeStr[]=           //���ʽ������Ϣ
{
	"���ʽ����зǷ��ַ���",
	"�����ź����ӷǷ��ַ���",
	"���ֺ�Ƿ�ֱ�����������ţ�",
	"���ʽ�к��зǷ��ַ���",
	"ȱ�������ţ�",
	"�������ޱ��ʽ����ʽ��������",
	"���ʽ�Ƿ���������ʽ��������"
};


//����ʽ��E -> T+E | T-E | T���ĺ��������������Ӽ��������ʽ��
//���ؼ�����
int CExpress::E_AddSub()
{
	int rtn=T_MulDiv();              //����Ӽ��������ʽ����Ԫ
	
	while(expr[pos]=='+'||expr[pos]=='-')
	{
		int op=expr[pos++];          //ȡ�ַ��������е�ǰλ�õķ��ŵ�op
		int opr2=T_MulDiv();          //����Ӽ��������ʽ����Ԫ
		
		//������ֵ
		if(op=='+')                        //�����"+"��
			rtn+=opr2;                     //���üӷ�����
		else                               //������"-"�ţ�
			rtn-=opr2;                      //�ü�������
	}
	return rtn;
}

//�Ƶ�ʽ��T -> F*T | F/T | F���ĺ��������������˳��������ʽ��
//���ؼ�����
int CExpress::T_MulDiv()
{
	int rtn=F_Number();          //����˳��������ʽ����Ԫ
	
	while(expr[pos]=='*'||expr[pos]=='/')
	{
		int op=expr[pos++];        //ȡ�ַ��������е�ǰλ�õķ��ŵ�op
		int opr2=F_Number();      //����˳��������ʽ����Ԫ
		
		//������ֵ
		if(op=='*')                       //�����"*"��
			rtn*=opr2;                     //���ó˷�����
		else                              //������"\"�ţ�
			rtn/=opr2;                     //�ó�������
	}
	return rtn;
}

//����ʽ��F -> i | (E)���ĺ����������������ֺ������ڵı��ʽ��
int CExpress::F_Number()
{
	int rtn;                            //�����洢����ֵ�ı���
	
	//�ò���ʽF->(E)�Ƶ���
	if(expr[pos]=='(')              //����ַ���������ǰλ�õķ�����"("
	{
		pos++;                         //��ָʾ����һָ����һ������
		rtn=E_AddSub();           //���ò���ʽ��E -> T+E | T-E | T���ķ�������
		
		if(expr[pos++]!=')')         //���û����"("ƥ���")"
			Error(NO_RIGHT);        //���������
		
		return rtn;
	} 
	
	
	if(isdigit(expr[pos]))        //����ַ��������е�ǰλ�õ��ַ�Ϊ����
	{
		//���ò���ʽF -> i�Ƶ�
		//���ַ��������е�ǰλ�õ��ַ���ת��Ϊ����
		rtn=atoi(expr+pos);
//		rtn=_atoi(expr.GetAt(pos-1));
		//�ı�ָʾ����ֵ�������ַ������������ֲ��֣��ҵ���һ�������ַ���
		while(isdigit(expr[pos]))
			pos++;
	}
	else                                      //������������������Ӧ�Ĵ���
	{
		if(expr[pos]==')')                    //�������һ��")"
			Error(EMPTY_BRACKET);    //���������ǿյģ������������������ʽ��
		else if(expr[pos]=='\0')           //�����ʱ���봮����
			Error(UNEXPECTED_END);  //���������ʽ�Ƿ�����
		else
			Error(INVALID_CHAR_IN);    //���������ַ����к��зǷ��ַ�
	}
	
	return rtn;
}

//�������������������룬����ָ������λ�ã�������Ϣ��
void CExpress::Error(int ErrCode)
{
//	cout<<'\r';                      //����
//	while(pos--)
//		cout<<' ';                   //��ӡ�ո񣬰�ָʾ�����"^"�Ƶ������ַ����ĳ���λ��
//	cout<<"^ �﷨���� ������  ";
//	cout<<ErrCodeStr[ErrCode];       //���������Ϣ
//	cout<<endl<<'\a';                //����������
	char buffer[100]=" ";
	int len=0;
	while(NULL!=ErrCodeStr[ErrCode][len])
		len++;
	for(int i=0;i<len;i++)
		buffer[i]=ErrCodeStr[ErrCode][i];
	buffer[len]='\0';

	AfxMessageBox (buffer,MB_OK,0);
	longjmp(errjb,1);            //��ת��main()�����е�setjmp���ô���������setjmp(errjb)�ķ���ֵΪ1
}