
// MFC-GraphDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC-Graph.h"
#include "MFC-GraphDlg.h"
#include "afxdialogex.h"
#include "CreatDirectDlg.h"
#include "ShortPathDlg.h"
#include "ALGraph.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
extern Mgraph mg;
extern gpnode bnode[50];//结点坐标
int ct = 0;
int f = 1;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCGraphDlg 对话框



CMFCGraphDlg::CMFCGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCGraphDlg::IDD, pParent)
	, OutputDfs(_T(""))
	, OutputBfs(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DFS_OUT, OutputDfs);
	DDX_Text(pDX, IDC_BFS_OUT, OutputBfs);
}

BEGIN_MESSAGE_MAP(CMFCGraphDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMFCGraphDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_CREATE, &CMFCGraphDlg::OnBnClickedBtnCreate)
	ON_BN_CLICKED(IDC_CLEAR, &CMFCGraphDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BTN_TRAVERSE, &CMFCGraphDlg::OnBnClickedBtnTraverse)
	ON_EN_CHANGE(IDC_BFS_OUT, &CMFCGraphDlg::OnEnChangeBfsOut)
	ON_EN_CHANGE(IDC_DFS_OUT, &CMFCGraphDlg::OnEnChangeDfsOut)
	ON_BN_CLICKED(IDC_BTN_DIJKSTRA, &CMFCGraphDlg::OnBnClickedBtnDijkstra)
	ON_BN_CLICKED(IDC_BTN_PRIM, &CMFCGraphDlg::OnBnClickedBtnPrim)
	ON_BN_CLICKED(IDC_BTN_KRUSKAL, &CMFCGraphDlg::OnBnClickedBtnKruskal)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCGraphDlg::OnBnClickedButton6)
	ON_STN_CLICKED(IDC_PICTURE, &CMFCGraphDlg::OnStnClickedPicture)
END_MESSAGE_MAP()


// CMFCGraphDlg 消息处理程序

BOOL CMFCGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCGraphDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


void CMFCGraphDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//在这里写画图代码
		CPaintDC dc(this); // device context for painting
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CFormView::OnPaint
		CRect rect;
		GetClientRect(rect);
		//CWnd *pWnd = GetDlgItem(IDC_PICTURE);//IDC_picture为picture控件ID
		//pWnd->GetClientRect(&rect);//rc为控件的大小。
		CClientDC gdc(GetDlgItem(IDC_PICTURE));
		while (f)
		{
			CWnd *pWnd = GetDlgItem(IDC_PICTURE);            //画图范围
			CDC *pDC = pWnd->GetDC();     //数据类型
			if (f == 1)
			{
				
				//画圆
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				gdc.SelectObject(&pen);
				if (mg.number)ct %= mg.number;     //此处要取余，不取余的话ct会越来越大，多按遍历按钮直线会对不齐
				for (int i = 0; i < mg.number; i++)
				{
					/*int flag = 1;
					mg.bnode[ct].x = rand() % 400 + 100;
					mg.bnode[ct].y = rand() % 400 + 100;
					while (flag)
					{
						
						for (int j = 0; j < ct; j++)
						{
							if (abs(mg.bnode[ct].x - mg.bnode[j].x) < 30 || abs(mg.bnode[ct].y - mg.bnode[j].y) < 30)
							{
								flag = 0; break;
							}
						}
						if (flag)break;
						else
						{
							mg.bnode[ct].x = rand() % 400 + 100;
							mg.bnode[ct].y = rand() % 400 + 100;
							flag = 1;
						}
					}*/
					CBrush cbrush(RGB(0, 0, 0));
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//画圆
					CString cc;
					cc.Format(_T("%c"), mg.vexs[i]);
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//输出节点上的信息cc
					ct++;
				}
				
				//画直线
				for (int i = 0; i < mg.number; i++) //这里要取顶点数而不是边数
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CBrush brush(RGB(0, 0, 0));
							gdc.MoveTo(mg.bnode[i].x + 10, mg.bnode[i].y + 10);
							gdc.LineTo(mg.bnode[j].x + 10, mg.bnode[j].y + 10);
							CString ss;
							ss.Format(_T("%d"), mg.arcs[i][j]);
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//输出边上的信息
						}
					}
				}
			}
			//画p直线
			if (f == 2)
			{
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				gdc.SelectObject(&pen);
				for (int i = 0; i < mg.number; i++)
				{
					CBrush cbrush(RGB(0, 0, 0));
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//画圆
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CBrush brush(RGB(0, 0, 0));
							gdc.MoveTo(mg.bnode[i].x + 10, mg.bnode[i].y + 10);
							gdc.LineTo(mg.bnode[j].x + 10, mg.bnode[j].y + 10);
						}
					}
				}
				CPen pen2;
				pen2.CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
				gdc.SelectObject(&pen2);
				for (int i = 0; i < mg.ctp; i++)  //画直线
				{		
					int begg = mg.LocateVex(mg.outprim[i].beg);
					int endd = mg.LocateVex(mg.outprim[i].end);
					gdc.MoveTo(mg.bnode[begg].x + 10, mg.bnode[begg].y + 10);
					gdc.LineTo(mg.bnode[endd].x + 10, mg.bnode[endd].y + 10);
				}
				for (int i = 0; i < mg.number; i++)
				{
					CString cc;
					cc.Format(_T("%c"), mg.vexs[i]);
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//输出节点上的信息cc
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CString ss;
							ss.Format(_T("%d"), mg.arcs[i][j]);
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//输出边上的信息
						}
					}
				}
				
			}
			//画k直线
			if (f == 3)
			{
				//CString strMsg;
				//strMsg.Format(_T("%d"), mg.ctk);
				//MessageBox(strMsg);
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				gdc.SelectObject(&pen);
				for (int i = 0; i < mg.number; i++)
				{
					CBrush cbrush(RGB(0, 0, 0));
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//画圆
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CBrush brush(RGB(0, 0, 0));
							gdc.MoveTo(mg.bnode[i].x + 10, mg.bnode[i].y + 10);
							gdc.LineTo(mg.bnode[j].x + 10, mg.bnode[j].y + 10);
						}
					}
				}
				CPen pen3;
				pen3.CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
				gdc.SelectObject(&pen3);
				for (int i = 0; i < mg.ctk; i++)
				{
					int begg = mg.LocateVex(mg.outkruskal[i].beg);
					int endd = mg.LocateVex(mg.outkruskal[i].end);
					gdc.MoveTo(mg.bnode[begg].x + 10, mg.bnode[begg].y + 10);
					gdc.LineTo(mg.bnode[endd].x + 10, mg.bnode[endd].y + 10);
				}
				for (int i = 0; i < mg.number; i++)
				{
					CString cc;
					cc.Format(_T("%c"), mg.vexs[i]);
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//输出节点上的信息cc
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] < 1000 && mg.arcs[i][j] > 0)
						{
							CString ss;
							ss.Format(_T("%d"), mg.arcs[i][j]);
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//输出边上的信息
						}
					}
				}
			}
			//画d直线
			if (f == 4)
			{
				//加窗口处理起始点和终点的选择
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				gdc.SelectObject(&pen);
				for (int i = 0; i < mg.number; i++)
				{
					CBrush cbrush(RGB(0, 0, 0));
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//画圆
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CBrush brush(RGB(0, 0, 0));
							gdc.MoveTo(mg.bnode[i].x + 10, mg.bnode[i].y + 10);
							gdc.LineTo(mg.bnode[j].x + 10, mg.bnode[j].y + 10);
						}
					}
				}
				if (mg.ctd[mg.start5][mg.end5] == 1 || mg.ctd[mg.start5][mg.end5] == 0)
					MessageBox(L"没有通路");
				else
				{
					CPen pen4;
					pen4.CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
					gdc.SelectObject(&pen4);
					for (int i = 0; i < mg.ctd[mg.start5][mg.end5] - 1; i++)
					{
						if (mg.outdijkstra[mg.start5][mg.end5][i] && mg.outdijkstra[mg.start5][mg.end5][i] < 1000
							&& mg.outdijkstra[mg.start5][mg.end5][i + 1] && mg.outdijkstra[mg.start5][mg.end5][i + 1] < 1000)
						{
							int begg = mg.LocateVex(mg.outdijkstra[mg.start5][mg.end5][i]);
							int endd = mg.LocateVex(mg.outdijkstra[mg.start5][mg.end5][i + 1]);
							gdc.MoveTo(mg.bnode[begg].x + 10, mg.bnode[begg].y + 10);
							gdc.LineTo(mg.bnode[endd].x + 10, mg.bnode[endd].y + 10);
						}
					}
				}
				for (int i = 0; i < mg.number; i++)
				{
					CString cc;
					cc.Format(_T("%c"), mg.vexs[i]);
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//输出节点上的信息cc
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CString ss;
							ss.Format(_T("%d"), mg.arcs[i][j]);
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//输出边上的信息
						}
					}
				}
			}
			f = 0;
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCGraphDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();//退出对话框
}


