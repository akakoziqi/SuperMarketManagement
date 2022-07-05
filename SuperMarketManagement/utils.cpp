/*
 | ���й���ϵͳ
 | �ļ�����: utils.cpp
 | �ļ�����: С����
 | ��������: 2022-07-02
 | ��������: 2022-07-05
 | ������Ա: Akako
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
/// �ӱ༭���л�ȡ�����ַ���
/// </summary>
/// <param name="pthis">Dialog��thisָ��</param>
/// <param name="ctl_id">�༭��ؼ�ID</param>
/// <returns>tstring���������ַ���</returns>
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
/// ��ȡ��ǰʱ���ַ���
/// </summary>
/// <param name=""></param>
/// <returns></returns>
extern std::wstring utils::getTime(void)
{
#pragma warning( disable : 4996 )
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//תΪ�ַ���
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
	std::string ss_str = ss.str();
	std::wstring wtime(ss_str.begin(), ss_str.end());
	return wtime;
}

/// <summary>
/// wstring����ת��Ϊstring����
/// </summary>
/// <param name="ws">wstring����</param>
/// <returns>string����</returns>
extern std::string utils::wstring2string(const std::wstring& ws)
{
	_bstr_t t = ws.c_str();
	char* pchar = (char*)t;
	std::string result = pchar;
	return result;
}

/// <summary>
/// ���ô���Ϊȫ��
/// </summary>
/// <param name="pthis">Dialog thisָ��</param>
extern void utils::FullScreen(CDialogEx* pthis)
{
	int with = GetSystemMetrics(SM_CXFULLSCREEN);
	int heigh = GetSystemMetrics(SM_CYFULLSCREEN);
	pthis->SetWindowPos(NULL, 0, 0, with, heigh, NULL);
}