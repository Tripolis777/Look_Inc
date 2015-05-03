
// project_Look_IncDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "project_Look_Inc.h"
#include "project_Look_IncDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// диалоговое окно Cproject_Look_IncDlg



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


// обработчики сообщений Cproject_Look_IncDlg

BOOL Cproject_Look_IncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	table = new HashTable(16);

	CRect rect;
	hexTableOut.GetClientRect(&rect);
	int interval = (rect.Width() - 50) / 3;

	hexTableOut.InsertColumn(0, _T("№"), LVCFMT_LEFT, 50);
	hexTableOut.InsertColumn(1, _T("Значение хеш-функции"), LVCFMT_LEFT, interval);
	hexTableOut.InsertColumn(2, _T("Значение ключа"), LVCFMT_LEFT, interval);
	hexTableOut.InsertColumn(3, _T("Кол-во коллизий"), LVCFMT_LEFT, interval);

	updateTable();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void Cproject_Look_IncDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Cproject_Look_IncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cproject_Look_IncDlg::OnBnClickedEnter()						// Кнопка добавить
{
	UpdateData(TRUE);												// Считываем данные с элемента TextEdit

	if (!table->searchItem(keyValue).isEmpty())						// Проверяем, есть ли элемент в списке
	{
		AfxMessageBox(L"Данный элемент уже есть в списке", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	if (table->isCrowded())
	{
		AfxMessageBox(L"Таблица переполнена. Вы не можете ввести больше 16 строк.", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	if (!table->insertItem(keyValue))								// Если что-то нехорошее случится, мы получим окошко
	{
		AfxMessageBox(L"Ошибка добавления элемента", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	keyValue = 0;
	UpdateData(FALSE);
	updateTable();													// Обновляем элемент ListCtrl, который выводит нашу таблицу на эран
}


void Cproject_Look_IncDlg::OnBnClickedSearch()						// Кнопка найти
{
	UpdateData(TRUE);

	HashTableRow row = table->searchItem(keyValue);					// Находим элемент
	if (row.isEmpty())
	{
		AfxMessageBox(L"Элемент не найден.", MB_OK | MB_ICONERROR, NULL);
		return;
	}

	CString msg;													// Создаем строку сообщения
	msg.Format(_T("№: %i Хеш-Ключ: %i Ключ: %i Коллизий: %i"), row.row + 1, row.hashKey, row.key, row.collision);

	keyValue = 0;
	UpdateData(FALSE);

	AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION, NULL);			// Выводим данные

}

void Cproject_Look_IncDlg::updateTable()							// Обновление таблицы
{

	hexTableOut.DeleteAllItems();									// Очищаем наш список

	for (int i = 0; i < table->getSize(); i++)						//Добавляем элементы
	{
		HashTableRow row = table->getItem(i);						// Вот она наша функция построчного получения строк таблицы
		if (row.isEmpty())
			continue;

		addTableItem(row.row, row.hashKey, row.key, row.collision);	// Функция добавления строки в список

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

void Cproject_Look_IncDlg::OnOK()	// Чтобы при нажатии Enter наша программа не закрывалась, мы переопределили эту функцию 
{
	OnBnClickedEnter();
}

void Cproject_Look_IncDlg::OnBnClickedSave()	// Кнопка Save
{
	table->saveTable();
	AfxMessageBox(L"Таблица сохранена.", MB_OK | MB_ICONINFORMATION, NULL);
}


void Cproject_Look_IncDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void Cproject_Look_IncDlg::OnBnClickedAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
