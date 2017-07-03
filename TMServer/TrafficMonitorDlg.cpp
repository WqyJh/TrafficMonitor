
// TrafficMonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TrafficMonitorDlg.h"
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


// CTrafficMonitorDlg 对话框



CTrafficMonitorDlg::CTrafficMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAFFICMONITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrafficMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, serveList);
	DDX_Control(pDX, IDC_EDIT2, Edit_carNum);
	DDX_Control(pDX, IDC_EDIT3, Edit_time);
	DDX_Control(pDX, IDC_EDIT4, Edit_path);
	DDX_Control(pDX, IDC_EDIT1, edit_find);
}

BEGIN_MESSAGE_MAP(CTrafficMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTrafficMonitorDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTrafficMonitorDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON4, &CTrafficMonitorDlg::OnBnClickedUpdate)
	ON_BN_CLICKED(IDC_BUTTON1, &CTrafficMonitorDlg::OnBnClickedFind)
	ON_BN_CLICKED(IDC_BUTTON5, &CTrafficMonitorDlg::OnBnClickedShowAll)
	ON_STN_CLICKED(IDC_PICTURE, &CTrafficMonitorDlg::OnStnClickedPicture)
END_MESSAGE_MAP()


// CTrafficMonitorDlg 消息处理程序

BOOL CTrafficMonitorDlg::OnInitDialog()
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
	plateDao.set_gszFile("database.db");
	plateDao.init();

	server = new Server("127.0.0.1", 50084);
	int init_success = server->init();
	if (init_success == 0)
	{
		// 服务器初始化成功，开始服务
		server->serve();
	}
	else
	{
		// 服务器初始化失败
		MessageBox(_T("服务器初始化失败！"));
		return FALSE;
	}

	CRect rect;
	serveList.GetClientRect(&rect);
	serveList.SetExtendedStyle(serveList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	serveList.InsertColumn(0, _T("车牌号"), LVCFMT_CENTER, rect.Width() / 4, 0);
	serveList.InsertColumn(1, _T("上传日期"), LVCFMT_CENTER, rect.Width() / 4, 1);
	serveList.InsertColumn(2, _T("图片地址"), LVCFMT_CENTER, rect.Width() / 2, 2);
	//显示出查询到的内容
	showData(plates);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

CTrafficMonitorDlg::~CTrafficMonitorDlg()
{
	plateDao.release();
}

void CTrafficMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTrafficMonitorDlg::OnPaint()
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
HCURSOR CTrafficMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTrafficMonitorDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLISTVIEW *pnml = (NMLISTVIEW*)pNMHDR;
	CString str;
	if (-1 != pnml->iItem)
	{
		NowID = pnml->iItem;
		str = serveList.GetItemText(pnml->iItem, 2);//获取地址
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
		CWnd  *pWnd = GetDlgItem(IDC_PICTURE);
		pWnd->GetClientRect(rectControl);


		CDC *pDc = GetDlgItem(IDC_PICTURE)->GetDC();
		SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

		rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

		((CStatic*)GetDlgItem(IDC_PICTURE))->SetBitmap(NULL);

		//以下两种方法都可绘制图片
		//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域
		image.Draw(pDc->m_hDC, rectPicture);                //将图片绘制到Picture控件表示的矩形区域

		image.Destroy();
		pWnd->ReleaseDC(pDc);


		
		this->SetDlgItemTextW(IDC_EDIT2, serveList.GetItemText(pnml->iItem, 0));
		this->SetDlgItemTextW(IDC_EDIT3, serveList.GetItemText(pnml->iItem, 1));
		this->SetDlgItemTextW(IDC_EDIT4, serveList.GetItemText(pnml->iItem, 2));
		//根据选定行的内容给plate赋值
		plate = *plates[NowID];
	}
	*pResult = 0;
}


void CTrafficMonitorDlg::OnBnClickedDelete()
{
	if (NowID == -1)
	{
		MessageBox(_T("请选择要删除的记录"));
		return;
	}
	//数据库里删除
	if (plateDao.remove(plate) != 0)
	{
		MessageBox(_T("删除失败"));
		return;
	}
	//表里删除
	serveList.DeleteItem(NowID);
	//删除容器里的数据
	for (std::vector<Plate*>::iterator iter = plates.begin(); iter != plates.end();)
	{
		if (**iter == plate)
			iter = plates.erase(iter);
		else
			iter++;
	}
	this->SetDlgItemTextW(IDC_EDIT2, NULL);
	this->SetDlgItemTextW(IDC_EDIT3, NULL);
	this->SetDlgItemTextW(IDC_EDIT4, NULL);
	NowID = -1;


	// TODO: 在此添加控件通知处理程序代码
}

