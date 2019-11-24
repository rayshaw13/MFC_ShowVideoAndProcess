
// ShowVideoAndProcessDlg.h : ͷ�ļ�
//

#pragma once
#include<opencv2/opencv.hpp>
#include<string>
#include<thread>
#include "afxwin.h"


// CShowVideoAndProcessDlg �Ի���
class CShowVideoAndProcessDlg : public CDialogEx
{

// ����
public:
	CShowVideoAndProcessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWVIDEOANDPROCESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	std::thread m_th_showimg[2];

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	int count;//�԰��´��ļ���ť���м��������ڶ��δ��ļ���ʼ(count>1)��ÿ��Ҫ�ȹر��̣߳������²��ŵ���Ƶ��ͻ��
};

//�̺߳���
void thread_func(const std::string file, CWnd* hwnd);
void ShowMatImageIn(cv::Mat& src, CWnd* hwnd);
void ShowMatImageOut(cv::Mat& src, CWnd* hwnd);
void DrawImg(cv::Mat &img, CWnd* hwnd, bool bRoomToCtrlSize);