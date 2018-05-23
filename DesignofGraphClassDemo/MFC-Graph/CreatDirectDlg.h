#pragma once
#include "afxcmn.h"
#include "ALGraph.h"
#include "MFC-GraphDlg.h"

// CCreatDirectDlg 对话框

class CCreatDirectDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreatDirectDlg)

public:
	CCreatDirectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreatDirectDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl vex_ListCtrl;
	virtual BOOL OnInitDialog();
	CString Number;
	CString Arcnum;
	CString Vexs;
	afx_msg void OnBnClickedBtnVex();
	afx_msg void OnLvnItemchangedListCtreateVex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedBtnInit3();
};
