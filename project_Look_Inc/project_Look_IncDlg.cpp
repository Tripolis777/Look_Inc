
// project_Look_IncDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "project_Look_Inc.h"
#include "project_Look_IncDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
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


// ���������� ���� Cproject_Look_IncDlg



Cproject_Look_IncDlg::Cproject_Look_IncDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cproject_Look_IncDlg::IDD, pParent)
	, keyValue(0)
	, freePlaceValue(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cproject_Look_IncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, hexTableOut);
	DDX_Text(pDX, IDC_EDIT1, keyValue);
	DDV_MinMaxInt(pDX, keyValue, 0, 2147483647);
	DDX_Text(pDX, IDC_EDIT2, freePlaceValue);
}

BEGIN_MESSAGE_MAP(Cproject_Look_IncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cproject_Look_IncDlg::OnBnClickedEnter)
	ON_BN_CLICKED(IDC_BUTTON2, &Cproject_Look_IncDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON3, &Cproject_Look_IncDlg::OnBnClickedSave)
	ON_EN_CHANGE(IDC_EDIT1, &Cproject_Look_IncDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON5, &Cproject_Look_IncDlg::OnBnClickedAbout)
END_MESSAGE_MAP()


// ����������� ��������� Cproject_Look_IncDlg

BOOL Cproject_Look_IncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
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

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
	table = new HashTable(16);

	CRect rect;
	hexTableOut.GetClientRect(&rect);
	int interval = (rect.Width() - 50) / 3;

	hexTableOut.InsertColumn(0, _T("�"), LVCFMT_LEFT, 50);
	hexTableOut.InsertColumn(1, _T("�������� ���-�������"), LVCFMT_LEFT, interval);
	hexTableOut.InsertColumn(2, _T("�������� �����"), LVCFMT_LEFT, interval);
	hexTableOut.InsertColumn(3, _T("���-�� ��������"), LVCFMT_LEFT, interval);

	updateTable();

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void Cproject_Look_IncDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void Cproject_Look_IncDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR Cproject_Look_IncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cproject_Look_IncDlg::OnBnClickedEnter()						// ������ ��������
{
	UpdateData(TRUE);												// ��������� ������ � �������� TextEdit

	if (!table->searchItem(keyValue).isEmpty())						// ���������, ���� �� ������� � ������
	{
		AfxMessageBox(L"������ ������� ��� ���� � ������", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	if (table->isCrowded())
	{
		AfxMessageBox(L"������� �����������. �� �� ������ ������ ������ 16 �����.", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	if (!table->insertItem(keyValue))								// ���� ���-�� ��������� ��������, �� ������� ������
	{
		AfxMessageBox(L"������ ���������� ��������", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	keyValue = 0;
	UpdateData(FALSE);
	updateTable();													// ��������� ������� ListCtrl, ������� ������� ���� ������� �� ����
}


void Cproject_Look_IncDlg::OnBnClickedSearch()						// ������ �����
{
	UpdateData(TRUE);

	HashTableRow row = table->searchItem(keyValue);					// ������� �������
	if (row.isEmpty())
	{
		AfxMessageBox(L"������� �� ������.", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	CString msg;													// ������� ������ ���������
	msg.Format(_T("�: %i ���-����: %i ����: %i ��������: %i"), row.row + 1, row.hashKey, row.key, row.collision);

	keyValue = 0;
	UpdateData(FALSE);

	AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION, NULL);			// ������� ������

}

void Cproject_Look_IncDlg::updateTable()							// ���������� �������
{

	hexTableOut.DeleteAllItems();									// ������� ��� ������

	for (int i = 0; i < table->getSize(); i++)						//��������� ��������
	{
		HashTableRow row = table->getItem(i);						// ��� ��� ���� ������� ����������� ��������� ����� �������
		if (row.isEmpty())
			continue;

		addTableItem(row.row, row.hashKey, row.key, row.collision);	// ������� ���������� ������ � ������

	}
	freePlaceValue = table->getFreeValue();
	UpdateData(FALSE);
}

void Cproject_Look_IncDlg::addTableItem(int row, int hashKey, int key, int collision)
{
	CString rowStr, hashKeyStr, keyStr, collStr;
	rowStr.Format(_T("%i"), row + 1);
	hashKeyStr.Format(_T("%i"), hashKey);
	keyStr.Format(_T("%i"), key);
	collStr.Format(_T("%i"), collision);

	int i = hexTableOut.GetItemCount();

	hexTableOut.InsertItem(row, rowStr, 0);
	hexTableOut.SetItemText(i, 1, hashKeyStr);
	hexTableOut.SetItemText(i, 2, keyStr);
	hexTableOut.SetItemText(i, 3, collStr);
}

void Cproject_Look_IncDlg::OnOK()	// ����� ��� ������� Enter ���� ��������� �� �����������, �� �������������� ��� ������� 
{
	OnBnClickedEnter();
}

void Cproject_Look_IncDlg::OnBnClickedSave()	// ������ Save
{
	table->saveTable();
	AfxMessageBox(L"������� ���������.", MB_OK | MB_ICONINFORMATION, NULL);
}


void Cproject_Look_IncDlg::OnEnChangeEdit1()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
}


void Cproject_Look_IncDlg::OnBnClickedAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
