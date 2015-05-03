
// project_Look_Inc.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CProApp:
// О реализации данного класса см. project_Look_Inc.cpp
//

class CProApp : public CWinApp
{
public:
	CProApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CProApp theApp;