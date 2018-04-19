
// VoiceDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VoiceDemo.h"
#include "VoiceDemoDlg.h"
#include "afxdialogex.h"

#include "CloudVoiceInstance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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


// CVoiceDemoDlg 对话框



CVoiceDemoDlg::CVoiceDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVoiceDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mInstance = NULL;
}

void CVoiceDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVoiceDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CVoiceDemoDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CVoiceDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CVoiceDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CVoiceDemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CVoiceDemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CVoiceDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON8, &CVoiceDemoDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CVoiceDemoDlg 消息处理程序

BOOL CVoiceDemoDlg::OnInitDialog()
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
	SetDlgItemText(IDC_EDIT1, "test2425");

	mInstance = new CloudVoiceInstance();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVoiceDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVoiceDemoDlg::OnPaint()
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
HCURSOR CVoiceDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVoiceDemoDlg::OnBnClickedButton1()
{
	if (!mInstance)
	{
		MessageBox(_T("系统错误"),NULL,NULL);
	}
	mInstance->Init();
	//开启定时器
	GetSafeHwnd();
	SetTimer(1, 10, NULL); 
}


void CVoiceDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	if (nIDEvent == 1)
	{
		if (1)
		{
			mInstance->Poll();
		}
	}
}


void CVoiceDemoDlg::OnBnClickedButton2()
{
	CString strRoomName;
	GetDlgItemText(IDC_EDIT1,strRoomName);
	if (strRoomName.GetLength() > 0)
	{
		mInstance->joinRoom(strRoomName.GetBuffer());
	}
}


void CVoiceDemoDlg::OnBnClickedButton4()
{
	//mic ++
}


void CVoiceDemoDlg::OnBnClickedButton6()
{
	// mic --
}


void CVoiceDemoDlg::OnBnClickedButton5()
{
	// speaker++
}



void CVoiceDemoDlg::OnBnClickedButton3()
{
	// 按下发言.
	mInstance->openMic();
}


void CVoiceDemoDlg::OnBnClickedButton8()
{
	mInstance->closeMc();
}
