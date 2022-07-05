/*
 | 超市管理系统
 | 文件名称: Buy.cpp
 | 文件作用: 进货提示框
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

// Buy.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "Buy.h"
#include "utils.h"

// Buy 对话框

IMPLEMENT_DYNAMIC(Buy, CDialogEx)

Buy::Buy(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BUY, pParent)
{

}

Buy::~Buy()
{
}

void Buy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Buy, CDialogEx)
	ON_BN_CLICKED(IDOK, &Buy::OnBnClickedOk)
END_MESSAGE_MAP()


// Buy 消息处理程序


tstring Buy::GetEditBoxString(int ctl_id) const
{
	return utils::GetDialogEditorString(this, ctl_id);
}

void Buy::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	tstring name = GetEditBoxString(IDC_EDIT_BUY_NAME);
	tstring vendor = GetEditBoxString(IDC_EDIT_BUY_VENDOR);
	tstring price = GetEditBoxString(IDC_EDIT_BUY_PRICE);
	tstring quantity = GetEditBoxString(IDC_EDIT_BUY_QUANTITY);

	// 如果存在此商品， 且价格相同
	if (sqlite.existItemInTableW(L"Good", 
		std::format(L"name == '{}' AND price == {}", 
			name, 
			price
		).c_str(), L"id"))
	{
		// 数量更新
		sqlite.executeSQLNoRet(
			std::format(
				L"UPDATE Good SET quantity = quantity + {} WHERE name = '{}' AND price == {}",
				quantity,
				name,
				price
			).c_str()
		);
	}
	// 如果不存在此商品，或者价格不相同
	else
	{
		// 添加条目
		sqlite.executeSQLNoRet(
			std::format(
				L"INSERT INTO Good(name, price, quantity) VALUES('{}', '{}', '{}')",
				name,
				price,
				quantity
			).c_str()
		);
	}

	// 向进货表中添加条目
	sqlite.executeSQLNoRet(
		std::format(
			L"INSERT INTO OrderTable(datime, name, vendor, price, quantity, operator) "
			"VALUES('{}', '{}', '{}', '{}', {}, '{}')",
			utils::getTime(),
			name,
			vendor,
			price,
			quantity,
			currentUser
		).c_str()
	);
	CDialogEx::OnOK();
}
