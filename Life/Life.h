
// Life.h : ������� ���� ��������� ��� ���������� Life
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CLifeApp:
// � ���������� ������� ������ ��. Life.cpp
//

class CLifeApp : public CWinApp
{
public:
	CLifeApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLifeApp theApp;
