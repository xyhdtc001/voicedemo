
// VoiceDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VoiceDemo.h"
#include "VoiceDemoDlg.h"
#include "afxdialogex.h"

#include "CloudVoiceInstance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CVoiceDemoDlg �Ի���



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


// CVoiceDemoDlg ��Ϣ�������

BOOL CVoiceDemoDlg::OnInitDialog()
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
	SetDlgItemText(IDC_EDIT1, "test2425");

	mInstance = new CloudVoiceInstance();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVoiceDemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVoiceDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVoiceDemoDlg::OnBnClickedButton1()
{
	if (!mInstance)
	{
		MessageBox(_T("ϵͳ����"),NULL,NULL);
	}
	mInstance->Init();
	//������ʱ��
	GetSafeHwnd();
	SetTimer(1, 10, NULL); 
}


void CVoiceDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// ���·���.
	mInstance->openMic();
}


void CVoiceDemoDlg::OnBnClickedButton8()
{
	mInstance->closeMc();
}
