#pragma once
#include "afxdialogex.h"


// Statistic 对话框

class Statistic : public CDialogEx
{
	DECLARE_DYNAMIC(Statistic)

public:
	Statistic(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Statistic();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STATISTIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CComboBox Combo;
public:
	afx_msg void OnCbnSelchangeComboStatistic();
};
