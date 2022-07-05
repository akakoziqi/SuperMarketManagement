/*
 | 超市管理系统
 | 文件名称: utils.h
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


#pragma once

namespace utils
{
	extern tstring GetDialogEditorString(const CDialogEx* pthis, int ctl_id);
	extern std::wstring getTime(void);
	extern std::string wstring2string(const std::wstring& ws);
	extern void FullScreen(CDialogEx* pthis);
}

