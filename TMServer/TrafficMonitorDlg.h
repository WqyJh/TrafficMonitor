
// TrafficMonitorDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "Plate.h"
#include "PlateDao.h"
#include "afxwin.h"


// CTrafficMonitorDlg 对话框
class CTrafficMonitorDlg : public CDialogEx
{
// 构造
public:
	CTrafficMonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAFFICMONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	Plate plate;//单个车牌号信息
	PlateDao plateDao;
	CListCtrl serveList;
	int NowID=-1;//选中行的标识符
	std::vector<Plate *> plates;//存放显示出来的所有车牌号信息
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedFind();
	afx_msg void OnBnClickedShowAll();
	CEdit Edit_carNum;//车牌号
	CEdit Edit_time;//上传时间
	CEdit Edit_path;//上传路径
	CEdit edit_find;
};
