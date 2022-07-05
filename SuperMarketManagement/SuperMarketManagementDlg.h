/*
 | 超市管理系统
 | 文件名称: SuperMarketManagementDlg.h
 | 文件作用: 主窗口逻辑
 | 创建日期: 2022-07-02
 | 更新日期: 2022-07-05
 | 开发人员: Akako
 +----------------------------
 MIT License

 Copyright (C) Akako

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/



// SuperMarketManagementDlg.h: 头文件
//

#pragma once

// 当前程序运行模式
typedef enum Mode
{
	ADMIN_MODE,
	NORMAL_MODE,
	GUEST_MODE,
	ERROR_MODE
} Mode_t;

/// <summary>
/// 检查数据库是否创建
/// </summary>
/// <param name="">none</param>
void checkDatabase(void);

/// <summary>
/// 刷新UI布局
/// </summary>
/// <param name="dlg">Dialog this指针</param>
void refreshGoodLayout(CDialogEx* dlg);

/// <summary>
/// 初始化商品列表框
/// </summary>
/// <param name="dlg">Dialog this指针</param>
void initGoodList(CDialogEx* dlg);

/// <summary>
/// 刷新商品列表框
/// </summary>
/// <param name="dlg">Dialog this指针</param>
void refreshGoodList(CDialogEx* dlg);

// CSuperMarketManagementDlg 对话框
class CSuperMarketManagementDlg : public CDialogEx
{
// 构造
public:
	CSuperMarketManagementDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUPERMARKETMANAGEMENT_DIALOG };
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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonBuy();
	afx_msg void OnBnClickedButtonSold();
	afx_msg void OnBnClickedButtonStaff();
	afx_msg void OnBnClickedButtonBuylist();
	afx_msg void OnBnClickedButtonSoldlist();
};
