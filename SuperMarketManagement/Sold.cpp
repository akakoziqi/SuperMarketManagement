/*
 | 超市管理系统
 | 文件名称: Sold.cpp
 | 文件作用: 卖出提示框
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

// Sold.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "Sold.h"
#include "utils.h"


// Sold 对话框

IMPLEMENT_DYNAMIC(Sold, CDialogEx)

Sold::Sold(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOLD, pParent)
{

}

Sold::~Sold()
{
}

void Sold::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void Sold::SetProperty(const tstring& _name)
{
	name = _name;
}


BEGIN_MESSAGE_MAP(Sold, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Sold::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &Sold::OnBnClickedOk)
END_MESSAGE_MAP()


// Sold 消息处理程序

BOOL Sold::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 初始化
	CEdit* pName = (CEdit*)this->GetDlgItem(IDC_EDIT_SOLD_NAME);
	pName->SetWindowText(std::format(L"{}", this->name).c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void Sold::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

// 确认售出
void Sold::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	tstring quantity = utils::GetDialogEditorString(this, IDC_EDIT_SOLD_QUANTITY);
	tstring nocori;
	// 将输入字符转为数字

	int num = std::atoi(utils::wstring2string(quantity).c_str());
	sqlite.executeSQLWithRet(
		std::format(L"SELECT quantity FROM Good WHERE name == '{}'", this->name).c_str(),
		[&](std::vector<tstring>& lst) -> void {
			nocori = lst[0];
		}
	);
	// 剩余储量
	int reserved = std::atoi(utils::wstring2string(nocori).c_str());
	if (num <= 0)
	{
		MessageBox(_T("请输入正确的数量"), _T("错误"), MB_OK);
		return;
	}
	if (reserved - num < 0)
	{
		MessageBox(_T("剩余库存不足"), _T("错误"), MB_OK);
		return;
	}
	// 如果OK,进行数据库操作
	sqlite.executeSQLNoRet(std::format(
		L"UPDATE Good SET quantity = {} WHERE name = '{}'", 
		reserved - num, 
		name).c_str());

	// 向售出表中添加条目
	sqlite.executeSQLNoRet(std::format(
		L"INSERT INTO Sales(datime, name, quantity, operator)"
		"VALUES('{}', '{}', {}, '{}')", 
		utils::getTime(), 
		name,
		num,
		currentUser).c_str());

	CDialogEx::OnOK();
}
