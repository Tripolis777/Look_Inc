
// project_Look_IncDlg.h : ���� ���������
//

#pragma once
#include "afxcmn.h"
#include "HashTable.h"
#include "HashTableRow.h"
#include "afxwin.h"

// ���������� ���� Cproject_Look_IncDlg
class Cproject_Look_IncDlg : public CDialogEx
{
// ��������
public:
	Cproject_Look_IncDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_PROJECT_LOOK_INC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

	void updateTable();
public:
	CListCtrl hexTableOut;
	HashTable* table;
	afx_msg void OnBnClickedEnter();
	int keyValue;
	afx_msg void OnBnClickedSearch();
	void addTableItem(int row, int hashKey, int key, int collision);
	afx_msg void OnBnClickedSave();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedAbout();
	int freePlaceValue;
};
