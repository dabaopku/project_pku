// Evolution.h : Evolution Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CEvolutionApp:
// �йش����ʵ�֣������ Evolution.cpp
//

class CEvolutionApp : public CWinApp
{
public:
	CEvolutionApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEvolutionApp theApp;