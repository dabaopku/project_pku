// CleanSameInfo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCleanSameInfoApp:
// �йش����ʵ�֣������ CleanSameInfo.cpp
//

class CCleanSameInfoApp : public CWinApp
{
public:
	CCleanSameInfoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCleanSameInfoApp theApp;