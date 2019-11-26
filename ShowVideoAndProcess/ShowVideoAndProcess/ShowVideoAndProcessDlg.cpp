
// ShowVideoAndProcessDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CShowVideoAndProcessDlg �Ի���



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


// CShowVideoAndProcessDlg ��Ϣ�������

BOOL CShowVideoAndProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//int videoNumber = 0;

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	count = 0;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CShowVideoAndProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CShowVideoAndProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShowVideoAndProcessDlg::OnBnClickedGetCamera()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("û����������ͷ"));
}

void thread_func(const std::string file, CWnd* hwnd)
{
	// ����Ƶ
	cv::VideoCapture capture;
	capture.open(file);
	// ��ͼ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡedit�ؼ��ڵ��ı����򿪽��в���

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

	//���Ų��Ŵ���õ���Ƶ
	//cv::waitKey(30000);
	Sleep(2000);

	std::string strReady;
	if (videoNumber == 1)
	{
		//дһ������������̶���ַ���ٵ��ò��ź���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	count += 1;
	//���ڶ��ο�ʼ���ļ������ȹر��ϴβ��Ŵ򿪵��߳�
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
		_T("��Ƶ�ļ�(*.mp4; *.avi; *.mkv)|*.mp4; *.avi; *.mkv|flv�ļ�(*.flv)|*.flv||"),//ָ��Ҫ�򿪵��ļ�����
		NULL);
	if (open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_FileName, img_select);//img_selectΪѡ����ļ���·����IDC_FileNameΪedit�ؼ�����
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
			pBmpInfo1 = (BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];//bmpͼ��ͷ�ļ�
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
			pBmpInfo1 = (BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER)];//bmpͼ��ͷ�ļ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static WORD unicode = 0xFEFF;
	CString str;
	GetDlgItem(IDC_ImgName)->GetWindowText(str);
	std::string fileLocation;
	fileLocation = CT2A(str.GetString());

	cv::Mat imgMatIn;
	imgMatIn = cv::imread(fileLocation, 1);

	DrawImg(imgMatIn, &m_img1ctrl, true);

	//��·�����ַ���fileLocation���д����л�����һ·����ʾ��ӦͼƬ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnClose();
}

void CShowVideoAndProcessDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog open_img(TRUE,
		NULL,
		NULL,
		OFN_OVERWRITEPROMPT,
		_T("ͼƬ�ļ�(*.jpg; *.bmp; *.png)|*.jpg; *.bmp; *.png|jpeg�ļ�(*.jpeg)|*.jpeg||"),//ָ��Ҫ�򿪵��ļ�����
		NULL);
	if (open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_ImgName, img_select);//img_selectΪѡ����ļ���·����IDC_FileNameΪedit�ؼ�����
	}
}

void DrawImg(cv::Mat &img, CWnd* hwnd, bool bRoomToCtrlSize)
{
	//����cv::Mat����ͼ��
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