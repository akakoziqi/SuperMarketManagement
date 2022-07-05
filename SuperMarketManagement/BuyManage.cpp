/*
 | 超市管理系统
 | 文件名称: BuyManage.cpp
 | 文件作用: 进货管理界面
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

// BuyManage.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "BuyManage.h"


// BuyManage 对话框

IMPLEMENT_DYNAMIC(BuyManage, CDialogEx)

BuyManage::BuyManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BUYMANAGE, pParent)
{

}

BuyManage::~BuyManage()
{
}

void BuyManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BuyManage, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_BUYMANAGE_DELETE, &BuyManage::OnBnClickedButtonBuymanageDelete)
END_MESSAGE_MAP()


// BuyManage 消息处理程序

void refreshBuyManageLayout(CDialogEx* dlg)
{
	CButton* pButtonDelete = (CButton*)dlg->GetDlgItem(IDC_BUTTON_BUYMANAGE_DELETE);
	CButton* pButtonExit = (CButton*)dlg->GetDlgItem(IDCANCEL);
	CListCtrl* pGoodListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_BUYMANAGE);

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

	if (pButtonDelete)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonDelete->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 0, 0, 0, SWP_NOSIZE);
	}

	if (pButtonExit)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonExit->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 1, 0, 0, SWP_NOSIZE);
	}
}

void refreshBuyManageList(CDialogEx* dlg)
{
	CListCtrl* pListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_BUYMANAGE);
	// 先清空所有项
	pListView->DeleteAllItems();
	int count = 0;
	sqlite.executeSQLWithRet(std::format(L"SELECT * FROM OrderTable").c_str(),
		[&](std::vector<tstring>& lst) -> void
		{
			pListView->InsertItem(count, (LPCTSTR)lst[0].c_str());
			pListView->SetItemText(count, 1, (LPCTSTR)lst[1].c_str());
			pListView->SetItemText(count, 2, (LPCTSTR)lst[2].c_str());
			pListView->SetItemText(count, 3, (LPCTSTR)lst[3].c_str());
			pListView->SetItemText(count, 4, (LPCTSTR)lst[4].c_str());
			pListView->SetItemText(count, 5, (LPCTSTR)lst[5].c_str());
			pListView->SetItemText(count, 6, (LPCTSTR)lst[6].c_str());
			count++;
		});

}

void initBuyManageList(CDialogEx* dlg)
{
	CListCtrl* pGoodListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_BUYMANAGE);

	//设置控件属性。
	pGoodListView->SetExtendedStyle(pGoodListView->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pGoodListView->InsertColumn(0, _T("ID"), LVCFMT_LEFT, 200, 0);
	pGoodListView->InsertColumn(1, _T("日期 时间"), LVCFMT_LEFT, 200, 0);
	pGoodListView->InsertColumn(2, _T("商品名"), LVCFMT_RIGHT, 200, 1);
	pGoodListView->InsertColumn(3, _T("供应商"), LVCFMT_RIGHT, 200, 2);
	pGoodListView->InsertColumn(4, _T("单价"), LVCFMT_RIGHT, 200, 3);
	pGoodListView->InsertColumn(5, _T("数量"), LVCFMT_RIGHT, 200, 4);
	pGoodListView->InsertColumn(6, _T("采购员"), LVCFMT_RIGHT, 200, 5);
}


BOOL BuyManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	refreshBuyManageLayout(this);
	initBuyManageList(this);
	refreshBuyManageList(this);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void BuyManage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	refreshBuyManageLayout(this);
}


void BuyManage::OnBnClickedButtonBuymanageDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pList = (CListCtrl*)this->GetDlgItem(IDC_LIST_BUYMANAGE);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一条记录"), _T("提示"), MB_OK);
		return;
	}
	// 获得当前选择的项的位置
	int currentItem = pList->GetNextSelectedItem(pos);
	// 获取所选ID
	tstring itemname(pList->GetItemText(currentItem, 0));

	sqlite.executeSQLNoRet(
		std::format(L"DELETE FROM OrderTable WHERE id == '{}'",
			itemname
		).c_str()
	);
	refreshBuyManageList(this);
}
