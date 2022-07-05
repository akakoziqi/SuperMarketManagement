/*
 | 超市管理系统
 | 文件名称: utils.cpp
 | 文件作用: 小工具
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

#include "pch.h"
#include "utils.h"

/// <summary>
/// 从编辑框中获取输入字符串
/// </summary>
/// <param name="pthis">Dialog的this指针</param>
/// <param name="ctl_id">编辑框控件ID</param>
/// <returns>tstring类型输入字符串</returns>
extern tstring utils::GetDialogEditorString(const CDialogEx* pthis, int ctl_id)
{
	auto* edit = reinterpret_cast<CEdit*>(pthis->GetDlgItem(ctl_id));
	auto length = edit->GetWindowTextLengthW() + 1;
	// 
	tstring res;
	res.reserve(length);
	res.resize(length - 1, 0x00);
	edit->GetWindowTextW(res.data(), length);
	return res;
}

/// <summary>
/// 获取当前时间字符串
/// </summary>
/// <param name=""></param>
/// <returns></returns>
extern std::wstring utils::getTime(void)
{
#pragma warning( disable : 4996 )
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//转为字符串
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
	std::string ss_str = ss.str();
	std::wstring wtime(ss_str.begin(), ss_str.end());
	return wtime;
}

/// <summary>
/// wstring类型转换为string类型
/// </summary>
/// <param name="ws">wstring类型</param>
/// <returns>string类型</returns>
extern std::string utils::wstring2string(const std::wstring& ws)
{
	_bstr_t t = ws.c_str();
	char* pchar = (char*)t;
	std::string result = pchar;
	return result;
}

/// <summary>
/// 设置窗口为全屏
/// </summary>
/// <param name="pthis">Dialog this指针</param>
extern void utils::FullScreen(CDialogEx* pthis)
{
	int with = GetSystemMetrics(SM_CXFULLSCREEN);
	int heigh = GetSystemMetrics(SM_CYFULLSCREEN);
	pthis->SetWindowPos(NULL, 0, 0, with, heigh, NULL);
}