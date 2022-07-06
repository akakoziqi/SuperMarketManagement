/*
 | 超市管理系统
 | 文件名称: SoldManage.cpp
 | 文件作用: 售货管理
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

// SoldManage.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "SoldManage.h"
#include "utils.h"

// SoldManage 对话框

IMPLEMENT_DYNAMIC(SoldManage, CDialogEx)

SoldManage::SoldManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOLDMANAGE, pParent)
{

}

SoldManage::~SoldManage()
{
}

void SoldManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SoldManage, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SOLDMANAGE_DELETE, &SoldManage::OnBnClickedButtonSoldmanageDelete)
END_MESSAGE_MAP()


// SoldManage 消息处理程序


void initSoldList(CDialogEx* dlg)
{
	CListCtrl* pListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_SOLDMANAGE);

	//设置控件属性。
	pListView->SetExtendedStyle(pListView->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pListView->InsertColumn(0, _T("ID"), LVCFMT_LEFT, 200, 0);
	pListView->InsertColumn(1, _T("日期 时间"), LVCFMT_LEFT, 200, 1);
	pListView->InsertColumn(2, _T("商品名"), LVCFMT_LEFT, 200, 2);
	pListView->InsertColumn(3, _T("商品单价"), LVCFMT_LEFT, 200, 3);
	pListView->InsertColumn(4, _T("数量"), LVCFMT_LEFT, 200, 4);
	pListView->InsertColumn(5, _T("操作员"), LVCFMT_LEFT, 200, 5);
}

void refreshSoldList(CDialogEx* dlg)
{
	CListCtrl* pListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_SOLDMANAGE);
	// 先清空所有项
	pListView->DeleteAllItems();
	int count = 0;
	sqlite.executeSQLWithRet(std::format(L"SELECT * FROM Sales").c_str(),
		[&](std::vector<tstring>& lst) -> void
		{
			pListView->InsertItem(count, (LPCTSTR)lst[0].c_str());
			pListView->SetItemText(count, 1, (LPCTSTR)lst[1].c_str());
			pListView->SetItemText(count, 2, (LPCTSTR)lst[2].c_str());
			pListView->SetItemText(count, 3, (LPCTSTR)lst[3].c_str());
			pListView->SetItemText(count, 4, (LPCTSTR)lst[4].c_str());
			pListView->SetItemText(count, 5, (LPCTSTR)lst[5].c_str());
			count++;
		});

}

void refreshSoldLayout(CDialogEx* dlg)
{
	CButton* pButtonDelete = (CButton*)dlg->GetDlgItem(IDC_BUTTON_SOLDMANAGE_DELETE);
	CButton* pButtonExit = (CButton*)dlg->GetDlgItem(IDCANCEL);
	CListCtrl* pListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_SOLDMANAGE);

	CRect  rect;
	// 调整列表框大小以适应窗口大小
	if (pListView)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rect
		rect.top += 100;
		rect.left += 250;
		rect.bottom -= 50;
		rect.right -= 50;
		pListView->MoveWindow(&rect, true);
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


BOOL SoldManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 设置窗口初始化为全屏
	utils::FullScreen(this);

	refreshSoldLayout(this);
	initSoldList(this);
	refreshSoldList(this);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void SoldManage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	refreshSoldLayout(this);
}


void SoldManage::OnBnClickedButtonSoldmanageDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pList = (CListCtrl*)this->GetDlgItem(IDC_LIST_SOLDMANAGE);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一条记录"), _T("提示"), MB_OK);
		return;
	}
	// 获得当前选择的项的位置
	int currentItem = pList->GetNextSelectedItem(pos);
	// 获取所选商品ID
	tstring itemname(pList->GetItemText(currentItem, 0));

	sqlite.executeSQLNoRet(
		std::format(L"DELETE FROM Sales WHERE id == '{}'",
			itemname
		).c_str()
	);
	refreshSoldList(this);
}
