
// RtspTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CRtspTestDlg �Ի���
class CRtspTestDlg : public CDialog
{
// ����
public:
	CRtspTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RTSPTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	static int CALLBACK AVDataCallBack(int iAVSelect, char* pAVData, int iDataLen, int iWidth, int iHeight, int SessionID, void* pUserData);
	CEdit m_url;
	afx_msg void OnBnClickedButton4();
};
