#pragma once
#include "afxwin.h"
#include "CreatDirectDlg.h"
#include <map>
using namespace std;
// VEX_Add 对话框

class VEX_Add : public CDialog
{
	DECLARE_DYNAMIC(VEX_Add)

public:
	VEX_Add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~VEX_Add();

// 对话框数据
	enum { IDD = IDD_VEX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Vex2;
	CString Weight;
	afx_msg void OnEnChangeEdit1();
	CString Vex1;
	afx_msg void OnBnClickedOk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
