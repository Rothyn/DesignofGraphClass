// VEX_Add.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include<string> 
#include<iostream> 
#include<cstring> 
#include "MFC-Graph.h"
#include "VEX_Add.h"
#include "afxdialogex.h"
#include "CreatDirectDlg.h"
#include "ALGraph.h"
using namespace std;

// VEX_Add �Ի���

IMPLEMENT_DYNAMIC(VEX_Add, CDialog)

extern Mgraph mg;
VEX_Add::VEX_Add(CWnd* pParent /*=NULL*/)
	: CDialog(VEX_Add::IDD, pParent)
	, Vex1(_T(""))
	, Vex2(_T(""))
	, Weight(_T(""))
	
{

}

VEX_Add::~VEX_Add()
{
}

void VEX_Add::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Vex1);
	DDX_Text(pDX, IDC_EDIT2, Vex2);
	DDX_Text(pDX, IDC_EDIT3, Weight);
	
}


BEGIN_MESSAGE_MAP(VEX_Add, CDialog)
	ON_BN_CLICKED(IDOK, &VEX_Add::OnBnClickedOk)
END_MESSAGE_MAP()


// VEX_Add ��Ϣ�������

void VEX_Add::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	mg.Init2(Vex1, Vex2, Weight);

	CDialog::OnOK();
}
