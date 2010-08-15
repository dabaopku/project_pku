 #include <csetjmp>
#include "stdafx.h"

#define EXP_LEN    100             //定义输入字符缓冲区的长度

/*------------出错代码的宏定义--------------*/
#define INVALID_CHAR_TAIL 0        //表达式后跟有非法字符
#define CHAR_AFTER_RIGHT 1         //右括号后连接非法字符
#define LEFT_AFTER_NUM  2          //数字后非法直接连接左括号
#define INVALID_CHAR_IN  3         //表达式中含有非法字符
#define NO_RIGHT   4               //缺少右括号
#define EMPTY_BRACKET  5           //括号内无表达式
#define UNEXPECTED_END  6          //预期外的算术表达式结束

static jmp_buf errjb;              //出错跳转缓冲器

class CExpress
{
public:

	CExpress(){pos=0;
	}
	//********以下是函数声明*********
	//产生式“E -> T+E | T-E | T”的函数，用来分析加减算术表达式。
	int E_AddSub(); 
	//产生式“T -> F*T | F/T | F”的函数，用来分析乘除算术表达式。
	int T_MulDiv(); 
	//产生式“F -> i | (E)”的函数，用来分析数字和括号内的表达式。
	int F_Number();
	//出错处理函数，可以指出错误位置，出错信息。
	void Error(int ErrCode);
	
	int pos;                        //字符指示器标志：用来保存正在分析的字符的位置
	char expr[EXP_LEN];             //算术表达式输入字符缓冲区
//	CString expr;
};


