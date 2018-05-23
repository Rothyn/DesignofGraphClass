
// MFC-GraphDlg.h : ͷ�ļ�
//
#pragma once
#include "ALGraph.h"
#include <iostream>
using namespace std;



// CMFCGraphDlg �Ի���
class CMFCGraphDlg : public CDialogEx
{
// ����
public:
	CMFCGraphDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCGRAPH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
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
