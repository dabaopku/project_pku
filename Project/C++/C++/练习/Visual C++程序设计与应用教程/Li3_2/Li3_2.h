// Li3_2.h : Li3_2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLi3_2App:
// �йش����ʵ�֣������ Li3_2.cpp
//

class CLi3_2App : public CWinApp
{
public:
	CLi3_2App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLi3_2App theApp;