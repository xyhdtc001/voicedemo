
// VoiceDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVoiceDemoApp: 
// �йش����ʵ�֣������ VoiceDemo.cpp
//

class CVoiceDemoApp : public CWinApp
{
public:
	CVoiceDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVoiceDemoApp theApp;