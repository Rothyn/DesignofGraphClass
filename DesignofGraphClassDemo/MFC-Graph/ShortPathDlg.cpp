// ShortPathDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC-Graph.h"
#include "ShortPathDlg.h"
#include "ALGraph.h"
#include "CreatDirectDlg.h"
#include "MFC-GraphDlg.h"
#include "afxdialogex.h"


// ShortPathDlg 对话框

IMPLEMENT_DYNAMIC(ShortPathDlg, CDialogEx)
extern Mgraph mg;

ShortPathDlg::ShortPathDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShortPathDlg::IDD, pParent)
	, startvex(_T(""))
	, endvex(_T(""))
{

}

ShortPathDlg::~ShortPathDlg()
{
}

void ShortPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, startvex);
	DDX_Text(pDX, IDC_EDIT2, endvex);
}


BEGIN_MESSAGE_MAP(ShortPathDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ShortPathDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ShortPathDlg 消息处理程序


void ShortPathDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	mg.Init5(startvex, endvex);
	CDialogEx::OnOK();	
}
