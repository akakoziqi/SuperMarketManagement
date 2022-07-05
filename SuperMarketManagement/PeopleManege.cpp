/*
 | 超市管理系统
 | 文件名称: PeopleManage.cpp
 | 文件作用: 人员管理
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


// PeopleManege.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "PeopleManege.h"
#include "PeopleAdd.h"

// PeopleManege 对话框

IMPLEMENT_DYNAMIC(PeopleManege, CDialogEx)

PeopleManege::PeopleManege(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PEOPLEMANAGE, pParent)
{

}

PeopleManege::~PeopleManege()
{
}

void PeopleManege::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PeopleManege, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDCANCEL, &PeopleManege::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_PEOPLE_ADD, &PeopleManege::OnBnClickedButtonPeopleAdd)
	ON_BN_CLICKED(IDC_BUTTON_PEOPLE_DELETE, &PeopleManege::OnBnClickedButtonPeopleDelete)
END_MESSAGE_MAP()


// PeopleManege 消息处理程序

void initPeopleList(CDialogEx* dlg)
{
	CListCtrl* pListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_PEOPLE);

	//设置控件属性。
	pListView->SetExtendedStyle(pListView->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pListView->InsertColumn(0, _T("用户名"), LVCFMT_LEFT, 200, 0);
	pListView->InsertColumn(1, _T("权限"), LVCFMT_LEFT, 200, 1);
	pListView->InsertColumn(2, _T("最后登录日期"), LVCFMT_LEFT, 200, 2);
}

void refreshPelpleList(CDialogEx* dlg)
{
	CListCtrl* pListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_PEOPLE);
	// 先清空所有项
	pListView->DeleteAllItems();
	int count = 0;
	sqlite.executeSQLWithRet(std::format(L"SELECT username, permission, last_login_time FROM User").c_str(),
		[&](std::vector<tstring>& lst) -> void
		{
			pListView->InsertItem(count, (LPCTSTR)lst[0].c_str());
			pListView->SetItemText(count, 1, (LPCTSTR)lst[1].c_str());
			pListView->SetItemText(count, 2, (LPCTSTR)lst[2].c_str());
			count++;
		});

}

void refreshPeopleLayout(CDialogEx* dlg)
{
	CButton* pButtonAdd = (CButton*)dlg->GetDlgItem(IDC_BUTTON_PEOPLE_ADD);
	CButton* pButtonDelete = (CButton*)dlg->GetDlgItem(IDC_BUTTON_PEOPLE_DELETE);
	CButton* pButtonExit = (CButton*)dlg->GetDlgItem(IDCANCEL);
	CListCtrl* pListView = (CListCtrl*)dlg->GetDlgItem(IDC_LIST_PEOPLE);

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

	if (pButtonAdd)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonAdd->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 0, 0, 0, SWP_NOSIZE);
	}

	if (pButtonDelete)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonDelete->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 1, 0, 0, SWP_NOSIZE);
	}

	if (pButtonExit)
	{
		dlg->GetWindowRect(&rect);  //获取窗口rect，
		dlg->ScreenToClient(rect);  //从窗口尺寸转换到用户区rec
		pButtonExit->SetWindowPos(NULL, rect.left + 50, rect.top + 100 + 100 * 2, 0, 0, SWP_NOSIZE);
	}

}

void PeopleManege::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	refreshPeopleLayout(this);
}

BOOL PeopleManege::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	initPeopleList(this);
	refreshPeopleLayout(this);
	refreshPelpleList(this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

// 返回
void PeopleManege::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}




void PeopleManege::OnBnClickedButtonPeopleAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	PeopleAdd peopleaddDlg;
	peopleaddDlg.DoModal();
	refreshPelpleList(this);
}


void PeopleManege::OnBnClickedButtonPeopleDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pList = (CListCtrl*)this->GetDlgItem(IDC_LIST_PEOPLE);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一个用户"), _T("提示"), MB_OK);
		return;
	}
	// 获得当前选择的项的位置
	int currentItem = pList->GetNextSelectedItem(pos);
	// 获取所选商品名
	tstring username(pList->GetItemText(currentItem, 0));

	sqlite.executeSQLNoRet(
		std::format(L"DELETE FROM User WHERE username == '{}'",
			username
		).c_str()
	);
	refreshPelpleList(this);
}
