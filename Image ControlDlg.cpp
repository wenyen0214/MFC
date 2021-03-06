
// Image ControlDlg.cpp: 實作檔案
//

#include "stdafx.h"
#include "Image Control.h"
#include "Image ControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageControlDlg 對話方塊



CImageControlDlg::CImageControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGECONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl );
	//DDX_Control(pDX, IDC_STATIC, m_ImageCtrl);

}

BEGIN_MESSAGE_MAP(CImageControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImageControlDlg::OnBnClickedButton1)
	ON_COMMAND(IDC_STATIC, &CImageControlDlg::OnStatic)
	ON_UPDATE_COMMAND_UI(IDC_STATIC, &CImageControlDlg::OnUpdateStatic)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CImageControlDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CImageControlDlg 訊息處理常式

BOOL CImageControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CImageControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CImageControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CImageControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageControlDlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_ListCtrl.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 40);//插入列
	m_ListCtrl.InsertColumn(1, _T("NAME"), LVCFMT_LEFT, 200);
	CString Str;
	//int nRow = m_ListCtrl.InsertItem(0, _T("AAAAAA"));//插入行
	for (int i = 1; i < 10; i++)
	{
		int nRow = m_ListCtrl.InsertItem(i, _T("AAAAAA"));//插入行
		Str.Format(_T("%d"),i);
		m_ListCtrl.SetItemText(i-1,0,  Str);
		m_ListCtrl.SetItemText(nRow, 1, _T("BBB"));
		TRACE("%d\n", nRow);
	}

	

	/*
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC); // 得到 Picture Control 句柄
	pWnd->ModifyStyle(0, SS_BITMAP); // 修改它的屬性為位圖
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL, _T("C:\\Users\\user\\Downloads\\Image\\sample_640×426.bmp"),
		IMAGE_BITMAP,
		640,
		426,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	*/
	/*
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC); // 得到 Picture Control 句柄
	CImage image;
	image.Load(_T("C:\\Users\\user\\Downloads\\Image\\sample_640×426.bmp"));
	HBITMAP hBmp = image.Detach();
	pWnd->SetBitmap(hBmp);
	pWnd->SetWindowPos(NULL,
		0,
		0,
		100,
		50,
		SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

	*/
	
	CStatic *pwnd = (CStatic*)GetDlgItem(IDC_STATIC);
	pwnd->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	pwnd->SetBitmap((HBITMAP)::LoadImage(NULL,
		_T("sample_640×426.bmp"),// 添加资源号或本地文件名
		IMAGE_BITMAP,                                  // 装载位图IMAGE_CURSOR光标IMAGE_ICON图标
		0,                                             // 宽度0为默认大小
		0,                                             // 高度像素为单位
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
		

	/*
	CString strFileName;
	CBitmap ccBitmap;


	LPTSTR  lpstrPath = NULL;
	TCHAR   tszTempPath[_MAX_PATH];

	ZeroMemory(tszTempPath, MAX_PATH);

	GetCurrentDirectory(MAX_PATH, tszTempPath);

	lpstrPath = tszTempPath;



	CFileDialog filedlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Image (*.bmp)|*.bmp"));

	filedlg.m_ofn.lpstrInitialDir = lpstrPath; //Open the directory where the current folder is located

	if (filedlg.DoModal() == IDOK)
		strFileName = filedlg.GetFileName();
	else
		return;

	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, strFileName, IMAGE_BITMAP,
		0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//CBitmap m_bitmap; 
	ccBitmap.Attach(hBitmap);

	CStatic *pwnd = (CStatic*)GetDlgItem(IDC_STATIC);
	CDC dcImage;
	CDC *pDC = pwnd->GetDC();

	if (!dcImage.CreateCompatibleDC(pDC))
		return;

	BITMAP bm;
	ccBitmap.GetBitmap(&bm);
	// show the image.
	dcImage.SelectObject(&ccBitmap);
	pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	*/
//	bitmap.LoadBitmap(IDB_BITMAP);

//	m_ImageCtrl.SetBitmap(bitmap);

	// Now it would be supposed to fit the control:
//	CDC *pDC = m_ImageCtrl.GetDC();
//	CDC m_DC;

//	m_DC.CreateCompatibleDC(pDC);
//	m_DC.SelectObject(&bitmap);

//	pDC->StretchBlt(0, 0, rect->Width(), rect->Height(), &m_DC, 0, 0, 67, 37, SRCCOPY);


}


void CImageControlDlg::OnStatic()
{
	// TODO: 在此加入您的命令處理常式程式碼
}


void CImageControlDlg::OnUpdateStatic(CCmdUI *pCmdUI)
{
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}


void CImageControlDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}
