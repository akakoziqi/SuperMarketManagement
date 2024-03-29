/*
 | 超市管理系统
 | 文件名称: alloc.cpp
 | 文件作用: 内存分配
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

#include "alloc.h"
#include "pch.h"

// 该函数可以保证每次的返回值有效, 不然会终止程序
void* __memalloc(size_t sz_count)
{
    void* p = malloc(sz_count);
    if (p == NULL)
    {
        assert(0);
        abort();                                // 异常终止
        return NULL;
    }
    return p;
}
// 释放内存
void memfree(void* p)
{
    if (p == NULL)
    {
        return;
    }
    free(p);
}
