
// TMClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "Uploader.h"


// CTMClientDlg 对话框
class CTMClientDlg : public CDialogEx
{
// 构造
public:
	CTMClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TMCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int fileNum = 0;
	int upNum;//记录已上传文件数
	std::string  filepath;
	std::vector<std::string> filename;
	CListCtrl clientList;
	Uploader uploadFile;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OpenFile();
	afx_msg void HelpInformation();
	afx_msg void OnBnClickedUpload();
};
