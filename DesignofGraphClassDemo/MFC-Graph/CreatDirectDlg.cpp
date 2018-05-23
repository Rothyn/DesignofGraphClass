// CreatDirectDlg.cpp : ʵ���ļ�
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

// CCreatDirectDlg �Ի���

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


// CCreatDirectDlg ��Ϣ�������


void CCreatDirectDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialog::OnOK();
}


BOOL CCreatDirectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString tmp[3] = { L"��һ������", L"�ڶ�������", L"�ߵ�Ȩֵ" };
	for (int i = 0; i<3; i++)
	{
		vex_ListCtrl.InsertColumn(i, (LPCTSTR)tmp[i], LVCFMT_CENTER);
		vex_ListCtrl.SetColumnWidth(i, 120);
	}
	DWORD dwStyle = vex_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	vex_ListCtrl.SetExtendedStyle(dwStyle); //������չ���
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CCreatDirectDlg::OnBnClickedBtnVex()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCreatDirectDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCreatDirectDlg::OnBnClickedBtnInit3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	mg.Init1(Number, Arcnum, Vexs);
	mg.Init3();
	Invalidate();
}
