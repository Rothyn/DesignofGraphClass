
// MFC-Graph.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCGraphApp: 
// �йش����ʵ�֣������ MFC-Graph.cpp
//




class CMFCGraphApp : public CWinApp
{
public:
	CMFCGraphApp();
	
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCGraphApp theApp;