// MFC_���±�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_���±�App:
// �йش����ʵ�֣������ MFC_���±�.cpp
//

class CMFC_���±�App : public CWinApp
{
public:
	CMFC_���±�App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_���±�App theApp;