void CTrafficMonitorDlg::OnBnClickedUpdate()//更新某条信息
{
	USES_CONVERSION;//Unicode下字符转换说明，下同
	if (NowID == -1)
	{
		MessageBox(_T("请选择要修改的记录"));
		return;
	}
	CString carNum, time, path;//保存输入的车牌信息
	Edit_carNum.GetWindowText(carNum);
	Edit_time.GetWindowText(time);
	Edit_path.GetWindowText(path);
	plate.set_number(W2A(carNum));
	/*plate.set_time(_ttol(time));
	plate.set_path(W2A(path));*/
	if (carNum.GetLength() == 0 || time.GetLength() == 0 || path.GetLength() == 0)
	{
		MessageBox(_T("修改有误"));
		return;
	}
	if (plateDao.update(plate) != 0)//更新数据库内容
	{
		MessageBox(_T("修改失败"));
		return;
	}
	////将修改后的车牌信息显示到列表中
	*plates[NowID] = plate;
	serveList.SetItemText(NowID, 0, carNum);
	serveList.SetItemText(NowID, 1, time);
	serveList.SetItemText(NowID, 2, path);
	NowID = -1;
	// TODO: 在此添加控件通知处理程序代码
}


void CTrafficMonitorDlg::OnBnClickedFind()
{
	USES_CONVERSION;
	CString info;
	edit_find.GetWindowText(info);//获取要查询的信息
	plates.swap(plateDao.findByNumber(W2A(info)));
	if (plates.size() == 0)//如果没有返回值，查询输入的是否为日期
	{
		plates = plateDao.findByTime(W2A(info));//根据日期查询
		if (plates.size() == 0)//如果没查到，提示Not Found
		{
			MessageBox(_T("Not Found"));
			return;
		}
	}
	serveList.DeleteAllItems();//查到了，先清空所有列表项
	showData(plates);
	//CString ptime;
	//int i = 0;
	//for (auto iplate = plates.cbegin(); iplate != plates.cend(); ++iplate, ++i)//依次显示出查询到的内容
	//{
	//	ptime.Format(_T("%ld"), (*iplate)->get_time());
	//	serveList.InsertItem(i, (CString)(*iplate)->get_number().c_str());
	//	serveList.SetItemText(i, 1, ptime);
	//	serveList.SetItemText(i, 2, (CString)(*iplate)->get_path().c_str());
	//}
	// TODO: 在此添加控件通知处理程序代码
}


void CTrafficMonitorDlg::OnBnClickedShowAll()
{
	serveList.DeleteAllItems();
	for (int i = 0; i < plates.size(); i++)
	{
		delete plates[i];
		plates[i] = NULL;
	}
	plates.clear();
	plates.swap(plateDao.findAll());
	showData(plates);
	/*for (int i = 0; i < plates.size(); ++i)
	{
		ptime.Format(_T("%ld"), plates[i]->get_time());
		serveList.InsertItem(i, (CString)plates[i]->get_number().c_str());
		serveList.SetItemText(i, 1, ptime);
		serveList.SetItemText(i, 2, (CString)plates[i]->get_path().c_str());
	}*/

	// TODO: 在此添加控件通知处理程序代码
}


void CTrafficMonitorDlg::showData(std::vector<Plate*> &plates)
{
	CString ptime;
	int i = 0;
	time_t time;
	struct tm* lt = NULL;
	for (auto iplate = plates.cbegin(); iplate != plates.cend(); ++iplate, ++i)//依次显示出查询到的内容
	{
		time = (*iplate)->get_time();
		lt = localtime(&time);
		ptime.Format(_T("%d年%d月%d日 %d时%d分"), lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
			lt->tm_hour , lt->tm_min + 1);
		serveList.InsertItem(i, (CString)(*iplate)->get_number().c_str());
		serveList.SetItemText(i, 1, ptime);
		serveList.SetItemText(i, 2, (CString)(*iplate)->get_path().c_str());
	}
}

void CTrafficMonitorDlg::OnStnClickedPicture()
{
	
}
