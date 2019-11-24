
// ShowVideoAndProcessDlg.h : 头文件
//

#pragma once
#include<opencv2/opencv.hpp>
#include<string>
#include<thread>
#include "afxwin.h"


// CShowVideoAndProcessDlg 对话框
class CShowVideoAndProcessDlg : public CDialogEx
{

// 构造
public:
	CShowVideoAndProcessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWVIDEOANDPROCESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	std::thread m_th_showimg[2];

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetCamera();
	afx_msg void OnBnClickedGetvideo();
	afx_msg void OnBnClickedOpenfile();

	int videoNumber;
	//VideoCapture cap[2];
	afx_msg void OnBnClickedStartprocess();
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedReadimg();
	CStatic m_video1ctrl;
	CStatic m_video2ctrl;
	CStatic m_img1ctrl;
	CStatic m_img2ctrl;

	int count;//对按下打开文件按钮进行计数，当第二次打开文件开始(count>1)，每次要先关闭线程，避免新播放的视频冲突。
};

//线程函数
void thread_func(const std::string file, CWnd* hwnd);
void ShowMatImageIn(cv::Mat& src, CWnd* hwnd);
void ShowMatImageOut(cv::Mat& src, CWnd* hwnd);
void DrawImg(cv::Mat &img, CWnd* hwnd, bool bRoomToCtrlSize);