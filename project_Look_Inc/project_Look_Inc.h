
// project_Look_Inc.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CProApp:
// � ���������� ������� ������ ��. project_Look_Inc.cpp
//

class CProApp : public CWinApp
{
public:
	CProApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CProApp theApp;