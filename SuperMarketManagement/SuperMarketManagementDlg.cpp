/*
 | 超市管理系统
 | 文件名称: SuperMarketManagementDlg.cpp
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


// SuperMarketManagementDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SuperMarketManagement.h"
#include "SuperMarketManagementDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "FirstUse.h"
#include "Login.h"
#include "Buy.h"
#include "Sold.h"
#include "PeopleManege.h"
#include "BuyManage.h"
#include "SoldManage.h"

Mode_t mode;

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


// CSuperMarketManagementDlg 对话框



CSuperMarketManagementDlg::CSuperMarketManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUPERMARKETMANAGEMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuperMarketManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSuperMarketManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CSuperMarketManagementDlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_BUY, &CSuperMarketManagementDlg::OnBnClickedButtonBuy)
	ON_BN_CLICKED(IDC_BUTTON_SOLD, &CSuperMarketManagementDlg::OnBnClickedButtonSold)
	ON_BN_CLICKED(IDC_BUTTON_STAFF, &CSuperMarketManagementDlg::OnBnClickedButtonStaff)
	ON_BN_CLICKED(IDC_BUTTON_BUYLIST, &CSuperMarketManagementDlg::OnBnClickedButtonBuylist)
	ON_BN_CLICKED(IDC_BUTTON_SOLDLIST, &CSuperMarketManagementDlg::OnBnClickedButtonSoldlist)
END_MESSAGE_MAP()


// CSuperMarketManagementDlg 消息处理程序

BOOL CSuperMarketManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	// 执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	sqlite.openDatabase(LR"(./data.db)");

	// 若存在表User，表示已经拥有管理员账户
	if (sqlite.existTable("User"))
	{
		LOGIN_Status_t res;
		Login loginDlg;

		// 登录界面
		res = (LOGIN_Status_t)loginDlg.DoModal();
		switch (res)
		{
		case LOGIN_USERNAME_WRONG:// 用户名不存在
			MessageBox(_T("用户名不存在"), _T("登录失败"), MB_OK);
			mode = ERROR_MODE;
			CDialogEx::OnCancel();
			break;
			
		case LOGIN_SUCCESS_ADMIN:// 管理员权限登录
			mode = ADMIN_MODE;
			break;

		case LOGIN_SUCCESS_NORMAL:
			mode = NORMAL_MODE;
			break;
			
		case LOGIN_PASSWORD_WRONG:// 密码错误
			MessageBox(_T("密码错误"), _T("登录失败"), MB_OK);
			mode = ERROR_MODE;
			CDialogEx::OnCancel();
			break;
			
		default:// 取消操作
			mode = GUEST_MODE;
			break;
		}
	}
	// 否则为第一次使用，提示用户设置一个管理员账号
	else
	{
		FirstUse firstuseDlg;
		firstuseDlg.DoModal();
		mode = ADMIN_MODE;
	}

	CButton* pButtonBuy = (CButton*)this->GetDlgItem(IDC_BUTTON_BUY);
	CButton* pButtonSold = (CButton*)this->GetDlgItem(IDC_BUTTON_SOLD);
	CButton* pButtonStaff = (CButton*)this->GetDlgItem(IDC_BUTTON_STAFF);
	CButton* pButtonBuyList = (CButton*)this->GetDlgItem(IDC_BUTTON_BUYLIST);
	CButton* pButtonSoldList = (CButton*)this->GetDlgItem(IDC_BUTTON_SOLDLIST);
	CButton* pButtonExit = (CButton*)this->GetDlgItem(IDCANCEL);
	CListCtrl* pGoodListView = (CListCtrl*)this->GetDlgItem(IDC_LIST_GOODS);

	// 根据权限设置按键状态
	switch (mode)
	{
	case ADMIN_MODE:
		// 管理员权限：所有按键可用
		pButtonBuy->EnableWindow(true);
		pButtonSold->EnableWindow(true);
		pButtonStaff->EnableWindow(true);
		pButtonBuyList->EnableWindow(true);
		pButtonSoldList->EnableWindow(true);
		break;
	case NORMAL_MODE:
		// 普通权限：只有售出、退出可用
		pButtonBuy->EnableWindow(false);
		pButtonSold->EnableWindow(true);
		pButtonStaff->EnableWindow(false);
		pButtonBuyList->EnableWindow(false);
		pButtonSoldList->EnableWindow(false);
		pButtonBuy->ShowWindow(SW_HIDE);
		pButtonSold->ShowWindow(SW_SHOW);
		pButtonStaff->ShowWindow(SW_HIDE);
		pButtonBuyList->ShowWindow(SW_HIDE);
		pButtonSoldList->ShowWindow(SW_HIDE);
		break;
		// 访客模式：所有按键都不可用，只能查看当前库存状态
		// 错误模式：同上
		break;
	default:
		pButtonBuy->EnableWindow(false);
		pButtonSold->EnableWindow(false);
		pButtonStaff->EnableWindow(false);
		pButtonBuyList->EnableWindow(false);
		pButtonSoldList->EnableWindow(false);
		pButtonBuy->ShowWindow(SW_HIDE);
		pButtonSold->ShowWindow(SW_HIDE);
		pButtonStaff->ShowWindow(SW_HIDE);
		pButtonBuyList->ShowWindow(SW_HIDE);
		pButtonSoldList->ShowWindow(SW_HIDE);
		break;
	}
	checkDatabase();
	// 刷新UI
	refreshLayout(this);

	initGoodList(this);

	refreshGoodList(this);
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSuperMarketManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSuperMarketManagementDlg::OnPaint()
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
HCURSOR CSuperMarketManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSuperMarketManagementDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CSuperMarketManagementDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	// 刷新UI
	refreshLayout(this);
}

void refreshLayout(CDialogEx* dlg)
{
	CButton* pButtonBuy = (CButton*)dlg->GetDlgItem(IDC_BUTTON_BUY);
	CButton* pButtonSold = (CButton*)dlg->GetDlgItem(IDC_BUTTON_SOLD);
	CButton* pButtonStaff = (CButton*)dlg->GetDlgItem(IDC_BUTTON_STAFF);
	CButton* pButtonBuyList = (CButton*)dlg->GetDlgItem(IDC_BUTTON_BUYLIST);
	CButton* pButtonSoldList = (CButton*)dlg->GetDlgItem(IDC_BUTTON_SOLDLIST);
	CButton* pButtonExit = (CButton*)dlg->GetDlgItem(IDCANCEL);
	CListCtrl* pGoodListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_GOODS);

	CRect  rect;

	// 调整列表框大小以适应窗口大小
	if (pGoodListView)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rect
		rect.top += 100;
		rect.left += 250;
		rect.bottom -= 50;
		rect.right -= 50;
		pGoodListView->MoveWindow(&rect, true);
	}

	if (pButtonBuy)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonBuy->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 0, 0, 0, SWP_NOSIZE);
	}

	if (pButtonSold)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonSold->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 1, 0, 0, SWP_NOSIZE);
	}

	if (pButtonStaff)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonStaff->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 2, 0, 0, SWP_NOSIZE);
	}

	if (pButtonBuyList)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonBuyList->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 3, 0, 0, SWP_NOSIZE);
	}

	if (pButtonSoldList)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonSoldList->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 4, 0, 0, SWP_NOSIZE);
	}

	if (pButtonExit)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonExit->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 5, 0, 0, SWP_NOSIZE);
	}
}

void refreshGoodList(CDialogEx* dlg)
{
	CListCtrl* pGoodListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_GOODS);
	// 先清空所有项
	pGoodListView->DeleteAllItems();
	int count = 0;
	sqlite.executeSQLWithRet(std::format(L"SELECT name, price, quantity FROM Good").c_str(), 
		[&](std::vector<tstring>& lst) -> void
		{
			pGoodListView->InsertItem(count, (LPCTSTR)lst[0].c_str());
			pGoodListView->SetItemText(count, 1, (LPCTSTR)lst[1].c_str());
			pGoodListView->SetItemText(count, 2, (LPCTSTR)lst[2].c_str());
			count++;
		});

}

void initGoodList(CDialogEx* dlg)
{
	CListCtrl* pGoodListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_GOODS);

	//设置控件属性。
	pGoodListView->SetExtendedStyle(pGoodListView->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pGoodListView->InsertColumn(0, _T("商品名"), LVCFMT_LEFT, 200, 0);
	pGoodListView->InsertColumn(1, _T("单价"), LVCFMT_RIGHT, 200, 1);
	pGoodListView->InsertColumn(2, _T("数量"), LVCFMT_RIGHT, 200, 2);
}

void checkDatabase(void)
{
	// 若OrderTable表不存在，则创建
	if (!sqlite.existTable("OrderTable"))
	{
		sqlite.executeSQLNoRet(
			LR"sql(CREATE TABLE "OrderTable" (
				"id"		INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
				"datime"	TEXT NOT NULL,
				"name"		TEXT NOT NULL,
				"vendor"	TEXT NOT NULL,
				"price"		TEXT NOT NULL,
				"quantity"	INTEGER NOT NULL,
				"operator"	TEXT NOT NULL); )sql"
		);
	}

	// 若Good表不存在，则创建
	if (!sqlite.existTable("Good"))
	{
		sqlite.executeSQLNoRet(
			LR"sql(CREATE TABLE "Good" (
				"id"		INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
				"name"		TEXT NOT NULL,
				"price"		INTEGER NOT NULL,
				"quantity"	INTEGER NOT NULL);)sql");
	}

	// 若Sales表不存在，则创建
	if (!sqlite.existTable("Sales"))
	{
		sqlite.executeSQLNoRet(
			LR"sql(CREATE TABLE "Sales" (
				"id"		INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
				"datime"	TEXT NOT NULL,
				"name"		TEXT NOT NULL,
				"quantity"	INTEGER NOT NULL,
				"operator"	TEXT NOT NULL);)sql");
	}
}

// 进货按键回调函数
void CSuperMarketManagementDlg::OnBnClickedButtonBuy()
{
	// TODO: 在此添加控件通知处理程序代码
	int res;
	Buy buyDlg;
	res = buyDlg.DoModal();
	// 确认添加了项时候刷新
	if (res == IDOK)
	{
		refreshGoodList(this);
	}
}

// 售货按键回调函数
void CSuperMarketManagementDlg::OnBnClickedButtonSold()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pList = (CListCtrl*)this->GetDlgItem(IDC_LIST_GOODS);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一项"), _T("提示"), MB_OK);
		return;
	}
	// 获得当前选择的项的位置
	int currentItem = pList->GetNextSelectedItem(pos); 
	// 获取所选商品名
	tstring name(pList->GetItemText(currentItem, 0));
	
	// 跳转售出窗口
	int res;
	Sold soldDlg;
	// 传递当前所选商品名
	soldDlg.SetProperty(name);
	res = soldDlg.DoModal();
	
	if (res == IDOK)
	{
		refreshGoodList(this);
	}
}


void CSuperMarketManagementDlg::OnBnClickedButtonStaff()
{
	// TODO: 在此添加控件通知处理程序代码
	PeopleManege peopleDlg;
	peopleDlg.DoModal();

}


void CSuperMarketManagementDlg::OnBnClickedButtonBuylist()
{
	// TODO: 在此添加控件通知处理程序代码
	BuyManage buymanageDlg;
	buymanageDlg.DoModal();
}


void CSuperMarketManagementDlg::OnBnClickedButtonSoldlist()
{
	// TODO: 在此添加控件通知处理程序代码
	SoldManage soldmanageDlg;
	soldmanageDlg.DoModal();
}
