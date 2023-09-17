
// ShotIDCreatorDlg.h: 头文件
//

#pragma once

#include "CClientSocket.h"

// CShotIDCreatorDlg 对话框
class CShotIDCreatorDlg : public CDialogEx
{
// 构造
public:
	CShotIDCreatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOTIDCREATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
	bool ConfineData();
	void sendShotNum(int); //发送炮号

	CClientSocket* m_UDPSocket; //本地UDP服务
	SOCKET sockServer;
	BOOL UDPStatus; //UDP工作状态
	int MaxShotID; // 最大炮号

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
	afx_msg void OnBnClickedStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent); //定时器
	int ShotNumber;
	int m_interval;
	int mPort;
};
