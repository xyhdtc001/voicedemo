
// VoiceDemoDlg.h : 头文件
//

#pragma once


// CVoiceDemoDlg 对话框
class CloudVoiceInstance;
class CVoiceDemoDlg : public CDialogEx
{
// 构造
public:
	CVoiceDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VOICEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();


	CloudVoiceInstance *mInstance;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButtonspadd();
	afx_msg void OnBnClickedButtonspdee();
};
