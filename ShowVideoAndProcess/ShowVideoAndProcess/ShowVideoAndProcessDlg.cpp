
// ShowVideoAndProcessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShowVideoAndProcess.h"
#include "ShowVideoAndProcessDlg.h"
#include "afxdialogex.h"
#include <atomic>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


std::atomic_bool g_thread_run = false;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CShowVideoAndProcessDlg 对话框



CShowVideoAndProcessDlg::CShowVideoAndProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHOWVIDEOANDPROCESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowVideoAndProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VideoIn, m_video1ctrl);
	DDX_Control(pDX, IDC_VideoOut, m_video2ctrl);
	DDX_Control(pDX, IDC_ImgIn, m_img1ctrl);
	DDX_Control(pDX, IDC_ImgOut, m_img2ctrl);
}

BEGIN_MESSAGE_MAP(CShowVideoAndProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GetCamera, &CShowVideoAndProcessDlg::OnBnClickedGetCamera)
	ON_BN_CLICKED(IDC_GetVideo, &CShowVideoAndProcessDlg::OnBnClickedGetvideo)
	ON_BN_CLICKED(IDC_OpenFile, &CShowVideoAndProcessDlg::OnBnClickedOpenfile)
	ON_BN_CLICKED(IDC_StartProcess, &CShowVideoAndProcessDlg::OnBnClickedStartprocess)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ReadImg, &CShowVideoAndProcessDlg::OnBnClickedReadimg)
END_MESSAGE_MAP()


// CShowVideoAndProcessDlg 消息处理程序

BOOL CShowVideoAndProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//int videoNumber = 0;

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	count = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShowVideoAndProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShowVideoAndProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShowVideoAndProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShowVideoAndProcessDlg::OnBnClickedGetCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("没有连接摄像头"));
}

void thread_func(const std::string file, CWnd* hwnd)
{
	// 打开视频
	cv::VideoCapture capture;
	capture.open(file);
	// 绘图
	//cv::namedWindow("video1", 1);
	cv::waitKey(3000);
	while (g_thread_run)
	{
		cv::Mat frameOut;
		capture >> frameOut;
		//capture >> frameOut;
		if (frameOut.empty()) {
			break;
		}
		ShowMatImageOut(frameOut, hwnd);
	}
	ReleaseCapture();
}

void CShowVideoAndProcessDlg::OnBnClickedGetvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取edit控件内的文本并打开进行播放

	static WORD unicode = 0xFEFF;
	CString str;
	GetDlgItem(IDC_FileName)->GetWindowText(str);
	std::string fileLocation;
	fileLocation = CT2A(str.GetString());
	g_thread_run = true;
	m_th_showimg[0] = std::thread{ thread_func,fileLocation,&m_video1ctrl };
	if (str == "D:\\dataTrain\\videoin\\originalVideo6_1y.mp4")//D:\FFOutput\videoin
	{
		videoNumber = 1;
	}
	else if (str == "D:\\dataTrain\\videoin\\originalVideo6_2y.mp4")
	{
		videoNumber = 2;
	}
	else
	{
		videoNumber = 3;
	}

	//接着播放处理好的视频
	//cv::waitKey(30000);
	Sleep(2000);

	std::string strReady;
	if (videoNumber == 1)
	{
		//写一个函数，传入固定地址，再调用播放函数
		strReady = "D:\\FFOutput\\videoOu\\predictVideo6_1.mp4";
	}
	else if (videoNumber == 2)
	{
		strReady = "D:\\FFOutput\\videoOu\\predictVideo6_2.mp4";
	}
	else
	{
		strReady = "D:\\FFOutput\\videoOu\\predictVideo6_3.mp4";
	}
	g_thread_run = true;
	m_th_showimg[1] = std::thread{ thread_func,strReady, &m_video2ctrl };
}

void CShowVideoAndProcessDlg::OnBnClickedOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	count += 1;
	//当第二次开始打开文件，首先关闭上次播放打开的线程
	if (count > 1)
	{
		g_thread_run = false;
		for (int i = 0; i < 2; ++i) {
			if (m_th_showimg[i].joinable())
				m_th_showimg[i].join();
		}
	}
	CFileDialog open_img(TRUE,
		NULL,
		NULL,
		OFN_OVERWRITEPROMPT,
		_T("视频文件(*.mp4; *.avi; *.mkv)|*.mp4; *.avi; *.mkv|flv文件(*.flv)|*.flv||"),//指定要打开的文件类型
		NULL);
	if (open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_FileName, img_select);//img_select为选择的文件的路径，IDC_FileName为edit控件名称
	}
}

