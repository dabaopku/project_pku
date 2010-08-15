#include "CExpress.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

const string ErrCodeStr[]=           //表达式出错信息
{
	"表达式后跟有非法字符！",
	"右括号后连接非法字符！",
	"数字后非法直接连接左括号！",
	"表达式中含有非法字符！",
	"缺少右括号！",
	"括号内无表达式或表达式不完整！",
	"表达式非法结束或表达式不完整！"
};


//产生式“E -> T+E | T-E | T”的函数，用来分析加减算术表达式。
//返回计算结果
int CExpress::E_AddSub()
{
	int rtn=T_MulDiv();              //计算加减算术表达式的左元
	
	while(expr[pos]=='+'||expr[pos]=='-')
	{
		int op=expr[pos++];          //取字符缓冲区中当前位置的符号到op
		int opr2=T_MulDiv();          //计算加减算术表达式的右元
		
		//计算求值
		if(op=='+')                        //如果是"+"号
			rtn+=opr2;                     //则用加法计算
		else                               //否则（是"-"号）
			rtn-=opr2;                      //用减法计算
	}
	return rtn;
}

//推导式“T -> F*T | F/T | F”的函数，用来分析乘除算术表达式。
//返回计算结果
int CExpress::T_MulDiv()
{
	int rtn=F_Number();          //计算乘除算术表达式的左元
	
	while(expr[pos]=='*'||expr[pos]=='/')
	{
		int op=expr[pos++];        //取字符缓冲区中当前位置的符号到op
		int opr2=F_Number();      //计算乘除算术表达式的右元
		
		//计算求值
		if(op=='*')                       //如果是"*"号
			rtn*=opr2;                     //则用乘法计算
		else                              //否则（是"\"号）
			rtn/=opr2;                     //用除法计算
	}
	return rtn;
}

//产生式“F -> i | (E)”的函数，用来分析数字和括号内的表达式。
int CExpress::F_Number()
{
	int rtn;                            //声明存储返回值的变量
	
	//用产生式F->(E)推导：
	if(expr[pos]=='(')              //如果字符缓冲区当前位置的符号是"("
	{
		pos++;                         //则指示器加一指向下一个符号
		rtn=E_AddSub();           //调用产生式“E -> T+E | T-E | T”的分析函数
		
		if(expr[pos++]!=')')         //如果没有与"("匹配的")"
			Error(NO_RIGHT);        //则产生错误
		
		return rtn;
	} 
	
	
	if(isdigit(expr[pos]))        //如果字符缓冲区中当前位置的字符为数字
	{
		//则用产生式F -> i推导
		//把字符缓冲区中当前位置的字符串转换为整数
		rtn=atoi(expr+pos);
//		rtn=_atoi(expr.GetAt(pos-1));
		//改变指示器的值，跳过字符缓冲区的数字部分，找到下一个输入字符。
		while(isdigit(expr[pos]))
			pos++;
	}
	else                                      //如果不是数字则产生相应的错误
	{
		if(expr[pos]==')')                    //如果发现一个")"
			Error(EMPTY_BRACKET);    //则是括号是空的，即括号内无算术表达式。
		else if(expr[pos]=='\0')           //如果此时输入串结束
			Error(UNEXPECTED_END);  //则算术表达式非法结束
		else
			Error(INVALID_CHAR_IN);    //否则输入字符串中含有非法字符
	}
	
	return rtn;
}

//出错处理函数，输入错误代码，可以指出错误位置，出错信息。
void CExpress::Error(int ErrCode)
{
//	cout<<'\r';                      //换行
//	while(pos--)
//		cout<<' ';                   //打印空格，把指示错误的"^"移到输入字符串的出错位置
//	cout<<"^ 语法错误 ！！！  ";
//	cout<<ErrCodeStr[ErrCode];       //输出错误信息
//	cout<<endl<<'\a';                //发出警报音
	char buffer[100]=" ";
	int len=0;
	while(NULL!=ErrCodeStr[ErrCode][len])
		len++;
	for(int i=0;i<len;i++)
		buffer[i]=ErrCodeStr[ErrCode][i];
	buffer[len]='\0';

	AfxMessageBox (buffer,MB_OK,0);
	longjmp(errjb,1);            //跳转到main()函数中的setjmp调用处，并设置setjmp(errjb)的返回值为1
}