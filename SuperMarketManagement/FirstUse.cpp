/*
 | 超市管理系统
 | 文件名称: FirstUse.cpp
 | 文件作用: 第一次使用引导界面
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


// FirstUse.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "FirstUse.h"
#include "utils.h"

// FirstUse 对话框

IMPLEMENT_DYNAMIC(FirstUse, CDialogEx)

FirstUse::FirstUse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIRSTUSE, pParent)
{

}

FirstUse::~FirstUse()
{
}

void FirstUse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FirstUse, CDialogEx)
	ON_BN_CLICKED(IDOK, &FirstUse::OnBnClickedOk)
END_MESSAGE_MAP()


// FirstUse 消息处理程序


void FirstUse::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	auto username = utils::GetDialogEditorString(this, IDC_EDIT_USERNAME);
	auto password = utils::GetDialogEditorString(this, IDC_EDIT_PASSWORD);

	// 对输入进行错误判断
	if (tstring(username).length() == 0)
	{
		MessageBox(_T("用户名不能为空"), _T("错误"), MB_OK);
		return;
	}
	if (tstring(password).length() == 0)
	{
		MessageBox(_T("密码不能为空"), _T("错误"), MB_OK);
		return;
	}

	// 创建用户表
	sqlite.executeSQLNoRet(_T(R"sql(CREATE TABLE "User" (
		"id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
		"username"	TEXT NOT NULL,
		"password"	TEXT NOT NULL,
		"permission"	TEXT NOT NULL,
		"last_login_time"	TEXT NOT NULL);)sql"));

	// 向表中插入第一个管理员用户
	sqlite.executeSQLNoRet(std::format(L"INSERT INTO User(username, password, permission, last_login_time) VALUES('{}','{}','Admin','{}')",
										username, password, utils::getTime()).c_str());
	if (!sqlite.existTable("User"))
	{
		// 错误
		assert(0);
	}
	// 设置当前用户
	currentUser.append(username);
	mode = ADMIN_MODE;

	CDialogEx::OnOK();
}
