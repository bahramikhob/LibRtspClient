
// RtspTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RtspTest.h"
#include "RtspTestDlg.h"

#include "libRtspAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRtspTestDlg �Ի���




CRtspTestDlg::CRtspTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRtspTestDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRtspTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_url);
}

BEGIN_MESSAGE_MAP(CRtspTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CRtspTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRtspTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRtspTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRtspTestDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CRtspTestDlg ��Ϣ�������

BOOL CRtspTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_url.SetWindowText("rtsp://192.168.0.213:8557/PSIA/Streaming/channels/2?videoCodecType=H.264");


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRtspTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRtspTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRtspTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CALLBACK CRtspTestDlg::AVDataCallBack(int iAVSelect, char* pAVData, int iDataLen, int iWidth, int iHeight, int SessionID, void* pUserData)
{
	return 0;
	static FILE* pFile = NULL;
	if (pFile == NULL)
	{
		pFile = fopen("record.H264", "wb");
	}

	if (pFile != NULL)
	{
		if (iAVSelect == 0)
		{
			fwrite(pAVData, iDataLen, 1, pFile);
		}
	}

// 	char data[64] = {0};
// 	sprintf(data, "Select = %d DataLen = %d w = %d h = %d\n", iAVSelect, iDataLen, iWidth, iHeight);
// 	OutputDebugStringA(data);
	return 0;
}

void CRtspTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//_CrtSetBreakAlloc(706);
	//_CrtSetBreakAlloc(707);
	//_CrtSetBreakAlloc(1039);
	//_CrtSetBreakAlloc(1040);
	CString url;
	m_url.GetWindowText(url);
	
	//RTSP_StartStream("rtsp://192.168.0.214:8557/PSIA/Streaming/channels/2?videoCodecType=H.264", AVDataCallBack, (void *)this);
	RTSP_StartStream(url, AVDataCallBack, (void *)this);
}

void CRtspTestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RTSP_StopStream();
}

void CRtspTestDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i = 0; i < 50; i++)
	{
		RTSP_StartStream("rtsp://192.168.0.214:8557/PSIA/Streaming/channels/2?videoCodecType=H.264", AVDataCallBack, (void *)this);
		Sleep(3000);
		RTSP_StopStream();
		Sleep(1000);
	}
	
}

void CRtspTestDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	srand((unsigned int)time(NULL));
	char* newtest = NULL;
	for (int i = 0; i < 100000; i++)
	{
		char temp[64];
		int size = rand()%(1024*1024*30) + 30*1024*1024;

		sprintf(temp, "%d %d\n", i, size);
		OutputDebugStringA(temp);

		newtest = new char[size];
		memset(newtest, 7, size);
		//Sleep(100);
		delete[] newtest;
		newtest = NULL;
	}



}
