/*
 | 超市管理系统
 | 文件名称: Login.cpp
 | 文件作用: 登录界面
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


// Login.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "Login.h"
#include "utils.h"

tstring currentUser;

IMPLEMENT_DYNAMIC(Login, CDialog)

Login::Login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Login, CDialog)
	ON_BN_CLICKED(IDC_LOGIN, &Login::OnBnClickedLogin)
	ON_BN_CLICKED(IDCANCEL, &Login::OnBnClickedCancel)
END_MESSAGE_MAP()

tstring Login::GetEditBoxString(int ctl_id) const
{
	return utils::GetDialogEditorString(this, ctl_id);
}

// Login 消息处理程序


void Login::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	tstring username = GetEditBoxString(IDC_LOGIN_USERNAME);
	tstring password = GetEditBoxString(IDC_LOGIN_PASSWORD);

	// 如果用户名不存在
	if (!sqlite.existItemInTableW(L"User", std::format(L"Username = '{}'", username).c_str(), L"Password"))
	{
		EndDialog(LOGIN_USERNAME_WRONG);
	}
	else
	{
		// 用户名存在
		sqlite.executeSQLWithRet(
			std::format(L"SELECT Password, Permission FROM User WHERE Username = '{}'", username).c_str(),
			[&](std::vector<tstring>& lst) -> void
			{
				assert(lst.size() == 2);
				if (password == lst[0])
				{
					// 第二项为权限
					if (tstring(L"Admin") == lst[1])
					{
						// 拥有管理员权限
						EndDialog(LOGIN_SUCCESS_ADMIN);
					}
					else
					{
						// 普通权限
						EndDialog(LOGIN_SUCCESS_NORMAL);
					}
					// 设置当前操作员（登录用户）
					currentUser.append(username);
					// 更新最后登录时间
					sqlite.executeSQLNoRet(
						std::format(
							L"UPDATE User SET last_login_time = '{}' "
							"WHERE username = '{}'",
							utils::getTime(),
							username).c_str()
					);
				}
				else
				{
					// 密码错误
					EndDialog(LOGIN_PASSWORD_WRONG);
				}
			});
	}
}


void Login::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(LOGIN_CANCEL);
}
