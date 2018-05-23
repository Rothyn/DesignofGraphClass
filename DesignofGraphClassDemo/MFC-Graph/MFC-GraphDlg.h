
// MFC-GraphDlg.h : 头文件
//
#pragma once
#include "ALGraph.h"
#include <iostream>
using namespace std;



// CMFCGraphDlg 对话框
class CMFCGraphDlg : public CDialogEx
{
// 构造
public:
	CMFCGraphDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCGRAPH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	int circle(int number);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnBnClickedClear();
	CString OutputDfs;
	CString OutputBfs;
	afx_msg void OnBnClickedBtnTraverse();
	afx_msg void OnEnChangeBfsOut();
	afx_msg void OnEnChangeDfsOut();
	afx_msg void OnBnClickedBtnDijkstra();
	afx_msg void OnBnClickedBtnPrim();
	afx_msg void OnBnClickedBtnKruskal();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnStnClickedPicture();
};
