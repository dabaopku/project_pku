// Li3_6.h : Li3_6 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLi3_6App:
// �йش����ʵ�֣������ Li3_6.cpp
//

class CLi3_6App : public CWinApp
{
public:
	CLi3_6App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLi3_6App theApp;