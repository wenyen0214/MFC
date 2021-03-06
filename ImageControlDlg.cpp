
// ImageControlDlg.cpp: 實作檔案
//

#include "stdafx.h"
#include "ImageControl.h"
#include "ImageControlDlg.h"
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




CImageControlDlg::CImageControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGECONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImageControlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CImageControlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageControlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CImageControlDlg::OnBnClickedButton3)
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

	// TODO: add control notification handler code here

	BITMAPINFO *pBmpInfo;       //記錄影象細節
	BYTE *pBmpData;             //影象資料
	BITMAPFILEHEADER bmpHeader; //檔案頭
	BITMAPINFOHEADER bmpInfo;   //資訊頭
	CFile bmpFile;              //記錄開啟檔案

	bmpFile.Open(_T("C:\\Users\\user\\Downloads\\Image\\sample_98×426.bmp"), CFile::modeRead | CFile::typeBinary);
	bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER));
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER));
	//為影象資料申請空間
	memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData, dataBytes);
	bmpFile.Close();

	CWnd *pWnd = GetDlgItem(ID_Image); //獲得pictrue控制元件視窗的控制代碼
	CRect rect;
	pWnd->GetClientRect(&rect); //獲得pictrue控制元件所在的矩形區域
	CDC *pDC = pWnd->GetDC(); //獲得pictrue控制元件的DC
	pDC->SetStretchBltMode(COLORONCOLOR);

	int nWidth = bmpInfo.biWidth;
	int nHeight = bmpInfo.biHeight;
	float fRatio;

	if (nWidth>nHeight)
		//如果原图宽度大于高度,且比显示区域的宽度大
	{
		float zoom = (float)nHeight / (float)nWidth;
		nWidth = rect.Width();
		nHeight = (int)(zoom * nWidth);
		fRatio = zoom;
	}
	else if (nHeight >= nWidth)
		//如果原图高度大于宽度,且比显示区域的高度大
	{
		float zoom = (float)nWidth / nHeight;
		nHeight = rect.Height();
		nWidth = (int)(zoom * nHeight);
		fRatio = zoom;
	}	

	StretchDIBits(pDC->GetSafeHdc(), 0, 0, nWidth, nHeight, 0, 0,
		bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);

	TRACE("fRatio: %f\nrect.Width(): %d ::%d \n rect.Height(): %d :: %d\n", fRatio, rect.Width(), nWidth, rect.Height() , nHeight);
	delete pBmpInfo;
	delete pBmpData;
	
}


void CImageControlDlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CDialogEx::OnOK();
}


void CImageControlDlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	CWnd *pWnd = GetDlgItem(ID_Image); //獲得pictrue控制元件視窗的控制代碼
	CRect rect;
	pWnd->GetClientRect(&rect); //獲得pictrue控制元件所在的矩形區域
	CDC *pDC = pWnd->GetDC(); //獲得pictrue控制元件的DC
	CDC *pMemDC = new CDC;
	pMemDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, 512, 512);
	pMemDC->SelectObject(&bmp);
	pMemDC->FillSolidRect(0, 0, 512, 512, RGB(255, 255, 255));
	CStdioFile RawFile;
	unsigned char RawBuf[512][512][3];
	CString FilePath;
	FilePath.Format(_T("C:\\Users\\user\\Downloads\\Image\\peppers.raw"));
	if (!RawFile.Open(FilePath, CFile::modeRead | CFile::typeBinary))
		AfxMessageBox(_T("檔案開啟失敗"));

	for (int pY = 0; pY<200; ++pY)
		for (int pX = 0; pX<200; ++pX)
			for (int k = 0; k<3; ++k)
				RawBuf[pY][pX][k] = 0;

	if (!RawFile.Read(RawBuf, 512 * 512 * 3))
		AfxMessageBox(_T("讀檔失敗"));
	RawFile.Close();

	unsigned char **pData;
	pData = new unsigned char *[200];
	//此矩陣有 n 個列(rows); 先 new 出 n 個 int *
	for (int i = 0; i < 200; i++)
	{
		pData[i] = new unsigned char[200 * 3];
		//每一列有 m 行(columns); array[i] 指向新 new 出的 m 個 int
	}

	int nPixel = 0;

	for (int pY = 0; pY < 200; ++pY)
	{
		nPixel = 0;

		for (int pX = 0; pX<200  ; pX = pX+1)
		{
			for (int k = 0; k <  3; k = k + 1)
			{
				(pData)[pY][pX*3+k] = RawBuf[pY][pX][k];
			}
			
		}
	}
		
				
	
	TRACE("AAAAAAAAAAAAAAA\n");
	// 動態矩陣用完後還給系統, 好習慣! 怎麼 new 來的就怎麼還 !
	
	CImage img;
	img.Create(512, 512, 24 /* bpp */, 0 /* No alpha channel */);

	/*
	int nPixel = 0;
	for (int row = 0; row < 512; row++)
	{
		for (int col = 0; col < 512; col++)
		{
			BYTE r = BYTE(RawBuf[nPixel++]);
			BYTE g = BYTE(RawBuf[nPixel++]);
			BYTE b = BYTE(RawBuf[nPixel++]);
			img.SetPixel(row, col, RGB(r, g, b));
		}
	}
	*/

	for (int pY = 0; pY < 512; ++pY)
		for (int pX = 0; pX < 512; ++pX)
		{
			pMemDC->SetPixel(pX, pY, RGB(RawBuf[pY][pX][0],
				RawBuf[pY][pX][1], RawBuf[pY][pX][2]));
			//img.SetPixel(pX, pY, RGB(RawBuf[pY][pX][0],RawBuf[pY][pX][1], RawBuf[pY][pX][2]));
		}

	TRACE("BBBBBBBBBBBBBBBBBBB\n");

	for (int pY = 0; pY<200; ++pY)
		for (int pX = 0; pX<200; ++pX)
		{
			img.SetPixel(pX, pY, RGB(BYTE(pData[pY][pX*3]), BYTE((pData)[pY][pX*3+1]), BYTE((pData)[pY][pX*3+2]) ));
			pMemDC->SetPixel(pX, pY, RGB(pData[pY][pX*3], (pData)[pY][pX*3 + 1], (pData)[pY][pX*3 + 2]));
		}
				
	img.Save(_T(".\\test.bmp"), Gdiplus::ImageFormatBMP);

	int nWidth = 512;
	int nHeight = 512;
	float fRatio;

	if (nWidth>nHeight)
		//如果原图宽度大于高度,且比显示区域的宽度大
	{
		float zoom = (float)nHeight / (float)nWidth;
		nWidth = rect.Width();
		nHeight = (int)(zoom * nWidth);
		fRatio = zoom;
	}
	else if (nHeight >= nWidth)
		//如果原图高度大于宽度,且比显示区域的高度大
	{
		float zoom = (float)nWidth / nHeight;
		nHeight = rect.Height();
		nWidth = (int)(zoom * nHeight);
		fRatio = zoom;
	}

	pDC->StretchBlt(0, 0, nWidth, nHeight, pMemDC, 0, 0,
		512, 512, SRCCOPY);

	TRACE("fRatio: %f\nrect.Width(): %d ::%d \n rect.Height(): %d :: %d\n", fRatio, rect.Width(), nWidth, rect.Height(), nHeight);

	for (int i = 0; i < 200; i++)
	{
		delete[] pData[i];
	}

	delete[] pData;
	ReleaseDC(pMemDC);
	delete pMemDC;
	ReleaseDC(pDC);

}


void CImageControlDlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CWnd *pWnd = GetDlgItem(ID_Image); //獲得pictrue控制元件視窗的控制代碼
	CRect rect;
	pWnd->GetClientRect(&rect); //獲得pictrue控制元件所在的矩形區域
	CDC *pDC = pWnd->GetDC(); //獲得pictrue控制元件的DC
	CDC *pMemDC = new CDC ;
	pMemDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, 512,512);
	pMemDC->SelectObject(&bmp);
	pMemDC->FillSolidRect(0, 0, 512, 512, RGB(255, 255, 255));
	CStdioFile RawFile;
	unsigned char RawBuf[512][512][3];
	CString FilePath;
	FilePath.Format(_T("C:\\Users\\user\\Downloads\\Image\\peppers.raw"));
	if (!RawFile.Open(FilePath, CFile::modeRead | CFile::typeBinary))
		AfxMessageBox(_T("檔案開啟失敗"));

	for (int pY = 0; pY<512; ++pY)
		for (int pX = 0; pX<512; ++pX)
			for (int k = 0; k<3; ++k)
				RawBuf[pY][pX][k] = 0;


	if (!RawFile.Read(RawBuf, 512 * 512 * 3))
		AfxMessageBox(_T("讀檔失敗"));
	RawFile.Close();

	


	for (int pY = 0; pY < 512; ++pY)
		for (int pX = 0; pX < 512; ++pX)
		{
			pMemDC->SetPixel(pX, pY, RGB(RawBuf[pY][pX][0],
							RawBuf[pY][pX][1], RawBuf[pY][pX][2]));
			
		}

	int nWidth = 512;
	int nHeight = 512;
	float fRatio;

	if (nWidth>nHeight)
		//如果原图宽度大于高度,且比显示区域的宽度大
	{
		float zoom = (float)nHeight / (float)nWidth;
		nWidth = rect.Width();
		nHeight = (int)(zoom * nWidth);
		fRatio = zoom;
	}
	else if (nHeight >= nWidth)
		//如果原图高度大于宽度,且比显示区域的高度大
	{
		float zoom = (float)nWidth / nHeight;
		nHeight = rect.Height();
		nWidth = (int)(zoom * nHeight);
		fRatio = zoom;
	}

	pDC->StretchBlt(0, 0, nWidth, nHeight, pMemDC, 0, 0,
		512, 512,  SRCCOPY);
	ReleaseDC(pMemDC);
	delete pMemDC;
	TRACE("fRatio: %f\nrect.Width(): %d ::%d \n rect.Height(): %d :: %d\n", fRatio, rect.Width(), nWidth, rect.Height(), nHeight);
	


	// Create the header info
	BITMAPINFO *pBmpInfo;       //記錄影象細節
	BYTE *pBmpData;             //影象資料
	BITMAPFILEHEADER bmpHeader; //檔案頭
	BITMAPINFOHEADER bmInfohdr;   //資訊頭
	CFile bmpFile;              //記錄開啟檔案

	int width = 512, height = 512, Bpp = 3;

	bmInfohdr.biSize = sizeof(BITMAPINFOHEADER);
	bmInfohdr.biWidth = width;
	bmInfohdr.biHeight = height;
	bmInfohdr.biPlanes = 1;
	bmInfohdr.biBitCount = Bpp * 8;
	bmInfohdr.biCompression = BI_RGB;
	bmInfohdr.biSizeImage = width * height*Bpp;
	bmInfohdr.biXPelsPerMeter = 0;
	bmInfohdr.biYPelsPerMeter = 0;
	bmInfohdr.biClrUsed = 0;
	bmInfohdr.biClrImportant = 0;

	BITMAPINFO bmInfo;
	bmInfo.bmiHeader = bmInfohdr;
	bmInfo.bmiColors[0].rgbBlue = 255;

	unsigned char *data = new unsigned char(width * height*Bpp);



	
	ReleaseDC(pDC);
	delete data;

}

