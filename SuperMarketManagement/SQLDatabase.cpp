/*
 | ���й���ϵͳ
 | �ļ�����: SQLDatabase.cpp
 | �ļ�����: sqlite3���ݿ�ķ�װ
 | ��������: 2020-05-18
 | ��������: 2022-07-05
 | ������Ա: JuYan
 | �޸���Ա��Akako
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

#include "pch.h"
#include "SQLDatabase.h"

SQLDatabase::SQLDatabase()
{
    db = NULL;
}
SQLDatabase::~SQLDatabase()
{
}

// utf16->utf8, �ⲿ��memfree�ͷ�
void SQLDatabase::UTF16toUTF8(const wchar_t* utf16, char** utf8)
{
    int len;
    char* utf8sql;
    len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, NULL, NULL);
    assert(len != 0);

    utf8sql = memalloc(char, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, utf16, -1, utf8sql, len, NULL, NULL);

    *utf8 = utf8sql;
}

// utf8->utf16, �ⲿ��memfree�ͷ�
void SQLDatabase::UTF8toUTF16(const char* utf8, wchar_t** utf16)
{
    int len;
    wchar_t* utf16sql;
    len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    assert(len != 0);

    utf16sql = memalloc(wchar_t, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16sql, len);

    *utf16 = utf16sql;
}

// �����ݿ�
bool SQLDatabase::openDatabase(const tchar* file)
{
    int ret;
#if _UNICODE
    ret = sqlite3_open16(file, &db);                                // utf-16
#else
    ret = sqlite3_open(file, &db);                                  // utf-8
#endif
    if (ret != SQLITE_OK)
    {
        return false;
    }
    return true;
}

// ���ڱ�
bool SQLDatabase::existTable(const char* name)
{
    bool res = false;
    char sql[256];
    sprintf_s(sql, "SELECT count(*) AS cnt FROM sqlite_master WHERE type='table' AND name='%s';", name);
    int ret = sqlite3_exec(db, sql, callback_exist_table, &res, NULL);
    if (ret != SQLITE_OK)                                           // �������һ���ɹ���
    {
        assert(0);
        abort();
    }
    return res;
}

// ���ڱ�
bool SQLDatabase::existTableW(const tchar* name)
{
    char* pname;
#ifdef _UNICODE
    UTF16toUTF8(name, &pname);
#else
    // TODO ansi -> utf-8
#endif
    bool res = false;
    char sql[256];
    sprintf_s(sql, "SELECT count(*) AS cnt FROM sqlite_master WHERE type='table' AND name='%s';", pname);
    int ret = sqlite3_exec(db, sql, callback_exist_table, &res, NULL);
    if (ret != SQLITE_OK)                                           // �������һ���ɹ���
    {
        assert(0);
        abort();
    }
    return res;
}
// �ж�һ�����Ƿ�Ϊ��(ֻ�ж����µ�)
bool SQLDatabase::existItemInTable(const char* table, const char* cond, const char* itemname)
{
    bool res = false;
    char sql[256];
    sprintf_s(sql, "SELECT %s FROM %s WHERE %s;", itemname, table, cond);
    int ret = sqlite3_exec(db, sql, callback_item_is_null, &res, NULL);
    if (ret != SQLITE_OK)                                           // �������һ���ɹ���
    {
        assert(0);
        abort();
    }
    return res;
}

// �ж�һ�����Ƿ�Ϊ��(ֻ�ж����µ�)
bool SQLDatabase::existItemInTableW(const tchar* table, const tchar* cond, const tchar* itemname)
{
    char* ptable;
    char* pcond;
    char* pitemname;
#ifdef _UNICODE
    UTF16toUTF8(table, &ptable);
    UTF16toUTF8(cond, &pcond);
    UTF16toUTF8(itemname, &pitemname);
#else
    // TODO ansi -> utf-8
#endif

    bool res = false;
    char sql[256];
    sprintf_s(sql, "SELECT %s FROM %s WHERE %s;", pitemname, ptable, pcond);
    int ret = sqlite3_exec(db, sql, callback_item_is_null, &res, NULL);
    if (ret != SQLITE_OK)                                           // �������һ���ɹ���
    {
        assert(0);
        abort();
    }
    return res;
}
// ִ�в����������ݵ�sql
bool SQLDatabase::executeSQLNoRet(const tchar* sql)
{
    char* utf8sql;
#ifdef _UNICODE
    UTF16toUTF8(sql, &utf8sql);
#else
    // TODO ansi -> utf-8
#endif
    int ret = sqlite3_exec(db, utf8sql, NULL, NULL, NULL);          // ����utf-8���
    memfree(utf8sql);
    if (ret != SQLITE_OK)
    {
        return false;
    }
    return true;
}
// ִ��Я�����ص�sql
bool SQLDatabase::executeSQLWithRet(const tchar* sql, const std::function<void(std::vector<tstring>& lst)>& call)
{
    char* utf8sql;
#ifdef _UNICODE
    UTF16toUTF8(sql, &utf8sql);
#else
    // TODO ansi -> utf-8
#endif
    typedef int(*callback)(void*, int, char**, char**);
    int ret = sqlite3_exec(db, utf8sql, (callback)callback_select_col, (void*)&call, NULL);
    memfree(utf8sql);
    if (ret != SQLITE_OK)
    {
        return false;
    }
    return true;
}
// �ر�
void SQLDatabase::closeDatabase()
{
    if (db != NULL)
    {
        sqlite3_close(db);
    }
}

// ���ڱ�
int SQLDatabase::callback_exist_table(void* param, int argc, char** argv, char** azColName)
{
    assert(argc == 1);
    assert(argv[0]);
    if (argv[0][0] != '0')                                          // ����ֵ��cnt = 0�����ĸ�ʽ
    {
        *((bool*)param) = true;
    }
    else {
        *((bool*)param) = false;
    }
    return 0;
}
// �Ƿ�Ϊnull
int SQLDatabase::callback_item_is_null(void* param, int argc, char** argv, char** azColName)
{
    assert(argc == 1);
    if (argv[0] != NULL)
    {
        *((bool*)param) = true;
    }
    else {
        *((bool*)param) = false;
    }
    return 0;
}
// select�ص�
int SQLDatabase::callback_select_col(const void* param, int argc, char** argv, char** azColName)
{
    std::vector<tstring> p;
    int i;
    tchar* dat;
    for (i = 0; i < argc; i++)
    {
        if (argv[i] != NULL)
        {
            SQLDatabase::UTF8toUTF16(argv[i], &dat);
            p.emplace_back(dat);
            memfree(dat);
        }
        else {
            p.emplace_back(_T(""));
        }
    }
    (*(std::function<void(std::vector<tstring>& lst)>*)param)(p);
    return 0;
}
