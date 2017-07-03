
// TMClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TMClient.h"
#include "TMClientDlg.h"
#include "afxdialogex.h"
#include <stdio.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTMClientDlg 对话框



CTMClientDlg::CTMClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TMCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTMClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, clientList);
}

BEGIN_MESSAGE_MAP(CTMClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTMClientDlg::OnLvnItemchangedList1)
	ON_COMMAND(ID_32772, &CTMClientDlg::OpenFile)
	ON_COMMAND(ID_32771, &CTMClientDlg::HelpInformation)
	ON_BN_CLICKED(IDC_BUTTON1, &CTMClientDlg::OnBnClickedUpload)
END_MESSAGE_MAP()


// CTMClientDlg 消息处理程序

BOOL CTMClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	uploadFile.initialize();
	CRect rect;
	clientList.GetClientRect(&rect);
	clientList.SetExtendedStyle(clientList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	clientList.InsertColumn(0, _T("文件名"), LVCFMT_CENTER, rect.Width() / 2, 0);
	clientList.InsertColumn(1, _T("状态"), LVCFMT_CENTER, rect.Width() / 2, 1);

	//CRgn rgntmp;
	//RECT rc;
	//GetClientRect(&rc);
	//rgntmp.CreateRoundRectRgn(rc.left + 3, rc.top + 3, rc.right - rc.left, rc.bottom - rc.top - 3, 6, 6);
	//SetWindowRgn(rgntmp, TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTMClientDlg::OnDestroy()
{
	uploadFile.terminate();
}

void CTMClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTMClientDlg::OnPaint()
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
HCURSOR CTMClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTMClientDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLISTVIEW *pnml = (NMLISTVIEW*)pNMHDR;
	CString str;
	if (-1 != pnml->iItem)
		str = clientList.GetItemText(pnml->iItem, 0);//获取地址
	CImage image;
	image.Load(str);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面
	CRect rectControl;                        //控件矩形对象
	CRect rectPicture;                        //图片矩形对象

	int x = image.GetWidth();
	int y = image.GetHeight();
	//Picture Control的ID为IDC_IMAGE
	CWnd  *pWnd = GetDlgItem(IDC_STATIC);
	pWnd->GetClientRect(rectControl);


	CDC *pDc = GetDlgItem(IDC_STATIC)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_STATIC))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);                //将图片绘制到Picture控件表示的矩形区域

	image.Destroy();
	pWnd->ReleaseDC(pDc);

	*pResult = 0;
}


void CTMClientDlg::OpenFile()  // 菜单栏  打开文件  预览 选择
{
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, _T("Picture files(*.bmp;*.jpg;*.jpeg;*.png;*.gif)|*.bmp;*.jpg;*.jpeg;*.png;*.gif|"), NULL);
	//文件过滤器
	USES_CONVERSION;//unicode  环境下CString 转换为std：：string
	if (filedlg.DoModal() == IDOK)//批量选择
	{
		POSITION pos;
		CString path;
		pos = filedlg.GetStartPosition();
		while (pos != NULL)
		{
			
		     path =filedlg.GetNextPathName(pos);//获取多个文件路径	
			clientList.InsertItem(fileNum, path);   //插入文件路径到list control
			clientList.SetItemText(fileNum, 1, _T("待上传"));
			filename.push_back(W2A(path.Mid(path.ReverseFind('\\') + 1)));
			++fileNum;
		}
		filepath =W2A(path.Mid(0,path.ReverseFind('\\')));	
	}

}


void CTMClientDlg::HelpInformation()//点击帮助 --版本信息   显示版本信息
{
	CDialog *dlg = new CDialog;
	dlg->Create(IDD_ABOUTBOX, this);//版本信息
	dlg->ShowWindow(SW_SHOW);
	// TODO: 在此添加命令处理程序代码
}


void CTMClientDlg::OnBnClickedUpload()
{
	char ip[16];
	int port;
	wchar_t buf[256];
	_wgetcwd(buf, 128);
	FILE *config = fopen("config.txt", "r");
	fscanf(config, "ip=%s\n", ip);
	fscanf(config, "port=%d", &port);
	int ret = uploadFile.connect_server(ip, port);
	if (ret == 0)
	{
		// 连接成功，可以上传

		for (int i = 0; i < filename.size(); ++i)
		{
			if (uploadFile.upload(filepath, filename.at(i)) == 0)
			{
				clientList.SetItemText(i, 1, _T("上传成功"));
			}
		}
	} 
	else
	{
		// 连接失败，提示
		MessageBox(_T("服务器连接失败，无法上传"));
		return;
	}
	
	// TODO: 在此添加控件通知处理程序代码
}