void ShowMatImageOut(cv::Mat& src, CWnd* hwnd)
{
	try {
		if (src.empty()) {
			return;
		}
		BITMAPINFO*  pBmpInfo1 = NULL;
		if (src.channels() == 1) {
			pBmpInfo1 = (BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];//bmp图像头文件
			pBmpInfo1->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			pBmpInfo1->bmiHeader.biWidth = src.cols;
			pBmpInfo1->bmiHeader.biHeight = -src.rows;
			pBmpInfo1->bmiHeader.biPlanes = 1;
			pBmpInfo1->bmiHeader.biBitCount = 8;
			pBmpInfo1->bmiHeader.biCompression = BI_RGB;
			pBmpInfo1->bmiHeader.biSizeImage = 0;
			pBmpInfo1->bmiHeader.biXPelsPerMeter = 0;
			pBmpInfo1->bmiHeader.biYPelsPerMeter = 0;
			pBmpInfo1->bmiHeader.biClrUsed = 0;
			pBmpInfo1->bmiHeader.biClrImportant = 0;
			for (int i = 0; i < 256; i++)
			{
				pBmpInfo1->bmiColors[i].rgbBlue = pBmpInfo1->bmiColors[i].rgbGreen = pBmpInfo1->bmiColors[i].rgbRed = (BYTE)i;
				pBmpInfo1->bmiColors[i].rgbReserved = 0;
			}
		}
		if (src.channels() == 3)
		{
			pBmpInfo1 = (BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER)];//bmp图像头文件
			pBmpInfo1->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			pBmpInfo1->bmiHeader.biWidth = src.cols;
			pBmpInfo1->bmiHeader.biHeight = -src.rows;
			pBmpInfo1->bmiHeader.biPlanes = 1;
			pBmpInfo1->bmiHeader.biBitCount = 24;
			pBmpInfo1->bmiHeader.biCompression = BI_RGB;
			pBmpInfo1->bmiHeader.biSizeImage = 0;
			pBmpInfo1->bmiHeader.biXPelsPerMeter = 0;
			pBmpInfo1->bmiHeader.biYPelsPerMeter = 0;
			pBmpInfo1->bmiHeader.biClrUsed = 0;
			pBmpInfo1->bmiHeader.biClrImportant = 0;
		}
		Sleep(24);
		const HDC& hdc = hwnd->GetDC()->GetSafeHdc();
		CRect BoxSize;
		hwnd->GetClientRect(&BoxSize);
		SetStretchBltMode(
			hdc,           // handle to device context
			HALFTONE);

		int jj = StretchDIBits(hdc, BoxSize.left, BoxSize.top, BoxSize.Width(), BoxSize.Height(), 0, 0, src.cols, src.rows, (void *)src.data,
			(BITMAPINFO*)pBmpInfo1, DIB_RGB_COLORS, SRCCOPY);
		delete[]pBmpInfo1;

		return;
	}
	catch (...)
	{
		return;
	}
}

void CShowVideoAndProcessDlg::OnBnClickedStartprocess()
{
	// TODO: 在此添加控件通知处理程序代码
	static WORD unicode = 0xFEFF;
	CString str;
	GetDlgItem(IDC_ImgName)->GetWindowText(str);
	std::string fileLocation;
	fileLocation = CT2A(str.GetString());

	cv::Mat imgMatIn;
	imgMatIn = cv::imread(fileLocation, 1);

	DrawImg(imgMatIn, &m_img1ctrl, true);

	//对路径的字符串fileLocation进行处理，切换至另一路径显示对应图片
	char fileNameIn[80];
	strcpy(fileNameIn, fileLocation.c_str());

	cv::Mat imgMatOut;
	imgMatOut = ImageBlur(imgMatIn);
	//imgMatOut = cv::imread(fileLocationOut, 1);
	Sleep(500);
	DrawImg(imgMatOut, &m_img2ctrl, true);

}

void CShowVideoAndProcessDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}

void CShowVideoAndProcessDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

void CShowVideoAndProcessDlg::OnDestroy()
{
	g_thread_run = false;
	for (int i = 0; i < 2; ++i) {
		if (m_th_showimg[i].joinable())
			m_th_showimg[i].join();
	}
	CDialogEx::OnDestroy();
}

void CShowVideoAndProcessDlg::OnBnClickedReadimg()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog open_img(TRUE,
		NULL,
		NULL,
		OFN_OVERWRITEPROMPT,
		_T("图片文件(*.jpg; *.bmp; *.png)|*.jpg; *.bmp; *.png|jpeg文件(*.jpeg)|*.jpeg||"),//指定要打开的文件类型
		NULL);
	if (open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_ImgName, img_select);//img_select为选择的文件的路径，IDC_FileName为edit控件名称
	}
}

void DrawImg(cv::Mat &img, CWnd* hwnd, bool bRoomToCtrlSize)
{
	//根据cv::Mat绘制图像
	cv::Mat imgTmp;
	CRect rect;
	hwnd->GetClientRect(&rect);
	ShowMatImageOut(img, hwnd);
}

cv::Mat ImageBlur(cv::Mat& src)
{
	cv::Mat outMat;
	cv::medianBlur(src, outMat, 5);
	return outMat;
}