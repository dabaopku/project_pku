// Li2_1.h : Li2_1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CLi2_1App:
// �йش����ʵ�֣������ Li2_1.cpp
//

class CLi2_1App : public CWinApp
{
public:
	CLi2_1App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLi2_1App theApp;