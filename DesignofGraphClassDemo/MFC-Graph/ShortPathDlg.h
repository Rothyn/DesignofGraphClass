#pragma once
//#include "stdafx.h"
#include "MFC-Graph.h"
#include "MFC-GraphDlg.h"
//#include "afxdialogex.h"
#include "ALGraph.h"

// ShortPathDlg �Ի���

class ShortPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShortPathDlg)

public:
	ShortPathDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShortPathDlg();

// �Ի�������
	enum { IDD = IDD_SHORTPATH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString startvex;
	CString endvex;
	afx_msg void OnBnClickedOk();
};
