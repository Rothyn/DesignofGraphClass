#pragma once
//#include "stdafx.h"
#include "MFC-Graph.h"
#include "MFC-GraphDlg.h"
//#include "afxdialogex.h"
#include "ALGraph.h"

// ShortPathDlg 对话框

class ShortPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShortPathDlg)

public:
	ShortPathDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ShortPathDlg();

// 对话框数据
	enum { IDD = IDD_SHORTPATH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString startvex;
	CString endvex;
	afx_msg void OnBnClickedOk();
};
