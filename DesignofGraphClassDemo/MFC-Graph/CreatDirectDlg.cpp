// CreatDirectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC-Graph.h"
#include "CreatDirectDlg.h"
#include "afxdialogex.h"
#include "VEX_Add.h"
#include "VEX_Add.h"
#include "ALGraph.h"
#include "MFC-GraphDlg.h"
#include <iostream>
using namespace std;

// CCreatDirectDlg 对话框

IMPLEMENT_DYNAMIC(CCreatDirectDlg, CDialog)
extern Mgraph mg;
extern int f;
CCreatDirectDlg::CCreatDirectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreatDirectDlg::IDD, pParent)
	, Number(_T(""))
	, Arcnum(_T(""))
	, Vexs(_T(""))
{

}

CCreatDirectDlg::~CCreatDirectDlg()
{
}

void CCreatDirectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTREATE_VEX, vex_ListCtrl);
	DDX_Text(pDX, IDC_EDIT1, Number);
	DDX_Text(pDX, IDC_EDIT2, Arcnum);
	DDX_Text(pDX, IDC_EDIT3, Vexs);
}


BEGIN_MESSAGE_MAP(CCreatDirectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCreatDirectDlg::OnBnClickedOk)
	
	ON_BN_CLICKED(IDC_BTN_VEX, &CCreatDirectDlg::OnBnClickedBtnVex)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTREATE_VEX, &CCreatDirectDlg::OnLvnItemchangedListCtreateVex)
	ON_EN_CHANGE(IDC_EDIT1, &CCreatDirectDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BTN_INIT3, &CCreatDirectDlg::OnBnClickedBtnInit3)
END_MESSAGE_MAP()


// CCreatDirectDlg 消息处理程序


void CCreatDirectDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	CDialog::OnOK();
}


BOOL CCreatDirectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString tmp[3] = { L"第一个顶点", L"第二个顶点", L"边的权值" };
	for (int i = 0; i<3; i++)
	{
		vex_ListCtrl.InsertColumn(i, (LPCTSTR)tmp[i], LVCFMT_CENTER);
		vex_ListCtrl.SetColumnWidth(i, 120);
	}
	DWORD dwStyle = vex_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	vex_ListCtrl.SetExtendedStyle(dwStyle); //设置扩展风格
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CCreatDirectDlg::OnBnClickedBtnVex()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	VEX_Add d;
	if (d.DoModal() == IDOK)
	{
		int index = vex_ListCtrl.GetItemCount();
		vex_ListCtrl.InsertItem(index, d.Vex1);
		vex_ListCtrl.SetItemText(index, 1, d.Vex2);
		vex_ListCtrl.SetItemText(index, 2, d.Weight);
	}
}


void CCreatDirectDlg::OnLvnItemchangedListCtreateVex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCreatDirectDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCreatDirectDlg::OnBnClickedBtnInit3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	mg.Init1(Number, Arcnum, Vexs);
	mg.Init3();
	Invalidate();
}
