/*
 | 超市管理系统S
 | 文件名称: Statistic.cpp
 | 文件作用: 统计信息
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

// Statistic.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "Statistic.h"
#include "utils.h"

// Statistic 对话框

IMPLEMENT_DYNAMIC(Statistic, CDialogEx)

Statistic::Statistic(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STATISTIC, pParent)
{

}

Statistic::~Statistic()
{
}

void Statistic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STATISTIC, Combo);
}


BEGIN_MESSAGE_MAP(Statistic, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_STATISTIC, &Statistic::OnCbnSelchangeComboStatistic)
END_MESSAGE_MAP()


// Statistic 消息处理程序


BOOL Statistic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化列表
	Combo.AddString(_T("订单数"));
	Combo.AddString(_T("营业额"));
	//默认显示订单数
	Combo.SetCurSel(0);
	int num = 0;
	sqlite.executeSQLWithRet(L"SELECT quantity FROM Sales",
		[&](std::vector<tstring>& lst) -> void
		{
			num++;
		}
	);

	CEdit* pEdit = (CEdit*)this->GetDlgItem(IDC_EDIT_STATISTIC);
	pEdit->SetWindowTextW(std::format(L"{}", num).c_str());


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Statistic::OnCbnSelchangeComboStatistic()
{
	// TODO: 在此添加控件通知处理程序代码
	int num = 0;
	int index = Combo.GetCurSel();
	CEdit* pEdit = (CEdit*)this->GetDlgItem(IDC_EDIT_STATISTIC);

	switch (index)
	{
		// 订单数
	case 0:
		num = 0;
		sqlite.executeSQLWithRet(L"SELECT quantity FROM Sales",
			[&](std::vector<tstring>& lst) -> void
			{
				num++;
			}
		);
		pEdit->SetWindowTextW(std::format(L"{}", num).c_str());
		break;
		// 营业额
	case 1:
		num = 0;
		sqlite.executeSQLWithRet(L"SELECT price, quantity FROM Sales",
			[&](std::vector<tstring>& lst) -> void
			{
				num += std::atoi(utils::wstring2string(lst[0].c_str()).c_str()) * 
					   std::atoi(utils::wstring2string(lst[1].c_str()).c_str());
			}
		);
		pEdit->SetWindowTextW(std::format(L"{}", num).c_str());
		break;

	default:
		break;
	}
}
