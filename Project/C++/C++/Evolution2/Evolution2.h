// Evolution2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEvolution2App:
// �йش����ʵ�֣������ Evolution2.cpp
//

class CEvolution2App : public CWinApp
{
public:
	CEvolution2App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CEvolution2App theApp;