
// ShotIDCreatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ShotIDCreator.h"
#include "ShotIDCreatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShotIDCreatorDlg 对话框



CShotIDCreatorDlg::CShotIDCreatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOTIDCREATOR_DIALOG, pParent)
	, MaxShotID(99999)
	, ShotNumber(1)
	, m_interval(60)
	, mPort(12100)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShotIDCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ShotNumber);
	//DDV_MinMaxInt(pDX, ShotNumber, 0, 99999);
	DDX_Text(pDX, IDC_EDIT2, m_interval);
	//DDV_MinMaxInt(pDX, m_interval, 10, INT_MAX);
	DDX_Text(pDX, IDC_EDIT3, mPort);
	//DDV_MinMaxInt(pDX, mPort, 0, 65535);
}

BEGIN_MESSAGE_MAP(CShotIDCreatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, &CShotIDCreatorDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CShotIDCreatorDlg 消息处理程序

BOOL CShotIDCreatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShotIDCreatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShotIDCreatorDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShotIDCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShotIDCreatorDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //刷新界面参数到相应变量
	CString strTemp;
	GetDlgItemText(IDC_START, strTemp);
	if (strTemp == _T("开始"))
	{
		if (!ConfineData()) return;
		// 开启定时器，第1个参数表示ID号，第二个参数表示刷新时间ms
		// 首次进入程序时，间隔短时间便发射第一个炮号，后面再按照界面间隔刷新炮号。
		int firstInterval = 10;
		int timeInterval = firstInterval * 1000;
		SetTimer(2, timeInterval, NULL);
		//Sleep(firstInterval * 1000);

		/*timeInterval = m_interval * 1000;
		SetTimer(1, timeInterval, NULL);*/
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		SetDlgItemText(IDC_START, _T("停止"));
	}
	else {
		KillTimer(1);
		KillTimer(2);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
		SetDlgItemText(IDC_START, _T("开始"));
	}
}

//定时器
void CShotIDCreatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		if(ShotNumber< MaxShotID){
			ShotNumber += 1;
			UpdateData(FALSE); //刷新内存值到界面
			sendShotNum(ShotNumber);
		}
		else {
			OnBnClickedStart();
			CString msg;
			msg.Format(_T("炮号大于最大值:%d"), MaxShotID);
			MessageBox(msg, _T("炮号溢出"), MB_OKCANCEL | MB_ICONWARNING);
			KillTimer(1);  //只进入一次
		}
		break;
	case 2:
		if (ShotNumber < MaxShotID) {
			sendShotNum(ShotNumber);
			SetTimer(1, m_interval *1000, NULL);
		}
		else {
			OnBnClickedStart();
			CString msg;
			msg.Format(_T("炮号大于最大值:%d"), MaxShotID);
			MessageBox(msg, _T("炮号溢出"), MB_OKCANCEL | MB_ICONWARNING);
			KillTimer(2);  //只进入一次
		}
		KillTimer(2);  //只进入一次
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CShotIDCreatorDlg::sendShotNum(int shotID)
{
	//将炮号转化为标准格式
	char m_dataToSend[11] = "+PLS_"; 

	CString str1;
	str1.Format(_T("%05d"), shotID);
	for (int i = 0; i < 5; i++)
	{
		m_dataToSend[i+5] = str1[i];
	}

	SOCKADDR_IN addr;
	int broad = 1;
	SOCKET sockServer = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(sockServer, SOL_SOCKET, SO_BROADCAST, (const char*)&broad, sizeof(broad));

	addr.sin_addr.s_addr = INADDR_BROADCAST;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(mPort);
	sendto(sockServer, m_dataToSend, strlen(m_dataToSend) + 1, 0, (SOCKADDR*)&addr, sizeof(SOCKADDR));
}


//限制时间间隔输入范围0~65535
bool CShotIDCreatorDlg::ConfineData() {
	UpdateData(true);
	if (m_interval < 10)
	{
		MessageBox(_T("时间间隔输入范围应大于等于10s\n"));
		m_interval = 10;
		UpdateData(false);
		return false;
	}

	if ((mPort < 0) || (mPort > 65535))
	{
		MessageBox(_T("端口的范围为0~65535\n"));
		if (mPort > 65535)
		{
			mPort = 65535;
		}
		else
		{
			mPort = 1;
		}
		UpdateData(false);
		return false;
	}

	if (ShotNumber < 0)
	{
		MessageBox(_T("炮号输入应大于0\n"));
		m_interval = 10;
		UpdateData(false);
		return false;
	}
	return true;
}