
// ShowVideoAndProcess.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShowVideoAndProcessApp: 
// �йش����ʵ�֣������ ShowVideoAndProcess.cpp
//

class CShowVideoAndProcessApp : public CWinApp
{
public:
	CShowVideoAndProcessApp();

// ��д
public:
	virtual BOOL InitInstance();
//private:
//	int videoNumber;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShowVideoAndProcessApp theApp;