/*
 | 超市管理系统
 | 文件名称: PeopleAdd.cpp
 | 文件作用: 人员添加提示框
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


// PeopleAdd.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "PeopleAdd.h"
#include "utils.h"

// PeopleAdd 对话框

IMPLEMENT_DYNAMIC(PeopleAdd, CDialogEx)

PeopleAdd::PeopleAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PEOLPEADD, pParent)
{

}

PeopleAdd::~PeopleAdd()
{
}

void PeopleAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PeopleAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &PeopleAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// PeopleAdd 消息处理程序


void PeopleAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	tstring userid = utils::GetDialogEditorString(this, IDC_EDIT_PEOPLEADD_USERID);
	tstring passwd = utils::GetDialogEditorString(this, IDC_EDIT_PEOPLEADD_PASSWORD);
	CButton* pRadio = (CButton*)this->GetDlgItem(IDC_RADIO_PERMISSION);
	tstring permission;
	
	if (pRadio->GetCheck())
	{
		permission = L"Admin";
	}
	else
	{
		permission = L"Normal";
	}

	sqlite.executeSQLNoRet(
		std::format(L"INSERT INTO User(username, password, permission, last_login_time) "
			"VALUES('{}', '{}', '{}', '{}')",
			userid,
			passwd,
			permission,
			utils::getTime()
		).c_str()
	);

	CDialogEx::OnOK();
}
