// �������.h : ������� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// EvolutionApp:
// �йش����ʵ�֣������ �������.cpp
//

class EvolutionApp : public CWinApp
{
public:
	EvolutionApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern EvolutionApp theApp;