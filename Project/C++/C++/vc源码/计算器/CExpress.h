 #include <csetjmp>
#include "stdafx.h"

#define EXP_LEN    100             //���������ַ��������ĳ���

/*------------�������ĺ궨��--------------*/
#define INVALID_CHAR_TAIL 0        //���ʽ����зǷ��ַ�
#define CHAR_AFTER_RIGHT 1         //�����ź����ӷǷ��ַ�
#define LEFT_AFTER_NUM  2          //���ֺ�Ƿ�ֱ������������
#define INVALID_CHAR_IN  3         //���ʽ�к��зǷ��ַ�
#define NO_RIGHT   4               //ȱ��������
#define EMPTY_BRACKET  5           //�������ޱ��ʽ
#define UNEXPECTED_END  6          //Ԥ������������ʽ����

static jmp_buf errjb;              //������ת������

class CExpress
{
public:

	CExpress(){pos=0;
	}
	//********�����Ǻ�������*********
	//����ʽ��E -> T+E | T-E | T���ĺ��������������Ӽ��������ʽ��
	int E_AddSub(); 
	//����ʽ��T -> F*T | F/T | F���ĺ��������������˳��������ʽ��
	int T_MulDiv(); 
	//����ʽ��F -> i | (E)���ĺ����������������ֺ������ڵı��ʽ��
	int F_Number();
	//��������������ָ������λ�ã�������Ϣ��
	void Error(int ErrCode);
	
	int pos;                        //�ַ�ָʾ����־�������������ڷ������ַ���λ��
	char expr[EXP_LEN];             //�������ʽ�����ַ�������
//	CString expr;
};


