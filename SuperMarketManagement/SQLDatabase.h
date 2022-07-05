/*
 | 超市管理系统
 | 文件名称: SQLDatabase.h
 | 文件作用: sqlite3数据库的封装
 | 创建日期: 2020-05-18
 | 更新日期: 2022-07-05
 | 开发人员: JuYan
 | 修改人员：Akako
 +----------------------------
 MIT License

 Copyright (C) JuYan

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
#include "pch.h"
#include "alloc.h"


class SQLDatabase
{
public :
	SQLDatabase();
	~SQLDatabase();
	bool openDatabase(const tchar* file);
	bool existTable(const char* name);
	bool existTableW(const tchar* name);
	bool existItemInTable(const char* table, const char* cond, const char* itemname);
	bool existItemInTableW(const tchar* table, const tchar* cond, const tchar* itemname);
	bool executeSQLNoRet(const tchar* sql);
	bool executeSQLWithRet(const tchar* sql, const std::function<void(std::vector<tstring>& lst)>& call);
	void closeDatabase();
private:
	sqlite3* db;
	static int  callback_exist_table(void* param, int argc, char** argv, char** azColName);
	static int  callback_item_is_null(void* param, int argc, char** argv, char** azColName);
	static int  callback_select_col(const void* param, int argc, char** argv, char** azColName);
	static void UTF16toUTF8(const wchar_t* utf16, char** utf8);
	static void UTF8toUTF16(const char* utf8, wchar_t** utf16);
};

