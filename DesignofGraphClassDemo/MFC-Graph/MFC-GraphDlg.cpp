
// MFC-GraphDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
extern Mgraph mg;
extern gpnode bnode[50];//�������
int ct = 0;
int f = 1;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCGraphDlg �Ի���



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


// CMFCGraphDlg ��Ϣ�������

BOOL CMFCGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�


void CMFCGraphDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//������д��ͼ����
		CPaintDC dc(this); // device context for painting
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint
		CRect rect;
		GetClientRect(rect);
		//CWnd *pWnd = GetDlgItem(IDC_PICTURE);//IDC_pictureΪpicture�ؼ�ID
		//pWnd->GetClientRect(&rect);//rcΪ�ؼ��Ĵ�С��
		CClientDC gdc(GetDlgItem(IDC_PICTURE));
		while (f)
		{
			CWnd *pWnd = GetDlgItem(IDC_PICTURE);            //��ͼ��Χ
			CDC *pDC = pWnd->GetDC();     //��������
			if (f == 1)
			{
				
				//��Բ
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				gdc.SelectObject(&pen);
				if (mg.number)ct %= mg.number;     //�˴�Ҫȡ�࣬��ȡ��Ļ�ct��Խ��Խ�󣬶ఴ������ťֱ�߻�Բ���
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
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//��Բ
					CString cc;
					cc.Format(_T("%c"), mg.vexs[i]);
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//����ڵ��ϵ���Ϣcc
					ct++;
				}
				
				//��ֱ��
				for (int i = 0; i < mg.number; i++) //����Ҫȡ�����������Ǳ���
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
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//������ϵ���Ϣ
						}
					}
				}
			}
			//��pֱ��
			if (f == 2)
			{
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				gdc.SelectObject(&pen);
				for (int i = 0; i < mg.number; i++)
				{
					CBrush cbrush(RGB(0, 0, 0));
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//��Բ
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
				for (int i = 0; i < mg.ctp; i++)  //��ֱ��
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
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//����ڵ��ϵ���Ϣcc
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CString ss;
							ss.Format(_T("%d"), mg.arcs[i][j]);
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//������ϵ���Ϣ
						}
					}
				}
				
			}
			//��kֱ��
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
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//��Բ
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
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//����ڵ��ϵ���Ϣcc
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] < 1000 && mg.arcs[i][j] > 0)
						{
							CString ss;
							ss.Format(_T("%d"), mg.arcs[i][j]);
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//������ϵ���Ϣ
						}
					}
				}
			}
			//��dֱ��
			if (f == 4)
			{
				//�Ӵ��ڴ�����ʼ����յ��ѡ��
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				gdc.SelectObject(&pen);
				for (int i = 0; i < mg.number; i++)
				{
					CBrush cbrush(RGB(0, 0, 0));
					pDC->Ellipse(mg.bnode[i].x, mg.bnode[i].y, mg.bnode[i].x + 30, mg.bnode[i].y + 30);//��Բ
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
					MessageBox(L"û��ͨ·");
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
					pDC->TextOutW(mg.bnode[i].x + 10, mg.bnode[i].y + 7, cc);//����ڵ��ϵ���Ϣcc
				}
				for (int i = 0; i < mg.number; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (mg.arcs[i][j] != 1000 && mg.arcs[i][j] != 0)
						{
							CString ss;
							ss.Format(_T("%d"), mg.arcs[i][j]);
							pDC->TextOutW((mg.bnode[j].x + 10 + mg.bnode[i].x + 10) / 2, (mg.bnode[j].y + mg.bnode[i].y) / 2, ss);//������ϵ���Ϣ
						}
					}
				}
			}
			f = 0;
		}
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCGraphDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();//�˳��Ի���
}


void CMFCGraphDlg::OnBnClickedBtnCreate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CCreatDirectDlg dlgg;
	if (dlgg.DoModal() == IDOK)
	{
		

	}
}


void CMFCGraphDlg::OnBnClickedClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	f = 0; Invalidate();
	ct = mg.ctk = mg.ctp = 0;//��ս�����ʾ
	//��ձ༭��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCGraphDlg::OnEnChangeDfsOut()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}




void CMFCGraphDlg::OnBnClickedBtnPrim()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	mg.Init4();  //һ��Ҫ��visited[]ȫ�ָ�Ϊ0
	mg.Prim();
	f = 2;
	Invalidate();
	UpdateData(false);
}


void CMFCGraphDlg::OnBnClickedBtnKruskal()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	mg.Kruskal();
	f = 3;
	Invalidate();
	UpdateData(false);
}



void CMFCGraphDlg::OnBnClickedBtnDijkstra()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	mg.Init6();
	f = 1;
	Invalidate();
	//UpdateData(false);
}


void CMFCGraphDlg::OnStnClickedPicture()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