void CMFCGraphDlg::OnBnClickedBtnCreate()
{
	// TODO:  在此添加控件通知处理程序代码
	CCreatDirectDlg dlgg;
	if (dlgg.DoModal() == IDOK)
	{
		

	}
}


void CMFCGraphDlg::OnBnClickedClear()
{
	// TODO:  在此添加控件通知处理程序代码
	f = 0; Invalidate();
	ct = mg.ctk = mg.ctp = 0;//清空界面演示
	//清空编辑框
	mg.dfs = "";
	OutputBfs = "";
	OutputDfs = "";
	mg.arcnum = 0;mg.number = 0;
	mg.Init3();
	mg.Init4();
	UpdateData(false);
}


void CMFCGraphDlg::OnBnClickedBtnTraverse()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	mg.dfs = "";
	mg.Init4();
	mg.DFS1(0);
 	OutputDfs = mg.dfs;
	OutputBfs = mg.BFS();
	f = 1;
	Invalidate();
	UpdateData(false);
}


void CMFCGraphDlg::OnEnChangeBfsOut()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCGraphDlg::OnEnChangeDfsOut()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void CMFCGraphDlg::OnBnClickedBtnPrim()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	mg.Init4();  //一定要把visited[]全恢复为0
	mg.Prim();
	f = 2;
	Invalidate();
	UpdateData(false);
}


void CMFCGraphDlg::OnBnClickedBtnKruskal()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	mg.Kruskal();
	f = 3;
	Invalidate();
	UpdateData(false);
}



void CMFCGraphDlg::OnBnClickedBtnDijkstra()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	mg.Dijkstra();
	ShortPathDlg dlgg;
	if (dlgg.DoModal() == IDOK)
	{
		f = 4;
	}
	Invalidate();
	UpdateData(false);
}

void CMFCGraphDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	mg.Init6();
	f = 1;
	Invalidate();
	//UpdateData(false);
}


void CMFCGraphDlg::OnStnClickedPicture()
{
	// TODO:  在此添加控件通知处理程序代码
}
